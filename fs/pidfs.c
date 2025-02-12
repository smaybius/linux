// SPDX-License-Identifier: GPL-2.0
#include <linux/anon_inodes.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/magic.h>
#include <linux/mount.h>
#include <linux/pid.h>
#include <linux/pidfs.h>
#include <linux/pid_namespace.h>
#include <linux/poll.h>
#include <linux/proc_fs.h>
#include <linux/proc_ns.h>
#include <linux/pseudo_fs.h>
#include <linux/seq_file.h>
#include <uapi/linux/pidfd.h>

#include "internal.h"

static int pidfd_release(struct inode *inode, struct file *file)
{
#ifndef CONFIG_FS_PID
	struct pid *pid = file->private_data;

	file->private_data = NULL;
	put_pid(pid);
#endif
	return 0;
}

#ifdef CONFIG_PROC_FS
/**
 * pidfd_show_fdinfo - print information about a pidfd
 * @m: proc fdinfo file
 * @f: file referencing a pidfd
 *
 * Pid:
 * This function will print the pid that a given pidfd refers to in the
 * pid namespace of the procfs instance.
 * If the pid namespace of the process is not a descendant of the pid
 * namespace of the procfs instance 0 will be shown as its pid. This is
 * similar to calling getppid() on a process whose parent is outside of
 * its pid namespace.
 *
 * NSpid:
 * If pid namespaces are supported then this function will also print
 * the pid of a given pidfd refers to for all descendant pid namespaces
 * starting from the current pid namespace of the instance, i.e. the
 * Pid field and the first entry in the NSpid field will be identical.
 * If the pid namespace of the process is not a descendant of the pid
 * namespace of the procfs instance 0 will be shown as its first NSpid
 * entry and no others will be shown.
 * Note that this differs from the Pid and NSpid fields in
 * /proc/<pid>/status where Pid and NSpid are always shown relative to
 * the  pid namespace of the procfs instance. The difference becomes
 * obvious when sending around a pidfd between pid namespaces from a
 * different branch of the tree, i.e. where no ancestral relation is
 * present between the pid namespaces:
 * - create two new pid namespaces ns1 and ns2 in the initial pid
 *   namespace (also take care to create new mount namespaces in the
 *   new pid namespace and mount procfs)
 * - create a process with a pidfd in ns1
 * - send pidfd from ns1 to ns2
 * - read /proc/self/fdinfo/<pidfd> and observe that both Pid and NSpid
 *   have exactly one entry, which is 0
 */
static void pidfd_show_fdinfo(struct seq_file *m, struct file *f)
{
	struct pid *pid = pidfd_pid(f);
	struct pid_namespace *ns;
	pid_t nr = -1;

	if (likely(pid_has_task(pid, PIDTYPE_PID))) {
		ns = proc_pid_ns(file_inode(m->file)->i_sb);
		nr = pid_nr_ns(pid, ns);
	}

	seq_put_decimal_ll(m, "Pid:\t", nr);

#ifdef CONFIG_PID_NS
	seq_put_decimal_ll(m, "\nNSpid:\t", nr);
	if (nr > 0) {
		int i;

		/* If nr is non-zero it means that 'pid' is valid and that
		 * ns, i.e. the pid namespace associated with the procfs
		 * instance, is in the pid namespace hierarchy of pid.
		 * Start at one below the already printed level.
		 */
		for (i = ns->level + 1; i <= pid->level; i++)
			seq_put_decimal_ll(m, "\t", pid->numbers[i].nr);
	}
#endif
	seq_putc(m, '\n');
}
#endif

/*
 * Poll support for process exit notification.
 */
static __poll_t pidfd_poll(struct file *file, struct poll_table_struct *pts)
{
	struct pid *pid = pidfd_pid(file);
	bool thread = file->f_flags & PIDFD_THREAD;
	struct task_struct *task;
	__poll_t poll_flags = 0;

	poll_wait(file, &pid->wait_pidfd, pts);
	/*
	 * Depending on PIDFD_THREAD, inform pollers when the thread
	 * or the whole thread-group exits.
	 */
	guard(rcu)();
	task = pid_task(pid, PIDTYPE_PID);
	if (!task)
		poll_flags = EPOLLIN | EPOLLRDNORM | EPOLLHUP;
	else if (task->exit_state && (thread || thread_group_empty(task)))
		poll_flags = EPOLLIN | EPOLLRDNORM;

	return poll_flags;
}

