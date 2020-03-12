#include "include/serial.h"

serial_driver * serial_create_driver( const char * port, serial_speed speed, bool should_block )
{
    serial_driver * driver = (serial_driver *) calloc( 1, sizeof(serial_driver) );
    
    driver->is_connected = false;
    
    driver->socket = open( port, O_RDWR | O_NOCTTY | O_SYNC );
    if( driver->socket < 0 )
    {
        driver->status = SOCKET_OPEN_ERROR;
        return driver;
    }

    struct termios tty;
    if( tcgetattr( driver->socket, &tty ) != 0 )
    {
        driver->status = SOCKET_ATTR_GET_ERROR;
        return driver;
    }

    cfsetospeed( &tty, speed );
    cfsetispeed( &tty, speed );

    //Extracted from https://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty.c_iflag &= ~IGNBRK;         // disable break processing
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN] =                // read doesn't block
        should_block ? 1 : 0;
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;

    if( tcsetattr( driver->socket, TCSANOW, &tty ) != 0 )
    {
        driver->status = SOCKET_ATTR_SET_ERROR;
        return driver;
    }

    driver->port = (char *) malloc( strlen(port) + 1 );    //Copy port to driver
    sprintf( driver->port, "%s", port );

    driver->is_connected = true;
    driver->status = A_OK;
    
    return driver;
}

void serial_free_driver( serial_driver * driver )
{
    if(driver == NULL)
        return;

    if(driver->is_connected)
    {
        close( driver->socket );
        driver->port = 0;
    }

    if(driver->port != NULL)
        free( driver->port );
    
    free(driver);
}

serial_status serial_printf( serial_driver * driver, char * format, ... )
{
    if(!driver->is_connected)
        return NOT_CONNECTED;
    
    va_list arg;
    va_start( arg, format );
    
    static char buffer[SERIAL_MAX_BUFFER] = {0};

    vsnprintf(buffer, SERIAL_MAX_BUFFER, format, arg );

    return serial_send( driver, buffer, SERIAL_MAX_BUFFER );
}

serial_status serial_receive( serial_driver * driver )
{
    return serial_recv( driver, driver->buffer, SERIAL_MAX_BUFFER );
}

serial_status serial_send( serial_driver * driver, char * str, size_t size )
{
    if( !driver->is_connected )
        return NOT_CONNECTED;
    
    if( write( driver->socket, str, size ) < 0 )
    {
        return SEND_ERROR;
    }

    return A_OK;
}

serial_status serial_recv( serial_driver * driver, char * str, size_t size )
{
    if( !driver->is_connected )
        return NOT_CONNECTED;
    
    if( (driver->buffer_size = read( driver->socket, str, size )) < 0 )
    {
        if (
            errno == ECONNREFUSED || 
            errno == EBADF || 
            errno == EINTR || 
            errno == EINVAL || 
            errno == ENOTSOCK 
        )
        {
            if (
                errno != EAGAIN ||
                errno != EWOULDBLOCK
            )
            {
                return READ_ERROR;
            }

            return A_OK;
        }
    }
    
    return A_OK;
}

char * serial_get_buffer( serial_driver * driver, size_t * size )
{
    *size = driver->buffer_size; 
    return driver->buffer;
}