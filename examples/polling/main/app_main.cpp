#include <freertos/FreeRTOS.h>
#include <iostream>
#include <nvs_flash.h>

#include "VL6180X.h"

/* config */
#define I2C_PORT I2C_NUM_0
#define PIN_SDA GPIO_NUM_21
#define PIN_SCL GPIO_NUM_22

#include "app_log.h"

extern "C" void app_main() {
  /* Boot Message */
  logi << "VL6180X" << std::endl;

  /* NVS flash initialization */
  nvs_flash_init();

  /* initialization */
  VL6180X vl(I2C_PORT);
  vl.i2cMasterInit(PIN_SDA, PIN_SCL);
  if (!vl.init()) {
    loge << "Failed to initialize VL6180X :(" << std::endl;
    vTaskDelay(portMAX_DELAY);
  }

  /* Main Loop */
  while (1) {
    /* measurement */
    uint16_t result_mm = 0;
    TickType_t tick_start = xTaskGetTickCount();
    bool res = vl.read(&result_mm);
    TickType_t tick_end = xTaskGetTickCount();
    int took_ms = pdTICKS_TO_MS((int)tick_end - tick_start);
    if (res)
      logi << "Range: " << (int)result_mm << " [mm]"
           << " took " << took_ms << " [ms]" << std::endl;
    else
      loge << "Failed to measure :(" << std::endl;
  }

  /* sleep forever */
  vTaskDelay(portMAX_DELAY);
}
