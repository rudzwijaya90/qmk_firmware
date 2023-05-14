#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BL 0
#define _FL 1

enum tapstates {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
};

enum tapkeys {
  LCTLTD = 0,
  CPSLCK,
  LCSPC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BL: (Base Layer) Default Layer
   * ,----------------------------------------------------------------.
   * |Esc | 1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |~ ` |
   * |----------------------------------------------------------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |Del |
   * |----------------------------------------------------------------|
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgUp|
   * |----------------------------------------------------------------|
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|PgDn|
   * |----------------------------------------------------------------|
   * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
   * `----------------------------------------------------------------'
   *
   * Note: Shift + Esc = ~
   *       Win   + Esc = `
   *       Hold  + RShift = (
   *       Hold  + LShift = )
   */
[_BL] = LAYOUT_ansi(
  KC_GESC,    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS, KC_EQL, KC_BSPC,KC_GRV, \
  KC_TAB,  KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC, KC_RBRC,KC_BSLS,KC_DEL, \
  TD(CPSLCK), KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,         KC_ENT,KC_PGUP,  \
  KC_LSPO,         KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,   KC_RSPC,KC_UP,KC_PGDN, \
  TD(LCTLTD), KC_LGUI,KC_LALT,            KC_SPC,                    KC_RALT,MO(_FL),KC_RCTRL, KC_LEFT,KC_DOWN,KC_RGHT),

  /* Keymap _FL: Function Layer
   * ,----------------------------------------------------------------.
   * |   | F1|F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
   * |----------------------------------------------------------------|
   * |     |Hme|Up|End|PgUp|   |   |   |   |   |Prt|Scr|Pse|     |Hme |
   * |----------------------------------------------------------------|
   * |      |<- |Dn | ->|PgDn|  |<- |Dn |Up | ->|   |   |Task Mng|End |
   * |----------------------------------------------------------------|
   * |        |   |   |Bl-|BL |BL+|   |VU-|VU+|MUT|   |   McL|MsU|McR |
   * |----------------------------------------------------------------|
   * |    |    |    |       My PC           |   |   |    |MsL|MsD|MsR |
   * `----------------------------------------------------------------'
   */
[_FL] = LAYOUT_ansi(
  _______, KC_F1 ,KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL, KC_INS ,  \
  _______,KC_HOME, KC_UP,KC_END,KC_PGUP, _______,_______,_______,_______,_______,KC_PSCR, KC_SLCK, KC_PAUS, _______,KC_HOME, \
  _______,KC_LEFT,KC_DOWN,KC_RIGHT,KC_PGDN,_______,KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,_______,_______,LCTL(LALT(KC_DEL)),KC_END, \
  _______,_______,_______,BL_DEC, BL_TOGG,BL_INC, _______,KC_VOLD,KC_VOLU,KC_MUTE,_______,KC_BTN1, KC_MS_U, KC_BTN2, \
  _______,_______,_______,                TD(LCSPC),               _______,_______,_______,KC_MS_L,KC_MS_D, KC_MS_R),
};


int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  else return 3;
}

static int lctap_state;

void lc_finished (qk_tap_dance_state_t *state, void *user_data) {
  lctap_state = cur_dance(state);
  switch (lctap_state) {
    case SINGLE_TAP: register_mods(MOD_BIT(KC_LCTL));register_code(KC_T); break;
    case SINGLE_HOLD: register_code(KC_LCTL); break;
  }
}

void lc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lctap_state) {
    case SINGLE_TAP: unregister_code(KC_T);unregister_mods(MOD_BIT(KC_LCTL)); break;
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
  }
  lctap_state = 0;
}

static int ldtap_state;

void lx_finished (qk_tap_dance_state_t *state, void *user_data) {
  ldtap_state = cur_dance(state);
  switch (ldtap_state) {
    case SINGLE_TAP: register_code(KC_CAPS); break;
    case SINGLE_HOLD: layer_on(_FL); break;
  }
}

void lx_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ldtap_state) {
    case SINGLE_TAP: unregister_code(KC_CAPS); break;
    case SINGLE_HOLD: layer_off(_FL); break;
  }
  ldtap_state = 0;
}

static int lspctap_state;

void lspc_finished (qk_tap_dance_state_t *state, void *user_data) {
  lspctap_state = cur_dance(state);
  switch (lspctap_state) {
    case SINGLE_TAP: register_code(KC_MYCM); break;
    case DOUBLE_TAP: register_code(KC_ENT); break;
  }
}

void lspc_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lspctap_state) {
    case SINGLE_TAP: unregister_code(KC_MYCM); break;
    case DOUBLE_TAP: unregister_code(KC_ENT); break;
  }
  lspctap_state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [LCTLTD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,lc_finished, lc_reset),
  [CPSLCK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,lx_finished, lx_reset),
  [LCSPC]= ACTION_TAP_DANCE_FN_ADVANCED(NULL,lspc_finished, lspc_reset),
};