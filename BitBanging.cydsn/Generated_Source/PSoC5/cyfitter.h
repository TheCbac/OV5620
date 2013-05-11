#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice.h>
#include <cydevice_trm.h>

/* LCD_Char_1_LCDPort */
#define LCD_Char_1_LCDPort__0__MASK 0x01u
#define LCD_Char_1_LCDPort__0__PC CYREG_PRT2_PC0
#define LCD_Char_1_LCDPort__0__PORT 2u
#define LCD_Char_1_LCDPort__0__SHIFT 0
#define LCD_Char_1_LCDPort__1__MASK 0x02u
#define LCD_Char_1_LCDPort__1__PC CYREG_PRT2_PC1
#define LCD_Char_1_LCDPort__1__PORT 2u
#define LCD_Char_1_LCDPort__1__SHIFT 1
#define LCD_Char_1_LCDPort__2__MASK 0x04u
#define LCD_Char_1_LCDPort__2__PC CYREG_PRT2_PC2
#define LCD_Char_1_LCDPort__2__PORT 2u
#define LCD_Char_1_LCDPort__2__SHIFT 2
#define LCD_Char_1_LCDPort__3__MASK 0x08u
#define LCD_Char_1_LCDPort__3__PC CYREG_PRT2_PC3
#define LCD_Char_1_LCDPort__3__PORT 2u
#define LCD_Char_1_LCDPort__3__SHIFT 3
#define LCD_Char_1_LCDPort__4__MASK 0x10u
#define LCD_Char_1_LCDPort__4__PC CYREG_PRT2_PC4
#define LCD_Char_1_LCDPort__4__PORT 2u
#define LCD_Char_1_LCDPort__4__SHIFT 4
#define LCD_Char_1_LCDPort__5__MASK 0x20u
#define LCD_Char_1_LCDPort__5__PC CYREG_PRT2_PC5
#define LCD_Char_1_LCDPort__5__PORT 2u
#define LCD_Char_1_LCDPort__5__SHIFT 5
#define LCD_Char_1_LCDPort__6__MASK 0x40u
#define LCD_Char_1_LCDPort__6__PC CYREG_PRT2_PC6
#define LCD_Char_1_LCDPort__6__PORT 2u
#define LCD_Char_1_LCDPort__6__SHIFT 6
#define LCD_Char_1_LCDPort__AG CYREG_PRT2_AG
#define LCD_Char_1_LCDPort__AMUX CYREG_PRT2_AMUX
#define LCD_Char_1_LCDPort__BIE CYREG_PRT2_BIE
#define LCD_Char_1_LCDPort__BIT_MASK CYREG_PRT2_BIT_MASK
#define LCD_Char_1_LCDPort__BYP CYREG_PRT2_BYP
#define LCD_Char_1_LCDPort__CTL CYREG_PRT2_CTL
#define LCD_Char_1_LCDPort__DM0 CYREG_PRT2_DM0
#define LCD_Char_1_LCDPort__DM1 CYREG_PRT2_DM1
#define LCD_Char_1_LCDPort__DM2 CYREG_PRT2_DM2
#define LCD_Char_1_LCDPort__DR CYREG_PRT2_DR
#define LCD_Char_1_LCDPort__INP_DIS CYREG_PRT2_INP_DIS
#define LCD_Char_1_LCDPort__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define LCD_Char_1_LCDPort__LCD_EN CYREG_PRT2_LCD_EN
#define LCD_Char_1_LCDPort__MASK 0x7Fu
#define LCD_Char_1_LCDPort__PORT 2u
#define LCD_Char_1_LCDPort__PRT CYREG_PRT2_PRT
#define LCD_Char_1_LCDPort__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define LCD_Char_1_LCDPort__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define LCD_Char_1_LCDPort__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define LCD_Char_1_LCDPort__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define LCD_Char_1_LCDPort__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define LCD_Char_1_LCDPort__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define LCD_Char_1_LCDPort__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define LCD_Char_1_LCDPort__PS CYREG_PRT2_PS
#define LCD_Char_1_LCDPort__SHIFT 0
#define LCD_Char_1_LCDPort__SLW CYREG_PRT2_SLW

/* UART_IntClock */
#define UART_IntClock__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define UART_IntClock__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define UART_IntClock__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define UART_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define UART_IntClock__INDEX 0x00u
#define UART_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define UART_IntClock__PM_ACT_MSK 0x01u
#define UART_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define UART_IntClock__PM_STBY_MSK 0x01u

