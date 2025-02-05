// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2024 - Google LLC
 * Author: Marc Zyngier <maz@kernel.org>
 */

#include <asm/sysreg-defs.h>

/*
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 *
 * If any of these BUILD_BUG_ON() fails, that's because some bits that
 * were reserved have gained some other meaning, and KVM needs to know
 * about those.
 *
 * In such case, do *NOT* blindly change the assertion so that it
 * passes, but also teach the rest of the code about the actual
 * change.
 *
 * WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING
 */
static inline void check_res_bits(void)
{
#ifdef CONFIG_KVM_ARM64_RES_BITS_PARANOIA

	BUILD_BUG_ON(OSDTRRX_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(MDCCINT_EL1_RES0		!= (GENMASK_ULL(63, 31) | GENMASK_ULL(28, 0)));
	BUILD_BUG_ON(MDSCR_EL1_RES0		!= (GENMASK_ULL(63, 36) | GENMASK_ULL(28, 28) | GENMASK_ULL(25, 24) | GENMASK_ULL(20, 20) | GENMASK_ULL(18, 16) | GENMASK_ULL(11, 7) | GENMASK_ULL(5, 1)));
	BUILD_BUG_ON(OSDTRTX_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(OSECCR_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(OSLAR_EL1_RES0		!= (GENMASK_ULL(63, 1)));
	BUILD_BUG_ON(ID_PFR0_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_PFR1_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_DFR0_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_AFR0_EL1_RES0		!= (GENMASK_ULL(63, 16)));
	BUILD_BUG_ON(ID_MMFR0_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_MMFR1_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_MMFR2_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_MMFR3_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_ISAR0_EL1_RES0		!= (GENMASK_ULL(63, 28)));
	BUILD_BUG_ON(ID_ISAR1_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_ISAR2_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_ISAR3_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_ISAR4_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_ISAR5_EL1_RES0		!= (GENMASK_ULL(63, 32) | GENMASK_ULL(23, 20)));
	BUILD_BUG_ON(ID_ISAR6_EL1_RES0		!= (GENMASK_ULL(63, 28)));
	BUILD_BUG_ON(ID_MMFR4_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(MVFR0_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(MVFR1_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(MVFR2_EL1_RES0		!= (GENMASK_ULL(63, 8)));
	BUILD_BUG_ON(ID_PFR2_EL1_RES0		!= (GENMASK_ULL(63, 12)));
	BUILD_BUG_ON(ID_DFR1_EL1_RES0		!= (GENMASK_ULL(63, 8)));
	BUILD_BUG_ON(ID_MMFR5_EL1_RES0		!= (GENMASK_ULL(63, 8)));
	BUILD_BUG_ON(ID_AA64PFR1_EL1_RES0	!= (GENMASK_ULL(23, 20)));
	BUILD_BUG_ON(ID_AA64PFR2_EL1_RES0	!= (GENMASK_ULL(63, 36) | GENMASK_ULL(31, 12)));
	BUILD_BUG_ON(ID_AA64ZFR0_EL1_RES0	!= (GENMASK_ULL(63, 60) | GENMASK_ULL(51, 48) | GENMASK_ULL(39, 36) | GENMASK_ULL(31, 28) | GENMASK_ULL(15, 8)));
	BUILD_BUG_ON(ID_AA64SMFR0_EL1_RES0	!= (GENMASK_ULL(62, 61) | GENMASK_ULL(51, 49) | GENMASK_ULL(31, 31) | GENMASK_ULL(27, 0)));
	BUILD_BUG_ON(ID_AA64FPFR0_EL1_RES0	!= (GENMASK_ULL(63, 32) | GENMASK_ULL(27, 2)));
	BUILD_BUG_ON(ID_AA64DFR0_EL1_RES0	!= (GENMASK_ULL(27, 24) | GENMASK_ULL(19, 16)));
	BUILD_BUG_ON(ID_AA64AFR0_EL1_RES0	!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(ID_AA64AFR1_EL1_RES0	!= (GENMASK_ULL(63, 0)));
	BUILD_BUG_ON(ID_AA64ISAR0_EL1_RES0	!= (GENMASK_ULL(3, 0)));
	BUILD_BUG_ON(ID_AA64ISAR2_EL1_RES0	!= (GENMASK_ULL(47, 44)));
	BUILD_BUG_ON(ID_AA64ISAR3_EL1_RES0	!= (GENMASK_ULL(63, 16)));
	BUILD_BUG_ON(ID_AA64MMFR0_EL1_RES0	!= (GENMASK_ULL(55, 48)));
	BUILD_BUG_ON(ID_AA64MMFR2_EL1_RES0	!= (GENMASK_ULL(47, 44)));
	BUILD_BUG_ON(ID_AA64MMFR3_EL1_RES0	!= (GENMASK_ULL(51, 48)));
	BUILD_BUG_ON(ID_AA64MMFR4_EL1_RES0	!= (GENMASK_ULL(63, 40) | GENMASK_ULL(35, 28) | GENMASK_ULL(3, 0)));
	BUILD_BUG_ON(SCTLR_EL1_RES0		!= (GENMASK_ULL(17, 17)));
	BUILD_BUG_ON(CPACR_ELx_RES0		!= (GENMASK_ULL(63, 30) | GENMASK_ULL(27, 26) | GENMASK_ULL(23, 22) | GENMASK_ULL(19, 18) | GENMASK_ULL(15, 0)));
	BUILD_BUG_ON(SMPRI_EL1_RES0		!= (GENMASK_ULL(63, 4)));
	BUILD_BUG_ON(ZCR_ELx_RES0		!= (GENMASK_ULL(63, 9)));
	BUILD_BUG_ON(SMCR_ELx_RES0		!= (GENMASK_ULL(63, 32) | GENMASK_ULL(29, 9)));
	BUILD_BUG_ON(GCSCR_ELx_RES0		!= (GENMASK_ULL(63, 10) | GENMASK_ULL(7, 7) | GENMASK_ULL(4, 1)));
	BUILD_BUG_ON(GCSPR_ELx_RES0		!= (GENMASK_ULL(2, 0)));
	BUILD_BUG_ON(GCSCRE0_EL1_RES0		!= (GENMASK_ULL(63, 11) | GENMASK_ULL(7, 6) | GENMASK_ULL(4, 1)));
	BUILD_BUG_ON(ALLINT_RES0		!= (GENMASK_ULL(63, 14) | GENMASK_ULL(12, 0)));
	BUILD_BUG_ON(PMSCR_EL1_RES0		!= (GENMASK_ULL(63, 8) | GENMASK_ULL(2, 2)));
	BUILD_BUG_ON(PMSICR_EL1_RES0		!= (GENMASK_ULL(55, 32)));
	BUILD_BUG_ON(PMSIRR_EL1_RES0		!= (GENMASK_ULL(63, 32) | GENMASK_ULL(7, 1)));
	BUILD_BUG_ON(PMSFCR_EL1_RES0		!= (GENMASK_ULL(63, 19) | GENMASK_ULL(15, 4)));
	BUILD_BUG_ON(PMSLATFR_EL1_RES0		!= (GENMASK_ULL(63, 16)));
	BUILD_BUG_ON(PMSIDR_EL1_RES0		!= (GENMASK_ULL(63, 25) | GENMASK_ULL(7, 7)));
	BUILD_BUG_ON(PMBLIMITR_EL1_RES0		!= (GENMASK_ULL(11, 6) | GENMASK_ULL(4, 3)));
	BUILD_BUG_ON(PMBSR_EL1_RES0		!= (GENMASK_ULL(63, 32) | GENMASK_ULL(25, 20)));
	BUILD_BUG_ON(PMBIDR_EL1_RES0		!= (GENMASK_ULL(63, 12) | GENMASK_ULL(7, 6)));
	BUILD_BUG_ON(CONTEXTIDR_ELx_RES0	!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(CCSIDR_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(CLIDR_EL1_RES0		!= (GENMASK_ULL(63, 47)));
	BUILD_BUG_ON(CCSIDR2_EL1_RES0		!= (GENMASK_ULL(63, 24)));
	BUILD_BUG_ON(GMID_EL1_RES0		!= (GENMASK_ULL(63, 4)));
	BUILD_BUG_ON(SMIDR_EL1_RES0		!= (GENMASK_ULL(63, 32) | GENMASK_ULL(14, 12)));
	BUILD_BUG_ON(CSSELR_EL1_RES0		!= (GENMASK_ULL(63, 5)));
	BUILD_BUG_ON(CTR_EL0_RES0		!= (GENMASK_ULL(63, 38) | GENMASK_ULL(30, 30) | GENMASK_ULL(13, 4)));
	BUILD_BUG_ON(CTR_EL0_RES1       	!= (GENMASK_ULL(31, 31)));
	BUILD_BUG_ON(DCZID_EL0_RES0		!= (GENMASK_ULL(63, 5)));
	BUILD_BUG_ON(SVCR_RES0			!= (GENMASK_ULL(63, 2)));
	BUILD_BUG_ON(FPMR_RES0			!= (GENMASK_ULL(63, 38) | GENMASK_ULL(23, 23) | GENMASK_ULL(13, 9)));
	BUILD_BUG_ON(HFGxTR_EL2_RES0		!= (GENMASK_ULL(51, 51)));
	BUILD_BUG_ON(HFGITR_EL2_RES0		!= (GENMASK_ULL(63, 63) | GENMASK_ULL(61, 61)));
	BUILD_BUG_ON(HDFGRTR_EL2_RES0		!= (GENMASK_ULL(49, 49) | GENMASK_ULL(42, 42) | GENMASK_ULL(39, 38) | GENMASK_ULL(21, 20) | GENMASK_ULL(8, 8)));
	BUILD_BUG_ON(HDFGWTR_EL2_RES0		!= (GENMASK_ULL(63, 63) | GENMASK_ULL(59, 58) | GENMASK_ULL(51, 51) | GENMASK_ULL(47, 47) | GENMASK_ULL(43, 43) | GENMASK_ULL(40, 38) | GENMASK_ULL(34, 34) | GENMASK_ULL(30, 30) | GENMASK_ULL(22, 22) | GENMASK_ULL(9, 9) | GENMASK_ULL(6, 6)));
	BUILD_BUG_ON(HAFGRTR_EL2_RES0		!= (GENMASK_ULL(63, 50) | GENMASK_ULL(16, 5)));
	BUILD_BUG_ON(HCRX_EL2_RES0		!= (GENMASK_ULL(63, 25) | GENMASK_ULL(13, 12)));
	BUILD_BUG_ON(DACR32_EL2_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(PMSCR_EL2_RES0		!= (GENMASK_ULL(63, 8) | GENMASK_ULL(2, 2)));
	BUILD_BUG_ON(TCR2_EL1x_RES0		!= (GENMASK_ULL(63, 16) | GENMASK_ULL(13, 12) | GENMASK_ULL(9, 6)));
	BUILD_BUG_ON(TCR2_EL2_RES0		!= (GENMASK_ULL(63, 16)));
	BUILD_BUG_ON(LORSA_EL1_RES0		!= (GENMASK_ULL(63, 52) | GENMASK_ULL(15, 1)));
	BUILD_BUG_ON(LOREA_EL1_RES0		!= (GENMASK_ULL(63, 52) | GENMASK_ULL(15, 0)));
	BUILD_BUG_ON(LORN_EL1_RES0		!= (GENMASK_ULL(63, 8)));
	BUILD_BUG_ON(LORC_EL1_RES0		!= (GENMASK_ULL(63, 10) | GENMASK_ULL(1, 1)));
	BUILD_BUG_ON(LORID_EL1_RES0		!= (GENMASK_ULL(63, 24) | GENMASK_ULL(15, 8)));
	BUILD_BUG_ON(ISR_EL1_RES0		!= (GENMASK_ULL(63, 11) | GENMASK_ULL(5, 0)));
	BUILD_BUG_ON(ICC_NMIAR1_EL1_RES0	!= (GENMASK_ULL(63, 24)));
	BUILD_BUG_ON(TRBLIMITR_EL1_RES0		!= (GENMASK_ULL(11, 7)));
	BUILD_BUG_ON(TRBBASER_EL1_RES0		!= (GENMASK_ULL(11, 0)));
	BUILD_BUG_ON(TRBSR_EL1_RES0		!= (GENMASK_ULL(63, 56) | GENMASK_ULL(25, 24) | GENMASK_ULL(19, 19) | GENMASK_ULL(16, 16)));
	BUILD_BUG_ON(TRBMAR_EL1_RES0		!= (GENMASK_ULL(63, 12)));
	BUILD_BUG_ON(TRBTRG_EL1_RES0		!= (GENMASK_ULL(63, 32)));
	BUILD_BUG_ON(TRBIDR_EL1_RES0		!= (GENMASK_ULL(63, 12) | GENMASK_ULL(7, 6)));

#endif
}
