#include "include/gui.h"

bool gtk_is_init = false;

static char * glade_file_paths[] =
{
    "./caliprint.glade",
    "../assets/caliprint.glade",
    "/usr/share/caliprint/caliprint.glade",
};

static char * preferences_file_paths[] = 
{
    "./caliprint.conf",
    "../assets/caliprint.conf",
    "/etc/caliprint.conf",
};

gui_status gui_init( gui_context * context, int * argc, const char *** argv )
{
    //Check for any errors
    gui_error_handle( context );
    
    //Initialize GTK3
    gtk_init( argc, (char ***) argv );
    gtk_is_init = true;

    //Get builder from file
    context->builder = gtk_builder_new_from_file(
        context->builder_file_path
    );

    //Connect widget signals
    gui_connect_signals( context );

    //Check for any errors
    gui_error_handle( context );
    
    //Display main window
    gtk_widget_show_all(
        GTK_WIDGET(
            context->main_window
        )
    );

    g_object_unref( context->builder );

    gui_apply_preferences( context );

    gtk_main();

    return GUI_OK;
}

void gui_end( gui_context * context )
{   
    if( gtk_is_init )
    {
        gtk_main_quit();
        gtk_is_init = false;
    }
    gui_free_context(context);
}

gui_context * gui_create_context(  )
{
    //Allocate and return context
    gui_context * context =
        ( gui_context * ) calloc( 1, sizeof(gui_context) );
    
    //Get glade file path
    char * builder_file_path = check_for_files( glade_file_paths, 3 );
    //Check for glade file    
    if( builder_file_path == NULL )
    {
        gui_set_status(context, GTK_NO_FILE_ERROR);
        return context;
    }
    if( !check_for_file_access( builder_file_path ) )
    {
        gui_set_status(context, GTK_FILE_ACCESS_ERROR);
        return context;
    }
    //Allocate path in context
    context->builder_file_path = allocate_string(builder_file_path);

    //Get preferences from files
    char * preferences_file_path = check_for_files( preferences_file_paths, 3 );
    if( preferences_file_path == NULL )
    {
        //If not found, create one locally and write defaults to it
        preferences_file_path = preferences_file_paths[0];
        if( !check_for_file_access(preferences_file_path) )
        {
            gui_set_status(context, PREFERENCES_FILE_ACCESS_ERROR);
            return context;
        }
        FILE * fp = fopen(preferences_file_path, "a");
        fclose(fp);
        context->preferences = preferences_create_from_file( preferences_file_path );
        preferences_save( context->preferences );
        if(preferences_get_status(context->preferences) != PREFERENCES_OK)
        {
            gui_set_status( context, preferences_get_status(context->preferences) );
            return context;
        }
    }
    else
        context->preferences = preferences_create_from_file( preferences_file_path );
 
    context->gcode = gcode_create(
        context->preferences->printer_lenght,
        context->preferences->printer_width,
        context->preferences->printer_height
    );

    context->status = GUI_OK;

    return context;
}

void gui_free_context( gui_context * context )
{
    if(context == NULL)
        return;
    
    if(context->builder_file_path != NULL)
    {
        free( context->builder_file_path );
    }

    if(context->serial != NULL)
    {
        serial_free_driver( context->serial );
    }

    if(context->gcode != NULL)
    {
        gcode_free_params( context->gcode );
    }

    if(context->preferences != NULL)
    {
        preferences_free_object( context->preferences );
    }
        
    free( context );
}

void gui_set_status( gui_context * context, gui_status status )
{
    context->status = status;
}

gui_status gui_get_status( gui_context * context )
{
    return context->status;
}

void gui_apply_preferences( gui_context * context )
{
    char buffer[100] = {0};
    snprintf( buffer, 99, "%f", context->preferences->z_level );
    gtk_entry_set_text( context->control_z_level, buffer );
    
    gtk_entry_set_text( context->preferences_serial_port, context->preferences->serial_port );
    
    snprintf( buffer, 99, "%d", baudrate_to_int(context->preferences->serial_baudrate) );
    gtk_entry_set_text( context->preferences_serial_baudrate, buffer );
    
    snprintf( buffer, 99, "%f", context->preferences->printer_height );
    gtk_entry_set_text( context->preferences_printer_height, buffer );
    
    snprintf( buffer, 99, "%f", context->preferences->printer_width );
    gtk_entry_set_text( context->preferences_printer_width, buffer );
    
    snprintf( buffer, 99, "%f", context->preferences->printer_lenght );
    gtk_entry_set_text( context->preferences_printer_length, buffer );
}