/* UART_BUART */
#define UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB07_08_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B0_UDB07_08_ST
#define UART_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B0_UDB07_MSK
#define UART_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B0_UDB07_MSK_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B0_UDB07_MSK_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B0_UDB07_ACTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B0_UDB07_ST_CTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B0_UDB07_ST_CTL
#define UART_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B0_UDB07_ST
#define UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB07_08_ACTL
#define UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB07_08_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB07_08_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB07_08_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B0_UDB07_08_CTL
#define UART_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B0_UDB07_08_MSK
#define UART_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B0_UDB07_08_MSK
#define UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B0_UDB07_08_MSK
#define UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB07_08_MSK
#define UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B0_UDB07_ACTL
#define UART_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B0_UDB07_CTL
#define UART_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B0_UDB07_ST_CTL
#define UART_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B0_UDB07_CTL
#define UART_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B0_UDB07_ST_CTL
#define UART_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB07_MSK_ACTL
#define UART_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B0_UDB07_MSK
#define UART_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B0_UDB07_MSK_ACTL
#define UART_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_B1_UDB04_05_A0
#define UART_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_B1_UDB04_05_A1
#define UART_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_B1_UDB04_05_D0
#define UART_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_B1_UDB04_05_D1
#define UART_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define UART_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_B1_UDB04_05_F0
#define UART_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_B1_UDB04_05_F1
#define UART_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B1_UDB04_A0_A1
#define UART_BUART_sRX_RxShifter_u0__A0_REG CYREG_B1_UDB04_A0
#define UART_BUART_sRX_RxShifter_u0__A1_REG CYREG_B1_UDB04_A1
#define UART_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B1_UDB04_D0_D1
#define UART_BUART_sRX_RxShifter_u0__D0_REG CYREG_B1_UDB04_D0
#define UART_BUART_sRX_RxShifter_u0__D1_REG CYREG_B1_UDB04_D1
#define UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define UART_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B1_UDB04_F0_F1
#define UART_BUART_sRX_RxShifter_u0__F0_REG CYREG_B1_UDB04_F0
#define UART_BUART_sRX_RxShifter_u0__F1_REG CYREG_B1_UDB04_F1
#define UART_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define UART_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B1_UDB07_08_ST
#define UART_BUART_sRX_RxSts__3__MASK 0x08u
#define UART_BUART_sRX_RxSts__3__POS 3
#define UART_BUART_sRX_RxSts__4__MASK 0x10u
#define UART_BUART_sRX_RxSts__4__POS 4
#define UART_BUART_sRX_RxSts__5__MASK 0x20u
#define UART_BUART_sRX_RxSts__5__POS 5
#define UART_BUART_sRX_RxSts__MASK 0x38u
#define UART_BUART_sRX_RxSts__MASK_REG CYREG_B1_UDB07_MSK
#define UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define UART_BUART_sRX_RxSts__STATUS_REG CYREG_B1_UDB07_ST
#define UART_BUART_sTX_TxShifter_u0__16BIT_A0_REG CYREG_B1_UDB07_08_A0
#define UART_BUART_sTX_TxShifter_u0__16BIT_A1_REG CYREG_B1_UDB07_08_A1
#define UART_BUART_sTX_TxShifter_u0__16BIT_D0_REG CYREG_B1_UDB07_08_D0
#define UART_BUART_sTX_TxShifter_u0__16BIT_D1_REG CYREG_B1_UDB07_08_D1
#define UART_BUART_sTX_TxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define UART_BUART_sTX_TxShifter_u0__16BIT_F0_REG CYREG_B1_UDB07_08_F0
#define UART_BUART_sTX_TxShifter_u0__16BIT_F1_REG CYREG_B1_UDB07_08_F1
#define UART_BUART_sTX_TxShifter_u0__A0_A1_REG CYREG_B1_UDB07_A0_A1
#define UART_BUART_sTX_TxShifter_u0__A0_REG CYREG_B1_UDB07_A0
#define UART_BUART_sTX_TxShifter_u0__A1_REG CYREG_B1_UDB07_A1
#define UART_BUART_sTX_TxShifter_u0__D0_D1_REG CYREG_B1_UDB07_D0_D1
#define UART_BUART_sTX_TxShifter_u0__D0_REG CYREG_B1_UDB07_D0
#define UART_BUART_sTX_TxShifter_u0__D1_REG CYREG_B1_UDB07_D1
#define UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define UART_BUART_sTX_TxShifter_u0__F0_F1_REG CYREG_B1_UDB07_F0_F1
#define UART_BUART_sTX_TxShifter_u0__F0_REG CYREG_B1_UDB07_F0
#define UART_BUART_sTX_TxShifter_u0__F1_REG CYREG_B1_UDB07_F1
#define UART_BUART_sTX_TxSts__0__MASK 0x01u
#define UART_BUART_sTX_TxSts__0__POS 0
#define UART_BUART_sTX_TxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB04_05_ACTL
#define UART_BUART_sTX_TxSts__16BIT_STATUS_REG CYREG_B1_UDB04_05_ST
#define UART_BUART_sTX_TxSts__1__MASK 0x02u
#define UART_BUART_sTX_TxSts__1__POS 1
#define UART_BUART_sTX_TxSts__2__MASK 0x04u
#define UART_BUART_sTX_TxSts__2__POS 2
#define UART_BUART_sTX_TxSts__3__MASK 0x08u
#define UART_BUART_sTX_TxSts__3__POS 3
#define UART_BUART_sTX_TxSts__MASK 0x0Fu
#define UART_BUART_sTX_TxSts__MASK_REG CYREG_B1_UDB04_MSK
#define UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG CYREG_B1_UDB04_ACTL
#define UART_BUART_sTX_TxSts__STATUS_REG CYREG_B1_UDB04_ST
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A0_REG CYREG_B1_UDB06_07_A0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_A1_REG CYREG_B1_UDB06_07_A1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D0_REG CYREG_B1_UDB06_07_D0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_D1_REG CYREG_B1_UDB06_07_D1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_DP_AUX_CTL_REG CYREG_B1_UDB06_07_ACTL
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F0_REG CYREG_B1_UDB06_07_F0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__16BIT_F1_REG CYREG_B1_UDB06_07_F1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_A1_REG CYREG_B1_UDB06_A0_A1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__A0_REG CYREG_B1_UDB06_A0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__A1_REG CYREG_B1_UDB06_A1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_D1_REG CYREG_B1_UDB06_D0_D1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG CYREG_B1_UDB06_D0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG CYREG_B1_UDB06_D1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__DP_AUX_CTL_REG CYREG_B1_UDB06_ACTL
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_F1_REG CYREG_B1_UDB06_F0_F1
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__F0_REG CYREG_B1_UDB06_F0
#define UART_BUART_sTX_sCLOCK_TxBitClkGen__F1_REG CYREG_B1_UDB06_F1

