#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include <unistd.h>

#include <errno.h>
#include <fcntl.h> 
#include <string.h>
#include <termios.h>
#include <unistd.h>

#include <glib.h>
#include <glib/gprintf.h>

#define SERIAL_MAX_BUFFER 1000

extern int errno;

typedef enum serial_status
{
    NO_SERIAL_ERROR = 0x0b,
    SERIAL_PORT_OPEN_ERROR = 0x0c,
    SERIAL_PORT_ATTR_GET_ERROR = 0x0d,
    SERIAL_PORT_ATTR_SET_ERROR = 0x0e,
    SERIAL_SEND_ERROR = 0x0f,
    SERIAL_READ_ERROR = 0x10,
    NOT_CONNECTED = 0x11,
    SERIAL_OK = 0x12,
} serial_status;

typedef struct serial_driver 
{
    int socket;
    bool
        is_connected,
        should_block;
    char * port;
    char buffer[SERIAL_MAX_BUFFER];
    serial_status status;
    size_t buffer_size;
} serial_driver;

typedef enum serial_speed
{
    SP9600 = B9600,
    SP19200 = B19200,
    SP57600 = B57600,
    SP115200 = B115200,
} serial_speed;

serial_driver * serial_create_driver( const char * port, serial_speed speed, bool should_block );
void serial_free_driver( serial_driver * driver );

serial_status serial_printf( serial_driver * driver, char * format, ... );
serial_status serial_receive( serial_driver * driver );

serial_status serial_send( serial_driver * driver, char * str, size_t size );
serial_status serial_recv( serial_driver * driver, char * str, size_t size );

bool serial_is_connected( serial_driver * driver );
serial_status serial_get_status( serial_driver * driver );
const char * serial_get_port( serial_driver * driver );

const char * serial_get_buffer( serial_driver * driver, size_t * size );
