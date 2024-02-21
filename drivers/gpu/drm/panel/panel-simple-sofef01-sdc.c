// SPDX-License-Identifier: GPL-2.0-only
// Copyright (c) 2013, The Linux Foundation. All rights reserved.

static const struct drm_display_mode sofef01_sdc_mode = {
	.clock = (1080 + 32 + 73 + 98) * (2340 + 8 + 1 + 8) * 60 / 1000,
	.hdisplay = 1080,
	.hsync_start = 1080 + 32,
	.hsync_end = 1080 + 32 + 73,
	.htotal = 1080 + 32 + 73 + 98,
	.vdisplay = 2340,
	.vsync_start = 2340 + 8,
	.vsync_end = 2340 + 8 + 1,
	.vtotal = 2340 + 8 + 1 + 8,
	.width_mm = 62,
	.height_mm = 134,
};

static const struct panel_desc_dsi sofef01_sdc = {
	.desc = {
		.modes = &sofef01_sdc_mode,
		.num_modes = 1,
		.bpc = 8,
		.size = {
			.width = 62,
			.height = 134,
		},
		.connector_type = DRM_MODE_CONNECTOR_DSI,
	},
	.flags = MIPI_DSI_MODE_VIDEO_BURST | MIPI_DSI_CLOCK_NON_CONTINUOUS |
		 MIPI_DSI_MODE_LPM,
	.format = MIPI_DSI_FMT_RGB888,
	.lanes = 4,
};