/* ClockLine */
#define ClockLine__0__MASK 0x10u
#define ClockLine__0__PC CYREG_PRT12_PC4
#define ClockLine__0__PORT 12u
#define ClockLine__0__SHIFT 4
#define ClockLine__AG CYREG_PRT12_AG
#define ClockLine__BIE CYREG_PRT12_BIE
#define ClockLine__BIT_MASK CYREG_PRT12_BIT_MASK
#define ClockLine__BYP CYREG_PRT12_BYP
#define ClockLine__DM0 CYREG_PRT12_DM0
#define ClockLine__DM1 CYREG_PRT12_DM1
#define ClockLine__DM2 CYREG_PRT12_DM2
#define ClockLine__DR CYREG_PRT12_DR
#define ClockLine__INP_DIS CYREG_PRT12_INP_DIS
#define ClockLine__MASK 0x10u
#define ClockLine__PORT 12u
#define ClockLine__PRT CYREG_PRT12_PRT
#define ClockLine__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define ClockLine__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define ClockLine__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define ClockLine__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define ClockLine__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define ClockLine__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define ClockLine__PS CYREG_PRT12_PS
#define ClockLine__SHIFT 4
#define ClockLine__SIO_CFG CYREG_PRT12_SIO_CFG
#define ClockLine__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define ClockLine__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define ClockLine__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define ClockLine__SLW CYREG_PRT12_SLW

/* DataLine */
#define DataLine__0__MASK 0x20u
#define DataLine__0__PC CYREG_PRT12_PC5
#define DataLine__0__PORT 12u
#define DataLine__0__SHIFT 5
#define DataLine__AG CYREG_PRT12_AG
#define DataLine__BIE CYREG_PRT12_BIE
#define DataLine__BIT_MASK CYREG_PRT12_BIT_MASK
#define DataLine__BYP CYREG_PRT12_BYP
#define DataLine__DM0 CYREG_PRT12_DM0
#define DataLine__DM1 CYREG_PRT12_DM1
#define DataLine__DM2 CYREG_PRT12_DM2
#define DataLine__DR CYREG_PRT12_DR
#define DataLine__INP_DIS CYREG_PRT12_INP_DIS
#define DataLine__MASK 0x20u
#define DataLine__PORT 12u
#define DataLine__PRT CYREG_PRT12_PRT
#define DataLine__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define DataLine__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define DataLine__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define DataLine__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define DataLine__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define DataLine__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define DataLine__PS CYREG_PRT12_PS
#define DataLine__SHIFT 5
#define DataLine__SIO_CFG CYREG_PRT12_SIO_CFG
#define DataLine__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define DataLine__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define DataLine__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define DataLine__SLW CYREG_PRT12_SLW

/* isr_HREF */
#define isr_HREF__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_HREF__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_HREF__INTC_MASK 0x01u
#define isr_HREF__INTC_NUMBER 0u
#define isr_HREF__INTC_PRIOR_NUM 7u
#define isr_HREF__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define isr_HREF__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_HREF__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* isr_PCLK */
#define isr_PCLK__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_PCLK__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_PCLK__INTC_MASK 0x02u
#define isr_PCLK__INTC_NUMBER 1u
#define isr_PCLK__INTC_PRIOR_NUM 7u
#define isr_PCLK__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define isr_PCLK__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_PCLK__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* isr_VREF */
#define isr_VREF__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_VREF__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_VREF__INTC_MASK 0x04u
#define isr_VREF__INTC_NUMBER 2u
#define isr_VREF__INTC_PRIOR_NUM 7u
#define isr_VREF__INTC_PRIOR_REG CYREG_NVIC_PRI_2
#define isr_VREF__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_VREF__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Clock_1 */
#define Clock_1__CFG0 CYREG_CLKDIST_DCFG1_CFG0
#define Clock_1__CFG1 CYREG_CLKDIST_DCFG1_CFG1
#define Clock_1__CFG2 CYREG_CLKDIST_DCFG1_CFG2
#define Clock_1__CFG2_SRC_SEL_MASK 0x07u
#define Clock_1__INDEX 0x01u
#define Clock_1__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Clock_1__PM_ACT_MSK 0x02u
#define Clock_1__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Clock_1__PM_STBY_MSK 0x02u

