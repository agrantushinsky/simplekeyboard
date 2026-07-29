#ifndef TUSB_CONFIG_H_
#define TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

// ==========================================================================
// Board & Operating System Configuration
// ==========================================================================
#define CFG_TUSB_MCU                OPT_MCU_STM32F0
#define CFG_TUSB_OS                 OPT_OS_FREERTOS

/* Enabled USB Device Mode */
#define CFG_TUD_ENABLED             1

/* Full Speed / Low Speed Endpoint Buffer Size */
#define CFG_TUD_ENDPOINT_MAX_SIZE   64

// ==========================================================================
// Class Driver Configuration
// ==========================================================================
#define CFG_TUD_HID                 1
#define CFG_TUD_CDC                 0
#define CFG_TUD_MSC                 0

/* HID Endpoint Queue Sizes */
#define CFG_TUD_HID_EP_BUFSIZE      64

#ifdef __cplusplus
}
#endif

#endif /* TUSB_CONFIG_H_ */
