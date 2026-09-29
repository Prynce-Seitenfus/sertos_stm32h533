/**
 * @file sertos_app_config.h
 * @brief Application-level configuration overrides for SertOS on STM32H533.
 */

#ifndef SERTOS_APP_CONFIG_H
#define SERTOS_APP_CONFIG_H

#define SERTOS_CONFIG_MAX_PRIORITIES        (8U)
#define SERTOS_CONFIG_TICK_RATE_HZ          (1000U)
#define SERTOS_CONFIG_STACK_ALIGNMENT_BYTES (8U)
#define SERTOS_CONFIG_MINIMAL_STACK_SIZE    (256U)
#define SERTOS_CONFIG_TIME_SLICING          (1U)
#define SERTOS_CONFIG_ASSERT_ENABLED        (1U)

#endif /* SERTOS_APP_CONFIG_H */
