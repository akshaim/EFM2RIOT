/*
 * Copyright (C) 2015-2018 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_slstk3701a
 * @{
 *
 * @file
 * @brief       Configuration of CPU peripherals for the SLSTK3701A starter kit
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "cpu.h"
#include "periph_cpu.h"
#include "em_cmu.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Internal macro to calculate *_NUMOF based on config.
 */
#define PERIPH_NUMOF(config)    (sizeof(config) / sizeof(config[0]))

/**
 * @name    Clock configuration
 * @{
 */
#ifndef CLOCK_HF
#define CLOCK_HF            cmuSelect_HFXO
#endif
#ifndef CLOCK_CORE_DIV
#define CLOCK_CORE_DIV      cmuClkDiv_1
#endif
#ifndef CLOCK_LFA
#define CLOCK_LFA           cmuSelect_LFXO
#endif
#ifndef CLOCK_LFB
#define CLOCK_LFB           cmuSelect_LFXO
#endif
#ifndef CLOCK_LFE
#define CLOCK_LFE           cmuSelect_LFXO
#endif
/** @} */

/**
 * @name    ADC configuration
 * @{
 */
static const adc_conf_t adc_config[] = {
    {
        .dev = ADC0,
        .cmu = cmuClock_ADC0,
    }
};

static const adc_chan_conf_t adc_channel_config[] = {
    {
        .dev = 0,
        .input = adcPosSelTEMP,
        .reference = adcRef1V25,
        .acq_time = adcAcqTime8
    },
    {
        .dev = 0,
        .input = adcPosSelAVDD,
        .reference = adcRef5V,
        .acq_time = adcAcqTime8
    }
};

#define ADC_DEV_NUMOF       PERIPH_NUMOF(adc_config)
#define ADC_NUMOF           PERIPH_NUMOF(adc_channel_config)
/** @} */

/**
 * @name    I2C configuration
 * @{
 */
static const i2c_conf_t i2c_config[] = {
    {
        .dev = I2C0,
        .sda_pin = GPIO_PIN(PC, 0),
        .scl_pin = GPIO_PIN(PC, 1),
        .loc = I2C_ROUTELOC0_SDALOC_LOC4 |
               I2C_ROUTELOC0_SCLLOC_LOC4,
        .cmu = cmuClock_I2C0,
        .irq = I2C0_IRQn
    },
    {
        .dev = I2C1,
        .sda_pin = GPIO_PIN(PC, 7),
        .scl_pin = GPIO_PIN(PC, 5),
        .loc = I2C_ROUTELOC0_SDALOC_LOC0 |
               I2C_ROUTELOC0_SCLLOC_LOC0,
        .cmu = cmuClock_I2C1,
        .irq = I2C1_IRQn
    },
    {
        .dev = I2C2,
        .sda_pin = GPIO_PIN(PI, 4),
        .scl_pin = GPIO_PIN(PI, 5),
        .loc = I2C_ROUTELOC0_SDALOC_LOC7 |
               I2C_ROUTELOC0_SCLLOC_LOC7,
        .cmu = cmuClock_I2C2,
        .irq = I2C2_IRQn
    }
};

#define I2C_NUMOF           PERIPH_NUMOF(i2c_config)
#define I2C_0_ISR           isr_i2c0
#define I2C_1_ISR           isr_i2c1
#define I2C_2_ISR           isr_i2c2
/** @} */

/**
 * @brief   RTC configuration
 */
#define RTC_NUMOF           (1U)

/**
 * @name    RTT configuration
 * @{
 */
#define RTT_NUMOF           (1U)

#define RTT_MAX_VALUE       (0xFFFFFFFF)
#define RTT_FREQUENCY       (1U)
/** @} */

/**
 * @name    SPI configuration
 * @{
 */
static const spi_dev_t spi_config[] = {
    {
        .dev = USART1,
        .mosi_pin = GPIO_PIN(PA, 14),
        .miso_pin = GPIO_UNDEF,
        .clk_pin = GPIO_PIN(PC, 15),
        .loc = USART_ROUTELOC0_TXLOC_LOC6 |
               USART_ROUTELOC0_CLKLOC_LOC3,
        .cmu = cmuClock_USART1,
        .irq = USART1_RX_IRQn
    }
};

#define SPI_NUMOF           PERIPH_NUMOF(spi_config)
/** @} */

/**
 * @name    Timer configuration
 *
 * The implementation uses two timers in cascade mode.
 * @{
 */
static const timer_conf_t timer_config[] = {
    {
        {
            .dev = TIMER0,
            .cmu = cmuClock_TIMER0
        },
        {
            .dev = TIMER1,
            .cmu = cmuClock_TIMER1
        },
        .irq = TIMER1_IRQn
    }
};

#define TIMER_NUMOF         PERIPH_NUMOF(timer_config)
#define TIMER_0_ISR         isr_timer1
/** @} */

/**
 * @name    UART configuration
 * @{
 */
static const uart_conf_t uart_config[] = {
    {
        .dev = USART4,
        .rx_pin = GPIO_PIN(PH, 5),
        .tx_pin = GPIO_PIN(PH, 4),
        .loc = USART_ROUTELOC0_RXLOC_LOC4 |
               USART_ROUTELOC0_TXLOC_LOC4,
        .cmu = cmuClock_USART4,
        .irq = USART4_RX_IRQn
    },
};

#define UART_NUMOF          PERIPH_NUMOF(uart_config)
#define UART_0_ISR_RX       isr_usart4_rx
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
