#pragma once

#include_next "mcuconf.h"

#undef STM32_ADC_USE_ADC1
#define STM32_ADC_USE_ADC1 TRUE

#undef STM32_PWM_USE_TIM2
#define STM32_PWM_USE_TIM2 TRUE

#undef STM32_ST_USE_TIMER
#define STM32_ST_USE_TIMER 5
