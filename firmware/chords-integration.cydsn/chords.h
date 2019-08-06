#include <device.h>

// Chords parameters
char  *chords_endpoint = "ec2-3-13-105-177.us-east-2.compute.amazonaws.com";   // Your CHORDS portal URL
int   chords_port = 80;                             // Port 80 for a standard webpage connection
char  *chords_write_key = "key";                    // Your key for writing to CHORDS
uint8 write_key_enabled = 1u;                       // Set to 1 if you want to require a key for write access
int   instrument_id = 1;                            // Your instrument id
uint8 is_test = 0u;

int format_chords_url(char *send_str, char *chords_endpoint, int chords_port, 
    int instrument_id, char *chords_write_key, uint8 write_key_enabled, uint8 is_test);

int format_chords_url_general(char *send_str, char *labels[], float readings[],
                        int nvars, char *chords_endpoint, int chords_port,
                        int instrument_id, char *chords_write_key,
                        uint8 write_key_enabled, uint8 is_test);

/* [] END OF FILE */
