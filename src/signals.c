#include "include/gui.h"

void gui_connect_signals( gui_context * context )
{
    //Check if GTK is initialized
    if( !gtk_is_init )
    {
        gui_set_status(context, GTK_NOT_INIT);
        return;
    }
    
    // ###########
    // Windows
    // ###########

    //Get Main Window from builder
    context->main_window = GTK_WINDOW(
        gtk_builder_get_object( 
            context->builder, 
            "main_window"
        )
    );
    //Connect destroy signal for window
    g_signal_connect(
        context->main_window,
        "destroy",
        G_CALLBACK(on_main_window_destroy_callback),
        context
    );

    //Get Preferences Window from builder
    context->preferences_window = GTK_WINDOW(
        gtk_builder_get_object( 
            context->builder, 
            "preferences_window"
        )
    );
    //Connect hide signal for window
    g_signal_connect(
        context->preferences_window,
        "delete-event",
        G_CALLBACK(gtk_widget_hide_on_delete),
        context->preferences_window
    );

    // #######
    // Buttons
    // #######

    //Control connect Button
    context->control_connect = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_connect"
        )
    );
    g_signal_connect(
        context->control_connect,
        "clicked",
        G_CALLBACK(on_control_connect_pressed_callback),
        context
    );

    //Control preferences Button
    context->control_preferences = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_preferences"
        )
    );
    g_signal_connect(
        context->control_preferences,
        "clicked",
        G_CALLBACK(on_control_preferences_pressed_callback),
        context
    );
    
    //Control Home Button
    context->control_home = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_home"
        )
    );
    g_signal_connect(
        context->control_home,
        "clicked",
        G_CALLBACK(on_control_home_pressed_callback),
        context
    );
    
    //Control Home X Button
    context->control_home_x = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_home_x"
        )
    );
    g_signal_connect(
        context->control_home_x,
        "clicked",
        G_CALLBACK(on_control_home_x_pressed_callback),
        context
    );
    
    //Control Home Y Button
    context->control_home_y = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_home_y"
        )
    );
    g_signal_connect(
        context->control_home_y,
        "clicked",
        G_CALLBACK(on_control_home_y_pressed_callback),
        context
    );

    //Control Home Z Button
    context->control_home_z = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_home_z"
        )
    );
    g_signal_connect(
        context->control_home_z,
        "clicked",
        G_CALLBACK(on_control_home_z_pressed_callback),
        context
    );

    //Raise Z Button
    context->control_raise_z = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_raise_z"
        )
    );
    g_signal_connect(
        context->control_raise_z,
        "clicked",
        G_CALLBACK(on_control_raise_z_pressed_callback),
        context
    );

    //Lower Z Button
    context->control_lower_z = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_lower_z"
        )
    );
    g_signal_connect(
        context->control_lower_z,
        "clicked",
        G_CALLBACK(on_control_lower_z_pressed_callback),
        context
    );

    //Lower Z Button
    context->preferences_save = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "preferences_save"
        )
    );
    g_signal_connect(
        context->preferences_save,
        "clicked",
        G_CALLBACK(on_preferences_save_pressed_callback),
        context
    );

    // #########
    // TextViews
    // #########

    //Control Log
    context->control_log = GTK_TEXT_VIEW(
        gtk_builder_get_object(
            context->builder,
            "control_log"
        )
    );

    // #######
    // Entries
    // #######

    //Z's level
    context->control_z_level = GTK_ENTRY(
        gtk_builder_get_object(
            context->builder,
            "control_z_level"
        )
    );
    g_signal_connect(
        context->control_z_level,
        "activate",
        G_CALLBACK(on_control_z_level_edited),
        context
    );

    //Serial Port
    context->preferences_serial_port = GTK_ENTRY(
        gtk_builder_get_object(
            context->builder,
            "preferences_serial_port"
        )
    );
    g_signal_connect(
        context->preferences_serial_port,
        "activate",
        G_CALLBACK(on_preferences_serial_port_edited),
        context
    );

    //Serial BaudRate
    context->preferences_serial_baudrate = GTK_ENTRY(
        gtk_builder_get_object(
            context->builder,
            "preferences_serial_baudrate"
        )
    );
    g_signal_connect(
        context->preferences_serial_baudrate,
        "activate",
        G_CALLBACK(on_preferences_serial_baudrate_edited),
        context
    );

    //Printer Height
    context->preferences_printer_height = GTK_ENTRY(
        gtk_builder_get_object(
            context->builder,
            "preferences_printer_height"
        )
    );
    g_signal_connect(
        context->preferences_printer_height,
        "activate",
        G_CALLBACK(on_preferences_printer_height_edited),
        context
    );

    //Printer Width
    context->preferences_printer_width = GTK_ENTRY(
        gtk_builder_get_object(
            context->builder,
            "preferences_printer_width"
        )
    );
    g_signal_connect(
        context->preferences_printer_width,
        "activate",
        G_CALLBACK(on_preferences_printer_width_edited),
        context
    );

    //Printer Length
    context->preferences_printer_length = GTK_ENTRY(
        gtk_builder_get_object(
            context->builder,
            "preferences_printer_length"
        )
    );
    g_signal_connect(
        context->preferences_printer_length,
        "activate",
        G_CALLBACK(on_preferences_printer_length_edited),
        context
    );
}