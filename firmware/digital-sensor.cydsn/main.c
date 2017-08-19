#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <project.h>
#include "digital.h"

// Initialize variables
int depth_digital = -9999; // Digital depth reading


int main(void)
{
    // Enable global interrupts
    CyGlobalIntEnable;

    for(;;)
    {
        
        // Flash LED
        LED_Write(1u);
        CyDelay(100u);
        LED_Write(0u);
        
        // Take distance readings
        depth_digital = take_digital_depth_reading();
                
        // Delay 1 second
        CyDelay(1000u);
                      
    }
}

/* [] END OF FILE */
