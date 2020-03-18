#include "include/gui.h"
/*
Callback template (might vary depending on the widget):
gboolean function( GtkWidget *object, gpointer user_data )
{
    return true;
}
*/

//Main Window
gboolean on_main_window_destroy_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    preferences_save(context->preferences);
    gui_error_handle_and_set( context, preferences_get_status(context->preferences) );
    gui_end( context );
    return true;
}

//Connect Button
gboolean on_control_connect_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;

    //Disconnect
    if( context->serial != NULL && serial_is_connected( context->serial ) )
    {
        log_printf( 
            context->control_log, 
            "Disconnecting from %s...\n", 
            serial_get_port( context->serial )
        );

        serial_free_driver( context->serial );
        context->serial = NULL;

        gtk_button_set_label(
            context->control_connect,
            "Connect"
        );

        return true;
    }

    //Connect
    if( context->serial != NULL )
    {
        serial_free_driver( context->serial );
    }
    
    context->serial = serial_create_driver( "/dev/ttyS10", SP115200, false );
    if( serial_get_status( context->serial ) != SERIAL_OK )
    {
        gui_error_handle_and_set( 
            context,
            serial_get_status( context->serial )
        );
        return true;
    }
    else
    {
        log_printf( 
            context->control_log, 
            "Connected to %s\n",
            serial_get_port( context->serial )
        );

        gtk_button_set_label(
            context->control_connect,
            "Disconnect"
        );
    }


    return true;
}

//Preferences Widgets
gboolean on_control_preferences_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    gtk_window_present( context->preferences_window );
    return true;
}
gboolean on_preferences_serial_port_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    preferences_change_serial_port(
        context->preferences,
        (char *)gtk_entry_get_text(context->preferences_serial_port)
    );
    return true;
}
gboolean on_preferences_serial_baudrate_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    context->preferences->serial_baudrate = 
        int_to_baudrate(atoi(
            gtk_entry_get_text(context->preferences_serial_baudrate)
        ));
    return true;
}
gboolean on_preferences_printer_height_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    context->preferences->printer_height = 
        atof(
            gtk_entry_get_text(context->preferences_printer_height)
        );
    return true;
}
gboolean on_preferences_printer_width_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    context->preferences->printer_width = 
        atof(
            gtk_entry_get_text(context->preferences_printer_width)
        );
    return true;
}
gboolean on_preferences_printer_length_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    context->preferences->printer_lenght = 
        atof(
            gtk_entry_get_text(context->preferences_printer_length)
        );
    return true;
}

// Home Buttons
gboolean on_control_home_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "%s\n", gcode_home( context->gcode, GCODE_ALL ));
    return true;
}

// Home Buttons
gboolean on_control_home_x_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "%s\n", gcode_home( context->gcode, GCODE_X ));
    return true;
}

gboolean on_control_home_y_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "%s\n", gcode_home( context->gcode, GCODE_Y ));
    return true;
}

gboolean on_control_home_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "%s\n", gcode_home( context->gcode, GCODE_Z ));
    return true;
}

//Z's Widgets
gboolean on_control_z_level_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    context->preferences->z_level = 
        atof(
            gtk_entry_get_text(context->control_z_level)
        );
    return true;
}
gboolean on_control_raise_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}
gboolean on_control_lower_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}