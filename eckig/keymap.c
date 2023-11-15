#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "features/custom_shift_keys.h"

// super alt-tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
  HSV_152_255_255,
  HSV_0_0_255,
};
enum tap_dance_codes {
  DANCE_0,
  DANCE_1,
};

// Custom shift keys, see "https://getreuer.info/posts/keyboards/custom-shift-keys/index.html"
const custom_shift_key_t custom_shift_keys[] = {
  {DE_SCLN, DE_COLN}, // ; :
  {KC_COMM, DE_LABK}, // , <
  {KC_DOT , DE_RABK}, // . >
  {DE_QUOT, DE_DQUO}, // ' "
  {DE_SLSH, DE_QUES}, // / ?
};
uint8_t NUM_CUSTOM_SHIFT_KEYS = sizeof(custom_shift_keys) / sizeof(custom_shift_key_t);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_voyager(
    TD(DANCE_0),             KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_LGUI,                                           KC_LALT,  KC_PSCR,         KC_TRANSPARENT, KC_TRANSPARENT, ALT_TAB, TD(DANCE_1),
    MT(MOD_LGUI, KC_TAB),    DE_SCLN,  KC_COMM,  KC_DOT,   KC_P,     DE_Y,                                              KC_F,     KC_G,            KC_C,           KC_R,           KC_L,    DE_SLSH,
    MT(MOD_LCTL, KC_ESCAPE), KC_A,     KC_O,     KC_E,     KC_U,     KC_I,                                              KC_D,     KC_H,            KC_T,           KC_N,           KC_S,    MT(MOD_RCTL, DE_MINS),
    KC_LSFT,                 DE_QUOT,  KC_Q,     KC_J,     KC_K,     KC_X,                                              KC_B,     KC_M,            KC_W,           KC_V,           DE_Z,    KC_RSFT,
                                                    LT(2,KC_BSPC), LT(1,KC_DELETE),                                 LT(1,KC_ENTER),       LT(2,KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_F1,          KC_F2,              KC_F3,              KC_F4,          KC_F5,              KC_F6,                  KC_F7,          KC_F8,    KC_F9,    KC_F10,   KC_F11,         KC_F12,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,         KC_TRANSPARENT, KC_7,     KC_8,     KC_9,     KC_RIGHT,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT,     KC_LEFT,                KC_TRANSPARENT, KC_4,     KC_5,     KC_6,     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_DOWN,        KC_UP,              KC_RIGHT,               KC_0,           KC_1,     KC_2,     KC_3,     KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_0
  ),
  [2] = LAYOUT_voyager(
    RGB_TOG,        KC_TRANSPARENT,    HSV_152_255_255,     HSV_0_0_255,    RGB_VAD,            RGB_VAI,                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_PGUP, 
    KC_TRANSPARENT, DE_SS,             DE_ADIA,             DE_ODIA,        DE_UDIA,            DE_GRV,                 DE_AMPR,        DE_LBRC,        DE_RBRC,        DE_EURO,        KC_TRANSPARENT, KC_PGDN, 
    KC_TRANSPARENT, DE_CIRC,           DE_BSLS,             DE_PLUS,        DE_EQL,             DE_HASH,                DE_PIPE,        DE_LPRN,        DE_RPRN,        DE_PERC,        KC_TRANSPARENT, KC_HOME, 
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      DE_ASTR,        KC_TRANSPARENT,     KC_TRANSPARENT,         DE_TILD,        DE_LCBR,        DE_RCBR,        DE_AT,          KC_TRANSPARENT, KC_END, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_custom_shift_keys(keycode, record)) { return false; }

  switch (keycode) {
    case ALT_TAB:
      if (record->event.pressed) {
        if (!is_alt_tab_active) {
          is_alt_tab_active = true;
          register_code(KC_LALT);
        }
        alt_tab_timer = timer_read();
        register_code(KC_TAB);
      } else {
        unregister_code(KC_TAB);
      }
      break;
    case HSV_152_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(152,255,255);
      }
      return false;
    case HSV_0_0_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,0,255);
      }
      return false;
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 750) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}



typedef struct {
    bool is_press_action;
    uint8_t step;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    DOUBLE_SINGLE_TAP,
    MORE_TAPS
};

static tap dance_state[2];

uint8_t dance_step(qk_tap_dance_state_t *state);

uint8_t dance_step(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    return MORE_TAPS;
}


void on_dance_0(qk_tap_dance_state_t *state, void *user_data);
void dance_0_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_0_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_0(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(DE_DLR);
        tap_code16(DE_DLR);
        tap_code16(DE_DLR);
    }
    if(state->count > 3) {
        tap_code16(DE_DLR);
    }
}

void dance_0_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[0].step = dance_step(state);
    switch (dance_state[0].step) {
        case SINGLE_TAP: register_code16(DE_DLR); break;
        case SINGLE_HOLD: register_code16(KC_LALT); break;
        case DOUBLE_TAP: register_code16(DE_DLR); register_code16(DE_DLR); break;
        case DOUBLE_SINGLE_TAP: tap_code16(DE_DLR); register_code16(DE_DLR);
    }
}

void dance_0_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[0].step) {
        case SINGLE_TAP: unregister_code16(DE_DLR); break;
        case SINGLE_HOLD: unregister_code16(KC_LALT); break;
        case DOUBLE_TAP: unregister_code16(DE_DLR); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(DE_DLR); break;
    }
    dance_state[0].step = 0;
}
void on_dance_1(qk_tap_dance_state_t *state, void *user_data);
void dance_1_finished(qk_tap_dance_state_t *state, void *user_data);
void dance_1_reset(qk_tap_dance_state_t *state, void *user_data);

void on_dance_1(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 3) {
        tap_code16(DE_EXLM);
        tap_code16(DE_EXLM);
        tap_code16(DE_EXLM);
    }
    if(state->count > 3) {
        tap_code16(DE_EXLM);
    }
}

void dance_1_finished(qk_tap_dance_state_t *state, void *user_data) {
    dance_state[1].step = dance_step(state);
    switch (dance_state[1].step) {
        case SINGLE_TAP: register_code16(DE_EXLM); break;
        case SINGLE_HOLD: register_code16(KC_RALT); break;
        case DOUBLE_TAP: register_code16(DE_EXLM); register_code16(DE_EXLM); break;
        case DOUBLE_SINGLE_TAP: tap_code16(DE_EXLM); register_code16(DE_EXLM);
    }
}

void dance_1_reset(qk_tap_dance_state_t *state, void *user_data) {
    wait_ms(10);
    switch (dance_state[1].step) {
        case SINGLE_TAP: unregister_code16(DE_EXLM); break;
        case SINGLE_HOLD: unregister_code16(KC_RALT); break;
        case DOUBLE_TAP: unregister_code16(DE_EXLM); break;
        case DOUBLE_SINGLE_TAP: unregister_code16(DE_EXLM); break;
    }
    dance_state[1].step = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
        [DANCE_0] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_0, dance_0_finished, dance_0_reset),
        [DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(on_dance_1, dance_1_finished, dance_1_reset),
};
