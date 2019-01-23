#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _SYMB 1
#define _NAV 2
#define _UMLAUTS 3
#define _ADJUST 4

enum custom_keycodes {
    DUMMY_CUST = SAFE_RANGE,
    // DO NOT CHANGE ANYTHING FROM HERE
            A_UML,
    O_UML,
    U_UML,
    S_UML
    // TO HERE
};

char *alt_codes[][2] = {
        { // ae
                SS_RALT(SS_TAP(X_KP_1)SS_TAP(X_KP_3)SS_TAP(X_KP_2)),
                SS_RALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_2)),
        },
        { // oe
                SS_RALT(SS_TAP(X_KP_1)SS_TAP(X_KP_4)SS_TAP(X_KP_8)),
                SS_RALT(SS_TAP(X_KP_1)SS_TAP(X_KP_5)SS_TAP(X_KP_3)),
        },
        { // ue
                SS_RALT(SS_TAP(X_KP_1)SS_TAP(X_KP_2)SS_TAP(X_KP_9)),
                SS_RALT(SS_TAP(X_KP_1)SS_TAP(X_KP_5)SS_TAP(X_KP_4)),
        },
        { // ss
                SS_RALT(SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_5)),
                SS_RALT(SS_TAP(X_KP_2)SS_TAP(X_KP_2)SS_TAP(X_KP_5)),
        },
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case A_UML:
            case O_UML:
            case U_UML:
            case S_UML: {
                uint16_t index = keycode - A_UML;
                uint8_t shift = get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT));

                // Temporarily disable Shift so it doesn't interfere with the numpad keys.
                unregister_code(KC_LSFT);
                unregister_code(KC_RSFT);

                // Choose Alt code based on which key was pressed and whether Shift was held.
                send_string(alt_codes[index][(bool) shift]);

                // Restore Shift keys to their previous state.
                if (shift & MOD_BIT(KC_LSFT)) register_code(KC_LSFT);
                if (shift & MOD_BIT(KC_RSFT)) register_code(KC_RSFT);
                return false;
            }
            default:
                return true;
        }
    }
    return true;
};


// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// some helper defininitions to make the assignment more readable

//alt when hold, otherwise the asterisk from numpad
#define ALT_AST LALT_T(KC_PAST)
//ctrl when pressed, slash otherwise
#define CTRL_SL LCTL_T(KC_PSLS)

#define KC_NAGR LT(_NAV, KC_GRV)
#define KC_NAMI LT(_NAV, KC_MINS)

#define KC_ALAS LALT_T(KC_PAST)
#define KC_CTPL LCTL_T(KC_PSLS)

#define KC_ADEN LT(_ADJUST, KC_END)
#define KC_ADPU LT(_ADJUST, KC_PGUP)

#define KC_BKSL KC_BSLASH
#define SYM_L   MO(_SYMB)

#define MEPREV KC_MEDIA_PREV_TRACK
#define MENEXT KC_MEDIA_NEXT_TRACK
#define MESTOP KC_MEDIA_STOP
#define MEPLPA KC_MEDIA_PLAY_PAUSE

//brackets when pressed shortly, otherwise ctrl
#define RBRCK_CTRL RCTL_T(KC_RBRC)
#define LBRCK_CTRL LCTL_T(KC_LBRACKET)

#define UML_MOD MO(_UMLAUTS)

// @formatter:off
const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,------------------------------------------------.            ,------------------------------------------------.
 * |`-Lyr2|   1  |   2  |   3  |   4  |   5  | Lyr1 |            | Lyr1 |   6  |   7  |   8  |   9  |   0  |--Lyr2|
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |  [   |            |   ]  |   Y  |   U  |   I  |   O  |   P  |   =  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  | PgUp |            | End  |   H  |   J  |   K  |   L  |   ;  |   '  |
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * |Shift(|   Z  |   X  |   C  |   V  |   B  | PgDn |            | Home |   N  |   M  |   ,  |   .  |   \  |Shift)|
 * |------+------+------+------+------+------+------|            |------+------+------+------+------+------+------|
 * |  Gui |   +  |   -  |*(Alt)|/(Ctr)|Bcksp | Del  |            |Enter |Space |  Alt | Left | Down |  Up  | Right|
 * `------------------------------------------------'            `------------------------------------------------'
 */

[_QWERTY] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
   KC_NAGR ,KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,                                            KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_NAMI ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_TAB  ,KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,SYM_L   ,                          SYM_L   ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,KC_EQL  ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_ESC  ,KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_LBRC ,                          KC_RBRC ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,KC_SCLN ,KC_QUOT ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   KC_LSFT ,KC_Z    ,KC_X    ,KC_C    ,KC_V    ,KC_B    ,KC_ADPU ,KC_PGDN ,        KC_HOME ,KC_ADEN ,KC_N    ,KC_M    ,KC_COMM ,KC_DOT  ,KC_BKSL ,KC_RSFT ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   KC_LGUI ,UML_MOD ,KC_BSLASH,ALT_AST,     CTRL_SL ,    KC_BSPC ,KC_DEL  ,        KC_ENT  ,KC_SPC  ,    KC_RALT ,     KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),


