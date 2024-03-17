/* Copyright 2023 sporkus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

// --- EC matrix user configuration ---
// Actuation/release threshold = idle + offset
// Larger offset = More key travel distance, less sensitive
// Sensitivity can be adjusted using keycode: EC_AP_I/EC_AP_D
#define ACTUATION_OFFSET 150
#define RELEASE_OFFSET 170
#define DEFAULT_IDLE 500      // default value before tuning is completed
#define ECSM_DEBUG         // enables printing ec config and ADC readings
#define EC_MATRIX            // allows ec code to be enabled with ifdef

// enables tuning ec config every power cycle, disable to reduce write cycle to flash
//#define ECSM_TUNE_ON_BOOT

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 12
#define EC_MATRIX_ROWS 4
#define EC_MATRIX_COLS MATRIX_COLS

/* Custom matrix pins and port select array */
#define EC_MATRIX_ROW_PINS \
    { B14, B15, B12, B13 }
#define EC_MATRIX_COL_CHANNELS \
    { \
       2, 1, 0, 3, 5, 4, \
       10, 9, 8, 11, 13, 12 \
    }

/* Hardware peripherals pins */
#define MUX_SEL_PINS \
    { B3, B4, B5 }

#define MUX_EN_PINS \
    { B1, B0 }

#define DISCHARGE_PIN A4
#define ANALOG_PORT A3

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
//#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// --- Persistent Storage config ---
// Data size is in bytes. uint16_t = 2 bytes
// data block size needs to be uint16_t array length * 2
// Two addition words for actuation offsets and one byte for configuration check
#define EECONFIG_KB_DATA_SIZE ((MATRIX_ROWS * MATRIX_COLS + 2) * 2 + 1)

// extra list of direct pins to read
#define EXTRA_SWITCHES 1                      // number of extra switches
#define EXTRA_SWITCH_ROW (MATRIX_ROWS - 1)    // the last row
#define EXTRA_SWITCH_PINS {A5}

// Oled
#define I2C_DRIVER I2CD1
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PIN B6


/* more arm config https://docs.qmk.fm/#/i2c_driver?id=arm-configuration
https://www.playembedded.org/blog/stm32-i2c-chibios/#8_I2Cv2_I2Cv3_configuration_structure */

#define OLED_BRIGHTNESS 255