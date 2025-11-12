# Copyright (c) 2025
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nice_nano_v2_keyboard)

# Add application source files
target_sources(app PRIVATE
    app/src/layout.c
)

# Add board files
target_sources(app PRIVATE
    app/boards/arm/nice_nano_v2/board.c
)
