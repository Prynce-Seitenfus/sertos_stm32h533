#include "profiler_port.h"
#include "stm32h533xx.h"

void profiler_port_init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0U;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

uint32_t profiler_port_ticks(void)
{
    return (uint32_t)DWT->CYCCNT;
}
