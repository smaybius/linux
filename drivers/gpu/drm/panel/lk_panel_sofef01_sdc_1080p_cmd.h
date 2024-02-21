// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2024 FIXME
// Generated with linux-mdss-dsi-panel-driver-generator from vendor device tree:
//   Copyright (c) 2014, The Linux Foundation. All rights reserved. (FIXME)

#ifndef _PANEL_SOFEF01_SDC_1080P_CMD_H_
#define _PANEL_SOFEF01_SDC_1080P_CMD_H_

#include <mipi_dsi.h>
#include <panel_display.h>
#include <panel.h>
#include <string.h>

static struct panel_config sofef01_sdc_1080p_cmd_panel_data = {
	.panel_node_id = "qcom,mdss_dsi_sofef01_sdc_1080p_cmd",
	.panel_controller = "dsi:0:",
	.panel_compatible = "qcom,mdss-dsi-panel",
	.panel_type = 1,
	.panel_destination = "DISPLAY_1",
	/* .panel_orientation not supported yet */
	.panel_framerate = 60,
	.panel_lp11_init = 1,
	.panel_init_delay = 0,
};

static struct panel_resolution sofef01_sdc_1080p_cmd_panel_res = {
	.panel_width = 1080,
	.panel_height = 2340,
	.hfront_porch = 32,
	.hback_porch = 98,
	.hpulse_width = 73,
	.hsync_skew = 0,
	.vfront_porch = 8,
	.vback_porch = 8,
	.vpulse_width = 1,
	/* Borders not supported yet */
};

static struct color_info sofef01_sdc_1080p_cmd_color = {
	.color_format = 24,
	.color_order = DSI_RGB_SWAP_RGB,
	.underflow_color = 0xff,
	/* Borders and pixel packing not supported yet */
};

static char sofef01_sdc_1080p_cmd_on_cmd_0[] = {
	0x11, 0x00, 0x05, 0x80
};
static char sofef01_sdc_1080p_cmd_on_cmd_1[] = {
	0x35, 0x00, 0x15, 0x80
};
static char sofef01_sdc_1080p_cmd_on_cmd_2[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0x5a, 0x5a, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_3[] = {
	0x08, 0x00, 0x39, 0xc0, 0xeb, 0x17, 0x41, 0x92,
	0x0e, 0x10, 0x82, 0x5a
};
static char sofef01_sdc_1080p_cmd_on_cmd_4[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xa5, 0xa5, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_5[] = {
	0x05, 0x00, 0x39, 0xc0, 0x2a, 0x00, 0x00, 0x04,
	0x37, 0xff, 0xff, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_6[] = {
	0x05, 0x00, 0x39, 0xc0, 0x2b, 0x00, 0x00, 0x09,
	0x23, 0xff, 0xff, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_7[] = {
	0x53, 0x20, 0x15, 0x80
};
static char sofef01_sdc_1080p_cmd_on_cmd_8[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0x5a, 0x5a, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_9[] = {
	0xb0, 0x09, 0x15, 0x80
};
static char sofef01_sdc_1080p_cmd_on_cmd_10[] = {
	0x03, 0x00, 0x39, 0xc0, 0xe8, 0x11, 0x30, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_11[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xa5, 0xa5, 0xff
};
static char sofef01_sdc_1080p_cmd_on_cmd_12[] = {
	0x29, 0x00, 0x05, 0x80
};

static struct mipi_dsi_cmd sofef01_sdc_1080p_cmd_on_command[] = {
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_0), sofef01_sdc_1080p_cmd_on_cmd_0, 10 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_1), sofef01_sdc_1080p_cmd_on_cmd_1, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_2), sofef01_sdc_1080p_cmd_on_cmd_2, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_3), sofef01_sdc_1080p_cmd_on_cmd_3, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_4), sofef01_sdc_1080p_cmd_on_cmd_4, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_5), sofef01_sdc_1080p_cmd_on_cmd_5, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_6), sofef01_sdc_1080p_cmd_on_cmd_6, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_7), sofef01_sdc_1080p_cmd_on_cmd_7, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_8), sofef01_sdc_1080p_cmd_on_cmd_8, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_9), sofef01_sdc_1080p_cmd_on_cmd_9, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_10), sofef01_sdc_1080p_cmd_on_cmd_10, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_11), sofef01_sdc_1080p_cmd_on_cmd_11, 110 },
	{ sizeof(sofef01_sdc_1080p_cmd_on_cmd_12), sofef01_sdc_1080p_cmd_on_cmd_12, 0 },
};

