/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

static SemaphoreHandle_t xBinarySemaphore; // Global binary semaphore

void vTarefa1(void *pvParameters)
{
    while (1) {
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)) {
            printf("[Tarefa 1] Executou - Antonio RM 86639\n");

            vTaskDelay(pdMS_TO_TICKS(1000));    // Delay to slow down execution
            xSemaphoreGive(xBinarySemaphore);   // Release semaphore
            vTaskDelay(pdMS_TO_TICKS(50));      // Allow other tasks to acquire
        }
    }
}

void vTarefa2(void *pvParameters)
{
    while (1) {
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)) {
            printf("[Tarefa 2] Executou - Antonio RM 86639\n");

            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xBinarySemaphore);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void vTarefa3(void *pvParameters)
{
    while (1) {
        if (xSemaphoreTake(xBinarySemaphore, portMAX_DELAY)) {
            printf("[Tarefa 3] Executou - Antonio RM 86639\n");

            vTaskDelay(pdMS_TO_TICKS(1000));
            xSemaphoreGive(xBinarySemaphore);
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void app_main(void)
{
    // Create a binary semaphore
    xBinarySemaphore = xSemaphoreCreateBinary();

    if (xBinarySemaphore == NULL) {
        printf("Falha ao criar semáforo binário\n");
        return;
    }

    // Give the semaphore once at start so tasks can begin execution
    xSemaphoreGive(xBinarySemaphore);

    // Create tasks
    xTaskCreate(vTarefa1, "Tarefa1", 2048, NULL, 5, NULL);
    xTaskCreate(vTarefa2, "Tarefa2", 2048, NULL, 5, NULL);
    xTaskCreate(vTarefa3, "Tarefa3", 2048, NULL, 5, NULL);
}
