/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,          KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[1] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,          KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[2] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,          KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
[3] = LAYOUT( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,          KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)

};

/* Encoder */ 
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
    [2] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
    [3] = { ENCODER_CCW_CW(KC_NO, KC_NO) }
};

/* aRGB Configuration */

led_config_t g_led_config = { {
  // Key Matrix to LED Index
  {           NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  {      2,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  {      1,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  {      0,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED,   NO_LED },
  { NO_LED,   NO_LED,   NO_LED,                       NO_LED,                                 NO_LED,   NO_LED,   NO_LED }
}, {
  // LED Index to Physical Position
  { 0,  16 }, { 0,  8 }, { 0,  5 }
}, {
  // LED Index to Flag
  8, 8, 8
} };

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (layer_state_is (1)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 60, 15, 15);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 0, 0);
    }
    if (layer_state_is (2)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 15, 60, 15);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(1, 0, 0, 0);
    }
    if (layer_state_is (3)) {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 15, 15, 60);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 0);
    }
}