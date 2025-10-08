#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f4xx_hal.h" // Incluye todo HAL
#include <stdint.h>
#include <string.h>

// UART
extern UART_HandleTypeDef huart2;

// LEDs semáforo
#define semaforo_rojo_Pin     GPIO_PIN_8
#define semaforo_amarillo_Pin GPIO_PIN_9
#define semaforo_verde_Pin    GPIO_PIN_10
#define SEMAFORO_GPIO_PORT    GPIOA

// Jugadores
#define jugador1_Pin GPIO_PIN_0
#define jugador2_Pin GPIO_PIN_1
#define JUGADOR_GPIO_PORT GPIOA

// Flags
extern volatile uint8_t start_game_flag;
extern volatile uint8_t semaforo_verde_flag;

// Prototipos
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void Error_Handler(void);
void uart_printf(char *s);

#endif /* __MAIN_H */
