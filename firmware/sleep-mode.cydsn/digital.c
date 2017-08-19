/**
 * @file digital.c
 * @brief Implements functions for maxbotix ultrasonic sensors
 * @author Brandon Wong, Matt Bartos, Ivan Mondragon, Alec Beljanski
 * @version TODO
 * @date 2017-06-19
 */

#include <stdlib.h>
#include <string.h>
#include "digital.h"
#include "strlib.h"

// The buffer and index are dependent on eachother. This buffer is implemented
// as a circular buffer to avoid overflow.
static char ultrasonic_uart_buf[257] = {'\0'};
static uint8_t buf_idx = 0u;

void ultrasonic_uart_start() {
    Ultrasonic_UART_Start();
    ISR_Ultrasonic_UART_RX_StartEx(ISR_Ultrasonic_UART_RX);
}

void ultrasonic_uart_stop() {
    ISR_Ultrasonic_UART_RX_Stop();
    Ultrasonic_UART_Stop();
}

char* ultrasonic_uart_get_string() { return ultrasonic_uart_buf; }

size_t ultrasonic_uart_get_string_size() {
    return buf_idx;  // equivalent to strlen(sensors_uart_buf)
}

void ultrasonic_uart_clear_string() {
    Ultrasonic_UART_ClearRxBuffer();
    memset(ultrasonic_uart_buf, '\0', sizeof(ultrasonic_uart_buf));
    buf_idx = 0u;
}

CY_ISR(ISR_Ultrasonic_UART_RX) {
    // hold the next char in the rx register as a temporary variable
    char rx_char = Ultrasonic_UART_GetChar();

    // store the char in sensors_uart_buf
    if (rx_char) {
        // unsigned ints don't `overflow`, they reset at 0 if they are
        // incremented one more than it's max value. It will be obvious if an
        // `overflow` occurs
        ultrasonic_uart_buf[buf_idx++] = rx_char;
    }
}


/**
 * @brief Parse raw UART received string from any maxbotix sensor into @p
 * reading.
 *
 * @param reading Structure to store results into. Depth in millimeters.
 * @param str Raw UART received string.
 */
int parse_maxbotix_string(const char *str) {
    // Expected model name in UART "PN:MB7384\r", or corresponding sensor
    // long range : 7383
    // short range: 7384

    // Expect the UART to contain something like "Sonar..copyright..
    // \rTempI\rR1478\rR1477\r..."
    char depth_str[5] = {'\0'};
    if (strextract(str, depth_str, "TempI\rR", "\r")) {
        int depth = strtod(depth_str, NULL);
        int valid = 0;

        char model[5] = {'\0'};
        strextract(str, model, "PN:MB", "\r");

        if (strcmp(model, "7384") == 0) {  // Short range sensor
            valid = strcmp(depth_str, "5000");
        } else if (strcmp(model, "7383") == 0) {  // Long range sensor
            valid = strcmp(depth_str, "9999");
        }
        if (!valid){
            return -9999;
        }
        return depth;
        
    } else {
        return -9999;
    }
}

// Start ISR, Fill array, Return array, Stop ISR
int take_digital_depth_reading() {
    int depth = -9999;
    
    ultrasonic_uart_clear_string();
    ultrasonic_uart_start();

    Ultrasonic_Sensor_Power_Write(1u);  // Power on the sensor
    CyDelay(800u);  // Wait for UART to get readings from sensor
    Ultrasonic_Sensor_Power_Write(0u);  // Power off the sensor

    ultrasonic_uart_stop();
    char *uart_string = ultrasonic_uart_get_string();
    depth = parse_maxbotix_string(uart_string);    

    return depth;
}

/* [] END OF FILE */
