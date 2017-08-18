#include "battery.h"

float32 read_vbat(){
	int32 reading;
	float32 v_bat;
	/* flip on the ADC pin */
	VBAT_READ_EN_Write(1u);
	CyDelay(100u);	
	/* Start the ADC */
	VBAT_ADC_Wakeup();
	VBAT_ADC_Start(); 
    
	/* Read the voltage */
    reading = VBAT_ADC_Read32();
	v_bat = 11.0 * VBAT_ADC_CountsTo_Volts(reading);
	/* Stop the conversion */
	VBAT_ADC_Sleep();
	/* flip off the ADC pin */
	VBAT_READ_EN_Write(0u);	
    
	return v_bat;
}

/* [] END OF FILE */
