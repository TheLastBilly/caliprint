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
    FILE * fp;
    for( size_t i = 0; i < list_size; i++ )
    {
        fp = fopen( file_list[i] , "r" );
        if(fp != NULL)
        {
            fclose(fp);
            return file_list[i];
        }
    }
    return NULL;
}

char * allocate_string( char * str )
{
    size_t len = strlen(str)+1;
    char * ptr = calloc( 1, sizeof(char) * (len+1) );
    snprintf( ptr, len, "%s", str );
    return ptr;
}

int int_to_baudrate( int baudrate )
{
    switch (baudrate)
    {
    case 9600:
        return B9600;
        break;
    case 19200:
        return B19200;
        break;
    case 57600:
        return B57600;
        break;
    case 115200:
        return B115200;
        break;
    default:
        return B115200;
        break;
    }
}

int baudrate_to_int( int baudrate )
{
    switch (baudrate)
    {
    case B9600:
        return 9600;
        break;
    case B19200:
        return 19200;
        break;
    case B57600:
        return 57600;
        break;
    case B115200:
        return 115200;
        break;
    default:
        return B115200;
        break;
    }
}