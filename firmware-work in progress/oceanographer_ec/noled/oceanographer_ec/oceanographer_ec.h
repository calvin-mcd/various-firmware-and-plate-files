#pragma once

#include "quantum.h"
#include "ec_switch_matrix.h"

#define XXX KC_NO

enum ec_keycodes {
    EC_AP_I = QK_KB_0,  // Increases actuation point (more travel)
    EC_AP_D,            // Decreases actuation point
    EC_CLR              // Reset EC config
};
