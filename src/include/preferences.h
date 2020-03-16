#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uinstd.h>

#include "utils.h"

typedef enum preferences_status
{
    NO_PREFERENCES_FILE_ERROR = 0x13,
    PREFERENCES_FILE_ACCESS_ERROR = 0x14,
    PREFERENCES_FILE_FORMAT_ERROR =  0x15,
    PREFERENCES_OK = 0x16,
} preferences_status;

typedef struct preferences_object
{
    const char * serial_port;
    int serial_baudrate;

    float
        printer_height,
        printer_width,
        printer_lenght;
    
    bool is_initialized;

    preferences_status status;
} preferences_object;

preferences_object * preferences_create_from_file( const char * file_path );
void preferences_free_object( preferences_object * preferences );

const char * preferences_get_serial_port( preferences_object * preferences );
int preferences_get_serial_baudrate( preferences_object * preferences );
int preferences_get_printer_height( preferences_object * preferences );
int preferences_get_printer_width( preferences_object * preferences );
int preferences_get_printer_lenght( preferences_object * preferences );

preferences_status preferences_get_status( preferences_object * preferences );