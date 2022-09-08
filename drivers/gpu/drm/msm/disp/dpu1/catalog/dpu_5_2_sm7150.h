/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (c) 2023, David Wronek <davidwronek@gmail.com>
 * Copyright (c) 2023, Danila Tikhonov <danila@jiaxyga.com>
 */

#ifndef _DPU_5_2_SM7150_H
#define _DPU_5_2_SM7150_H

static const struct dpu_caps sm7150_dpu_caps = {

	/*.max_mixer_width = DEFAULT_DPU_OUTPUT_LINE_WIDTH,
	.max_mixer_blendstages = 0xb,
	.qseed_type = DPU_SSPP_SCALER_QSEED3LITE,
	.smart_dma_rev = DPU_SSPP_SMART_DMA_V2,
	.ubwc_version = DPU_HW_UBWC_VER_20,
	.has_src_split = true,
	.has_dim_layer = true,
	.has_idle_pc = true,
	.max_linewidth = DEFAULT_DPU_OUTPUT_LINE_WIDTH,
	.pixel_ram_size = DEFAULT_PIXEL_RAM_SIZE,*/

	.max_mixer_width = DEFAULT_DPU_OUTPUT_LINE_WIDTH,
	.max_mixer_blendstages = 0xb,
	.qseed_type = DPU_SSPP_SCALER_QSEED3LITE,
	.has_src_split = true,
	.has_dim_layer = true,
	.has_idle_pc = true,
	.has_3d_merge = true,
	.max_linewidth = DEFAULT_DPU_OUTPUT_LINE_WIDTH,
	.pixel_ram_size = DEFAULT_PIXEL_RAM_SIZE,
};

static const struct dpu_ubwc_cfg sm7150_ubwc_cfg = {
	.ubwc_version = DPU_HW_UBWC_VER_20,
	.highest_bank_bit = 0x1, // or 0x3 but DS says 0x1
};

static const struct dpu_mdp_cfg sm7150_mdp[] = {

	/*{
	.name = "top_0", .id = MDP_TOP,
	.base = 0x0, .len = 0x45c,
	.features = 0,
	.highest_bank_bit = 0x1,
	.clk_ctrls[DPU_CLK_CTRL_VIG0] = {
		.reg_off = 0x2AC, .bit_off = 0},
	.clk_ctrls[DPU_CLK_CTRL_DMA0] = {
		.reg_off = 0x2AC, .bit_off = 0},
	.clk_ctrls[DPU_CLK_CTRL_CURSOR0] = {
		.reg_off = 0x2B4, .bit_off = 8},
	.clk_ctrls[DPU_CLK_CTRL_CURSOR1] = {
		.reg_off = 0x2C4, .bit_off = 8},
	.clk_ctrls[DPU_CLK_CTRL_WB2] = {
		.reg_off = 0x3B8, .bit_off = 24},
	},*/

	{
	.name = "top_0", .id = MDP_TOP,
	.base = 0x0, .len = 0x45c,
	.features = 0,
	.clk_ctrls[DPU_CLK_CTRL_VIG0] = { .reg_off = 0x2ac, .bit_off = 0 },
	.clk_ctrls[DPU_CLK_CTRL_VIG1] = { .reg_off = 0x2b4, .bit_off = 0 },
	.clk_ctrls[DPU_CLK_CTRL_DMA0] = { .reg_off = 0x2ac, .bit_off = 8 },
	.clk_ctrls[DPU_CLK_CTRL_DMA1] = { .reg_off = 0x2b4, .bit_off = 8 },
	.clk_ctrls[DPU_CLK_CTRL_DMA2] = { .reg_off = 0x2bc, .bit_off = 8 },
	.clk_ctrls[DPU_CLK_CTRL_DMA3] = { .reg_off = 0x2c4, .bit_off = 8 },
	.clk_ctrls[DPU_CLK_CTRL_WB2] = { .reg_off = 0x3b8, .bit_off = 24 },
	},
};

static const struct dpu_sspp_sub_blks sm7150_vig_sblk_0 =
				_VIG_SBLK("0", 5, DPU_SSPP_SCALER_QSEED3LITE);
static const struct dpu_sspp_sub_blks sm7150_vig_sblk_1 =
				_VIG_SBLK("1", 6, DPU_SSPP_SCALER_QSEED3LITE);

