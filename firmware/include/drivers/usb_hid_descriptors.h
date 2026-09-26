#ifndef USB_HID_DESCRIPTORS_H
#define USB_HID_DESCRIPTORS_H

#include <stdint.h>

// ==========================================================================
// HID Report Structures
// ==========================================================================
#define NKRO_KEY_COUNT          120
#define NKRO_REPORT_BYTES       (NKRO_KEY_COUNT / 8) // 15 Bytes

// NKRO Keyboard Report (Report ID 1) -> Total Size: 17 Bytes
typedef struct __attribute__((packed)) {
    //uint8_t report_id;                    // Always 0x01
    uint8_t modifiers;                    // Bitmask: LCtrl..RGUI
    uint8_t key_bits[NKRO_REPORT_BYTES];  // Bitmask: 120 key states
} nkro_keyboard_report_t;

// Consumer Control / Media Report (Report ID 2) -> Total Size: 3 Bytes
typedef struct __attribute__((packed)) {
    //uint8_t  report_id;                   // Always 0x02
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
