#include "sertos_stm32h533.h"

#include <stdint.h>

#include "sertos_scheduler.h"
#include "sertos_queue.h"
#include "sertos_task.h"
#include "gpio.h"

#define SERTOS_DEMO_QUEUE_LENGTH       (8U)
#define SERTOS_DEMO_STACK_BYTES        (256U)
#define SERTOS_DEMO_QUEUE_ITEM_BYTES   (sizeof(uint32_t))

typedef struct SertosDemoQueueItem {
    uint32_t value;
} SertosDemoQueueItem;

static SertosQueue s_demo_queue;
static SertosQueueHandle s_demo_queue_handle;
static SertosDemoQueueItem s_demo_queue_storage[SERTOS_DEMO_QUEUE_LENGTH];

static uint8_t s_producer_stack[SERTOS_DEMO_STACK_BYTES]
    __attribute__((aligned(SERTOS_STACK_ALIGNMENT_BYTES)));
static uint8_t s_consumer_stack[SERTOS_DEMO_STACK_BYTES]
    __attribute__((aligned(SERTOS_STACK_ALIGNMENT_BYTES)));
static SertosTaskControlBlock s_producer_tcb;
static SertosTaskControlBlock s_consumer_tcb;
static SertosTaskHandle s_producer_handle;
static SertosTaskHandle s_consumer_handle;

static void sertos_task_producer(void *param)
{
    SertosDemoQueueItem item;
    static uint32_t seq = 0;
    uint8_t state = gpio_get("C", "13"); /* Read actual initial hardware state */
    uint8_t cnt = 0, paused = 0;
    (void)param;

    while (1) {
        uint8_t raw = gpio_get("C", "13");

        if (raw != state) {
            if (++cnt >= 4) {
                state = raw;
                cnt = 0;
                /* Active-low: toggle pause when pressed (0) */
                if (!state) paused ^= 1;
            }
        } else {
            cnt = 0;
        }

        if (!paused) {
            item.value = ++seq;
            sertos_queue_send(s_demo_queue_handle, &item, SERTOS_NO_WAIT);
        }

        sertos_scheduler_delay(10);
    }
}

static void sertos_task_consumer(void *param)
{
    SertosDemoQueueItem item;
    (void)param;

    while (1) {
        if (sertos_queue_receive(s_demo_queue_handle, &item, SERTOS_WAIT_FOREVER) == SERTOS_STATUS_OK) {
            /* 100 items = 1000 ms total: 0-49 ON (500 ms), 50-99 OFF (500 ms) */
            gpio_set("A", "5", (item.value % 100U) < 50U);
        }
    }
}

void sertos_init(void)
{
    SertosStatus status;
    SertosTaskConfig producer_cfg;
    SertosTaskConfig consumer_cfg;

    status = sertos_scheduler_init();
    if (status != SERTOS_STATUS_OK) {
        return;
    }

    status = sertos_queue_create_static(&s_demo_queue,
                                        s_demo_queue_storage,
                                        sizeof(s_demo_queue_storage),
                                        SERTOS_DEMO_QUEUE_ITEM_BYTES,
                                        &s_demo_queue_handle);
    if (status != SERTOS_STATUS_OK) {
        return;
    }

    producer_cfg.name = "sertos_task_producer";
    producer_cfg.entry_func = sertos_task_producer;
    producer_cfg.param = NULL;
    producer_cfg.priority = 3U;
    producer_cfg.stack_buffer = s_producer_stack;
    producer_cfg.stack_size = sizeof(s_producer_stack);

    consumer_cfg.name = "sertos_task_consumer";
    consumer_cfg.entry_func = sertos_task_consumer;
    consumer_cfg.param = NULL;
    consumer_cfg.priority = 2U;
    consumer_cfg.stack_buffer = s_consumer_stack;
    consumer_cfg.stack_size = sizeof(s_consumer_stack);

    status = sertos_task_create_static(&producer_cfg, &s_producer_tcb, &s_producer_handle);
    if (status != SERTOS_STATUS_OK) {
        return;
    }

    status = sertos_task_create_static(&consumer_cfg, &s_consumer_tcb, &s_consumer_handle);
    if (status != SERTOS_STATUS_OK) {
        return;
    }

    sertos_scheduler_start();
}
