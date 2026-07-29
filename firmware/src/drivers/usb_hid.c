#include "tusb.h"
#include "drivers/usb_hid_descriptors.h"
#include <stdio.h>
#include <string.h>

// --------------------------------------------------------------------------
// Standard USB Device Descriptor
// --------------------------------------------------------------------------
tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200, // USB 2.0
    .bDeviceClass       = 0x00,
    .bDeviceSubClass    = 0x00,
    .bDeviceProtocol    = 0x00,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT_MAX_SIZE,

    .idVendor           = 0x1234, // Custom VID
    .idProduct          = 0x5678, // Custom PID
    .bcdDevice          = 0x0100,

    .iManufacturer      = 0x01,
    .iProduct           = 0x02,
    .iSerialNumber      = 0x03,

    .bNumConfigurations = 0x01
};

uint8_t const * tud_descriptor_device_cb(void) {
    return (uint8_t const *) &desc_device;
}

// --------------------------------------------------------------------------
// HID Report Descriptor Callback
// --------------------------------------------------------------------------
uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return composite_hid_report_descriptor;
}

// --------------------------------------------------------------------------
// Configuration Descriptor
// --------------------------------------------------------------------------
enum {
    ITF_NUM_HID,
    ITF_NUM_TOTAL
};

#define CONFIG_TOTAL_LEN  (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)
#define EPNUM_HID         0x81

uint8_t const desc_configuration[] = {
    // Config number, interface count, string index, total length, attribute, power in mA
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x00, 100),

    // Interface number, string index, protocol, report descriptor len, EP In & Size, Polling Interval
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, HID_ITF_PROTOCOL_NONE, sizeof(composite_hid_report_descriptor), EPNUM_HID, CFG_TUD_ENDPOINT_MAX_SIZE, 1)
};

uint8_t const * tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    return desc_configuration;
}

// --------------------------------------------------------------------------
// String Descriptors Callback
// --------------------------------------------------------------------------
// STM32F0 Hardware Unique ID Register Base Address
#define STM32_UUID_ADDR (0x1FFFF7AC)

// Buffer to store the formatted 24-character hex string + null terminator
static char serial_str[25];

// Helper to convert the 96-bit MCU UID to an ASCII Hex String
static void get_hardware_serial_string(void) {
    uint32_t *uuid = (uint32_t *)STM32_UUID_ADDR;
    
    // Formats the 3x 32-bit words into a 24-character hexadecimal string
    snprintf(serial_str, sizeof(serial_str), "%08X%08X%08X", 
             (unsigned int)uuid[0], 
             (unsigned int)uuid[1], 
             (unsigned int)uuid[2]);
}

// --------------------------------------------------------------------------
// String Descriptors Callback
// --------------------------------------------------------------------------
char const* string_desc_arr[] = {
    (const char[]) { 0x09, 0x04 }, // 0: English (0x0409)
    "agrantushinsky",
    "simplekeyboard",
    serial_str
};

static uint16_t _desc_str[32];

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    (void) langid;
    uint8_t chr_count;

    // Populate the hardware serial string dynamically on the first request
    if (serial_str[0] == '\0') {
        get_hardware_serial_string();
    }

    if (index == 0) {
        memcpy(&_desc_str[1], string_desc_arr[0], 2);
        chr_count = 1;
    } else {
        if (index >= sizeof(string_desc_arr)/sizeof(string_desc_arr[0])) return NULL;

        const char* str = string_desc_arr[index];
        chr_count = strlen(str);
        if (chr_count > 31) chr_count = 31;

        // Convert ASCII string to UTF-16LE for USB String Descriptor
        for (uint8_t i = 0; i < chr_count; i++) {
            _desc_str[1 + i] = str[i];
        }
    }

    // First byte is length in bytes, second byte is descriptor type (STRING = 0x03)
    _desc_str[0] = (uint16_t)((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));
    return _desc_str;
}

// --------------------------------------------------------------------------
// Mandatory HID GET/SET Report Callbacks
// --------------------------------------------------------------------------
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    (void) instance; (void) report_id; (void) report_type; (void) buffer; (void) reqlen;
    return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    (void) instance; (void) report_id; (void) report_type; (void) buffer; (void) bufsize;
}