/* DataBus */
#define DataBus__0__MASK 0x01u
#define DataBus__0__PC CYREG_PRT4_PC0
#define DataBus__0__PORT 4u
#define DataBus__0__SHIFT 0
#define DataBus__1__MASK 0x02u
#define DataBus__1__PC CYREG_PRT4_PC1
#define DataBus__1__PORT 4u
#define DataBus__1__SHIFT 1
#define DataBus__2__MASK 0x04u
#define DataBus__2__PC CYREG_PRT4_PC2
#define DataBus__2__PORT 4u
#define DataBus__2__SHIFT 2
#define DataBus__3__MASK 0x08u
#define DataBus__3__PC CYREG_PRT4_PC3
#define DataBus__3__PORT 4u
#define DataBus__3__SHIFT 3
#define DataBus__4__MASK 0x10u
#define DataBus__4__PC CYREG_PRT4_PC4
#define DataBus__4__PORT 4u
#define DataBus__4__SHIFT 4
#define DataBus__5__MASK 0x20u
#define DataBus__5__PC CYREG_PRT4_PC5
#define DataBus__5__PORT 4u
#define DataBus__5__SHIFT 5
#define DataBus__6__MASK 0x40u
#define DataBus__6__PC CYREG_PRT4_PC6
#define DataBus__6__PORT 4u
#define DataBus__6__SHIFT 6
#define DataBus__7__MASK 0x80u
#define DataBus__7__PC CYREG_PRT4_PC7
#define DataBus__7__PORT 4u
#define DataBus__7__SHIFT 7
#define DataBus__AG CYREG_PRT4_AG
#define DataBus__AMUX CYREG_PRT4_AMUX
#define DataBus__BIE CYREG_PRT4_BIE
#define DataBus__BIT_MASK CYREG_PRT4_BIT_MASK
#define DataBus__BYP CYREG_PRT4_BYP
#define DataBus__CTL CYREG_PRT4_CTL
#define DataBus__DM0 CYREG_PRT4_DM0
#define DataBus__DM1 CYREG_PRT4_DM1
#define DataBus__DM2 CYREG_PRT4_DM2
#define DataBus__DR CYREG_PRT4_DR
#define DataBus__INP_DIS CYREG_PRT4_INP_DIS
#define DataBus__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define DataBus__LCD_EN CYREG_PRT4_LCD_EN
#define DataBus__MASK 0xFFu
#define DataBus__PORT 4u
#define DataBus__PRT CYREG_PRT4_PRT
#define DataBus__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define DataBus__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define DataBus__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define DataBus__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define DataBus__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define DataBus__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define DataBus__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define DataBus__PS CYREG_PRT4_PS
#define DataBus__SHIFT 0
#define DataBus__SLW CYREG_PRT4_SLW

/* isr_rx */
#define isr_rx__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_rx__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_rx__INTC_MASK 0x08u
#define isr_rx__INTC_NUMBER 3u
#define isr_rx__INTC_PRIOR_NUM 7u
#define isr_rx__INTC_PRIOR_REG CYREG_NVIC_PRI_3
#define isr_rx__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_rx__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* isr_tx */
#define isr_tx__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_tx__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_tx__INTC_MASK 0x10u
#define isr_tx__INTC_NUMBER 4u
#define isr_tx__INTC_PRIOR_NUM 7u
#define isr_tx__INTC_PRIOR_REG CYREG_NVIC_PRI_4
#define isr_tx__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_tx__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* EXPST */
#define EXPST__0__MASK 0x40u
#define EXPST__0__PC CYREG_PRT3_PC6
#define EXPST__0__PORT 3u
#define EXPST__0__SHIFT 6
#define EXPST__AG CYREG_PRT3_AG
#define EXPST__AMUX CYREG_PRT3_AMUX
#define EXPST__BIE CYREG_PRT3_BIE
#define EXPST__BIT_MASK CYREG_PRT3_BIT_MASK
#define EXPST__BYP CYREG_PRT3_BYP
#define EXPST__CTL CYREG_PRT3_CTL
#define EXPST__DM0 CYREG_PRT3_DM0
#define EXPST__DM1 CYREG_PRT3_DM1
#define EXPST__DM2 CYREG_PRT3_DM2
#define EXPST__DR CYREG_PRT3_DR
#define EXPST__INP_DIS CYREG_PRT3_INP_DIS
#define EXPST__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define EXPST__LCD_EN CYREG_PRT3_LCD_EN
#define EXPST__MASK 0x40u
#define EXPST__PORT 3u
#define EXPST__PRT CYREG_PRT3_PRT
#define EXPST__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define EXPST__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define EXPST__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define EXPST__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define EXPST__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define EXPST__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define EXPST__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define EXPST__PS CYREG_PRT3_PS
#define EXPST__SHIFT 6
#define EXPST__SLW CYREG_PRT3_SLW