static const struct file_operations pidfs_file_operations = {
	.release	= pidfd_release,
	.poll		= pidfd_poll,
#ifdef CONFIG_PROC_FS
	.show_fdinfo	= pidfd_show_fdinfo,
#endif
};

struct pid *pidfd_pid(const struct file *file)
{
	if (file->f_op != &pidfs_file_operations)
		return ERR_PTR(-EBADF);
#ifdef CONFIG_FS_PID
	return file_inode(file)->i_private;
#else
	return file->private_data;
#endif
}

#ifdef CONFIG_FS_PID
static struct vfsmount *pidfs_mnt __ro_after_init;

/*
 * The vfs falls back to simple_setattr() if i_op->setattr() isn't
 * implemented. Let's reject it completely until we have a clean
 * permission concept for pidfds.
 */
static int pidfs_setattr(struct mnt_idmap *idmap, struct dentry *dentry,
			 struct iattr *attr)
{
	return -EOPNOTSUPP;
}

static int pidfs_getattr(struct mnt_idmap *idmap, const struct path *path,
			 struct kstat *stat, u32 request_mask,
			 unsigned int query_flags)
{
	struct inode *inode = d_inode(path->dentry);

	generic_fillattr(&nop_mnt_idmap, request_mask, inode, stat);
	return 0;
}

static const struct inode_operations pidfs_inode_operations = {
	.getattr = pidfs_getattr,
	.setattr = pidfs_setattr,
};

static void pidfs_evict_inode(struct inode *inode)
{
	struct pid *pid = inode->i_private;

	clear_inode(inode);
	put_pid(pid);
}

static const struct super_operations pidfs_sops = {
	.drop_inode	= generic_delete_inode,
	.evict_inode	= pidfs_evict_inode,
	.statfs		= simple_statfs,
};

static char *pidfs_dname(struct dentry *dentry, char *buffer, int buflen)
{
	return dynamic_dname(buffer, buflen, "pidfd:[%lu]",
			     d_inode(dentry)->i_ino);
}

static const struct dentry_operations pidfs_dentry_operations = {
	.d_delete	= always_delete_dentry,
	.d_dname	= pidfs_dname,
	.d_prune	= stashed_dentry_prune,
};

static int pidfs_init_fs_context(struct fs_context *fc)
{
	struct pseudo_fs_context *ctx;

	ctx = init_pseudo(fc, PID_FS_MAGIC);
	if (!ctx)
		return -ENOMEM;

	ctx->ops = &pidfs_sops;
	ctx->dops = &pidfs_dentry_operations;
	return 0;
}

static struct file_system_type pidfs_type = {
	.name			= "pidfs",
	.init_fs_context	= pidfs_init_fs_context,
	.kill_sb		= kill_anon_super,
};

struct file *pidfs_alloc_file(struct pid *pid, unsigned int flags)
{

	struct file *pidfd_file;
	struct path path;
	int ret;

	ret = path_from_stashed(&pid->stashed, pid->ino, pidfs_mnt,
				&pidfs_file_operations, &pidfs_inode_operations,
				get_pid(pid), &path);
	if (ret <= 0)
		put_pid(pid);
	if (ret < 0)
		return ERR_PTR(ret);

	pidfd_file = alloc_file(&path, flags, &pidfs_file_operations);
	if (IS_ERR(pidfd_file))
		path_put(&path);
	return pidfd_file;
}

void __init pidfs_init(void)
{
	pidfs_mnt = kern_mount(&pidfs_type);
	if (IS_ERR(pidfs_mnt))
		panic("Failed to mount pidfs pseudo filesystem");
}

#else /* !CONFIG_FS_PID */

struct file *pidfs_alloc_file(struct pid *pid, unsigned int flags)
{
	struct file *pidfd_file;

	pidfd_file = anon_inode_getfile("[pidfd]", &pidfs_file_operations, pid,
					flags | O_RDWR);
	if (IS_ERR(pidfd_file))
		return pidfd_file;

	get_pid(pid);
	return pidfd_file;
}

void __init pidfs_init(void) { }
#endif
