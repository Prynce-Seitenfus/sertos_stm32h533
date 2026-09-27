#include "sertos_task_consumer.h"

#include "gpio.h"
#include "sertos_demo_queue.h"
#include "sertos_types.h"

void sertos_task_consumer(void* param)
{
    SertosDemoQueue* queue = (SertosDemoQueue*)param;
    SertosDemoQueueItem item;

    while (1) {
        if (sertos_demo_queue_receive(queue, &item, SERTOS_WAIT_FOREVER) == SERTOS_STATUS_OK) {
            gpio_set("A", "5", (item.value % 100U) < 50U);
        }
    }
}
