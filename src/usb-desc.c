//
// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// Licensed under MIT license - see https://opensource.org/licenses/MIT
//
#include "include.h"
#include "pico/stdlib.h"
#include "tusb.h"
#include "device/usbd.h"

tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0110,  // USB 1.1
    .bDeviceClass       = 0x03,
    .bDeviceSubClass    = 0x01,
    .bDeviceProtocol    = 0x01,
    .bMaxPacketSize0    = MAX_ENDPOINT0_SIZE,
    .idVendor           = SPOOFED_VID,
    .idProduct          = SPOOFED_PID,
    .bcdDevice          = 0x0100,
    .iManufacturer      = STRID_MANUFACTURER,
    .iProduct           = STRID_PRODUCT,
    .iSerialNumber      = STRID_SERIAL,
    .bNumConfigurations = 0x01
};

uint8_t const* tud_descriptor_device_cb(void) {
    return (uint8_t const *)&desc_device;
}

#define CONFIG_TOTAL_LEN (TUD_CONFIG_DESC_LEN + TUD_HID_DESC_LEN)

uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD()
};

uint8_t const * tud_hid_descriptor_report_cb(uint8_t instance) {
    (void) instance;
    return desc_hid_report;
}

static uint8_t desc_configuration[] = {
    TUD_CONFIG_DESCRIPTOR(1, ITF_NUM_TOTAL, 0, CONFIG_TOTAL_LEN, 0x80, 100),
    TUD_HID_DESCRIPTOR(ITF_NUM_HID, 0, true, sizeof(desc_hid_report), 0x81, 8, 10)
};

char const* string_desc_arr[] = {
    [STRID_LANGID]      = (const char[]) { 0x09, 0x04 },  // Supported language ID - English (US)
    [STRID_MANUFACTURER] = MANUFACTURER,
    [STRID_PRODUCT]      = PRODUCT,
    [STRID_SERIAL]       = SERIAL,
};

uint8_t const* tud_descriptor_configuration_cb(uint8_t index) {
    (void) index;
    return desc_configuration;
}

uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
    static uint16_t _desc_str[32 + 1];
    (void) langid;
    size_t chr_count;
    const char *str;

    switch (index) {
        case STRID_LANGID:
            memcpy(&_desc_str[1], string_desc_arr[0], 2);
            chr_count = 1;
            break;

        case STRID_SERIAL:
        case STRID_MANUFACTURER:
        case STRID_PRODUCT:
            str = string_desc_arr[index];
            chr_count = strlen(str);

            size_t const max_count = (sizeof(_desc_str) / sizeof(_desc_str[0])) - 1;
            if (chr_count > max_count) 
            {
                chr_count = max_count;
            }

            // Convert to UTF-16
            for (size_t ii = 0; ii < chr_count; ii++) {
                _desc_str[1 + ii] = str[ii];
            }
            break;
            
        default:
            return NULL;
    }

    // first byte is length (including header), second byte is string type
    _desc_str[0] = (uint16_t) ((TUSB_DESC_STRING << 8) | (2 * chr_count + 2));

    return _desc_str;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    (void) instance;
    (void) report_id;
    if (report_type == HID_REPORT_TYPE_OUTPUT) {
        if (bufsize >= 1) {
            uint8_t led_status = buffer[0];
            (void) led_status;
        }
    }
}

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;
    return 0;
}
