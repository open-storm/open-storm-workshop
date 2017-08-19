#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <project.h>
#include "extern.h"
#include "analog.h"
#include "digital.h"
#include "battery.h"
#include "sleep.h"

// Initialize variables
int depth_analog                   = -9999;         // Analog depth reading
int depth_digital                  = -9999;         // Digital depth reading
float v_bat                        = -9999;         // Battery voltage reading
uint8 awake                        = 1u;            // Variable that switches sleep mode on/off
int sleeptimer                     = 20;            // Number of wakeup cycles to wait in sleep mode                                                 // 20 wakeups corresponds to 20*256 ms ~= 5 seconds


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
