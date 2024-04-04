#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "features/custom_shift_keys.h"

// super alt-tab
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

#define LT1_ENTER  = LT(1,KC_ENTER);
#define LT1_DELETE = LT(1,KC_DELETE);
#define LT2_SPACE  = LT(2,KC_SPACE);
#define LT2_BSPC   = LT(2,KC_BSPC);

enum custom_keycodes {
  ALT_TAB   = SAFE_RANGE,
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
    TD(DANCE_0),             KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_LGUI,                      KC_PSCR,  KC_NO,   KC_NO,   KC_NO,   ALT_TAB, TD(DANCE_1),
    KC_TAB,                  DE_SCLN,  KC_COMM,  KC_DOT,   KC_P,     DE_Y,                         KC_F,     KC_G,    KC_C,    KC_R,    KC_L,    DE_SLSH,
    MT(MOD_LCTL, KC_ESCAPE), KC_A,     KC_O,     KC_E,     KC_U,     KC_I,                         KC_D,     KC_H,    KC_T,    KC_N,    KC_S,    MT(MOD_RCTL, DE_MINS),
    KC_LSFT,                 DE_QUOT,  KC_Q,     KC_J,     KC_K,     KC_X,                         KC_B,     KC_M,    KC_W,    KC_V,    DE_Z,    KC_RSFT,
                                                    LT2_BSPC,  LT1_DELETE,                        LT1_ENTER, LT2_SPACE
  ),
  [1] = LAYOUT_voyager(
    KC_F1,                   KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,                        KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_TRANSPARENT,          KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,                        KC_NO,    KC_7,    KC_8,    KC_9,    KC_NO,   KC_TRANSPARENT,
    KC_TRANSPARENT,          DE_ADIA,  DE_ODIA,  KC_NO,    DE_UDIA,  KC_NO,                        KC_NO,    KC_4,    KC_5,    KC_6,    DE_SS,   KC_TRANSPARENT,
    KC_TRANSPARENT,          KC_NO,    KC_NO,    KC_DOWN,  KC_UP,    KC_NO,                        KC_NO,    KC_1,    KC_2,    KC_3,    KC_NO,   KC_TRANSPARENT,
                                                    KC_LEFT,        KC_RIGHT,                   KC_TRANSPARENT, KC_0
  ),
  [2] = LAYOUT_voyager(
    RGB_TOG,                 KC_NO,    KC_NO,    KC_NO,    RGB_VAD,  RGB_VAI,                      KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_TRANSPARENT,          DE_DEG,   KC_NO,    KC_NO,    KC_NO,    DE_GRV,                       DE_AMPR,  DE_LBRC, DE_RBRC, DE_EURO, KC_NO,   KC_TRANSPARENT,
    KC_TRANSPARENT,          DE_CIRC,  DE_BSLS,  DE_PLUS,  DE_EQL,   DE_HASH,                      DE_PIPE,  DE_LPRN, DE_RPRN, DE_PERC, KC_NO,   KC_TRANSPARENT,
    KC_TRANSPARENT,          DE_SECT,  KC_NO,    DE_ASTR,  KC_NO,    KC_NO,                        DE_TILD,  DE_LCBR, DE_RCBR, DE_AT,   KC_NO,   KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,             KC_HOME,        KC_END
  ),
};


typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  tap_dance_action_t *action;

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
    case TD(DANCE_0):
    case TD(DANCE_1):
        action = &tap_dance_actions[TD_INDEX(keycode)];
        if (!record->event.pressed && action->state.count && !action->state.finished) {
            tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
            tap_code16(tap_hold->tap);
        }
  }
  return true;
}

void matrix_scan_user(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > 600) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

// config for "Hold On Other Key Press"
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT1_ENTER:
    case LT1_DELETE:
    case LT2_SPACE:
    case LT2_BSPC:
      // Immediately select the hold action when another key is pressed.
      return true;
    default:
      // Do not select the hold action when another key is pressed.
      return false;
  }
}

// taken from qmk docs (examples for tap-dance)
void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (state->pressed) {
        if (state->count == 1
#ifndef PERMISSIVE_HOLD
            && !state->interrupted
#endif
        ) {
            register_code16(tap_hold->hold);
            tap_hold->held = tap_hold->hold;
        } else {
            register_code16(tap_hold->tap);
            tap_hold->held = tap_hold->tap;
        }
    }
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

    if (tap_hold->held) {
        unregister_code16(tap_hold->held);
        tap_hold->held = 0;
    }
}

#define ACTION_TAP_DANCE_TAP_HOLD(tap, hold) \
    { .fn = {NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset}, .user_data = (void *)&((tap_dance_tap_hold_t){tap, hold, 0}), }

tap_dance_action_t tap_dance_actions[] = {
    [DANCE_0] = ACTION_TAP_DANCE_TAP_HOLD(DE_DLR, KC_LALT),
    [DANCE_1] = ACTION_TAP_DANCE_TAP_HOLD(DE_EXLM, KC_RALT),
};

extern rgb_config_t rgb_matrix_config;

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    float f = (float) rgb_matrix_config.hsv.v / UINT8_MAX;

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {

            uint8_t index = g_led_config.matrix_co[row][col];
            if (index >= led_min && index < led_max && index != NO_LED) {
                if (keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                  switch (layer) {
                    case 0:
                      rgb_matrix_set_color(index, 0, f * 128, f * 128);
                      break;
                    case 1:
                      rgb_matrix_set_color(index, 0, f * 255, f * 127);
                      break;
                    case 2:
                      rgb_matrix_set_color(index, f * 255, f * 255, f * 255);
                      break;
                  }
                } else {
                  rgb_matrix_set_color(index, 0, 0, 0);
                }
            }
        }
    }
    return false;
}