/* Pin_1 */
#define Pin_1__0__MASK 0x20u
#define Pin_1__0__PC CYREG_PRT0_PC5
#define Pin_1__0__PORT 0u
#define Pin_1__0__SHIFT 5
#define Pin_1__AG CYREG_PRT0_AG
#define Pin_1__AMUX CYREG_PRT0_AMUX
#define Pin_1__BIE CYREG_PRT0_BIE
#define Pin_1__BIT_MASK CYREG_PRT0_BIT_MASK
#define Pin_1__BYP CYREG_PRT0_BYP
#define Pin_1__CTL CYREG_PRT0_CTL
#define Pin_1__DM0 CYREG_PRT0_DM0
#define Pin_1__DM1 CYREG_PRT0_DM1
#define Pin_1__DM2 CYREG_PRT0_DM2
#define Pin_1__DR CYREG_PRT0_DR
#define Pin_1__INP_DIS CYREG_PRT0_INP_DIS
#define Pin_1__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Pin_1__LCD_EN CYREG_PRT0_LCD_EN
#define Pin_1__MASK 0x20u
#define Pin_1__PORT 0u
#define Pin_1__PRT CYREG_PRT0_PRT
#define Pin_1__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Pin_1__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Pin_1__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Pin_1__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Pin_1__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Pin_1__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Pin_1__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Pin_1__PS CYREG_PRT0_PS
#define Pin_1__SHIFT 5
#define Pin_1__SLW CYREG_PRT0_SLW

/* Pin_2 */
#define Pin_2__0__MASK 0x40u
#define Pin_2__0__PC CYREG_PRT0_PC6
#define Pin_2__0__PORT 0u
#define Pin_2__0__SHIFT 6
#define Pin_2__AG CYREG_PRT0_AG
#define Pin_2__AMUX CYREG_PRT0_AMUX
#define Pin_2__BIE CYREG_PRT0_BIE
#define Pin_2__BIT_MASK CYREG_PRT0_BIT_MASK
#define Pin_2__BYP CYREG_PRT0_BYP
#define Pin_2__CTL CYREG_PRT0_CTL
#define Pin_2__DM0 CYREG_PRT0_DM0
#define Pin_2__DM1 CYREG_PRT0_DM1
#define Pin_2__DM2 CYREG_PRT0_DM2
#define Pin_2__DR CYREG_PRT0_DR
#define Pin_2__INP_DIS CYREG_PRT0_INP_DIS
#define Pin_2__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Pin_2__LCD_EN CYREG_PRT0_LCD_EN
#define Pin_2__MASK 0x40u
#define Pin_2__PORT 0u
#define Pin_2__PRT CYREG_PRT0_PRT
#define Pin_2__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Pin_2__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Pin_2__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Pin_2__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Pin_2__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Pin_2__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Pin_2__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Pin_2__PS CYREG_PRT0_PS
#define Pin_2__SHIFT 6
#define Pin_2__SLW CYREG_PRT0_SLW

/* Pin_3 */
#define Pin_3__0__MASK 0x80u
#define Pin_3__0__PC CYREG_PRT0_PC7
#define Pin_3__0__PORT 0u
#define Pin_3__0__SHIFT 7
#define Pin_3__AG CYREG_PRT0_AG
#define Pin_3__AMUX CYREG_PRT0_AMUX
#define Pin_3__BIE CYREG_PRT0_BIE
#define Pin_3__BIT_MASK CYREG_PRT0_BIT_MASK
#define Pin_3__BYP CYREG_PRT0_BYP
#define Pin_3__CTL CYREG_PRT0_CTL
#define Pin_3__DM0 CYREG_PRT0_DM0
#define Pin_3__DM1 CYREG_PRT0_DM1
#define Pin_3__DM2 CYREG_PRT0_DM2
#define Pin_3__DR CYREG_PRT0_DR
#define Pin_3__INP_DIS CYREG_PRT0_INP_DIS
#define Pin_3__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Pin_3__LCD_EN CYREG_PRT0_LCD_EN
#define Pin_3__MASK 0x80u
#define Pin_3__PORT 0u
#define Pin_3__PRT CYREG_PRT0_PRT
#define Pin_3__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Pin_3__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Pin_3__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Pin_3__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Pin_3__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Pin_3__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Pin_3__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Pin_3__PS CYREG_PRT0_PS
#define Pin_3__SHIFT 7
#define Pin_3__SLW CYREG_PRT0_SLW

/* pin_4 */
#define pin_4__0__MASK 0x40u
#define pin_4__0__PC CYREG_PRT1_PC6
#define pin_4__0__PORT 1u
#define pin_4__0__SHIFT 6
#define pin_4__AG CYREG_PRT1_AG
#define pin_4__AMUX CYREG_PRT1_AMUX
#define pin_4__BIE CYREG_PRT1_BIE
#define pin_4__BIT_MASK CYREG_PRT1_BIT_MASK
#define pin_4__BYP CYREG_PRT1_BYP
#define pin_4__CTL CYREG_PRT1_CTL
#define pin_4__DM0 CYREG_PRT1_DM0
#define pin_4__DM1 CYREG_PRT1_DM1
#define pin_4__DM2 CYREG_PRT1_DM2
#define pin_4__DR CYREG_PRT1_DR
#define pin_4__INP_DIS CYREG_PRT1_INP_DIS
#define pin_4__LCD_COM_SEG CYREG_PRT1_LCD_COM_SEG
#define pin_4__LCD_EN CYREG_PRT1_LCD_EN
#define pin_4__MASK 0x40u
#define pin_4__PORT 1u
#define pin_4__PRT CYREG_PRT1_PRT
#define pin_4__PRTDSI__CAPS_SEL CYREG_PRT1_CAPS_SEL
#define pin_4__PRTDSI__DBL_SYNC_IN CYREG_PRT1_DBL_SYNC_IN
#define pin_4__PRTDSI__OE_SEL0 CYREG_PRT1_OE_SEL0
#define pin_4__PRTDSI__OE_SEL1 CYREG_PRT1_OE_SEL1
#define pin_4__PRTDSI__OUT_SEL0 CYREG_PRT1_OUT_SEL0
#define pin_4__PRTDSI__OUT_SEL1 CYREG_PRT1_OUT_SEL1
#define pin_4__PRTDSI__SYNC_OUT CYREG_PRT1_SYNC_OUT
#define pin_4__PS CYREG_PRT1_PS
#define pin_4__SHIFT 6
#define pin_4__SLW CYREG_PRT1_SLW