/* Symbols
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |      |      |      |  F6  |  F7  |  F8  |  F9  | F10  |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   !  |   @  |   {  |   }  |   |  |      |      |      |      |   7  |   8  |   9  | SysRq| Pause|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   #  |   $  |   [  |   ]  |   ~  |  Ins |      | Ins  |      |   4  |   5  |   6  | Appli| Print|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |   %  |   ^  |   (  |   )  |   `  |      |      |      |      |   1  |   2  |   3  |      | ScrLc|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |   0  |   0  |   .  |      | NumLc|
 * `------------------------------------------------'      `------------------------------------------------'
 */

[_SYMB] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
   _______ ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,KC_EXLM ,KC_AT   ,KC_LCBR ,KC_RCBR ,KC_PIPE ,_______ ,                          _______ ,KC_NLCK ,KC_KP_7 ,KC_KP_8 ,KC_KP_9 ,KC_SYSREQ,KC_PAUS,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,KC_HASH ,KC_DLR  ,KC_LBRC ,KC_RBRC ,KC_GRV  ,_______ ,                          _______ ,XXXXXXX ,KC_KP_4 ,KC_KP_5 ,KC_KP_6 ,KC_APP  ,KC_PSCR ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,KC_PERC ,KC_CIRC ,KC_LPRN ,KC_RPRN ,KC_TILD ,KC_INS  ,_______ ,        _______ ,KC_INS  ,XXXXXXX ,KC_KP_1 ,KC_KP_2 ,KC_KP_3 ,XXXXXXX ,KC_LSCR ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    KC_KP_0 ,     KC_KP_0 ,KC_PDOT ,XXXXXXX ,KC_NLCK
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),

/* Navigation
 * ,------------------------------------------------.      ,------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |  UP  |      |      |      |      |      |      |      |      |      |      |      |WH-UP |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      | LEFT | DOWN |RIGHT |      |      |      |      |      |      |M-LEFT|M-DOWN|M-RIGH| M-UP |WH-DWN|
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |      |      |      |      |      |MU-PRE|MU-NXT|      |L-CLCK|R-CLCK|      |      |      |      |      |
 * `------------------------------------------------'      `------------------------------------------------'
 */

[_NAV] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
   _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,XXXXXXX ,KC_UP   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_AUDIO_VOL_UP,                   _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,KC_WH_U ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,KC_LEFT ,KC_DOWN ,KC_RIGHT,XXXXXXX ,XXXXXXX ,KC_AUDIO_VOL_DOWN,                 _______ ,XXXXXXX ,KC_MS_L ,KC_MS_D ,KC_MS_U ,KC_MS_R ,KC_WH_D ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,MESTOP  ,MEPLPA  ,        _______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    MEPREV  ,MENEXT  ,        KC_BTN1 ,KC_BTN2 ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),

[_UMLAUTS] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
   _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,                                            _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,_______ ,KC_UP   ,_______ ,_______ ,_______ ,_______ ,                          _______ ,_______ ,U_UML   ,_______ ,O_UML   ,_______ ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,A_UML   ,S_UML   ,KC_RIGHT,_______ ,_______ ,_______ ,                          _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,        _______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,_______ ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   _______ ,_______ ,_______ ,_______ ,     _______ ,    _______ ,_______ ,        _______ ,_______ ,    _______ ,     _______ ,_______ ,_______ ,_______
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
),

[_ADJUST] = LAYOUT(
//┌────────┬────────┬────────┬────────┬────────┬────────┐                                           ┌────────┬────────┬────────┬────────┬────────┬────────┐
   XXXXXXX ,KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,                                            KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┐                         ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,RESET   ,RGB_M_P ,RGB_TOG ,RGB_MOD ,RGB_HUD ,RGB_HUI ,                          RGB_SAD ,RGB_SAI ,RGB_VAD ,RGB_VAI ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┤                         ├────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,                          XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┐       ┌────────┼────────┼────────┼────────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,_______ ,XXXXXXX ,        XXXXXXX ,_______ ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
//├────────┼────────┼────────┼────────┼────┬───┴────┬───┼────────┼────────┤       ├────────┼────────┼───┬────┴───┬────┼────────┼────────┼────────┼────────┤
   XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,     XXXXXXX ,    XXXXXXX ,XXXXXXX ,        XXXXXXX ,XXXXXXX ,    XXXXXXX ,     XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
//└────────┴────────┴────────┴────────┘    └────────┘   └────────┴────────┘       └────────┴────────┘   └────────┘    └────────┴────────┴────────┴────────┘
)

};

// @formatter:on

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
    eeconfig_update_default_layer(default_layer);
    default_layer_set(default_layer);
}

