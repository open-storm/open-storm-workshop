#include <project.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Starts the sensors UART with generic interrupt service.
 */
void ultrasonic_uart_start();

/**
 * @brief Stops the sensors UART and generic interrupt service.
 */
void ultrasonic_uart_stop();

/**
 * @brief Get the uart received string.
 *
 * @return Pointer to the string in the buffer.
 */
char* ultrasonic_uart_get_string();

/**
 * @brief Get the size of the string in the buffer.
 *
 * @return Size of string in buffer.
 */
size_t ultrasonic_uart_get_string_size();

/**
 * @brief Clears internal buffer.
 */
void ultrasonic_uart_clear_string();

/**
 * @brief Parse UART string for depth measurement.
 */
int parse_maxbotix_string(const char *str);

/**
 * @brief Take depth reading and return measurement.
 */
int take_digital_depth_reading();

CY_ISR_PROTO(ISR_Ultrasonic_UART_RX);

/* [] END OF FILE */