/* RST_B */
#define RST_B__0__MASK 0x10u
#define RST_B__0__PC CYREG_PRT3_PC4
#define RST_B__0__PORT 3u
#define RST_B__0__SHIFT 4
#define RST_B__AG CYREG_PRT3_AG
#define RST_B__AMUX CYREG_PRT3_AMUX
#define RST_B__BIE CYREG_PRT3_BIE
#define RST_B__BIT_MASK CYREG_PRT3_BIT_MASK
#define RST_B__BYP CYREG_PRT3_BYP
#define RST_B__CTL CYREG_PRT3_CTL
#define RST_B__DM0 CYREG_PRT3_DM0
#define RST_B__DM1 CYREG_PRT3_DM1
#define RST_B__DM2 CYREG_PRT3_DM2
#define RST_B__DR CYREG_PRT3_DR
#define RST_B__INP_DIS CYREG_PRT3_INP_DIS
#define RST_B__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define RST_B__LCD_EN CYREG_PRT3_LCD_EN
#define RST_B__MASK 0x10u
#define RST_B__PORT 3u
#define RST_B__PRT CYREG_PRT3_PRT
#define RST_B__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define RST_B__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define RST_B__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define RST_B__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define RST_B__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define RST_B__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define RST_B__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define RST_B__PS CYREG_PRT3_PS
#define RST_B__SHIFT 4
#define RST_B__SLW CYREG_PRT3_SLW

/* FREX */
#define FREX__0__MASK 0x20u
#define FREX__0__PC CYREG_PRT3_PC5
#define FREX__0__PORT 3u
#define FREX__0__SHIFT 5
#define FREX__AG CYREG_PRT3_AG
#define FREX__AMUX CYREG_PRT3_AMUX
#define FREX__BIE CYREG_PRT3_BIE
#define FREX__BIT_MASK CYREG_PRT3_BIT_MASK
#define FREX__BYP CYREG_PRT3_BYP
#define FREX__CTL CYREG_PRT3_CTL
#define FREX__DM0 CYREG_PRT3_DM0
#define FREX__DM1 CYREG_PRT3_DM1
#define FREX__DM2 CYREG_PRT3_DM2
#define FREX__DR CYREG_PRT3_DR
#define FREX__INP_DIS CYREG_PRT3_INP_DIS
#define FREX__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define FREX__LCD_EN CYREG_PRT3_LCD_EN
#define FREX__MASK 0x20u
#define FREX__PORT 3u
#define FREX__PRT CYREG_PRT3_PRT
#define FREX__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define FREX__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define FREX__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define FREX__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define FREX__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define FREX__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define FREX__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define FREX__PS CYREG_PRT3_PS
#define FREX__SHIFT 5
#define FREX__SLW CYREG_PRT3_SLW

/* HREF */
#define HREF__0__MASK 0x01u
#define HREF__0__PC CYREG_PRT6_PC0
#define HREF__0__PORT 6u
#define HREF__0__SHIFT 0
#define HREF__AG CYREG_PRT6_AG
#define HREF__AMUX CYREG_PRT6_AMUX
#define HREF__BIE CYREG_PRT6_BIE
#define HREF__BIT_MASK CYREG_PRT6_BIT_MASK
#define HREF__BYP CYREG_PRT6_BYP
#define HREF__CTL CYREG_PRT6_CTL
#define HREF__DM0 CYREG_PRT6_DM0
#define HREF__DM1 CYREG_PRT6_DM1
#define HREF__DM2 CYREG_PRT6_DM2
#define HREF__DR CYREG_PRT6_DR
#define HREF__INP_DIS CYREG_PRT6_INP_DIS
#define HREF__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define HREF__LCD_EN CYREG_PRT6_LCD_EN
#define HREF__MASK 0x01u
#define HREF__PORT 6u
#define HREF__PRT CYREG_PRT6_PRT
#define HREF__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define HREF__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define HREF__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define HREF__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define HREF__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define HREF__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define HREF__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define HREF__PS CYREG_PRT6_PS
#define HREF__SHIFT 0
#define HREF__SLW CYREG_PRT6_SLW

