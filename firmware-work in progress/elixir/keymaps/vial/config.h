#pragma once

#define VIAL_KEYBOARD_UID {0xF6, 0x85, 0xF5, 0x7F, 0xF3, 0xA9, 0xAB, 0x9D}

#define VIAL_UNLOCK_COMBO_ROWS { 1, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 11 }
#define DYNAMIC_KEYMAP_LAYER_COUNT 6

// Optimize combo processing to reduce CPU load
#define COMBO_TERM 40                  // Slightly faster combo timeout (default: 50ms)

// Tap Dance optimization
#define TAPPING_TERM 200               // Standard tapping term

// Additional performance optimizations for tap-hold keys
#define PERMISSIVE_HOLD                // Makes tap-hold more responsive
#define HOLD_ON_OTHER_KEY_PRESS        // Faster response for layer switching
#define TAP_CODE_DELAY 10              // Delay between tap code events


