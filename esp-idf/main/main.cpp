#include "esp_event.h"
#include "nvs_flash.h"

extern "C" void app_main(void) {
    // Initialize library to keep persistent data in flash storage
    ESP_ERROR_CHECK(nvs_flash_init());
    // Initialize event loop
    ESP_ERROR_CHECK(esp_event_loop_create_default());
}
