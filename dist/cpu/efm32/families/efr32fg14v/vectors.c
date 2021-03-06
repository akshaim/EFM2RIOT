/*
 * Copyright (C) 2015-2018 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_efr32fg14v
 * @{
 *
 * @file
 * @brief       Startup code and interrupt vector definition
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "vectors_cortexm.h"

/* define a local dummy handler as it needs to be in the same compilation unit
 * as the alias definition */
void dummy_handler(void)
{
    dummy_handler_default();
}

/* Silicon Labs specific interrupt vector */
WEAK_DEFAULT void isr_emu(void);
WEAK_DEFAULT void isr_frc_pri(void);
WEAK_DEFAULT void isr_wdog0(void);
WEAK_DEFAULT void isr_wdog1(void);
WEAK_DEFAULT void isr_frc(void);
WEAK_DEFAULT void isr_modem(void);
WEAK_DEFAULT void isr_rac_seq(void);
WEAK_DEFAULT void isr_rac_rsm(void);
WEAK_DEFAULT void isr_bufc(void);
WEAK_DEFAULT void isr_ldma(void);
WEAK_DEFAULT void isr_gpio_even(void);
WEAK_DEFAULT void isr_timer0(void);
WEAK_DEFAULT void isr_usart0_rx(void);
WEAK_DEFAULT void isr_usart0_tx(void);
WEAK_DEFAULT void isr_adc0(void);
WEAK_DEFAULT void isr_i2c0(void);
WEAK_DEFAULT void isr_gpio_odd(void);
WEAK_DEFAULT void isr_timer1(void);
WEAK_DEFAULT void isr_usart1_rx(void);
WEAK_DEFAULT void isr_usart1_tx(void);
WEAK_DEFAULT void isr_leuart0(void);
WEAK_DEFAULT void isr_cmu(void);
WEAK_DEFAULT void isr_msc(void);
WEAK_DEFAULT void isr_crypto0(void);
WEAK_DEFAULT void isr_letimer0(void);
WEAK_DEFAULT void isr_agc(void);
WEAK_DEFAULT void isr_protimer(void);
WEAK_DEFAULT void isr_prortc(void);
WEAK_DEFAULT void isr_rtcc(void);
WEAK_DEFAULT void isr_synth(void);
WEAK_DEFAULT void isr_cryotimer(void);
WEAK_DEFAULT void isr_rfsense(void);
WEAK_DEFAULT void isr_fpueh(void);
WEAK_DEFAULT void isr_smu(void);
WEAK_DEFAULT void isr_wtimer0(void);
WEAK_DEFAULT void isr_trng0(void);

/* interrupt vector table */
ISR_VECTOR(1) const isr_t vector_cpu[CPU_IRQ_NUMOF] = {
    [ 0] = isr_emu,                /* EMU */
    [ 1] = isr_frc_pri,            /* FRC_PRI */
    [ 2] = isr_wdog0,              /* WDOG0 */
    [ 3] = isr_wdog1,              /* WDOG1 */
    [ 4] = isr_frc,                /* FRC */
    [ 5] = isr_modem,              /* MODEM */
    [ 6] = isr_rac_seq,            /* RAC_SEQ */
    [ 7] = isr_rac_rsm,            /* RAC_RSM */
    [ 8] = isr_bufc,               /* BUFC */
    [ 9] = isr_ldma,               /* LDMA */
    [10] = isr_gpio_even,          /* GPIO_EVEN */
    [11] = isr_timer0,             /* TIMER0 */
    [12] = isr_usart0_rx,          /* USART0_RX */
    [13] = isr_usart0_tx,          /* USART0_TX */
    [15] = isr_adc0,               /* ADC0 */
    [17] = isr_i2c0,               /* I2C0 */
    [18] = isr_gpio_odd,           /* GPIO_ODD */
    [19] = isr_timer1,             /* TIMER1 */
    [20] = isr_usart1_rx,          /* USART1_RX */
    [21] = isr_usart1_tx,          /* USART1_TX */
    [22] = isr_leuart0,            /* LEUART0 */
    [24] = isr_cmu,                /* CMU */
    [25] = isr_msc,                /* MSC */
    [26] = isr_crypto0,            /* CRYPTO0 */
    [27] = isr_letimer0,           /* LETIMER0 */
    [28] = isr_agc,                /* AGC */
    [29] = isr_protimer,           /* PROTIMER */
    [30] = isr_prortc,             /* PRORTC */
    [31] = isr_rtcc,               /* RTCC */
    [32] = isr_synth,              /* SYNTH */
    [33] = isr_cryotimer,          /* CRYOTIMER */
    [34] = isr_rfsense,            /* RFSENSE */
    [35] = isr_fpueh,              /* FPUEH */
    [36] = isr_smu,                /* SMU */
    [37] = isr_wtimer0,            /* WTIMER0 */
    [40] = isr_trng0,              /* TRNG0 */
};
