KEYBOARD_SHARED_EP = yes

CUSTOM_MATRIX = lite
SRC += analog.c matrix.c ec_switch_matrix.c

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes        # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
AUDIO_ENABLE = no           # Audio output
OLED_ENABLE = yes			# OLED
WPM_ENABLE = yes			# WPM for OLED count
LTO_ENABLE = yes			# LTO firmware optimisation
