MOUSEKEY_ENABLE = yes    # Mouse keys
RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
TAP_DANCE_ENABLE = yes
WPM_ENABLE = yes
#to save space
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
MUSIC_ENABLE = no 
SPACE_CADET_ENABLE = no
CFLAGS += -flto
#to save space