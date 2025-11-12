/*
 * Copyright (c) 2025
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/init.h>
#include <zephyr/drivers/gpio.h>

static int board_init(void)
{
    return 0;
}

SYS_INIT(board_init, APPLICATION, CONFIG_APPLICATION_INIT_PRIORITY);
