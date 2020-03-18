#include "include/utils.h"

char * get_time( char * str )
{   
    time_t curr_time = time(NULL);
    struct tm * time_bd = localtime(&curr_time);

    snprintf( 
        str,
        12,
        "[%02d:%02d:%02d] ",
        time_bd->tm_hour,
        time_bd->tm_min,
        time_bd->tm_sec
    );
    
    return str + 11;
}

bool check_for_file_access( const char * file )
{
    return access( file, F_OK ) == 1 ? false : true;
}

char * check_for_files( char * file_list[], size_t list_size )
{
    for( size_t i = 0; i < list_size; i++ )
    {
        if( check_for_file_access( file_list[i] ) )
            return file_list[i];
    }
    return NULL;
}

char * allocate_string( char * str )
{
    size_t len = strlen(str);
    char * ptr = calloc( 1, sizeof(char) * (len+1) );
    snprintf( ptr, len, "%s", str );
    return ptr;
}