/* PCLK */
#define PCLK__0__MASK 0x01u
#define PCLK__0__PC CYREG_PRT0_PC0
#define PCLK__0__PORT 0u
#define PCLK__0__SHIFT 0
#define PCLK__AG CYREG_PRT0_AG
#define PCLK__AMUX CYREG_PRT0_AMUX
#define PCLK__BIE CYREG_PRT0_BIE
#define PCLK__BIT_MASK CYREG_PRT0_BIT_MASK
#define PCLK__BYP CYREG_PRT0_BYP
#define PCLK__CTL CYREG_PRT0_CTL
#define PCLK__DM0 CYREG_PRT0_DM0
#define PCLK__DM1 CYREG_PRT0_DM1
#define PCLK__DM2 CYREG_PRT0_DM2
#define PCLK__DR CYREG_PRT0_DR
#define PCLK__INP_DIS CYREG_PRT0_INP_DIS
#define PCLK__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define PCLK__LCD_EN CYREG_PRT0_LCD_EN
#define PCLK__MASK 0x01u
#define PCLK__PORT 0u
#define PCLK__PRT CYREG_PRT0_PRT
#define PCLK__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define PCLK__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define PCLK__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define PCLK__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define PCLK__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define PCLK__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define PCLK__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define PCLK__PS CYREG_PRT0_PS
#define PCLK__SHIFT 0
#define PCLK__SLW CYREG_PRT0_SLW

/* PWND */
#define PWND__0__MASK 0x08u
#define PWND__0__PC CYREG_PRT3_PC3
#define PWND__0__PORT 3u
#define PWND__0__SHIFT 3
#define PWND__AG CYREG_PRT3_AG
#define PWND__AMUX CYREG_PRT3_AMUX
#define PWND__BIE CYREG_PRT3_BIE
#define PWND__BIT_MASK CYREG_PRT3_BIT_MASK
#define PWND__BYP CYREG_PRT3_BYP
#define PWND__CTL CYREG_PRT3_CTL
#define PWND__DM0 CYREG_PRT3_DM0
#define PWND__DM1 CYREG_PRT3_DM1
#define PWND__DM2 CYREG_PRT3_DM2
#define PWND__DR CYREG_PRT3_DR
#define PWND__INP_DIS CYREG_PRT3_INP_DIS
#define PWND__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define PWND__LCD_EN CYREG_PRT3_LCD_EN
#define PWND__MASK 0x08u
#define PWND__PORT 3u
#define PWND__PRT CYREG_PRT3_PRT
#define PWND__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define PWND__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define PWND__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define PWND__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define PWND__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define PWND__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define PWND__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define PWND__PS CYREG_PRT3_PS
#define PWND__SHIFT 3
#define PWND__SLW CYREG_PRT3_SLW

/* VREF */
#define VREF__0__MASK 0x80u
#define VREF__0__PC CYREG_PRT12_PC7
#define VREF__0__PORT 12u
#define VREF__0__SHIFT 7
#define VREF__AG CYREG_PRT12_AG
#define VREF__BIE CYREG_PRT12_BIE
#define VREF__BIT_MASK CYREG_PRT12_BIT_MASK
#define VREF__BYP CYREG_PRT12_BYP
#define VREF__DM0 CYREG_PRT12_DM0
#define VREF__DM1 CYREG_PRT12_DM1
#define VREF__DM2 CYREG_PRT12_DM2
#define VREF__DR CYREG_PRT12_DR
#define VREF__INP_DIS CYREG_PRT12_INP_DIS
#define VREF__MASK 0x80u
#define VREF__PORT 12u
#define VREF__PRT CYREG_PRT12_PRT
#define VREF__PRTDSI__DBL_SYNC_IN CYREG_PRT12_DBL_SYNC_IN
#define VREF__PRTDSI__OE_SEL0 CYREG_PRT12_OE_SEL0
#define VREF__PRTDSI__OE_SEL1 CYREG_PRT12_OE_SEL1
#define VREF__PRTDSI__OUT_SEL0 CYREG_PRT12_OUT_SEL0
#define VREF__PRTDSI__OUT_SEL1 CYREG_PRT12_OUT_SEL1
#define VREF__PRTDSI__SYNC_OUT CYREG_PRT12_SYNC_OUT
#define VREF__PS CYREG_PRT12_PS
#define VREF__SHIFT 7
#define VREF__SIO_CFG CYREG_PRT12_SIO_CFG
#define VREF__SIO_DIFF CYREG_PRT12_SIO_DIFF
#define VREF__SIO_HYST_EN CYREG_PRT12_SIO_HYST_EN
#define VREF__SIO_REG_HIFREQ CYREG_PRT12_SIO_REG_HIFREQ
#define VREF__SLW CYREG_PRT12_SLW

