#include <project.h>
#include "analog.h"

// Initialize variables
int depth_analog = -9999;  // Analog depth reading


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
        
        // Take distance reading
        depth_analog = take_analog_depth_reading();
                
        // Delay 1 second
        CyDelay(1000u);          
    }
}

/* [] END OF FILE */
