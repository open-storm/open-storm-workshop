#ifndef EXTERN_H
#define EXTERN_H
#include <project.h>

#define MODEM_BUFFER_LENGTH     1600

extern int depth_analog;
extern int depth_digital;
extern float v_bat;    
    
// Buffer for cell module
extern char modem_received_buffer[MODEM_BUFFER_LENGTH];

// SSL/TLS enabled?
extern uint8 ssl_enabled;
extern uint8 enable_ssl_config;
extern uint8 enable_ssl_sec_config;

// Sleeptimer
extern int sleeptimer; // Number of wakeups before full power: 1172 @ 256ms ~5 min

// Modem
// Number of attempts modem made while trying to establish a connection
extern int max_conn_attempts;
extern int connection_attempt_counter;
extern int rssi; 
extern int fer;

#endif
/* [] END OF FILE */
