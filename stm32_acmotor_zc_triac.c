#include "main.h"
#include <stdio.h>
#include <string.h>

ADC_HandleTypeDef hadc;
TIM_HandleTypeDef htim3;
UART_HandleTypeDef huart2;

// Global variables
volatile uint32_t zero_cross_detected = 0;
uint32_t pot_value = 0;
uint32_t rpm = 0;
char uart_buffer[100];  // UART buffer for printing

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    if (GPIO_Pin == GPIO_PIN_0) {  // Zero-crossing detected (H11AA1)
        zero_cross_detected = 1;
        
        // Calculate phase angle and delay based on potentiometer or RPM input
        uint32_t phase_angle = (pot_value * 180) / 4096;
        uint32_t delay_us = (phase_angle * 8333) / 180;  // Delay in microseconds
        
        // Print delay angle, delay time, and RPM over UART
        sprintf(uart_buffer, "Phase Angle: %lu degrees, Delay Time: %lu us, Motor Speed: %lu RPM\n", phase_angle, delay_us, rpm);
        HAL_UART_Transmit(&huart2, (uint8_t*)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
        
        // Start the timer to trigger Triac firing after delay
        HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, delay_us);  // Delay for phase control
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    char input[10];
    HAL_UART_Receive(&huart2, (uint8_t*)input, sizeof(input), HAL_MAX_DELAY);
    // Parse the RPM command received via UART
    sscanf(input, "%lu", &rpm);  // Convert received string to RPM value (0-1800)
    
    // Map the RPM value to a phase angle or potentiometer value
    if (rpm <= 1800) {
        pot_value = (rpm * 4096) / 1800;  // Map RPM to potentiometer value
    }
    
    // Acknowledge the received command
    sprintf(uart_buffer, "Received RPM command: %lu\n", rpm);
    HAL_UART_Transmit(&huart2, (uint8_t*)uart_buffer, strlen(uart_buffer), HAL_MAX_DELAY);
}

int main(void) {
    // HAL Initialization
    HAL_Init();
    
    // System clock configuration
    SystemClock_Config();
    
    // Initialize all configured peripherals
    MX_GPIO_Init();
    MX_ADC_Init();
    MX_TIM3_Init();
    MX_USART2_UART_Init();  // Ensure UART is initialized
    
    // Start ADC for potentiometer reading
    HAL_ADC_Start(&hadc);
    
    // Start receiving data via UART
    HAL_UART_Receive_IT(&huart2, (uint8_t*)&uart_buffer, sizeof(uart_buffer));
    
    // Main loop
    while (1) {
        if (zero_cross_detected) {
            zero_cross_detected = 0;  // Reset zero-crossing flag
            
            // Continuously update the motor speed if adjusted via potentiometer or UART
            pot_value = HAL_ADC_GetValue(&hadc);
        }
    }
}
