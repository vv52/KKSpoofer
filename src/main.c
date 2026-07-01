#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "pico/bootrom.h"
#include "pico/multicore.h"
#include "hardware/watchdog.h"
#include "pio_usb.h"
#include "tusb.h"
#include "bsp/board_api.h"
#include "include.h"

void core1_main() {
    sleep_ms(10);
    pio_usb_configuration_t config = PIO_USB_DEFAULT_CONFIG;
    config.pin_dp = 0; // GPIO 0

    tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &config);
    tuh_init(1);

    while (1) {
        tuh_task();
    }
}

int main() {
    set_sys_clock_khz(120000, true);

    multicore_launch_core1(core1_main);
    tud_init(0);

    while (1) {
        tud_task();
    }
}

void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len) {
    if (tud_hid_ready()) {
        tud_hid_report(0, report, len);
    }
    tuh_hid_receive_report(dev_addr, instance);
}
