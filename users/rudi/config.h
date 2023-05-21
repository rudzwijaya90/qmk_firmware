#pragma once

//#define USE_MATRIX_I2C

// #define QUICK_TAP_TERM 70 // 120 default value
#define TAPPING_TERM 170 // 200 default value | The tapping term defines for how long in milliseconds you need to hold a key before the tap becomes a hold
#define TAPPING_TERM_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define PREVENT_STUCK_MODIFIERS

// #define OLED_BRIGHTNESS 120
// #define OLED_TIMEOUT 100000 // in ms

#define MOUSEKEY_INTERVAL 5
#define MOUSEKEY_MAX_SPEED 6
#define MOUSEKEY_WHEEL_INTERVAL 100

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    // #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    // #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

//to save space for firmware https://docs.qmk.fm/#/squeezing_avr
#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define NO_ACTION_ONESHOT
//to save space for firmware

// #define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"