static char sofef01_sdc_1080p_cmd_off_cmd_0[] = {
	0x28, 0x00, 0x05, 0x80
};
static char sofef01_sdc_1080p_cmd_off_cmd_1[] = {
	0x10, 0x00, 0x05, 0x80
};
static char sofef01_sdc_1080p_cmd_off_cmd_2[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0x5a, 0x5a, 0xff
};
static char sofef01_sdc_1080p_cmd_off_cmd_3[] = {
	0xb0, 0x05, 0x15, 0x80
};
static char sofef01_sdc_1080p_cmd_off_cmd_4[] = {
	0xf4, 0x01, 0x15, 0x80
};
static char sofef01_sdc_1080p_cmd_off_cmd_5[] = {
	0x03, 0x00, 0x39, 0xc0, 0xf0, 0xa5, 0xa5, 0xff
};

static struct mipi_dsi_cmd sofef01_sdc_1080p_cmd_off_command[] = {
	{ sizeof(sofef01_sdc_1080p_cmd_off_cmd_0), sofef01_sdc_1080p_cmd_off_cmd_0, 20 },
	{ sizeof(sofef01_sdc_1080p_cmd_off_cmd_1), sofef01_sdc_1080p_cmd_off_cmd_1, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_off_cmd_2), sofef01_sdc_1080p_cmd_off_cmd_2, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_off_cmd_3), sofef01_sdc_1080p_cmd_off_cmd_3, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_off_cmd_4), sofef01_sdc_1080p_cmd_off_cmd_4, 0 },
	{ sizeof(sofef01_sdc_1080p_cmd_off_cmd_5), sofef01_sdc_1080p_cmd_off_cmd_5, 120 },
};

static struct command_state sofef01_sdc_1080p_cmd_state = {
	.oncommand_state = 0,
	.offcommand_state = 0,
};

static struct commandpanel_info sofef01_sdc_1080p_cmd_command_panel = {
	/* FIXME: This is a command mode panel */
};

static struct videopanel_info sofef01_sdc_1080p_cmd_video_panel = {
	.hsync_pulse = 0,
	.hfp_power_mode = 0,
	.hbp_power_mode = 0,
	.hsa_power_mode = 0,
	.bllp_eof_power_mode = 1,
	.bllp_power_mode = 1,
	.traffic_mode = 2,
	/* This is bllp_eof_power_mode and bllp_power_mode combined */
	.bllp_eof_power = 1 << 3 | 1 << 0,
};

static struct lane_configuration sofef01_sdc_1080p_cmd_lane_config = {
	.dsi_lanes = 4,
	.dsi_lanemap = 0,
	.lane0_state = 1,
	.lane1_state = 1,
	.lane2_state = 1,
	.lane3_state = 1,
	.force_clk_lane_hs = 0,
};

static const uint32_t sofef01_sdc_1080p_cmd_timings[] = {
	
};

static struct panel_timing sofef01_sdc_1080p_cmd_timing_info = {
	.tclk_post = 0x0e,
	.tclk_pre = 0x36,
};

static struct panel_reset_sequence sofef01_sdc_1080p_cmd_reset_seq = {
	.pin_state = { 0, 1 },
	.sleep = { 10, 10 },
	.pin_direction = 2,
};

static struct backlight sofef01_sdc_1080p_cmd_backlight = {
	.bl_interface_type = BL_DCS,
	.bl_min_level = 1,
	.bl_max_level = 1023,
};

static inline void panel_sofef01_sdc_1080p_cmd_select(struct panel_struct *panel,
						      struct msm_panel_info *pinfo,
						      struct mdss_dsi_phy_ctrl *phy_db)
{
	panel->paneldata = &sofef01_sdc_1080p_cmd_panel_data;
	panel->panelres = &sofef01_sdc_1080p_cmd_panel_res;
	panel->color = &sofef01_sdc_1080p_cmd_color;
	panel->videopanel = &sofef01_sdc_1080p_cmd_video_panel;
	panel->commandpanel = &sofef01_sdc_1080p_cmd_command_panel;
	panel->state = &sofef01_sdc_1080p_cmd_state;
	panel->laneconfig = &sofef01_sdc_1080p_cmd_lane_config;
	panel->paneltiminginfo = &sofef01_sdc_1080p_cmd_timing_info;
	panel->panelresetseq = &sofef01_sdc_1080p_cmd_reset_seq;
	panel->backlightinfo = &sofef01_sdc_1080p_cmd_backlight;
	pinfo->mipi.panel_cmds = sofef01_sdc_1080p_cmd_on_command;
	pinfo->mipi.num_of_panel_cmds = ARRAY_SIZE(sofef01_sdc_1080p_cmd_on_command);
	memcpy(phy_db->timing, sofef01_sdc_1080p_cmd_timings, TIMING_SIZE);
	phy_db->regulator_mode = DSI_PHY_REGULATOR_DCDC_MODE;
}

#endif /* _PANEL_SOFEF01_SDC_1080P_CMD_H_ */
