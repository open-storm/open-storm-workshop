#include <project.h>
#include <stdlib.h>
#include "analog.h"

#define MAXBOTIX_V_RANGE 4.75
#define MAXBOTIX_RESOLUTION 5120

int take_analog_depth_reading(){
    // Initialize variables
    int16 adc_result = 0;
    float volt_reading = 0;
    int distance = -9999;
    
    // Initialize and start ADC
    ADC_SAR_1_Wakeup();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
    
    // Turn on sensor and delay briefly to let it settle
    Ultrasonic_Sensor_Power_Write(1u);
    CyDelay(500u);

    // If ADC has finished converting, get the result
    adc_result = ADC_SAR_1_GetResult16();
    // Convert the raw ADC reading to volts
    volt_reading = ADC_SAR_1_CountsTo_Volts(adc_result);
    distance = volt_reading * (MAXBOTIX_RESOLUTION / MAXBOTIX_V_RANGE);
    
    // Turn off sensor
    Ultrasonic_Sensor_Power_Write(0u);
    
    // Stop ADC conversion
    ADC_SAR_1_StartConvert();
    ADC_SAR_1_Sleep();
    
    return distance;
}

/* [] END OF FILE */