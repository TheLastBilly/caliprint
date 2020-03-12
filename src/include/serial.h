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

#define SERIAL_MAX_BUFFER 1000

extern int errno;

typedef enum serial_status
{
    IS_INIT,
    SOCKET_OPEN_ERROR,
    SOCKET_ATTR_GET_ERROR,
    SOCKET_ATTR_SET_ERROR,
    SEND_ERROR,
    READ_ERROR,
    NOT_CONNECTED,
    A_OK,
} serial_status;

typedef struct serial_driver 
{
    int socket;
    bool
        is_connected;
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

char * serial_get_buffer( serial_driver * driver, size_t * size );
