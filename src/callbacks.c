#include "include/gui.h"

static void update_entry_float( GtkEntry * entry, float f )
{
    char buffer[20] = {0};
    snprintf( buffer, 19, "%f", f );
    gtk_entry_set_text( entry, buffer );
}
static void update_entry_int( GtkEntry * entry, int i )
{
    char buffer[10] = {0};
    snprintf( buffer, 9, "%d", i );
    gtk_entry_set_text( entry, buffer );
}

//Main Window
gboolean on_main_window_destroy_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    preferences_save(context->preferences);
    gui_error_handle_and_set( context, preferences_get_status(context->preferences) );
    gui_end( context );
    return true;
}

//Panel Buttons
gboolean on_control_top_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        context->gcode->max_x/2,
        context->gcode->max_y,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_left_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        0.0,
        context->gcode->max_y/2,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_right_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        context->gcode->max_x,
        context->gcode->max_y/2,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_bottom_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        context->gcode->max_x/2,
        0,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_top_left_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        0.0,
        context->gcode->max_y,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_top_right_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        context->gcode->max_x,
        context->gcode->max_y,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_bottom_left_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        0.0,
        0.0,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_bottom_right_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        context->gcode->max_x,
        0.0,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_center_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_move_to( 
        context->gcode,
        context->gcode->max_x/2,
        context->gcode->max_y/2,
        context->gcode->z
    ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
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
    
    context->serial = serial_create_driver( 
        context->preferences->serial_port, 
        context->preferences->serial_baudrate, 
        false 
    );
    
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
    //This is stupid, I know, but it works well enough for now
    context->preferences->serial_baudrate = 
        int_to_baudrate(atoi(
            gtk_entry_get_text(context->preferences_serial_baudrate)
        ));
    update_entry_int(
        context->preferences_serial_baudrate,
        baudrate_to_int(
            context->preferences->serial_baudrate
        )
    );
    return true;
}
gboolean on_preferences_printer_height_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data; 
    double f_buffer = 
        atof(
            gtk_entry_get_text(context->preferences_printer_height)
        );
    if(f_buffer < 0.0)
        f_buffer *= -1;
    context->preferences->printer_height = f_buffer;
    context->gcode->max_z = f_buffer;
    update_entry_float(
        context->preferences_printer_height,
        f_buffer
    );
    return true;
}
gboolean on_preferences_printer_width_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    double f_buffer = 
        atof(
            gtk_entry_get_text(context->preferences_printer_width)
        );
    if(f_buffer < 0.0)
        f_buffer *= -1;
    context->preferences->printer_width = f_buffer;
    context->gcode->max_y = f_buffer;
    update_entry_float(
        context->preferences_printer_width,
        f_buffer
    );
    return true;
}
gboolean on_preferences_printer_length_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    double f_buffer = 
        atof(
            gtk_entry_get_text(context->preferences_printer_length)
        );
    if(f_buffer < 0.0)
        f_buffer *= -1;
    context->preferences->printer_lenght = f_buffer;
    context->gcode->max_x = f_buffer;
    update_entry_float(
        context->preferences_printer_length,
        f_buffer
    );
    return true;
}

// Home Buttons
gboolean on_control_home_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_home( context->gcode, GCODE_ALL ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_home_x_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_home( context->gcode, GCODE_X ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_home_y_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_home( context->gcode, GCODE_Y ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}
gboolean on_control_home_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_home( context->gcode, GCODE_Z ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    return true;
}

//Z's Widgets
gboolean on_control_z_level_edited( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    double f_buffer = 
        atof(
            gtk_entry_get_text(context->control_z_level)
        );
    if(f_buffer < 0.0)
        f_buffer *= -1;
    context->preferences->z_level = f_buffer;
    return true;
}
gboolean on_control_raise_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_translate( context->gcode, GCODE_Z, context->preferences->z_level ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    printf("%f\n", context->gcode->z);    
    return true;
}
gboolean on_control_lower_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    int err = serial_printf(context->serial, "%s", gcode_translate( context->gcode, GCODE_Z, context->preferences->z_level * -1 ));
    if(err != SERIAL_OK)
        gui_error_handle_and_set(context, err);
    printf("%f\n", context->gcode->z);    
    return true;
}