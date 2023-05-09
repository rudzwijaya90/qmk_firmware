// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

<<<<<<< Updated upstream
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Base */
     LLGUI,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSLS, KC_DEL,   \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_PGUP,  \
    TD_LCAP, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGDN,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                      KC_UP,          \
    KC_LCTL,                KC_LALT,  KC_SPC,   MO(1),            KC_SPC,   TD_RCTL,                                      KC_LEFT, KC_DOWN, KC_RGHT  \
=======
enum layers {
  _QWERTY,
  _FN,
  _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT( /* Base */
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSLS, KC_DEL,   \
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,          KC_PGUP,  \
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGDN,  \
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                      KC_UP,          \
    KC_LCTL,                   KC_LALT, KC_SPC,  MO(1),            KC_SPC,   TD_RCTL,                                      KC_LEFT, KC_DOWN, KC_RGHT \
>>>>>>> Stashed changes
  ),

  [_FN] = LAYOUT(
    _______, KC_F1,   KC_F2,    KC_F3,    KC_F4,   KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,  KC_F12,  _______, _______, KC_HOME, \
    _______, KC_BTN1, KC_UP,   KC_BTN2, KC_WH_U, KC_PGUP,  _______,  _______, KC_SCRL, KC_PAUS, KC_PSCR,  _______, _______,  KC_DEL,           KC_END, \
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_WH_D, KC_PGDN,  _______,  _______, _______, _______, _______,  _______, _______,                   _______, \
    _______, KC_LGUI, _______, _______, _______, _______,  _______,  _______, _______, _______,  KC_APP,  _______,                    _______,         \
<<<<<<< Updated upstream
    _______,                   _______, _______, _______,            _______,   MO(2),                                       _______, _______, _______ \
  ),

  [_ADJUST] = LAYOUT(
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,           _______,  \
=======
    _______,                            _______, _______,  _______,           _______,   MO(2),                              _______, _______, _______ \
  ),

  [_ADJUST] = LAYOUT(
    QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_WAKE, KC_SLEP, _______, \
    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, \
>>>>>>> Stashed changes
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY,                   _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                   KC_VOLU,          \
    _______,                   _______, _______, _______,                   _______, _______,                            KC_MPRV, KC_VOLD, KC_MNXT  \
  )
};
