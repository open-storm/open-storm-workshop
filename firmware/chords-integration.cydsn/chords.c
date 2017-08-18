#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "modem.h"
#include "extern.h"

int format_chords_url(char *send_str, char *chords_endpoint, int chords_port, 
    int instrument_id, char *chords_write_key, uint8 write_key_enabled, uint8 is_test){
    // Construct chords url
    sprintf(send_str, "%s%s", send_str, "GET /measurements/url_create?");
    // Specify instrument id
    sprintf(send_str, "%sinstrument_id=%d", send_str, instrument_id);
    // Add depth and battery voltage measurements
    sprintf(send_str, "%s&depth_analog=%d", send_str, depth_analog);
    sprintf(send_str, "%s&depth_digital=%d", send_str, depth_digital);
    sprintf(send_str, "%s&v_bat=%f", send_str, v_bat);
    // Add key if needed
    if (write_key_enabled){
        sprintf(send_str, "%s&key=%s", send_str, chords_write_key);
    }
    // If this is a test measurement, append "&test"
    if (is_test){
        sprintf(send_str, "%s&test", send_str);
    }
            
    // Construct the full HTTP request
    // It should look like this:
    //     GET /measurements/url_create?instrument_id=... HTTP/1.1\r\n
    //     Host: your.chords.endpoint.here\r\n
    //     Connection: Close\r\n\r\n
    // Where "\r\n" is a carriage-return + line feed (essentially a line break)
    sprintf(send_str, "%s HTTP/1.1\r\n", send_str);
    sprintf(send_str,"%s%s%s%s%d%s%s",
            send_str,
            "Host: ", chords_endpoint, ":", chords_port, "\r\n",
            "Connection: Close\r\n\r\n");
    
    return 1u;
}

int format_chords_url_general(char *send_str, char *labels[], float readings[],
                        int nvars, char *chords_endpoint, int chords_port,
                        int instrument_id, char *chords_write_key,
                        uint8 write_key_enabled, uint8 is_test){
                            
    int i = 0; // iterator through labels and readings
    // Construct chords url
    sprintf(send_str, "%s%s", send_str, "GET measurements/url_create?");
    sprintf(send_str, "%sinstrument_id=%d", send_str, instrument_id);
    for (i = 0; i < nvars; i++){
	    if (labels[i] && labels[i][0]){
            sprintf(send_str, "%s&%s=%f", send_str,
                    labels[i], readings[i]);
			}
        }
    if (write_key_enabled){
        sprintf(send_str, "%s&key=%s", send_str, chords_write_key);
    }
    // If this is a test measurement, append "&test"
    if (is_test){
        sprintf(send_str, "%s&test", send_str);
    }
    
    sprintf(send_str, "%s HTTP/1.1\r\n", send_str);
    sprintf(send_str,"%s%s%s%s%d%s%s",
            send_str,
            "Host: ", chords_endpoint, ":", chords_port, "\r\n",
            "Connection: Close\r\n\r\n");
    
    return i;
}

/* [] END OF FILE */
