/* Copyright 2019 Fate
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
#include QMK_KEYBOARD_H

enum arisu_layers {
  _QWERTY,
  _FN,
  _ADJUST
};


//Tap Dance 
typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};

enum {
    right_ctrl,
    left_caps,
};

#define TD_RCTL     TD(right_ctrl)
#define TD_LCAP     TD(left_caps)
#define LLGUI       GUI_T(KC_ESC) //hold Left GUI, Esc when tapped

uint8_t cur_dance(tap_dance_state_t *state);
void right_ctrl_finished(tap_dance_state_t *state, void *user_data);
void right_ctrl_reset(tap_dance_state_t *state, void *user_data);
void left_caps_finished(tap_dance_state_t *state, void *user_data);
void left_caps_reset(tap_dance_state_t *state, void *user_data);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Base */
     LLGUI,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSLS, KC_DEL,   \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_PGUP,  \
    TD_LCAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGDN,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                      KC_UP,          \
    KC_LCTL, KC_LALT,                 KC_SPC,   MO(1),            KC_SPC,   TD_RCTL,                                      KC_LEFT, KC_DOWN, KC_RGHT  \
  ),

  [_FN] = LAYOUT(
    _______, KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,  _______, _______, KC_HOME, \
    _______, KC_BTN1, KC_UP,   KC_BTN2, KC_WH_U, KC_PGUP,  _______,  _______, KC_SCRL, KC_PAUS, KC_PSCR,  _______, _______,  KC_DEL,           KC_END, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_D, KC_PGDN,  _______,  _______, _______, _______, _______,  _______, _______,                   _______, \
    _______, KC_LGUI, _______, _______, _______, _______,  _______,  _______, _______, _______,  KC_APP,  _______,                    _______,         \
    _______, _______,                            _______,  _______,           _______,   MO(2),                              _______, _______, _______ \
  ),

  [_ADJUST] = LAYOUT(
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WAKE, KC_SLEP, KC_HOME, \
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,           KC_END,  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY,                   KC_PWR,  \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_VOLU,          \
    _______, _______,                   _______, _______,                   _______, _______,                            KC_MPRV, KC_VOLD, KC_MNXT  \
  )
};

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_LCAP:
            // Immediately select the hold action when another key is pressed.
            return true;
        default:
            // Do not select the hold action when another key is pressed.
            return false;
    }
}

//Tap Dance setting
uint8_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    } else return DOUBLE_TAP;
    //} else if (state->count >= 2) {
    //    return DOUBLE_TAP;
    //}else return 8; // Magic number. At some point this method will expand to work for more presses
}

static tap right_ctrl_tap_state, left_caps_tap_state = {
    .is_press_action = true,
    .state = 0
};

// right_ctrl code
void right_ctrl_finished(tap_dance_state_t *state, void *user_data) {
    right_ctrl_tap_state.state = cur_dance(state);
    switch (right_ctrl_tap_state.state) {
        case SINGLE_TAP: register_code(KC_RGUI); break;
        case SINGLE_HOLD: register_code(KC_RCTL); break;
        // case DOUBLE_TAP: register_code(KC_DEL); break;
    }
}

void right_ctrl_reset(tap_dance_state_t *state, void *user_data) {
    switch (right_ctrl_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_RGUI); break;
        case SINGLE_HOLD: unregister_code(KC_RCTL); break;
        // case DOUBLE_TAP: unregister_code(KC_DEL); break;
    }
    right_ctrl_tap_state.state = 0;
}

// left_caps code
void left_caps_finished(tap_dance_state_t *state, void *user_data) {
    left_caps_tap_state.state = cur_dance(state);
    switch (left_caps_tap_state.state) {
        case SINGLE_TAP: register_code(KC_CAPS); break;
        case SINGLE_HOLD: layer_on(1); break;
        case DOUBLE_TAP: register_code(KC_MYCM); break;
    }
}

void left_caps_reset(tap_dance_state_t *state, void *user_data) {
    switch (left_caps_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_CAPS); break;
        case SINGLE_HOLD: layer_off(1); break;
        case DOUBLE_TAP: unregister_code(KC_MYCM); break;
    }
    left_caps_tap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [right_ctrl] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_ctrl_finished, right_ctrl_reset),
    [left_caps] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_caps_finished, left_caps_reset)
};