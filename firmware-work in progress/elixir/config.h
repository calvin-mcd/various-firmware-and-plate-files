/*
Copyright 2026 projectcain
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP18
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

// indicator led
#define RGB_DI_PIN GP18
#define RGB_MATRIX_DRIVER WS2812
#define RGBLED_NUM 1
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 255
#define RGBLIGHT_SLEEP  // Turn off LED when USB is suspended

#define LAYER_0_COLOR 0, 0, 255   // Blue
#define LAYER_1_COLOR 255, 128, 0 // Amber
#define LAYER_2_COLOR 0, 255, 0   // Green
#define LAYER_3_COLOR 255, 0, 0   // Red
#define LAYER_4_COLOR 0, 0, 255 // White
#define LAYER_5_COLOR 213, 255, 255 // Pink