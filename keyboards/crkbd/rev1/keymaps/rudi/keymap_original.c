    /*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H
#include <stdio.h>

#define _QWERTY 0
#define _COLEMAK 1
#define _NUMLOCK 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 5

#define LOWER  LT(_LOWER, KC_ENT)
#define RAISE  LT(_RAISE, KC_ENT)
#define ADJUST MO(_ADJUST)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  NUMLOCK,
};

// Tap dance
enum {
    right_alt,
    right_space,
    left_tab,
};

typedef struct {
    bool is_press_action;
    uint8_t state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP
};

#define FAST_TYPE_WPM 45 //Switch to fast animation when over words per minute
#define LSHFT_E     LSFT_T(KC_TAB) // Left Shift when held, Tab when tapped
#define RR_SFT      RSFT_T(KC_ENT) // Right Shift when held, Enter when tapped

// Tap Dance
#define TD_RSPC     TD(right_space)
#define TT_RALT     TD(right_alt)
#define TD_LTAB     TD(left_tab)

uint8_t cur_dance(tap_dance_state_t *state);
void right_alt_finished(tap_dance_state_t *state, void *user_data);
void right_alt_reset(tap_dance_state_t *state, void *user_data);
void right_space_finished(tap_dance_state_t *state, void *user_data);
void right_space_reset(tap_dance_state_t *state, void *user_data);
void left_tab_finished(tap_dance_state_t *state, void *user_data);
void left_tab_reset(tap_dance_state_t *state, void *user_data);

//Oled screen off
void suspend_power_down_user(void) {
    oled_off();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LSHFT_E,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LTAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  RR_SFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LALT,   LOWER,  KC_SPC,                      TD_RSPC,   RAISE, TT_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LSHFT_E,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LTAB,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  RR_SFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LALT,   LOWER,  KC_SPC,                      TD_RSPC,   RAISE,  TT_RALT
                                      //`--------------------------'  `--------------------------'
  ),

    //Numlock/Browsing Layout
  [_NUMLOCK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LSHFT_E,    KC_1,    KC_2,    KC_3,    KC_4, KC_WH_U,                        KC_P7,   KC_P8,   KC_P9, KC_PDOT, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LTAB, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_WH_D,                        KC_P4,   KC_P5,   KC_P6, KC_PMNS, KC_PSLS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_CALC, KC_PGDN, KC_PGUP, KC_MYCM,  KC_NUM,                        KC_P1,   KC_P2,   KC_P3, KC_PPLS, KC_PAST, KC_PENT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_BTN1, KC_BTN2,  KC_ENT,                      TD_RSPC,   KC_P0,   QWERTY
                                      //`--------------------------'  `--------------------------'
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LSHFT_E, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LTAB,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_TRNS,  KC_ENT,                      TD_RSPC,  ADJUST, TT_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      LSHFT_E,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      TD_LTAB,    KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_HOME,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_F6,  KC_F7,   KC_F8,   KC_F9,  KC_F10,                       KC_F11,  KC_F12, KC_PGUP, KC_PGDN,  KC_END, KC_PSCR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LALT,  ADJUST,  KC_ENT,                      TD_RSPC, KC_TRNS, TT_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCAP, KC_CAPS,                      NUMLOCK,  QWERTY, COLEMAK, XXXXXXX,  KC_PWR, KC_SLEP,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      KC_MSEL, KC_PAUS, KC_SCRL, KC_BRID, KC_BRIU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, KC_CPNL,                      KC_MPLY, KC_MUTE, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_TRNS,  KC_ENT,                      TD_RSPC, KC_TRNS, TT_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
       case TD_RSPC:
           return true;
       default:
           return false;
   }
}
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD_RSPC:
            return TAPPING_TERM + 120;
        default:
            return TAPPING_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
        case RAISE:
        case RR_SFT:
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

static tap right_alt_tap_state, right_space_tap_state, left_tab_tap_state = {
    .is_press_action = true,
    .state = 0
};

// right_alt code
void right_alt_finished(tap_dance_state_t *state, void *user_data) {
    right_alt_tap_state.state = cur_dance(state);
    switch (right_alt_tap_state.state) {
        case SINGLE_TAP: register_code(KC_RGUI); break;
        case SINGLE_HOLD: register_code(KC_RALT); break;
        case DOUBLE_TAP: register_code(KC_DEL); break;
    }
}

void right_alt_reset(tap_dance_state_t *state, void *user_data) {
    switch (right_alt_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_RGUI); break;
        case SINGLE_HOLD: unregister_code(KC_RALT); break;
        case DOUBLE_TAP: unregister_code(KC_DEL); break;
    }
    right_alt_tap_state.state = 0;
}

// right_space code
void right_space_finished(tap_dance_state_t *state, void *user_data) {
    right_space_tap_state.state = cur_dance(state);
    switch (right_space_tap_state.state) {
        case SINGLE_TAP: register_code(KC_SPC); break;
        case SINGLE_HOLD: register_code(KC_LGUI); break;
        case DOUBLE_TAP: register_code(KC_ESC); break;
    }
}

void right_space_reset(tap_dance_state_t *state, void *user_data) {
    switch (right_space_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_SPC); break;
        case SINGLE_HOLD: unregister_code(KC_LGUI); break;
        case DOUBLE_TAP: unregister_code(KC_ESC); break;
    }
    right_space_tap_state.state = 0;
}

// left_tab code
void left_tab_finished(tap_dance_state_t *state, void *user_data) {
    left_tab_tap_state.state = cur_dance(state);
    switch (left_tab_tap_state.state) {
        case SINGLE_TAP: register_code(KC_ESC); break;
        case SINGLE_HOLD: layer_on(_NUMLOCK); break;
        case DOUBLE_TAP: register_code(KC_CAPS); break;
    }
}

void left_tab_reset(tap_dance_state_t *state, void *user_data) {
    switch (left_tab_tap_state.state) {
        case SINGLE_TAP: unregister_code(KC_ESC); break;
        case SINGLE_HOLD: layer_off(_NUMLOCK); break;
        case DOUBLE_TAP: unregister_code(KC_CAPS); break;
    }
    left_tab_tap_state.state = 0;
}

tap_dance_action_t tap_dance_actions[] = {
    [right_alt] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_alt_finished, right_alt_reset),
    [right_space] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_space_finished, right_space_reset),
    [left_tab] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_tab_finished, left_tab_reset)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Colemak"), false);
            break;
        case _NUMLOCK:
            oled_write_ln_P(PSTR("Numlock"), false);
            break;
        case _LOWER:
            oled_write_ln_P(PSTR("Lower"), false);
            break;
        case _RAISE:
            oled_write_ln_P(PSTR("Raise"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 3);
    oled_write_P(PSTR(""), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAPS LOCK") : PSTR("         "), false);
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
        persistent_default_layer_set(1UL<<_QWERTY);
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed)
        persistent_default_layer_set(1UL<<_COLEMAK);
      return false;
      break;
    case NUMLOCK:
      if (record->event.pressed)
        persistent_default_layer_set(1UL<<_NUMLOCK);
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

// Powered by QMK
void oled_render_rudi(void) {
    oled_set_cursor(0, 1); // make it column 0 line 2 oled; kolom dihitung dari kiri ke kanan, line dihitung dari atas ke bawah
    oled_write_P(PSTR("Rudi Wijaya"), false);
}

// WPM counter code
void oled_render_speed(void) {
    oled_set_cursor(0, 2); // make it column 0 line 3 oled; kolom dihitung dari kiri ke kanan, line dihitung dari atas ke bawah
    oled_write_P(PSTR("WPM: "), false);
    oled_advance_char();
    oled_write_ln(get_u8_str(get_current_wpm(), '0'), false);
}

// New Logo
static void render_my_logo(void) {
  static const char PROGMEM my_logo[] = {
    // 'caligraphy', 128x32px
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x80, 0xe0, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x88, 0x8c, 0x9c, 0xb8, 0xb0, 
    0xf0, 0xe0, 0xc0, 0x80, 0x84, 0xbe, 0xfe, 0xff, 0xe1, 0x80, 0xc0, 0xe0, 0xe0, 0x70, 0x38, 0x0c, 
    0x0f, 0x07, 0x07, 0x27, 0xe7, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 
    0x00, 0x38, 0xff, 0x81, 0x00, 0x00, 0xe1, 0xe7, 0x83, 0x00, 0x00, 0xe0, 0xe0, 0xe0, 0xc0, 0xc0, 
    0xc0, 0x00, 0xfc, 0xfe, 0x8f, 0x8e, 0xce, 0xce, 0xce, 0x0e, 0x0c, 0xdc, 0xfc, 0x78, 0x38, 0x18, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xe0, 0xf0, 0xc0, 0x00, 0x00, 0xc0, 0xf8, 0x78, 
    0x38, 0x08, 0x00, 0x30, 0x30, 0x3e, 0xf8, 0xf0, 0xf0, 0x78, 0x78, 0xfc, 0xf6, 0xb3, 0x31, 0x31, 
    0x31, 0x30, 0x70, 0xf0, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf9, 0xfd, 0xb9, 0x39, 0x31, 
    0x31, 0x33, 0xf3, 0xf3, 0xc3, 0x83, 0x83, 0x8f, 0x1f, 0xff, 0xf3, 0x73, 0x67, 0x66, 0x66, 0x66, 
    0x66, 0x64, 0xe4, 0xc4, 0xc6, 0xc7, 0xc7, 0x87, 0x02, 0x00, 0x00, 0x04, 0x06, 0x07, 0x07, 0x03, 
    0x00, 0x00, 0x07, 0x1f, 0x7c, 0xf0, 0x01, 0x0f, 0x1f, 0x1c, 0x00, 0x03, 0x1f, 0x3c, 0x18, 0x1b, 
    0x1f, 0x0c, 0x01, 0x0f, 0x3f, 0xff, 0xf3, 0xe3, 0xef, 0xef, 0x6f, 0x63, 0x3f, 0x3e, 0x10, 0x00, 
    0x00, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x1f, 0x7f, 0x3f, 0x2f, 0x0f, 0x0f, 0x1b, 
    0x1a, 0x32, 0x62, 0x42, 0x02, 0x30, 0x3c, 0x7f, 0xf3, 0xf1, 0x78, 0xf8, 0xf1, 0xa3, 0x27, 0x26, 
    0x2c, 0x20, 0x20, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x03, 0x00, 
    0x00, 0x00, 0x00, 0x03, 0x07, 0x07, 0x01, 0x01, 0x03, 0x03, 0x03, 0x06, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x08, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1f, 0x0c, 0x00, 0x01, 0x01, 0x02, 
    0x06, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  oled_write_raw_P(my_logo, sizeof(my_logo));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_render_rudi();
        oled_render_speed();      
    } else {
        render_my_logo();
    }
    return false;
}

#endif // OLED_ENABLE
