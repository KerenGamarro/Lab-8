#include "main.h"

// UART
UART_HandleTypeDef huart2;

// Flags
volatile uint8_t start_game_flag = 0;
volatile uint8_t semaforo_verde_flag = 0;

// Recepción UART
uint8_t rx;
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage */
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /** Initializes the RCC Oscillators according to the specified parameters */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
    {
        Error_Handler();
    }
}


int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();

    // Inicia recepción UART por interrupción
    HAL_UART_Receive_IT(&huart2, &rx, 1);

    uart_printf("Esperando comando 'S' para iniciar juego...\r\n");

    while (1)
    {
        if (start_game_flag)
        {
            start_game_flag = 0;

            // Semáforo: rojo -> amarillo -> verde
            HAL_GPIO_WritePin(SEMAFORO_GPIO_PORT, semaforo_rojo_Pin, GPIO_PIN_SET);
            HAL_Delay(1000);
            HAL_GPIO_WritePin(SEMAFORO_GPIO_PORT, semaforo_rojo_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(SEMAFORO_GPIO_PORT, semaforo_amarillo_Pin, GPIO_PIN_SET);
            HAL_Delay(1000);
            HAL_GPIO_WritePin(SEMAFORO_GPIO_PORT, semaforo_amarillo_Pin, GPIO_PIN_RESET);

            HAL_GPIO_WritePin(SEMAFORO_GPIO_PORT, semaforo_verde_Pin, GPIO_PIN_SET);
            semaforo_verde_flag = 1;
            HAL_Delay(1000);
            HAL_GPIO_WritePin(SEMAFORO_GPIO_PORT, semaforo_verde_Pin, GPIO_PIN_RESET);
            semaforo_verde_flag = 0;

            uart_printf("Semáforo terminado. Juego activo.\r\n");
        }
    }
}

void uart_printf(char *s)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)s, strlen(s), HAL_MAX_DELAY);
}

void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;

    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
        Error_Handler();
    }
}

void MX_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Semáforo
    GPIO_InitStruct.Pin = semaforo_rojo_Pin | semaforo_amarillo_Pin | semaforo_verde_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(SEMAFORO_GPIO_PORT, &GPIO_InitStruct);

    // Jugadores
    GPIO_InitStruct.Pin = jugador1_Pin | jugador2_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(JUGADOR_GPIO_PORT, &GPIO_InitStruct);
}

// Callback UART recepción
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (rx == 'S' || rx == 's')
        {
            start_game_flag = 1;
        }

        // Reactivar recepción UART por interrupción
        HAL_UART_Receive_IT(&huart2, &rx, 1);
    }
}

void Error_Handler(void)
{
    while(1)
    {
        // Se queda aquí si hay error
    }
}
