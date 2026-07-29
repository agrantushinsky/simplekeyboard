#ifndef USB_HID_DESCRIPTORS_H
#define USB_HID_DESCRIPTORS_H

#include <stdint.h>

// ==========================================================================
// USB HID Keyboard Usage IDs (Page 0x07 - Keyboard/Keypad)
// ==========================================================================
#define KC_NO                   0x00
#define KC_ROLL_OVER            0x01
#define KC_POST_FAIL            0x02
#define KC_UNDEFINED            0x03
#define KC_A                    0x04
#define KC_B                    0x05
#define KC_C                    0x06
#define KC_D                    0x07
#define KC_E                    0x08
#define KC_F                    0x09
#define KC_G                    0x0A
#define KC_H                    0x0B
#define KC_I                    0x0C
#define KC_J                    0x0D
#define KC_K                    0x0E
#define KC_L                    0x0F
#define KC_M                    0x10
#define KC_N                    0x11
#define KC_O                    0x12
#define KC_P                    0x13
#define KC_Q                    0x14
#define KC_R                    0x15
#define KC_S                    0x16
#define KC_T                    0x17
#define KC_U                    0x18
#define KC_V                    0x19
#define KC_W                    0x1A
#define KC_X                    0x1B
#define KC_Y                    0x1C
#define KC_Z                    0x1D

// Numbers (Top Row)
#define KC_1                    0x1E
#define KC_2                    0x1F
#define KC_3                    0x20
#define KC_4                    0x21
#define KC_5                    0x22
#define KC_6                    0x23
#define KC_7                    0x24
#define KC_8                    0x25
#define KC_9                    0x26
#define KC_0                    0x27

// Control Keys
#define KC_ENTER                0x28
#define KC_ESCAPE               0x29
#define KC_BACKSPACE            0x2A
#define KC_TAB                  0x2B
#define KC_SPACE                0x2C
#define KC_MINUS                0x2D // - and _
#define KC_EQUAL                0x2E // = and +
#define KC_LEFT_BRACKET         0x2F // [ and {
#define KC_RIGHT_BRACKET        0x30 // ] and }
#define KC_BACKSLASH            0x31 // \ and |
#define KC_NONUS_HASH           0x32 // Non-US # and ~
#define KC_SEMICOLON            0x33 // ; and :
#define KC_APOSTROPHE           0x34 // ' and "
#define KC_GRAVE                0x35 // ` and ~
#define KC_COMMA                0x36 // , and <
#define KC_DOT                  0x37 // . and >
#define KC_SLASH                0x38 // / and ?
#define KC_CAPS_LOCK            0x39

// Function Keys
#define KC_F1                   0x3A
#define KC_F2                   0x3B
#define KC_F3                   0x3C
#define KC_F4                   0x3D
#define KC_F5                   0x3E
#define KC_F6                   0x3F
#define KC_F7                   0x40
#define KC_F8                   0x41
#define KC_F9                   0x42
#define KC_F10                  0x43
#define KC_F11                  0x44
#define KC_F12                  0x45
#define KC_F13                  0x68
#define KC_F14                  0x69
#define KC_F15                  0x6A
#define KC_F16                  0x6B
#define KC_F17                  0x6C
#define KC_F18                  0x6D
#define KC_F19                  0x6E
#define KC_F20                  0x6F
#define KC_F21                  0x70
#define KC_F22                  0x71
#define KC_F23                  0x72
#define KC_F24                  0x73

// Navigation & Lock Keys
#define KC_PRINT_SCREEN         0x46
#define KC_SCROLL_LOCK          0x47
#define KC_PAUSE                0x48
#define KC_INSERT               0x49
#define KC_HOME                 0x4A
#define KC_PAGE_UP              0x4B
#define KC_DELETE               0x4C
#define KC_END                  0x4D
#define KC_PAGE_DOWN            0x4E
#define KC_RIGHT                0x4F
#define KC_LEFT                 0x50
#define KC_DOWN                 0x51
#define KC_UP                   0x52

// Keypad
#define KC_NUM_LOCK             0x53
#define KC_KP_SLASH             0x54
#define KC_KP_ASTERISK          0x55
#define KC_KP_MINUS             0x56
#define KC_KP_PLUS              0x57
#define KC_KP_ENTER             0x58
#define KC_KP_1                 0x59
#define KC_KP_2                 0x5A
#define KC_KP_3                 0x5B
#define KC_KP_4                 0x5C
#define KC_KP_5                 0x5D
#define KC_KP_6                 0x5E
#define KC_KP_7                 0x5F
#define KC_KP_8                 0x60
#define KC_KP_9                 0x61
#define KC_KP_0                 0x62
#define KC_KP_DOT               0x63

