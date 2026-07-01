//
// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// Licensed under MIT license - see https://opensource.org/licenses/MIT
//
#ifndef TUSB_CONFIG_H
#define TUSB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

// #define CFG_TUD_FLASH_XFER_BUFFER   1

#ifndef CFG_TUSB_MCU
#error CFG_TUSB_MCU must be defined
#endif

#ifndef BOARD_TUH_RHPORT
#define BOARD_TUH_RHPORT           1
#endif

#ifndef BOARD_DEVICE_RHPORT_NUM
#define BOARD_DEVICE_RHPORT_NUM    0
#endif

#ifndef BOARD_TUD_RHPORT
#define BOARD_TUD_RHPORT     0
#endif

#ifndef BOARD_TUD_MAX_SPEED
#define BOARD_TUD_MAX_SPEED  OPT_MODE_FULL_SPEED
#endif

#define CFG_TUD_MAX_SPEED    BOARD_TUD_MAX_SPEED

#define CFG_TUSB_RHPORT0_MODE   (OPT_MODE_DEVICE | BOARD_TUD_MAX_SPEED)

#ifndef CFG_TUSB_OS
#define CFG_TUSB_OS           OPT_OS_NONE
#endif

#ifdef CFG_TUSB_DEBUG
#undef CFG_TUSB_DEBUG
#endif
#define CFG_TUSB_DEBUG 0

#define CFG_TUD_ENABLED       1

#define CFG_TUD_ENDPOINT0_SIZE    64

#define CFG_TUD_VENDOR           1
#define CFG_TUD_VENDOR_EP_BUFSIZE  64
#define CFG_TUD_VENDOR_RX_BUFSIZE  64
#define CFG_TUD_VENDOR_TX_BUFSIZE  64

#define CFG_TUD_DFU_RT           0

#define CFG_TUD_CDC              0

#define CFG_TUD_MSC              0

#define CFG_TUD_MIDI             0

#define CFG_TUD_AUDIO            0

#define CFG_TUD_VIDEO            0

#define CFG_TUD_BTH              0

#ifdef __cplusplus
}
#endif

#define CFG_TUH_ENABLED          1

#define CFG_TUD_HID              1

#define CFG_TUH_HID              1

#define CFG_TUH_RPI_PIO_USB      1

#endif // TUSB_CONFIG_H
