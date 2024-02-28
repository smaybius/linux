// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (c) 2024, Danila Tikhonov <danila@jiaxyga.com>
 */

#include <linux/backlight.h>
#include <linux/delay.h>
#include <linux/gpio/consumer.h>
#include <linux/module.h>
#include <linux/of.h>

#include <video/mipi_display.h>

#include <drm/drm_mipi_dsi.h>
#include <drm/drm_modes.h>
#include <drm/drm_panel.h>
#include <drm/drm_probe_helper.h>

/* Manufacturer Command Set */
#define MCS_ACCESS_PROT_OFF	0xb0 // MCS_MANPWR?
#define MCS_UNKNOWN_B7		0xb7
#define MCS_BIAS_CURRENT_CTRL	0xd1
#define MCS_PASSWD1		0xf0	/* Password Command for Level 2 Control */
//#define MCS_PASSWD2		0xf1	/* Password Command for MTP Control*/ UNUSED
#define MCS_PASSWD3		0xfc

struct ams639rq08 {
	struct drm_panel panel;
	struct mipi_dsi_device *dsi;
	struct gpio_desc *reset_gpio;
};

static inline struct ams639rq08 *to_ams639rq08(struct drm_panel *panel)
{
	return container_of(panel, struct ams639rq08, panel);
}

static void ams639rq08_reset(struct ams639rq08 *ctx)
{
	gpiod_set_value_cansleep(ctx->reset_gpio, 1);
	usleep_range(1000, 2000);
	gpiod_set_value_cansleep(ctx->reset_gpio, 0);
	usleep_range(10000, 11000);
}

static int ams639rq08_on(struct ams639rq08 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	/*
	 * Looks useless and needs testing.
	 * Davinci doesnt have these cmds:
	 *
	 * mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a);
	 * mipi_dsi_dcs_write_seq(dsi, 0xfc, 0x5a, 0x5a);
	 * mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x0c);
	 * mipi_dsi_dcs_write_seq(dsi, 0xff, 0x10);
	 * mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x2f);
	 * mipi_dsi_dcs_write_seq(dsi, 0xd1, 0x01);
	 * mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5);
	 * mipi_dsi_dcs_write_seq(dsi, 0xfc, 0xa5, 0xa5);
	 */

	/* Sleep Out */
	ret = mipi_dsi_dcs_exit_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to exit sleep mode: %d\n", ret);
		return ret;
	}
	usleep_range(10000, 11000);

	/* TE OUT(Vsync On) */
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a); // enable level2 control

	ret = mipi_dsi_dcs_set_tear_on(dsi, MIPI_DSI_DCS_TEAR_MODE_VBLANK);
	if (ret < 0) {
		dev_err(dev, "Failed to set tear on: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0xb7, 0x01, 0x4b);
	/* Dimming Speed Setting */
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x06);
	mipi_dsi_dcs_write_seq(dsi, 0xb7, 0x10);

	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5); // disable level2 control

	/* Page Address Set */
	ret = mipi_dsi_dcs_set_page_address(dsi, 0x0000, 0x0923);
	if (ret < 0) {
		dev_err(dev, "Failed to set page address: %d\n", ret);
		return ret;
	}

	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0x5a, 0x5a); // enable level2 control
	mipi_dsi_dcs_write_seq(dsi, 0xfc, 0x5a, 0x5a);
	/* Set DDIC internal HFP */
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x23);
	mipi_dsi_dcs_write_seq(dsi, 0xd1, 0x11);
	/* OFC Setting X? Mhz */
	mipi_dsi_dcs_write_seq(dsi, 0xe9, 0x11, 0x55,
				    0xa6, 0x75, 0xa3,
				    0xb9, 0xa1, 0x4a,
				    0x00, 0x1a, 0xb8);
	/* Err_FG Setting */
	mipi_dsi_dcs_write_seq(dsi, 0xe1,
				    0x00, 0x00, 0x02,
				    0x02, 0x42, 0x02);
	mipi_dsi_dcs_write_seq(dsi, 0xe2,
				    0x00, 0x00, 0x00,
				    0x00, 0x00, 0x00);
	mipi_dsi_dcs_write_seq(dsi, 0xb0, 0x0c);
	mipi_dsi_dcs_write_seq(dsi, 0xe1, 0x19);
	mipi_dsi_dcs_write_seq(dsi, 0xf0, 0xa5, 0xa5); // disable level2 control
	mipi_dsi_dcs_write_seq(dsi, 0xfc, 0xa5, 0xa5);
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_CONTROL_DISPLAY, 0x20);

	/* Brightness Control */
	ret = mipi_dsi_dcs_set_display_brightness(dsi, 0x0000);
	if (ret < 0) {
		dev_err(dev, "Failed to set display brightness: %d\n", ret);
		return ret;
	}

	/* Display On */
	mipi_dsi_dcs_write_seq(dsi, MIPI_DCS_WRITE_POWER_SAVE, 0x00);
	msleep(67);

	ret = mipi_dsi_dcs_set_display_on(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display on: %d\n", ret);
		return ret;
	}

	return 0;
}

