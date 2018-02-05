/*
 * Copyright (C) 2015-2017 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_brd4162a
 * @{
 *
 * @file
 * @brief       Board specific implementations BRD4162A board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Bas Stottelaar <basstottelaar@gmail.com>
 *
 * @}
 */

#include "board.h"
#include "board_common.h"

#include "periph/gpio.h"

void board_init(void)
{
    /* initialize the CPU */
    cpu_init();

    /* perform common board initialization */
    board_common_init();
}
