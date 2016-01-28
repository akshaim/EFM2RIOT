/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @defgroup    boards_{{ board }} Silicon Labs {{ board_display_name }} starter kit
 * @ingroup     boards
 * @brief       Support for the Silicon Labs {{ board_display_name }} starter kit
 * @{
 *
 * @file
 * @brief       Board specific definitions for the {{ board_display_name }} starter kit
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 */

#ifndef BOARD_H
#define BOARD_H

#include "cpu.h"

#include "periph_conf.h"
#include "periph/gpio.h"
#include "periph/spi.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Assign the hardware timer
 */
#define HW_TIMER            TIMER_DEV(0)

{% strip 2, true %}
    {% if architecture not in ["m0", "m0plus"] %}
        /**
         * @brief   Define for enabling Advanced Energy Monitor core output via SWO.
         * @{
         */
        #ifndef AEM_ENABLED
        #define AEM_ENABLED                 (1)
        #endif
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @brief   GPIO pin for enabling communication through the board controller
 * @{
 */
#ifndef BC_ENABLED
#define BC_ENABLED                  (1)
#endif
{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define BC_PIN              GPIO_PIN(PF, 7)
    {% elif board in ["stk3200"] %}
        #define BC_PIN              GPIO_PIN(PA, 9)
    {% elif board in ["slstk3401a"] %}
        #define BC_PIN              GPIO_PIN(PA, 5)
    {% elif board in ["slwstk6220a"] %}
        #define BC_PIN              GPIO_PIN(PA, 12)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @brief   User button pin definitions
 * @{
 */
{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define PB0_PIN             GPIO_PIN(PB, 9)
        #define PB1_PIN             GPIO_PIN(PB, 10)
    {% elif board in ["stk3200"] %}
        #define PB0_PIN             GPIO_PIN(PC, 8)
        #define PB1_PIN             GPIO_PIN(PC, 9)
    {% elif board in ["slstk3401a"] %}
        #define PB0_PIN             GPIO_PIN(PF, 6)
        #define PB1_PIN             GPIO_PIN(PF, 7)
    {% elif board in ["slwstk6220a"] %}
        #define PB0_PIN             GPIO_PIN(PE, 3)
        #define PB1_PIN             GPIO_PIN(PE, 2)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @brief    LED pin definitions
 * @{
 */
{% strip 2 %}
    {% if board in ["stk3600", "stk3700", "stk3800"] %}
        #define LED0_PIN            GPIO_PIN(PE, 2)
        #define LED1_PIN            GPIO_PIN(PE, 3)
    {% elif board in ["stk3200"] %}
        #define LED0_PIN            GPIO_PIN(PC, 10)
        #define LED1_PIN            GPIO_PIN(PC, 11)
    {% elif board in ["slstk3401a"] %}
        #define LED0_PIN            GPIO_PIN(PF, 4)
        #define LED1_PIN            GPIO_PIN(PF, 5)
    {% elif board in ["slwstk6220a"] %}
        #define LED0_PIN            GPIO_PIN(PF, 6)
        #define LED1_PIN            GPIO_PIN(PF, 7)
    {% endif %}
{% endstrip %}
/** @} */

/**
 * @brief   Macros for controlling the on-board LEDs.
 * @{
 */
#define LED0_ON             gpio_set(LED0_PIN)
#define LED0_OFF            gpio_clear(LED0_PIN)
#define LED0_TOGGLE         gpio_toggle(LED0_PIN)
#define LED1_ON             gpio_set(LED1_PIN)
#define LED1_OFF            gpio_clear(LED1_PIN)
#define LED1_TOGGLE         gpio_toggle(LED1_PIN)

/* for compatability to other boards */
#define LED_GREEN_ON        LED1_ON
#define LED_GREEN_OFF       LED1_OFF
#define LED_GREEN_TOGGLE    LED1_TOGGLE
#define LED_ORANGE_ON       /* not available */
#define LED_ORANGE_OFF      /* not available */
#define LED_ORANGE_TOGGLE   /* not available */
#define LED_RED_ON          LED0_ON
#define LED_RED_OFF         LED0_OFF
#define LED_RED_TOGGLE      LED0_TOGGLE
/** @} */

{% strip 2, true %}
    {% if board in ["stk3200"] %}
        /**
         * @brief   Connection to the on-board Sharp Memory LCD (LS013B7DH03)
         * @{
         */
        #define DISP_SPI            (SPI_0)
        #define DISP_COM_PIN        GPIO_PIN(PE, 10)
        #define DISP_CS_PIN         GPIO_PIN(PE, 11)
        #define DISP_SELECT_PIN     GPIO_PIN(PA, 8)
        #define DISP_POWER_PIN      GPIO_PIN(PA, 10)
        /** @} */
    {% elif board in ["slstk3401a"] %}
        /**
         * @brief   Connection to the on-board Sharp Memory LCD (LS013B7DH03)
         * @{
         */
        #define DISP_SPI            (SPI_0)
        #define DISP_COM_PIN        GPIO_PIN(PE, 10)
        #define DISP_CS_PIN         GPIO_PIN(PE, 11)
        #define DISP_SELECT_PIN     GPIO_PIN(PA, 8)
        #define DISP_POWER_PIN      GPIO_PIN(PA, 10)
        /** @} */
    {% elif board in ["slwstk6220a"] %}
        /**
         * @brief   Connection to the on-board Sharp Memory LCD (LS013B7DH03)
         * @{
         */
        #define DISP_SPI            (SPI_0)
        #define DISP_COM_PIN        GPIO_PIN(PE, 10)
        #define DISP_CS_PIN         GPIO_PIN(PE, 11)
        #define DISP_SELECT_PIN     GPIO_PIN(PA, 8)
        #define DISP_POWER_PIN      GPIO_PIN(PA, 10)
        /** @} */
    {% endif %}
{% endstrip %}

{% strip 2, true %}
    {% if board in ["slstk3401a"] %}
        /**
         * @brief   Connection to the on-board temperature/humidity sensor (Si7021)
         * @{
         */
        #define SI7021_I2C          (I2C_0)
        #define SI7021_ADDR         (0x40)
        #define SI7021_EN_PIN       GPIO_PIN(PD, 9)
        /** @} */
    {% elif board in ["slwstk6220a"] %}
        /**
         * @brief   Connection to the on-board temperature/humidity sensor (Si7021)
         * @{
         */
        #define SI7021_I2C          (I2C_0)
        #define SI7021_ADDR         (0x40)
        #define SI7021_EN_PIN       GPIO_PIN(PF, 8)
        /** @} */
    {% endif %}
{% endstrip %}

/**
 * @brief Initialize board specific hardware, including clock, LEDs and stdio
 */
void board_init(void);

#ifdef __cplusplus
}
#endif

#endif /* BOARD_H */
/** @} */
