#include <device.h>

int format_chords_url(char *send_str, char *chords_endpoint, int chords_port, 
    int instrument_id, char *chords_write_key, uint8 write_key_enabled, uint8 is_test);

int format_chords_url_general(char *send_str, char *labels[], float readings[],
                        int nvars, char *chords_endpoint, int chords_port,
                        int instrument_id, char *chords_write_key,
                        uint8 write_key_enabled, uint8 is_test);

/* [] END OF FILE */
