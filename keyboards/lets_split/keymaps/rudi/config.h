/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

<<<<<<< HEAD
/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS
=======
#include "../../rev2/config.h"

/* Select hand configuration */
// #define MASTER_LEFT
// #define MASTER_RIGHT
#define EE_HANDS
>>>>>>> origin/rudi

#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define TAPPING_TERM 170
#define MOUSEKEY_INTERVAL 5
#define MOUSEKEY_MAX_SPEED 6
#define MOUSEKEY_WHEEL_INTERVAL 120

<<<<<<< HEAD

#ifdef RGBLIGHT_ENABLE

    #define RGBLIGHT_ANIMATIONS
    #undef RGBLED_NUM
    #define RGBLED_NUM (8*2)
    #define RGB_DI_PIN D3 /* ws2812 RGB LED */
    #undef RGBLED_SPLIT
    #define RGBLED_SPLIT { 8, 8 } 
    #undef RGBLIGHT_SPLIT
    #define RGBLIGHT_SPLIT

=======
#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 16
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17
// #define USE_SERIAL

#ifdef RGBLIGHT_ENABLE
>>>>>>> origin/rudi
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif
