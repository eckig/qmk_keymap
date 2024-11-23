# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
MOUSEKEY_ENABLE = no
RGB_MATRIX_CUSTOM_KB = no
SPACE_CADET_ENABLE = no
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = no
REPEAT_KEY_ENABLE = yes
SRC += features/custom_shift_keys.c
SRC += features/achordion.c
