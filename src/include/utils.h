#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

// Stores the date as a string into a char array of size >= 12
char * get_time( char * str );

char * check_for_files( char * file_list[], size_t list_size );

bool check_for_file_access( const char * file );

char * allocate_string( char * str );

int int_to_baudrate( int baudrate );
int baudrate_to_int( int baudrate );