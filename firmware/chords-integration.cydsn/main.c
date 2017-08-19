#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <project.h>
#include "modem.h"
#include "extern.h"
#include "analog.h"
#include "digital.h"
#include "battery.h"
#include "sleep.h"
#include "chords.h"

// Initialize variables
int depth_analog                   = -9999;         // Analog depth reading
int depth_digital                  = -9999;         // Digital depth reading
float v_bat                        = -9999;         // Battery voltage reading
uint8 status                       = 0u;            // Variable to indicate success/failure of command
int connection_attempt_counter     = 0u;            // Number of times 
uint8 awake                        = 1u;            // Variable that switches sleep mode on/off
int sleeptimer                     = 20;            // Number of wakeup cycles to wait in sleep mode
                                                    // 20 wakeups corresponds to 20*256 ms ~= 5 seconds

// Initialize buffers
char send_str[MAX_SEND_LENGTH]     = {'\0'};        // Buffer to store GET request
char response_str[MAX_RECV_LENGTH] = {'\0'};        // Buffer to store server response
char socket_dial_str[100]          = {'\0'};        // Buffer to store initial socket request to server

int main(void)
{
    // Enable global interrupts
    CyGlobalIntEnable;
    
    // Enable sleep mode
    initialize_sleeptimer();

    for(;;)
    {
        if (awake){
            // Flash LED
            LED_Write(1u);
            CyDelay(100u);
            LED_Write(0u);
        
            // Take distance readings
            depth_analog = take_analog_depth_reading();
            CyDelay(500u);
            depth_digital = take_digital_depth_reading();
        
            // Take battery voltage reading
            v_bat = read_vbat();
                
            // Delay 1 second
            CyDelay(1000u);
        
            // Start the modem
            if (modem_startup(&connection_attempt_counter)) {
            
                // Reset all arrays
                memset(send_str, '\0', sizeof(send_str));
                memset(response_str, '\0', sizeof(response_str));
                memset(socket_dial_str, '\0', sizeof(socket_dial_str));
            
                // First, open a TCP socket
                // The following function will generate a string of the following form:
                // AT#SD=1,0,80,”storm.chordsrt.com”,0,0,1
                status = modem_socket_dial(socket_dial_str, chords_endpoint, chords_port, 1, 0);
            
                // Format the request to the chords server. This function will format 'send_str' as follows:
                //
                //     GET /measurements/url_create?instrument_id=<1>&depth_analog=<2>&depth_digital=<3>&v_bat=<4> HTTP/1.1\r\n
                //     Host: your.chords.endpoint.here\r\n
                //     Connection: Close\r\n\r\n
                //
                status = format_chords_url(send_str, chords_endpoint, chords_port, instrument_id, 
                chords_write_key, write_key_enabled, is_test);
            
                // Send the data
                status = modem_send_recv(send_str, response_str, 0, 0);
            
                // Close the TCP socket
                modem_socket_close(0);
            
                // Shut down modem
                modem_shutdown();
            
            }
            
            // Tell device to go to sleep
            awake = 0u;
        }
        
        else {    
            // Put device into low power-sleep mode
            go_to_sleep(sleeptimer, &awake);
        }            
    }
}

/* [] END OF FILE */
