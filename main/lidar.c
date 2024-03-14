
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"

static const int RX_BUF_SIZE = 1024;
#define HEADER 89

int dist; /*----actual distance measurements of LiDAR---*/
unsigned char check;        /*----save check value------------------------*/


#define RXD_PIN (GPIO_NUM_16)

void init(void)
{
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, UART_PIN_NO_CHANGE, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    while (1) {
        // Wait until data is available on UART 1
        int bytes_available = 0;
        while (!bytes_available) {
            uart_get_buffered_data_len(UART_NUM_1, (size_t*)&bytes_available);
            vTaskDelay(10 / portTICK_PERIOD_MS); // Set delau for 10 milliseconds
        }

        // Read the available data
        uint8_t data[9];
        const int rxBytes = uart_read_bytes(UART_NUM_1, data, sizeof(data), 100 / portTICK_PERIOD_MS);
        if (rxBytes == sizeof(data)) {
            // Check the first byte of the received data
            if (data[0] == HEADER) {
                // Calculate the check value
                check = 0;
                for (int i = 0; i < 8; i++) {
                    check += data[i];
                }
                // Verify the check value
                if (data[8] == check) {
                    // Extract the distance value
                    dist = data[2] + data[3] * 256;

                    // Print the distance value
                    ESP_LOGI(RX_TASK_TAG, "distance = %d", dist);
                }
            }
        }
        // Flush the UART buffer to clear any remaining data
        uart_flush_input(UART_NUM_1);
    }
}

void app_main(void)
{
    init();
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 2, NULL, configMAX_PRIORITIES - 1, NULL);
}