static const struct dpu_sspp_cfg sm7150_sspp[] = {
	/*SSPP_BLK("sspp_0", SSPP_VIG0, 0x4000, VIG_SM8250_MASK,
		sm7150_vig_sblk_0, 0,  SSPP_TYPE_VIG, DPU_CLK_CTRL_VIG0),
	SSPP_BLK("sspp_1", SSPP_VIG1, 0x6000, VIG_SM8250_MASK,
		sm7150_vig_sblk_1, 4,  SSPP_TYPE_VIG, DPU_CLK_CTRL_VIG1),
	SSPP_BLK("sspp_8", SSPP_DMA0, 0x24000,  DMA_SDM845_MASK,
		sdm845_dma_sblk_0, 1, SSPP_TYPE_DMA, DPU_CLK_CTRL_DMA0),
	SSPP_BLK("sspp_9", SSPP_DMA1, 0x26000,  DMA_CURSOR_SDM845_MASK,
		sdm845_dma_sblk_1, 5, SSPP_TYPE_DMA, DPU_CLK_CTRL_CURSOR0),
	SSPP_BLK("sspp_10", SSPP_DMA2, 0x28000,  DMA_CURSOR_SDM845_MASK,
		sdm845_dma_sblk_2, 9, SSPP_TYPE_DMA, DPU_CLK_CTRL_CURSOR1),,*/

	SSPP_BLK("sspp_0", SSPP_VIG0, 0x4000, 0x1f0, VIG_SDM845_MASK,
		sm7150_vig_sblk_0, 0, SSPP_TYPE_VIG, DPU_CLK_CTRL_VIG0),
	SSPP_BLK("sspp_1", SSPP_VIG1, 0x6000, 0x1f0, VIG_SDM845_MASK,
		sm7150_vig_sblk_1, 4, SSPP_TYPE_VIG, DPU_CLK_CTRL_VIG1),
	SSPP_BLK("sspp_2", SSPP_VIG2, 0x8000, 0x1f0, VIG_SDM845_MASK,
		sdm845_dma_sblk_0, 1, SSPP_TYPE_DMA, DPU_CLK_CTRL_DMA0),
	SSPP_BLK("sspp_9", SSPP_DMA1, 0x26000, 0x1f0, DMA_SDM845_MASK,
		sdm845_dma_sblk_1, 5, SSPP_TYPE_DMA, DPU_CLK_CTRL_DMA1),
	SSPP_BLK("sspp_10", SSPP_DMA2, 0x28000, 0x1f0, DMA_CURSOR_SDM845_MASK,
		sdm845_dma_sblk_2, 9, SSPP_TYPE_DMA, DPU_CLK_CTRL_DMA2),


	/*SSPP_BLK("sspp_0", SSPP_VIG0, 0x4000, 0x1f0, VIG_SDM845_MASK,
		sm7150_vig_sblk_0, 0, SSPP_TYPE_VIG, DPU_CLK_CTRL_VIG0),
	SSPP_BLK("sspp_1", SSPP_VIG1, 0x6000, 0x1f0, VIG_SM8250_MASK,
		sm7150_vig_sblk_1, 4, SSPP_TYPE_VIG, DPU_CLK_CTRL_VIG1),
	SSPP_BLK("sspp_8", SSPP_DMA0, 0x24000, 0x1f0, DMA_SDM845_MASK,
		sdm845_dma_sblk_0, 1, SSPP_TYPE_DMA, DPU_CLK_CTRL_DMA0),
	SSPP_BLK("sspp_9", SSPP_DMA1, 0x26000, 0x1f0, DMA_CURSOR_SDM845_MASK,
		sdm845_dma_sblk_1, 5, SSPP_TYPE_DMA, DPU_CLK_CTRL_CURSOR0),
	SSPP_BLK("sspp_10", SSPP_DMA2, 0x28000, 0x1f0, DMA_CURSOR_SDM845_MASK,
		sdm845_dma_sblk_2, 9, SSPP_TYPE_DMA, DPU_CLK_CTRL_CURSOR1),*/
};

static const struct dpu_lm_cfg sm7150_lm[] = {
	LM_BLK("lm_0", LM_0, 0x44000, MIXER_SDM845_MASK,
		&sdm845_lm_sblk, PINGPONG_0, LM_1, DSPP_0),
	LM_BLK("lm_1", LM_1, 0x45000, MIXER_SDM845_MASK,
		&sdm845_lm_sblk, PINGPONG_1, LM_0, DSPP_1),
	LM_BLK("lm_2", LM_2, 0x46000, MIXER_SDM845_MASK,
		&sdm845_lm_sblk, PINGPONG_2, LM_3, 0),
	LM_BLK("lm_3", LM_3, 0x47000, MIXER_SDM845_MASK,
		&sdm845_lm_sblk, PINGPONG_3, LM_2, 0),
	LM_BLK("lm_4", LM_4, 0x0, MIXER_SDM845_MASK,
		&sdm845_lm_sblk, PINGPONG_MAX, 0, 0),
	LM_BLK("lm_5", LM_5, 0x0, MIXER_SDM845_MASK,
		&sdm845_lm_sblk, PINGPONG_MAX, 0, 0),
};

static const struct dpu_dspp_cfg sm7150_dspp[] = {
	DSPP_BLK("dspp_0", DSPP_0, 0x54000, DSPP_SC7180_MASK,
		&sm8150_dspp_sblk),
	DSPP_BLK("dspp_1", DSPP_1, 0x56000, DSPP_SC7180_MASK,
		&sm8150_dspp_sblk),
};

