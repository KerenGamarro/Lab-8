#include "main.h"
#include "stm32f4xx_hal.h"

// EXTI callbacks para botones
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (semaforo_verde_flag == 0) // Corregido: sin acento
    {
        if (GPIO_Pin == jugador1_Pin)
        {
            uart_printf("Jugador 1 presionó antes del verde.\r\n");
        }
        else if (GPIO_Pin == jugador2_Pin)
        {
            uart_printf("Jugador 2 presionó antes del verde.\r\n");
        }
    }
    else
    {
        if (GPIO_Pin == jugador1_Pin)
        {
            uart_printf("Jugador 1 avanzó!\r\n");
        }
        else if (GPIO_Pin == jugador2_Pin)
        {
            uart_printf("Jugador 2 avanzó!\r\n");
        }
    }
}

// Interrupciones EXTI
void EXTI0_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(jugador1_Pin); }
void EXTI1_IRQHandler(void) { HAL_GPIO_EXTI_IRQHandler(jugador2_Pin); }