static int ams639rq08_off(struct ams639rq08 *ctx)
{
	struct mipi_dsi_device *dsi = ctx->dsi;
	struct device *dev = &dsi->dev;
	int ret;

	ret = mipi_dsi_dcs_set_display_off(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to set display off: %d\n", ret);
		return ret;
	}

	ret = mipi_dsi_dcs_enter_sleep_mode(dsi);
	if (ret < 0) {
		dev_err(dev, "Failed to enter sleep mode: %d\n", ret);
		return ret;
	}
	msleep(120);

	return 0;
}

static int ams639rq08_prepare(struct drm_panel *panel)
{
	struct ams639rq08 *ctx = to_ams639rq08(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ams639rq08_reset(ctx);

	ret = ams639rq08_on(ctx);
	if (ret < 0) {
		dev_err(dev, "Failed to initialize panel: %d\n", ret);
		gpiod_set_value_cansleep(ctx->reset_gpio, 1);
		return ret;
	}

	return 0;
}

static int ams639rq08_unprepare(struct drm_panel *panel)
{
	struct ams639rq08 *ctx = to_ams639rq08(panel);
	struct device *dev = &ctx->dsi->dev;
	int ret;

	ret = ams639rq08_off(ctx);
	if (ret < 0)
		dev_err(dev, "Failed to un-initialize panel: %d\n", ret);

	gpiod_set_value_cansleep(ctx->reset_gpio, 1);

	return 0;
}

static const struct drm_display_mode ams639rq08_mode = {
	.clock = (1080 + 64 + 20 + 64) * (2340 + 64 + 20 + 64) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 64,
	.hsync_end = 1080 + 64 + 20,
	.htotal = 1080 + 64 + 20 + 64,
	.vdisplay = 2340,
	.vsync_start = 2340 + 64,
	.vsync_end = 2340 + 64 + 20,	// davinci
	.vtotal = 2340 + 64 + 20 + 64,	// davinci
	.width_mm = 68,
	.height_mm = 147,
	.type = DRM_MODE_TYPE_DRIVER,
};

/*static const struct drm_display_mode ss_ea8076_global_mode = {
	.clock = (1080 + 64 + 20 + 64) * (2340 + 64 + 27 + 64) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 64,
	.hsync_end = 1080 + 64 + 20,
	.htotal = 1080 + 64 + 20 + 64,
	.vdisplay = 2340,
	.vsync_start = 2340 + 64,
	.vsync_end = 2340 + 64 + 27,	// raphael
	.vtotal = 2340 + 64 + 27 + 64,	// raphael
	.width_mm = 68,
	.height_mm = 147,
	.type = DRM_MODE_TYPE_DRIVER,
};*/

static int ams639rq08_get_modes(struct drm_panel *panel,
					struct drm_connector *connector)
{
	return drm_connector_helper_get_modes_fixed(connector, &ams639rq08_mode);
}

static const struct drm_panel_funcs ams639rq08_panel_funcs = {
	.prepare = ams639rq08_prepare,
	.unprepare = ams639rq08_unprepare,
	.get_modes = ams639rq08_get_modes,
};

static int ams639rq08_bl_update_status(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness = backlight_get_brightness(bl);
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_set_display_brightness_large(dsi, brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return 0;
}

static int ams639rq08_bl_get_brightness(struct backlight_device *bl)
{
	struct mipi_dsi_device *dsi = bl_get_data(bl);
	u16 brightness;
	int ret;

	dsi->mode_flags &= ~MIPI_DSI_MODE_LPM;

	ret = mipi_dsi_dcs_get_display_brightness_large(dsi, &brightness);
	if (ret < 0)
		return ret;

	dsi->mode_flags |= MIPI_DSI_MODE_LPM;

	return brightness;
}

static const struct backlight_ops ams639rq08_bl_ops = {
	.update_status = ams639rq08_bl_update_status,
	.get_brightness = ams639rq08_bl_get_brightness,
};

static struct backlight_device *
ams639rq08_create_backlight(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	const struct backlight_properties props = {
		.type = BACKLIGHT_RAW,
		.brightness = 2047,
		.max_brightness = 2047,
	};

	return devm_backlight_device_register(dev, dev_name(dev), dev, dsi,
						&ams639rq08_bl_ops, &props);
}

static int ams639rq08_probe(struct mipi_dsi_device *dsi)
{
	struct device *dev = &dsi->dev;
	struct ams639rq08 *ctx;
	int ret;

	ctx = devm_kzalloc(dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_HIGH);
	if (IS_ERR(ctx->reset_gpio))
		return dev_err_probe(dev, PTR_ERR(ctx->reset_gpio),
					"Failed to get reset-gpios\n");

	ctx->dsi = dsi;
	mipi_dsi_set_drvdata(dsi, ctx);

	dsi->lanes = 4;
	dsi->format = MIPI_DSI_FMT_RGB888;
	dsi->mode_flags = MIPI_DSI_MODE_VIDEO_BURST |
			  MIPI_DSI_CLOCK_NON_CONTINUOUS | MIPI_DSI_MODE_LPM;

	drm_panel_init(&ctx->panel, dev, &ams639rq08_panel_funcs,
			DRM_MODE_CONNECTOR_DSI);
	ctx->panel.prepare_prev_first = true;

	ctx->panel.backlight = ams639rq08_create_backlight(dsi);
	if (IS_ERR(ctx->panel.backlight))
		return dev_err_probe(dev, PTR_ERR(ctx->panel.backlight),
					"Failed to create backlight\n");

	drm_panel_add(&ctx->panel);

	ret = mipi_dsi_attach(dsi);
	if (ret < 0) {
		drm_panel_remove(&ctx->panel);
		return dev_err_probe(dev, ret, "Failed to attach to DSI host\n");
	}

	return 0;
}

static void ams639rq08_remove(struct mipi_dsi_device *dsi)
{
	struct ams639rq08 *ctx = mipi_dsi_get_drvdata(dsi);
	int ret;

	ret = mipi_dsi_detach(dsi);
	if (ret < 0)
		dev_err(&dsi->dev, "Failed to detach from DSI host: %d\n", ret);

	drm_panel_remove(&ctx->panel);
}

static const struct of_device_id ams639rq08_of_match[] = {
	{ .compatible = "samsung,ams639rq08" },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, ams639rq08_of_match);

static struct mipi_dsi_driver ams639rq08_driver = {
	.probe = ams639rq08_probe,
	.remove = ams639rq08_remove,
	.driver = {
		.name = "panel-samsung-ams639rq08",
		.of_match_table = ams639rq08_of_match,
	},
};
module_mipi_dsi_driver(ams639rq08_driver);

MODULE_AUTHOR("Danila Tikhonov <danila@jiaxyga.com>");
MODULE_DESCRIPTION("DRM driver for SAMSUNG AMS639RQ08 cmd mode dsi panel");
MODULE_LICENSE("GPL");
