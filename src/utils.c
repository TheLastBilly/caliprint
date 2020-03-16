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