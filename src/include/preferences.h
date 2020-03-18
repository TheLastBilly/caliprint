#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define PREFERENCES_MAX_LINE 100

typedef enum preferences_status
{
    NO_PREFERENCES_FILE_ERROR = 0x13,
    PREFERENCES_FILE_ACCESS_ERROR = 0x14,
    PREFERENCES_NOT_INIT_ERROR = 0x15,
    PREFERENCES_OK = 0x16,
} preferences_status;

typedef struct preferences_object
{
    char 
        * serial_port,
        * file_path;
    int serial_baudrate;

    float
        printer_height,
        printer_width,
        printer_lenght,
        z_level;

    bool is_initialized;

    preferences_status status;
} preferences_object;

preferences_object * preferences_create_from_file( const char * file_path );
void preferences_free_object( preferences_object * preferences );

void preferences_change_serial_port( preferences_object * preferences, char * serial_port );

preferences_status preferences_save( preferences_object * preferences );

preferences_status preferences_get_status( preferences_object * preferences );
