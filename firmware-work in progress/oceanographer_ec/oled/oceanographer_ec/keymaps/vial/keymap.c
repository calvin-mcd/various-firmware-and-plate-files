/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#include <stdio.h>
#include "os_detection.h"
#include "magic.h"

os_variant_t current_platform;
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum layer_names {
    _BASE, // Default Layer
    _FN, // Fn Layer 1
    _FN2, // Fn Layer 2
    _FN3 // Fn Layer 3
};

enum custom_keycode {
    JWRDL = QK_KB_0,
    JWRDR,
    SWRDL,
    SWRDR,
    TABL,
    TABR,
    DSKTPL,
    DSKTPR,
    PRVAPP,
    NXTAPP
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_HOME:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LGUI);
                tap_code(KC_LEFT);
                unregister_mods(MOD_LGUI);
            } else {
                tap_code(KC_HOME);
            }
            break;
        case KC_END:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LGUI);
                tap_code(KC_RIGHT);
                unregister_mods(MOD_LGUI);
            } else {
                tap_code(KC_END);
            }
            break;
        case KC_PGUP:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LGUI);
                tap_code(KC_UP);
                unregister_mods(MOD_LGUI);
            } else {
                tap_code(KC_PGUP);
            }
            break;
        case KC_PGDN:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LGUI);
                tap_code(KC_DOWN);
                unregister_mods(MOD_LGUI);
            } else {
                tap_code(KC_PGDN);
            }
            break;
        case KC_NUM_LOCK:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LSFT);
                tap_code(KC_CLEAR);
                unregister_mods(MOD_LSFT);
            } else {
                tap_code(KC_NUM_LOCK);
            }
            break;
        case KC_SCROLL_LOCK:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LCTL);
                tap_code(KC_F14);
                unregister_mods(MOD_LCTL);
            } else {
                tap_code(KC_SCROLL_LOCK);
            }
            break;
        case KC_PRINT_SCREEN:
            if (record->event.pressed && current_platform == OS_MACOS) {
                register_mods(MOD_LSFT);
                register_mods(MOD_LGUI);
                tap_code(KC_5);
                unregister_mods(MOD_LGUI);
                unregister_mods(MOD_LSFT);
            } else {
                tap_code(KC_PRINT_SCREEN);
            }
            break;
        case JWRDL:
            if (record->event.pressed) {
                (current_platform == OS_MACOS) ? register_mods(MOD_LALT) : register_mods(MOD_LCTL);
                tap_code(KC_LEFT);
                (current_platform == OS_MACOS) ? unregister_mods(MOD_LALT) : unregister_mods(MOD_LCTL);
            } else {
            }
            break;
        case JWRDR:
            if (record->event.pressed) {
                (current_platform == OS_MACOS) ? register_mods(MOD_LALT) : register_mods(MOD_LCTL);
                tap_code(KC_RIGHT);
                (current_platform == OS_MACOS) ? unregister_mods(MOD_LALT) : unregister_mods(MOD_LCTL);
            } else {
            }
            break;
        case SWRDL:
            if (record->event.pressed) {
                register_mods(MOD_LSFT);
                (current_platform == OS_MACOS) ? register_mods(MOD_LALT) : register_mods(MOD_LCTL);
                tap_code(KC_LEFT);
                (current_platform == OS_MACOS) ? unregister_mods(MOD_LALT) : unregister_mods(MOD_LCTL);
                unregister_mods(MOD_LSFT);
            } else {
            }
            break;
        case SWRDR:
            if (record->event.pressed) {
                register_mods(MOD_LSFT);
                (current_platform == OS_MACOS) ? register_mods(MOD_LALT) : register_mods(MOD_LCTL);
                tap_code(KC_RIGHT);
                (current_platform == OS_MACOS) ? unregister_mods(MOD_LALT) : unregister_mods(MOD_LCTL);
                unregister_mods(MOD_LSFT);
            } else {
            }
            break;
        case TABL:
            if (record->event.pressed) {
                register_mods(MOD_LCTL);
                register_mods(MOD_LSFT);
                tap_code(KC_TAB);
                unregister_mods(MOD_LSFT);
                unregister_mods(MOD_LCTL);
            } else {
            }
            break;
        case TABR:
            if (record->event.pressed) {
                register_mods(MOD_LCTL);
                tap_code(KC_TAB);
                unregister_mods(MOD_LCTL);
            } else {
            }
            break;
        case DSKTPL:
            if (record->event.pressed) {
                register_mods(MOD_LCTL);
                register_mods(MOD_LGUI);
                (current_platform == OS_LINUX) ? tap_code(KC_UP) : tap_code(KC_LEFT);
                unregister_mods(MOD_LGUI);
                unregister_mods(MOD_LCTL);
            } else {
            }
            break;
        case DSKTPR:
            if (record->event.pressed) {
                register_mods(MOD_LCTL);
                register_mods(MOD_LGUI);
                (current_platform == OS_LINUX) ? tap_code(KC_DOWN) : tap_code(KC_RGHT);
                unregister_mods(MOD_LGUI);
                unregister_mods(MOD_LCTL);
            } else {
            }
            break;
        case PRVAPP:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    (current_platform == OS_MACOS) ? register_code(KC_LGUI) : register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
                unregister_code(KC_LSFT);
            }
            break;
        case NXTAPP:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    (current_platform == OS_MACOS) ? register_code(KC_LGUI) : register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_big_bar( \
  KC_ESC,   KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,     KC_O,    KC_P,     KC_BSPC,  \
  KC_TAB,   KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,     KC_L,    KC_SLASH, KC_ENTER, \
  KC_LSFT,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMMA, KC_DOT,  KC_RSFT,  KC_UP, \
  KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                           KC_RALT,  KC_LEFT, KC_DOWN, KC_RIGHT, \
  KC_NO \
),
[1] = LAYOUT_big_bar( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_NO \
),
[2] = LAYOUT_big_bar( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_NO \
),
[3] = LAYOUT_big_bar( \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, \
  KC_NO \
)

};


