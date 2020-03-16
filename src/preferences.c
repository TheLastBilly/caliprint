#include "include/preferences.h"

preferences_object * preferences_create_from_file( const char * file_path )
{
    preferences_object * preferences = calloc( 1, sizeof(preferences_object) );
    if(file_path == NULL)
    {
        preferences->status = NO_PREFERENCES_FILE_ERROR;
        return preferences;
    }
    if(check_for_file_access( file_path ))
    {
        preferences->status = PREFERENCES_FILE_ACCESS_ERROR;
        return preferences;
    }
}
void preferences_free_object( preferences_object * preferences );

const char * preferences_get_serial_port( preferences_object * preferences );
int preferences_get_serial_baudrate( preferences_object * preferences );
int preferences_get_printer_height( preferences_object * preferences );
int preferences_get_printer_width( preferences_object * preferences );
int preferences_get_printer_lenght( preferences_object * preferences );

preferences_status preferences_get_status( preferences_object * preferences );