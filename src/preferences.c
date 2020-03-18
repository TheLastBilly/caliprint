#include "include/preferences.h"

static void parse_file( preferences_object * preferences, FILE * fp );
static void parse_line( preferences_object * preferences, const char * line );
static int int_to_baudrate( int baudrate );
static inline bool preferences_ok( preferences_object * preferences );

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

    FILE * file = fopen( file_path, "r" );
    parse_file( preferences, file );
    fclose(file);

    preferences->file_path = 
        allocate_string( (char *) file_path );
    
    preferences->status = PREFERENCES_OK;

    preferences->is_initialized = true;

    return preferences;
}
void preferences_free_object( preferences_object * preferences )
{
    if(preferences == NULL)
        return;
    if(preferences->serial_port != NULL)
        free(preferences->serial_port);
    if(preferences->file_path != NULL)
        free(preferences->file_path);
    free(preferences);
}

void preferences_change_serial_port( preferences_object * preferences, char * serial_port )
{
    if(!preferences_ok(preferences))
        return;
    if(preferences->serial_port != NULL)
        free(preferences->serial_port);
    preferences->serial_port = allocate_string( serial_port );
}

preferences_status preferences_save( preferences_object * preferences )
{
    if(!preferences_ok(preferences))
        return (preferences->status = PREFERENCES_NOT_INIT_ERROR);
    
    if(!check_for_file_access(preferences->file_path))
        return (preferences->status = PREFERENCES_FILE_ACCESS_ERROR);
    
    FILE * file = fopen( preferences->file_path, "w" );

    fprintf(
        file,
        "%s=%s;\n%s=%d;\n%s=%f;%s=%f;\n%s=%f;",
        "serial_port",
        preferences->serial_port,
        "serial_baudrate",
        preferences->serial_baudrate,
        "printer_height",
        preferences->printer_height,
        "printer_width",
        preferences->printer_width,
        "printer_lenght",
        preferences->printer_lenght
    );
    return preferences->status;
}

preferences_status preferences_get_status( preferences_object * preferences )
{
    return preferences->status;
}

static void parse_file( preferences_object * preferences, FILE * file )
{
    char line_buffer[PREFERENCES_MAX_LINE] = {0};
    while( fgets(line_buffer, PREFERENCES_MAX_LINE, file) != NULL )
    {
        parse_line( preferences, line_buffer );
    }
}

static void parse_line( preferences_object * preferences, const char * line )
{
    //Check if line is long enough or if it starts with #
    if(
        strlen(line) < 5 || 
        line[0] == '#'
    ) return;
    
    //Look for assign and end characters
    char * assign_char = 
        strchr( line, '=' );
    char * end_char = 
        strchr( line, ';' );

    if(
        assign_char == NULL || 
        end_char == NULL || 
        end_char < assign_char
    ) return;
    
    //If you find them, check for command and data size
    //and allocate them
    int command_len = assign_char - line;
    int data_len = end_char - assign_char;
    char command[command_len+1];
    char data[data_len];
    strncpy(command, line, command_len);
    strncpy(data, assign_char+1, data_len);
    data[data_len-1] = command[command_len] ='\0';

    if(strcmp(command, "serial_port") == 0)
    {   
        preferences->serial_port = 
            calloc( 1, sizeof(char) * strlen(data) );
        sprintf(
            preferences->serial_port, 
            "%s",
            data
        );
        return;
    }
    else if(strcmp(command, "serial_baudrate") == 0)
    {
        preferences->serial_baudrate = 
            int_to_baudrate((int)strtol(data, NULL, 10));
        return;
    }
    else if(strcmp(command, "printer_height") == 0)
    {
        preferences->printer_height = (atof(data));
        return;
    }
    else if(strcmp(command, "printer_width") == 0)
    {
        preferences->printer_width = (atof(data));
        return;
    }
    else if(strcmp(command, "printer_lenght") == 0)
    {
        preferences->printer_lenght = (atof(data));
        return;
    }
}

static int int_to_baudrate( int baudrate )
{
    switch (baudrate)
    {
    case 9600:
        return 9600;
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

static inline bool preferences_ok( preferences_object * preferences )
{
   return (preferences == NULL || preferences->is_initialized);
}