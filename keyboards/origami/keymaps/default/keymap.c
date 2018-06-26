#include "origami.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_ADJ ADJUST
#define KC_RST RESET
#define KC_LOBS LT(_LOWER,KC_BSPC)
#define KC_RASC LT(_RAISE,KC_ESC)
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     TAB , Q  , W  , F  , P  , B  ,                J  , L  , U  , Y  ,NUHS,DEL ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     LOBS, A  , R  , S  , T  , G  ,                K  , N  , E  , I  , O  ,QUOT,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     RASC, Z  , X  , C  , D  , V  ,                M  , H  ,COMM,DOT ,SLSH,RALT,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                       LGUI, SPC ,               SFTENT,RCTL
  //                  `----+----+----'        `----+----+----'
  ),

  [_LOWER] = LAYOUT_kc(
    //|----+----+----+----+----+----|              |----+----+----+----+----+----|
       CAPS ,INS ,NUBS,RBRC,NUHS,DQUO,               RPRN,PGUP, UP ,PGDN,PSCR,HOME,
    //|----+----+----+----+----+----|              |----+----+----+----+----+----|
       LOBS,DEL ,SCLN,LBRC, LCTL,COLN,               LPRN,LEFT,DOWN,RGHT,BSPC,END ,
    //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
       F1  , F2 , F3  , F4 , F5 , F6 ,                F7 , F8 , F9 ,F10 ,F11 ,F12 ,
    //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                        UNDS,SFTENT,                 RCTL,RALT
    //                  `----+----+----'        `----+----+----'
    ),

  [_RAISE] = LAYOUT_kc(
    //|----+----+----+----+----+----|              |----+----+----+----+----+----|
       ESC ,GRV ,CRSEL,EXSEL,ALT_ERASE,    ,       VOLU, 7  , 8  , 9  ,MPRV,MNXT,
    //|----+----+----+----+----+----|              |----+----+----+----+----+----|
       ADJ,PPLS,PMNS,PAST,PSLS, EQL,               VOLD,  4 , 5  , 6  ,MPLY,MSTP,
    //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
       RASC,UNDO,CUT,COPY,PASTE,MENU,               MUTE,  1 , 2  , 3  ,RCTL,RALT,
    //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                             ,SFTENT,                   0,PDOT  
    //                  `----+----+----'        `----+----+----'
    ),

  [_ADJUST] = LAYOUT_kc(
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     RST ,    ,    ,    ,    ,    ,                   , P7 , P8 , P9 ,    ,    ,
  //|----+----+----+----+----+----|              |----+----+----+----+----+----|
     ADJ,    ,    ,    ,    ,    ,                   , P4 , P5 , P6 ,    ,    ,
  //|----+----+----+----+----+----+----.    ,----|----+----+----+----+----+----|
     RASC,    ,    ,    ,    ,    ,                   , P1 , P2 , P3 ,    ,    ,
  //`----+----+----+--+-+----+----+----/    \----+----+----+----+----+----+----'
                           ,     ,                 LCTL,LGUI
  //                  `----+----+----'        `----+----+----'
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
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