/* XCLK */
#define XCLK__0__MASK 0x04u
#define XCLK__0__PC CYREG_PRT3_PC2
#define XCLK__0__PORT 3u
#define XCLK__0__SHIFT 2
#define XCLK__AG CYREG_PRT3_AG
#define XCLK__AMUX CYREG_PRT3_AMUX
#define XCLK__BIE CYREG_PRT3_BIE
#define XCLK__BIT_MASK CYREG_PRT3_BIT_MASK
#define XCLK__BYP CYREG_PRT3_BYP
#define XCLK__CTL CYREG_PRT3_CTL
#define XCLK__DM0 CYREG_PRT3_DM0
#define XCLK__DM1 CYREG_PRT3_DM1
#define XCLK__DM2 CYREG_PRT3_DM2
#define XCLK__DR CYREG_PRT3_DR
#define XCLK__INP_DIS CYREG_PRT3_INP_DIS
#define XCLK__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define XCLK__LCD_EN CYREG_PRT3_LCD_EN
#define XCLK__MASK 0x04u
#define XCLK__PORT 3u
#define XCLK__PRT CYREG_PRT3_PRT
#define XCLK__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define XCLK__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define XCLK__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define XCLK__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define XCLK__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define XCLK__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define XCLK__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define XCLK__PS CYREG_PRT3_PS
#define XCLK__SHIFT 2
#define XCLK__SLW CYREG_PRT3_SLW

/* LED */
#define LED__0__MASK 0x04u
#define LED__0__PC CYREG_PRT6_PC2
#define LED__0__PORT 6u
#define LED__0__SHIFT 2
#define LED__AG CYREG_PRT6_AG
#define LED__AMUX CYREG_PRT6_AMUX
#define LED__BIE CYREG_PRT6_BIE
#define LED__BIT_MASK CYREG_PRT6_BIT_MASK
#define LED__BYP CYREG_PRT6_BYP
#define LED__CTL CYREG_PRT6_CTL
#define LED__DM0 CYREG_PRT6_DM0
#define LED__DM1 CYREG_PRT6_DM1
#define LED__DM2 CYREG_PRT6_DM2
#define LED__DR CYREG_PRT6_DR
#define LED__INP_DIS CYREG_PRT6_INP_DIS
#define LED__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define LED__LCD_EN CYREG_PRT6_LCD_EN
#define LED__MASK 0x04u
#define LED__PORT 6u
#define LED__PRT CYREG_PRT6_PRT
#define LED__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define LED__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define LED__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define LED__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define LED__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define LED__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define LED__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define LED__PS CYREG_PRT6_PS
#define LED__SHIFT 2
#define LED__SLW CYREG_PRT6_SLW

/* RX */
#define RX__0__MASK 0x02u
#define RX__0__PC CYREG_PRT3_PC1
#define RX__0__PORT 3u
#define RX__0__SHIFT 1
#define RX__AG CYREG_PRT3_AG
#define RX__AMUX CYREG_PRT3_AMUX
#define RX__BIE CYREG_PRT3_BIE
#define RX__BIT_MASK CYREG_PRT3_BIT_MASK
#define RX__BYP CYREG_PRT3_BYP
#define RX__CTL CYREG_PRT3_CTL
#define RX__DM0 CYREG_PRT3_DM0
#define RX__DM1 CYREG_PRT3_DM1
#define RX__DM2 CYREG_PRT3_DM2
#define RX__DR CYREG_PRT3_DR
#define RX__INP_DIS CYREG_PRT3_INP_DIS
#define RX__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define RX__LCD_EN CYREG_PRT3_LCD_EN
#define RX__MASK 0x02u
#define RX__PORT 3u
#define RX__PRT CYREG_PRT3_PRT
#define RX__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define RX__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define RX__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define RX__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define RX__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define RX__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define RX__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define RX__PS CYREG_PRT3_PS
#define RX__SHIFT 1
#define RX__SLW CYREG_PRT3_SLW

/* TX */
#define TX__0__MASK 0x01u
#define TX__0__PC CYREG_PRT3_PC0
#define TX__0__PORT 3u
#define TX__0__SHIFT 0
#define TX__AG CYREG_PRT3_AG
#define TX__AMUX CYREG_PRT3_AMUX
#define TX__BIE CYREG_PRT3_BIE
#define TX__BIT_MASK CYREG_PRT3_BIT_MASK
#define TX__BYP CYREG_PRT3_BYP
#define TX__CTL CYREG_PRT3_CTL
#define TX__DM0 CYREG_PRT3_DM0
#define TX__DM1 CYREG_PRT3_DM1
#define TX__DM2 CYREG_PRT3_DM2
#define TX__DR CYREG_PRT3_DR
#define TX__INP_DIS CYREG_PRT3_INP_DIS
#define TX__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define TX__LCD_EN CYREG_PRT3_LCD_EN
#define TX__MASK 0x01u
#define TX__PORT 3u
#define TX__PRT CYREG_PRT3_PRT
#define TX__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define TX__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define TX__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define TX__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define TX__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define TX__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define TX__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define TX__PS CYREG_PRT3_PS
#define TX__SHIFT 0
#define TX__SLW CYREG_PRT3_SLW

/* Miscellaneous */
/* -- WARNING: define names containing LEOPARD or PANTHER are deprecated and will be removed in a future release */
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_MEMBER_5B 3u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_DIE_PSOC5LP 3u
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_DIE_PSOC5LP
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E123069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_5A 2u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REV_PSOC5LP_PRODUCTION
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_REQXRES 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DEBUG_ENABLE_MASK 0x20u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x1000
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x0000001Fu
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x4000
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5
#define CYDEV_VIO3_MV 5000
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
