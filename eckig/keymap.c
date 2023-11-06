#include QMK_KEYBOARD_H
#include "version.h"
#include "keymap_german.h"
#include "features/custom_shift_keys.h"

enum custom_keycodes {
  RGB_SLD = ML_SAFE_RANGE,
  HSV_0_255_255,
  HSV_74_255_255,
  HSV_169_255_255,
  DE_LSPO,
  DE_RSPC,
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
    DE_DLR,                  KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_TRANSPARENT,               TG(2),    KC_LALT,  KC_PSCR, KC_TRANSPARENT, KC_TRANSPARENT, DE_EXLM,
    MT(MOD_LGUI, KC_TAB),    DE_SCLN,  KC_COMM,  KC_DOT,   KC_P,     DE_Y,                         KC_F,     KC_G,     KC_C,    KC_R,           KC_L,           DE_SLSH,
    MT(MOD_LCTL, KC_ESCAPE), KC_A,     KC_O,     KC_E,     KC_U,     KC_I,                         KC_D,     KC_H,     KC_T,    KC_N,           KC_S,           MT(MOD_RCTL,DE_MINS),
    KC_LSFT,                 DE_QUOT,  KC_Q,     KC_J,     KC_K,     KC_X,                         KC_B,     KC_M,     KC_W,    KC_V,           DE_Z,           KC_RSFT,
                                                    LT(3,KC_BSPC), LT(1,KC_DELETE),                                 LT(1,KC_ENTER),       LT(3,KC_SPACE)
  ),
  [1] = LAYOUT_voyager(
    KC_F1,          KC_F2,              KC_F3,              KC_F4,          KC_F5,              KC_F6,                  KC_F7,          KC_F8,    KC_F9,    KC_F10,   KC_F11,         KC_F12,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,         KC_TRANSPARENT, KC_7,     KC_8,     KC_9,     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_TRANSPARENT, KC_UP,              KC_TRANSPARENT,         KC_TRANSPARENT, KC_4,     KC_5,     KC_6,     KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     KC_LEFT,        KC_DOWN,            KC_RIGHT,               KC_TRANSPARENT, KC_1,     KC_2,     KC_3,     KC_TRANSPARENT, KC_TRANSPARENT,
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_0
  ),
  [2] = LAYOUT_voyager(
    RGB_TOG,        TOGGLE_LAYER_COLOR, RGB_MOD,            RGB_SLD,        RGB_VAD,            RGB_VAI,                KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,          
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_AUDIO_VOL_DOWN,  KC_AUDIO_VOL_UP,KC_AUDIO_MUTE,      KC_TRANSPARENT,         KC_PGUP,        KC_HOME,        KC_UP,          KC_END,         KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,KC_MEDIA_NEXT_TRACK,KC_MEDIA_STOP,  KC_MEDIA_PLAY_PAUSE,KC_TRANSPARENT,         KC_PGDN,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,     HSV_0_255_255,  HSV_74_255_255,     HSV_169_255_255,        KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [3] = LAYOUT_voyager(
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      KC_TRANSPARENT, KC_TRANSPARENT,     KC_TRANSPARENT,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, DE_SS,             DE_ADIA,             DE_ODIA,        DE_UDIA,            DE_GRV,                 DE_AMPR,        DE_LBRC,        DE_RBRC,        DE_EURO,        KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, DE_CIRC,           DE_BSLS,             DE_PLUS,        DE_EQL,             DE_HASH,                DE_PIPE,        DE_LPRN,        DE_RPRN,        DE_PERC,        KC_TRANSPARENT, KC_TRANSPARENT, 
    KC_TRANSPARENT, KC_TRANSPARENT,    KC_TRANSPARENT,      DE_ASTR,        KC_TRANSPARENT,     KC_TRANSPARENT,         DE_TILD,        DE_LCBR,        DE_RCBR,        DE_AT,          KC_TRANSPARENT, KC_TRANSPARENT, 
                                                    KC_TRANSPARENT, KC_TRANSPARENT,                                 KC_TRANSPARENT, KC_TRANSPARENT
  ),
};


extern rgb_config_t rgb_matrix_config;

void keyboard_post_init_user(void) {
  rgb_matrix_enable();
}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [1] = { {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,255}, {169,255,255}, {169,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [2] = { {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {41,255,255}, {41,255,255}, {41,255,255}, {41,255,255}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

    [3] = { {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {0,0,0}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,84}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {0,0,0}, {0,0,0}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {0,0,0}, {0,0,0}, {169,255,84}, {169,255,84}, {169,255,84}, {169,255,84}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0} },

};

void set_layer_color(int layer) {
  for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
    HSV hsv = {
      .h = pgm_read_byte(&ledmap[layer][i][0]),
      .s = pgm_read_byte(&ledmap[layer][i][1]),
      .v = pgm_read_byte(&ledmap[layer][i][2]),
    };
    if (!hsv.h && !hsv.s && !hsv.v) {
        rgb_matrix_set_color( i, 0, 0, 0 );
    } else {
        RGB rgb = hsv_to_rgb( hsv );
        float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
        rgb_matrix_set_color( i, f * rgb.r, f * rgb.g, f * rgb.b );
    }
  }
}

void rgb_matrix_indicators_user(void) {
  if (keyboard_config.disable_layer_led) { return; }
  switch (biton32(layer_state)) {
    case 1:
      set_layer_color(1);
      break;
    case 2:
      set_layer_color(2);
      break;
    case 3:
      set_layer_color(3);
      break;
   default:
    if (rgb_matrix_get_flags() == LED_FLAG_NONE)
      rgb_matrix_set_color_all(0, 0, 0);
    break;
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!process_custom_shift_keys(keycode, record)) { return false; }

  switch (keycode) {
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
    case HSV_0_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(0,255,255);
      }
      return false;
    case HSV_74_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(74,255,255);
      }
      return false;
    case HSV_169_255_255:
      if (record->event.pressed) {
        rgblight_mode(1);
        rgblight_sethsv(169,255,255);
      }
      return false;
  }
  return true;
}