// Modifier Keys
#define KC_LCTRL                0xE0
#define KC_LSHIFT               0xE1
#define KC_LALT                 0xE2
#define KC_LGUI                 0xE3
#define KC_RCTRL                0xE4
#define KC_RSHIFT               0xE5
#define KC_RALT                 0xE6
#define KC_RGUI                 0xE7

// ==========================================================================
// USB HID Consumer Control Usage IDs (Page 0x0C - Consumer Devices)
// ==========================================================================
#define MEDIA_KEY_NONE          0x0000
#define MEDIA_KEY_POWER         0x0030
#define MEDIA_KEY_RESET         0x0031
#define MEDIA_KEY_SLEEP         0x0032
#define MEDIA_KEY_RECORD        0x00B2
#define MEDIA_KEY_FAST_FORWARD  0x00B3
#define MEDIA_KEY_REWIND        0x00B4
#define MEDIA_KEY_NEXT_TRACK    0x00B5
#define MEDIA_KEY_PREV_TRACK    0x00B6
#define MEDIA_KEY_STOP          0x00B7
#define MEDIA_KEY_EJECT         0x00B8
#define MEDIA_KEY_PLAY_PAUSE    0x00CD
#define MEDIA_KEY_MUTE          0x00E2
#define MEDIA_KEY_VOLUME_UP     0x00E9
#define MEDIA_KEY_VOLUME_DOWN   0x00EA

// ==========================================================================
// HID Report Structures
// ==========================================================================
#define NKRO_KEY_COUNT          120
#define NKRO_REPORT_BYTES       (NKRO_KEY_COUNT / 8) // 15 Bytes

// NKRO Keyboard Report (Report ID 1) -> Total Size: 17 Bytes
typedef struct __attribute__((packed)) {
    uint8_t report_id;                    // Always 0x01
    uint8_t modifiers;                    // Bitmask: LCtrl..RGUI
    uint8_t key_bits[NKRO_REPORT_BYTES];  // Bitmask: 120 key states
} nkro_keyboard_report_t;

// Consumer Control / Media Report (Report ID 2) -> Total Size: 3 Bytes
typedef struct __attribute__((packed)) {
    uint8_t  report_id;                   // Always 0x02
    uint16_t usage_id;                    // 16-bit Media usage code
} media_report_t;

// ==========================================================================
// Combined USB HID Report Descriptor
// ==========================================================================
static const uint8_t composite_hid_report_descriptor[] = {
    // ----------------------------------------------------------------------
    // COLLECTION 1: NKRO Keyboard (Report ID 1)
    // ----------------------------------------------------------------------
    0x05, 0x01,        // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,        // USAGE (Keyboard)
    0xA1, 0x01,        // COLLECTION (Application)
    0x85, 0x01,        //   REPORT_ID (1)

    // Modifiers (8 bits: LCtrl -> RGui)
    0x05, 0x07,        //   USAGE_PAGE (Keyboard/Keypad)
    0x19, 0xE0,        //   USAGE_MINIMUM (0xE0 - Left Control)
    0x29, 0xE7,        //   USAGE_MAXIMUM (0xE7 - Right GUI)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x25, 0x01,        //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,        //   REPORT_SIZE (1 bit)
    0x95, 0x08,        //   REPORT_COUNT (8)
    0x81, 0x02,        //   INPUT (Data, Var, Abs)

    // NKRO Bitmap (120 bits / 15 bytes)
    0x05, 0x07,        //   USAGE_PAGE (Keyboard/Keypad)
    0x19, 0x00,        //   USAGE_MINIMUM (0x00)
    0x29, NKRO_KEY_COUNT - 1, // USAGE_MAXIMUM (119 / 0x77)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x25, 0x01,        //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,        //   REPORT_SIZE (1 bit)
    0x95, NKRO_KEY_COUNT,    // REPORT_COUNT (120)
    0x81, 0x02,        //   INPUT (Data, Var, Abs)
    0xC0,              // END_COLLECTION

    // ----------------------------------------------------------------------
    // COLLECTION 2: Consumer Controls / Media Keys (Report ID 2)
    // ----------------------------------------------------------------------
    0x05, 0x0C,        // USAGE_PAGE (Consumer Devices)
    0x09, 0x01,        // USAGE (Consumer Control)
    0xA1, 0x01,        // COLLECTION (Application)
    0x85, 0x02,        //   REPORT_ID (2)
    0x15, 0x00,        //   LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x03,  //   LOGICAL_MAXIMUM (0x03FF / 1023)
    0x19, 0x00,        //   USAGE_MINIMUM (0)
    0x26, 0xFF, 0x03,  //   USAGE_MAXIMUM (0x03FF)
    0x75, 0x10,        //   REPORT_SIZE (16 bits)
    0x95, 0x01,        //   REPORT_COUNT (1)
    0x81, 0x00,        //   INPUT (Data, Array, Abs)
    0xC0               // END_COLLECTION
};

#endif // USB_HID_DESCRIPTORS_H
