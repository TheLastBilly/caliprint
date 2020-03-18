#include "include/gui.h"

void gui_error_print_all( gui_context * context, const char * format, ... )
{
    va_list arg;
    va_start( arg, format );
    log_vprintf( context->control_log, format, arg );
    va_end( arg );
}

void gui_error_terminate( gui_context * context )
{
    gui_error_print_all( context, "Terminating...\n" );
    gui_end( context );
    gui_free_context( context );
    exit(1);
}

void gui_error_handle_and_set( gui_context * context, int status )
{
    if( context == NULL )
        return;
    gui_set_status( context, status );
    gui_error_handle( context );
}

void gui_error_handle( gui_context * context )
{
    bool 
        should_terminate = false,
        should_log = true;
    int error = context->status;
    char buffer[100] = {0};
    
    switch (error)
    {
    case GCODE_NOT_READY:
        snprintf( buffer, 99, "Cannot send G-code yet (Pinter not ready).\n" );
        break;
    case GCODE_RECEIVE_ERROR:
        snprintf( buffer, 99, "Cannot receive ready status from printer (Printer not ready).\n" );
        break;    
    case GCODE_SERIAL_SEND_ERROR:
        snprintf( buffer, 99, "Cannot send G-code to printer.\n" );
        break;    
    case GCODE_OK:
        snprintf( buffer, 99, "G-code okay.\n" );
        should_log = false;
        break;    
    case GTK_NOT_INIT:
        snprintf( buffer, 99, "Gtk component not initialized.\n" );
        should_terminate = true;
        break;
    case GTK_NO_FILE_ERROR:
        snprintf( buffer, 99, "Glade file \"%s\" not found.\n", context->builder_file_path );
        should_terminate = true;
        break;
    case GTK_FILE_ACCESS_ERROR:
        snprintf( buffer, 99, "Glade file (%s) cannot be accessed.\n", context->builder_file_path );
        should_terminate = true;
        break;    
    case GUI_OK:
        snprintf( buffer, 99, "GUI components working properly.\n" );
        should_log = false;
        break;    
    case GTK_TRIVIAL_ERROR:
        should_log = false;
        break;    
    case GTK_ERROR:
        snprintf( buffer, 99, "Gtk generic error.\n" );
        should_terminate = true;
        break;
    case NO_SERIAL_ERROR:
        snprintf( buffer, 99, "Cannot find find serial port \"%s\".\n", serial_get_port(context->serial) );
        break;
    case SERIAL_PORT_OPEN_ERROR:
        snprintf( buffer, 99, "Cannot open \"%s\" serial port.\n", serial_get_port(context->serial) );
        break;
    case SERIAL_PORT_ATTR_GET_ERROR:
        snprintf( buffer, 99, "Cannot get attr for \"%s\" serial port.\n", serial_get_port(context->serial) );
        break;   
    case SERIAL_PORT_ATTR_SET_ERROR:
        snprintf( buffer, 99, "Cannot set attr for \"%s\" serial port.\n", serial_get_port(context->serial) );
        break;   
    case SERIAL_SEND_ERROR:
        snprintf( buffer, 99, "Cannot send data to \"%s\" serial port.\n", serial_get_port(context->serial) );
        break;
    case SERIAL_READ_ERROR:
        snprintf( buffer, 99, "Cannot read data from \"%s\" serial port.\n", serial_get_port(context->serial) );
        break;   
    case NOT_CONNECTED:
        snprintf( buffer, 99, "Not connected to printer.\n" );
        break;    
    case SERIAL_OK:
        snprintf( buffer, 99, "Serial connection OK.\n" );
        break;
    case NO_PREFERENCES_FILE_ERROR:
        snprintf( buffer, 99, "No preferences file found.\n" );
        break;
    case PREFERENCES_FILE_ACCESS_ERROR:
        snprintf( buffer, 99, "Cannot access preferences file.\n" );
        should_terminate = true;
        break;
    case PREFERENCES_NOT_INIT_ERROR:
        snprintf( buffer, 99, "Preferences object not initialized.\n" );
        should_terminate = true;
        break;
    case PREFERENCES_OK:
        snprintf( buffer, 99, "Preferences OK.\n" );
        should_log = false;
        break;
    default:
        snprintf( buffer, 99, "Unknown error.\n" );
        break;
    }
    
    if(should_log)
        gui_error_print_all( context, "%s", buffer );

    if(should_terminate)
        gui_error_terminate(context);
}