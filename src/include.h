//
// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// Licensed under MIT license - see https://opensource.org/licenses/MIT
//
#define SPOOFED_VID 0x0510
#define SPOOFED_PID 0x0002

#define MAX_ENDPOINT0_SIZE  64
#define ENDPOINT_BULK_SIZE  64

#define MANUFACTURER  "KONAMI CPJ1"
#define PRODUCT       "USB JIS Mini Keyboard"
#define SERIAL        "0"

enum {
    STRID_LANGID = 0,
    STRID_MANUFACTURER,
    STRID_PRODUCT,
    STRID_SERIAL,
};

enum {
    ITF_NUM_HID = 0,
    ITF_NUM_TOTAL
};


#define INFO(fmt, ...) printf("core%d: " fmt "\n", get_core_num(), ##__VA_ARGS__)
#ifdef DEBUG
#define DEBUG(...)  INFO(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

#define LOG_INTERVAL_COUNT 5000000

