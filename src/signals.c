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
}