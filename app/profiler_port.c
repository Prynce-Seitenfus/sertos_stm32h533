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
    return DWT->CYCCNT;
}

uint32_t profiler_port_enter_critical(void)
{
    uint32_t state = __get_PRIMASK();
    __disable_irq();
    return state;
}

void profiler_port_exit_critical(uint32_t state)
{
    __set_PRIMASK(state);
}