void matrix_scan_user(void) { // The very important timer.
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            (current_platform == OS_MACOS) ? unregister_code(KC_LGUI) : unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

/* Encoder */
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
    [2] = { ENCODER_CCW_CW(KC_NO, KC_NO) },
    [3] = { ENCODER_CCW_CW(KC_NO, KC_NO) }
};
#endif

/* OLED */

#ifdef OLED_ENABLE
    #ifdef DYNAMIC_MACRO_ENABLE
        bool macro1;
        bool macro1rec;
        bool macro2;
        bool macro2rec;
        bool prevEnabled;
        uint8_t prevRGBmode;

        void render_dynamic_macro_status(int col, int line){
            oled_set_cursor(col,line);
            macro1rec ? oled_write(PSTR("DM1"), macro1) : oled_write(PSTR("      "),false);
            oled_set_cursor(col,line+1);
            macro2rec ? oled_write(PSTR("DM2"), macro2) : oled_write(PSTR("      "),false);
        }

    #endif

    bool clear_screen = false;
    bool rerender_platform = false;

    static void render_logo(void) {
        static const char PROGMEM logo[] = {
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
            0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
        };

        oled_write(logo, false);
    }

    void render_keylock_status(led_t led_state) {
        bool caps_state = (led_state.caps_lock || is_caps_word_on());
        oled_write(PSTR("CAPS"), caps_state);
        oled_write(PSTR(" "), false);
        oled_write(PSTR("NUM"), led_state.num_lock);
        oled_write(PSTR(" "), false);
        oled_write(PSTR("SCRL"), led_state.scroll_lock);
        //oled_write_ln_P(PSTR(" "), false);
    }

    void render_mod_status(uint8_t modifiers) {
        oled_write(PSTR("SH"), (modifiers & MOD_MASK_SHIFT));
        oled_write(PSTR(" "), false);
        (current_platform == OS_MACOS || current_platform == OS_IOS)  ? oled_write(PSTR("CMD"), (modifiers & MOD_MASK_GUI)) : oled_write(PSTR("CT"), (modifiers & MOD_MASK_CTRL));
        oled_write(PSTR(" "), false);
        (current_platform == OS_MACOS || current_platform == OS_IOS) ? oled_write(PSTR("OPT"), (modifiers & MOD_MASK_ALT)) : oled_write(PSTR("ALT"), (modifiers & MOD_MASK_ALT));
        oled_write(PSTR(" "), false);
        (current_platform == OS_MACOS || current_platform == OS_IOS) ? oled_write(PSTR("CT"), (modifiers & MOD_MASK_CTRL)) : oled_write(PSTR("GUI"), (modifiers & MOD_MASK_GUI));
    }

    void render_key_status_or_logo(){
        led_t led_state = host_keyboard_led_state();
        uint8_t mod_state = (get_mods()|get_oneshot_mods());
        if ( !led_state.num_lock && !led_state.caps_lock && !led_state.scroll_lock
        && !(mod_state & MOD_MASK_SHIFT) && !(mod_state & MOD_MASK_ALT) && !(mod_state & MOD_MASK_CTRL) && !(mod_state & MOD_MASK_GUI)) {
            if(!clear_screen) {
                render_logo();
                rerender_platform = true;
            }
            clear_screen = true;
        } else {
            if (clear_screen == true) {
                oled_clear();
                oled_render();
                clear_screen = false;
            }
            oled_set_cursor(8,0);
            render_keylock_status(led_state);
            oled_set_cursor(8,1);
            render_mod_status(mod_state);
            rerender_platform = true;
        }

    }

    void render_current_layer(){
        switch (get_highest_layer(layer_state)) {
                case 0:
                    oled_write(PSTR("Layer 0"), false);
                    break;
                case 1:
                    oled_write(PSTR("Layer 1"), false);
                    break;
                case 2:
                    oled_write(PSTR("Layer 2"), false);
                    break;
                case 3:
                    oled_write(PSTR("Layer 3"), false);
                    break;
                default:
                    oled_write(PSTR("Layer ?"), false);    // Should never display, here as a catchall
        }
    }

    void render_current_wpm(){
        oled_write_P(PSTR("WPM: "), false);
        oled_write(get_u8_str(get_current_wpm(), '0'), false);
    }

    void render_platform_status(int col, int line) {
        /* Show Ctrl-Gui Swap options */
        static const char PROGMEM logo[][5][3] = {
            {{0x9B, 0x9C, 0}, {0xbb, 0xbc, 0}}, //Android
            {{0x99, 0x9A, 0}, {0xb9, 0xba, 0}}, //Linux
            {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}}, //Windows
            {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}}, //Mac/iOS
            {{0x9D, 0x9E, 0}, {0xbd, 0xbe, 0}}, //Empty Placeholder
        };
        current_platform = detected_host_os();
        switch (current_platform) {
            /*case OS_ANDROID: //Android
                oled_set_cursor(col,line);
                oled_write(logo[0][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[0][1], false);
                break;*/
            case OS_LINUX: //Linux
                oled_set_cursor(col,line);
                oled_write(logo[1][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[1][1], false);
                keymap_config.swap_lctl_lgui = false;
                keymap_config.swap_rctl_rgui = false;
                break;
            case OS_WINDOWS: //Windows
                oled_set_cursor(col,line);
                oled_write(logo[2][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[2][1], false);
                keymap_config.swap_lctl_lgui = false;
                keymap_config.swap_rctl_rgui = false;
                break;
            case OS_MACOS: //Mac
                oled_set_cursor(col,line);
                oled_write(logo[3][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[3][1], false);
                keymap_config.swap_lctl_lgui = true;
                keymap_config.swap_rctl_rgui = true;
                break;
            case OS_IOS: //iOS
                oled_set_cursor(col,line);
                oled_write(logo[3][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[3][1], false);
                keymap_config.swap_lctl_lgui = true;
                keymap_config.swap_rctl_rgui = true;
                break;
            default: //OS_UNSURE or not configured
                oled_set_cursor(col,line);
                oled_write(logo[4][0], false);
                oled_set_cursor(col,line+1);
                oled_write(logo[4][1], false);
                break;
        }
        rerender_platform = false;
    }

    bool oled_task_user(void) {
        render_key_status_or_logo();
        oled_set_cursor(8,2);
        render_current_layer();
        #ifdef DYNAMIC_MACRO_ENABLE
            render_dynamic_macro_status(18,2);
        #endif
        oled_set_cursor(8,3);
        render_current_wpm();
        #ifdef OS_DETECTION_ENABLE
            if(current_platform != detected_host_os() || rerender_platform) { render_platform_status(3,0); }
        #endif

        return false;
    }

#endif
























/// OLD CODE MUST DELETE after using animation code


oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_90; }

void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("L1\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("L2\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("L3\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("LO\n"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
}

/*  LOGO */

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

bool oled_task_user(void) {
    render_logo();
    return false;
}

static const char PROGMEM animation[][512] = {
    // 'frame_00', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_01', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_02', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_03', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_04', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    
    },
    // 'frame_05', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    
    },
    // 'frame_06', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    
    },
    // 'frame_07', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
   
    },
    // 'frame_08', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,224,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_09', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_10', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,120, 24, 12, 12,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_11', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_12', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1,  1,  0,  0,  0,  0,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_13', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_14', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_15', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_16', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_17', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,224,192,128,  0,  0,  0,128,192,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,195,231,255,255,126,255,255,231,195,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,  7,243,241,  0,  0,  0,  1,  3,  7,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_18', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_19', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,224,192,128,  0,  0,  0,128,192,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,195,231,255,255,126,255,255,231,195,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,  7,243,241,  0,  0,  0,  1,  3,  7,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_20', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_21', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,224,192,128,  0,  0,  0,128,192,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,195,231,255,255,126,255,255,231,195,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,  7,243,241,  0,  0,  0,  1,  3,  7,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_22', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_23', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,224,224,192,128,  0,  0,  0,128,192,224,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,129,195,231,255,255,126,255,255,231,195,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,  7,243,241,  0,  0,  0,  1,  3,  7,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,207, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 60, 63,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,128,224,120, 24, 12, 12,  0,  0, 12, 12, 24, 56,240,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,120, 24,  1, 29, 60,112,224,192,  0,  0,128,128,192,224,121, 57,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,225,224,128,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 31, 28,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3, 15, 62, 56,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 28,252,224,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  3,  3,240,240,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0, 12, 15,  7,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_24', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_25', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_26', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_27', 32x128px
    {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_28', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,  0, 31, 15,  0,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_29', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 24, 24, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_30', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 24, 24, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_31', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7, 15, 15,  8,  8, 15, 15, 15, 12,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_32', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_33', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_34', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_35', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_36', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_37', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_38', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_39', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_40', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,252,  0,255,  0,159, 81,146, 10,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 72,212, 82, 81, 80, 80, 80, 80, 80, 80, 80, 79, 64,127, 64, 79, 80, 80, 81, 82,212, 72,  0,  0,  0,  0,  0,  0,  0,  0,  2,  4,  4,  4,  3,  2,  4,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  8,  4,  6,  3,  1,  2,  4,  4,  4,  2,  1,  2,  4,  4,
    },
    // 'frame_41', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    },
    // 'frame_42', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,  0,192,  0,192, 64,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,  0,255,  0,255,  0,231, 20, 36, 66,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64,146, 53, 84,148, 20, 20, 20, 20, 20, 20, 20, 19, 16, 31, 16, 19, 20, 20,148, 84, 53,146, 64,128,  0,  0,  0,128, 64,128,  0,  0,  0,  1,  1,  0,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  1,  0,  1,  1,  0,  0,  0,  1,  1,  1,  0,  0,  0,
    },
    // 'frame_43', 32x128px
    {
        0,  0,  0, 48,112,224,192,128,  0,128,128,192,192, 96,  0,252,254,  0, 96,192,192,128,128,  0,128,192,224,112, 48,  0,  0,  0,  0,  0,  0,  0,  0,  0,241,251,  7, 14, 29, 56,240,224, 16,223,223, 16,224,240, 56, 29, 14,  7,251,241,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,227,119, 56, 92,110,199,195,129,  2,254,254,  2,129,195,199,110, 92, 56,119,227,192,128,  0,  0,  0,  0,  0,  0,  0,  3,  3,  1,  0,  0,  0,  0,  0,  0,  0,  1,128,159,143,128,  1,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255,  0,  6,  7,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,255,255, 32, 63, 63, 62,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,135,143,152,152, 12,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,135,199, 98, 48,255,255,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 64, 71,207,207,200,136,207,207,207,140,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  1,  0,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  4,  7,  7,  7,  4,  0,  7,  7,  7,  4,  4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128, 64, 32, 16,  8,  4,  2,  1,254,  0,255,  0,207, 40, 68,133,  2,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,  0, 36,106,169, 40, 40, 40, 40, 40, 40, 40, 40, 39, 32, 63, 32, 39, 40, 40, 40,169,106,164,  0,  0,  0,  0,  0,128,  0,  0,  0,  1,  2,  2,  2,  1,  2,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  2,  1,  2,  1,  0,  1,  2,  2,  2,  1,  0,  1,  2,
    }
};

#endif