static const struct dpu_pingpong_cfg sm7150_pp[] = {
	/*PP_BLK_TE("pingpong_0", PINGPONG_0, 0x70000, MERGE_3D_0, sdm845_pp_sblk_te,
		DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 8),
		DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 12)),
	PP_BLK_TE("pingpong_1", PINGPONG_1, 0x70800, MERGE_3D_0, sdm845_pp_sblk_te,
		DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 9),
		DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 13)),
	PP_BLK("pingpong_2", PINGPONG_2, 0x71000, MERGE_3D_1, sdm845_pp_sblk,
	DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 10),
	DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 14)),
	PP_BLK("pingpong_3", PINGPONG_3, 0x71800, MERGE_3D_1, sdm845_pp_sblk,
	DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 11),
	DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 15)),*/

	PP_BLK("pingpong_0", PINGPONG_0, 0x70000, PINGPONG_SM8150_MASK, MERGE_3D_0, sdm845_pp_sblk,
			DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 8),
			-1),
	PP_BLK("pingpong_1", PINGPONG_1, 0x70800, PINGPONG_SM8150_MASK, MERGE_3D_0, sdm845_pp_sblk,
			DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 9),
			-1),
	PP_BLK("pingpong_2", PINGPONG_2, 0x71000, PINGPONG_SM8150_MASK, MERGE_3D_1, sdm845_pp_sblk,
			DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 10),
			-1),
	PP_BLK("pingpong_3", PINGPONG_3, 0x71800, PINGPONG_SM8150_MASK, MERGE_3D_1, sdm845_pp_sblk,
			DPU_IRQ_IDX(MDP_SSPP_TOP0_INTR, 11),
			-1),
};

static const struct dpu_dsc_cfg sm7150_dsc[] = {
	DSC_BLK("dsc_0", DSC_0, 0x80000, BIT(DPU_DSC_OUTPUT_CTRL)),
	DSC_BLK("dsc_1", DSC_1, 0x80400, BIT(DPU_DSC_OUTPUT_CTRL)),
};

static const struct dpu_wb_cfg sm7150_wb[] = {
	WB_BLK("wb_2", WB_2, 0x65000, WB_SM8250_MASK, DPU_CLK_CTRL_WB2, 6,
			VBIF_RT, MDP_SSPP_TOP0_INTR, 4096, 4),
};

static const struct dpu_perf_cfg sm7150_perf_data = {
	.max_bw_low = 7100000,
	.max_bw_high = 7100000,
	.min_core_ib = 2400000,
	.min_llcc_ib = 800000,
	.min_dram_ib = 800000,
	.min_prefill_lines = 24,
	.danger_lut_tbl = {0xff, 0xffff, 0x0},
	.safe_lut_tbl = {0xfff0, 0xff00, 0xffff},
	.qos_lut_tbl = {
		{.nentry = ARRAY_SIZE(sm8150_qos_linear),
		.entries = sm8150_qos_linear
		},
		{.nentry = ARRAY_SIZE(sc7180_qos_macrotile),
		.entries = sc7180_qos_macrotile
		},
		{.nentry = ARRAY_SIZE(sc7180_qos_nrt),
		.entries = sc7180_qos_nrt
		},
	},
	.cdp_cfg = {
		{.rd_enable = 1, .wr_enable = 1},
		{.rd_enable = 1, .wr_enable = 0}
	},
	.clk_inefficiency_factor = 105,
	.bw_inefficiency_factor = 120,
};

const struct dpu_mdss_cfg dpu_sm7150_cfg = {
	.caps = &sm7150_dpu_caps,
	.ubwc = &sm7150_ubwc_cfg,
	.mdp_count = ARRAY_SIZE(sm7150_mdp),
	.mdp = sm7150_mdp,
	.ctl_count = ARRAY_SIZE(sm8150_ctl),
	.ctl = sm8150_ctl,
	.sspp_count = ARRAY_SIZE(sm7150_sspp),
	.sspp = sm7150_sspp,
	.mixer_count = ARRAY_SIZE(sm7150_lm),
	.mixer = sm7150_lm,
	.dspp_count = ARRAY_SIZE(sm7150_dspp),
	.dspp = sm7150_dspp,
	.pingpong_count = ARRAY_SIZE(sm7150_pp),
	.pingpong = sm7150_pp,
	.dsc_count = ARRAY_SIZE(sm7150_dsc),
	.dsc = sm7150_dsc,
	.intf_count = ARRAY_SIZE(sm8150_intf),
	.intf = sm8150_intf,
	.wb_count = ARRAY_SIZE(sm7150_wb),
	.wb = sm7150_wb,
	.vbif_count = ARRAY_SIZE(sdm845_vbif),
	.vbif = sdm845_vbif,
	.perf = &sm7150_perf_data,
	.mdss_irqs = BIT(MDP_SSPP_TOP0_INTR) | \
		     BIT(MDP_SSPP_TOP0_INTR2) | \
		     BIT(MDP_SSPP_TOP0_HIST_INTR) | \
		     BIT(MDP_INTF0_INTR) | \
		     BIT(MDP_INTF1_INTR) | \
		     BIT(MDP_INTF1_TEAR_INTR),
};

#endif
