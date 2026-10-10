#include QMK_KEYBOARD_H

enum layers { NUM, ABC, XYZ };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [NUM] = LAYOUT(KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9),
    [ABC] = LAYOUT(KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I),
    [XYZ] = LAYOUT(KC_X, KC_Y, KC_Z, KC_Q, KC_R, KC_V, KC_S, KC_T, KC_U),
};

// Encoder 1 -> layer 1 (123456789), encoder 2 -> layer 2 (abcdefghi),
// encoder 3 -> layer 3 (xyzqrvstu). Either turning direction works.
bool encoder_update_user(uint8_t index, bool clockwise) {
    layer_move(index);
    return false;
}

// Board LEDs from the schematic: GP25 user LED, GP26/27/28 user RGB LED
#define LED_USER GP25
#define LED_R    GP26
#define LED_G    GP27
#define LED_B    GP28
#define ACTIVE   1   // set to 0 if the LEDs are wired active-low
#define SET(p, on) gpio_write_pin((p), (on) ? ACTIVE : !ACTIVE)

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(LED_USER); gpio_set_pin_output(LED_R);
    gpio_set_pin_output(LED_G);    gpio_set_pin_output(LED_B);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    static const uint8_t hue[] = {128, 85, 213};   // cyan, green, magenta
    uint8_t l = get_highest_layer(state);
    SET(LED_R, l == 2);              // layer 3 magenta = R+B
    SET(LED_G, l == 0 || l == 1);    // layer 1 cyan = G+B, layer 2 green = G
    SET(LED_B, l == 0 || l == 2);
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(hue[l], 255, 140);
    return state;
}

void keyboard_post_init_user(void) { layer_state_set_user(layer_state); }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    SET(LED_USER, record->event.pressed);
    return true;
}
