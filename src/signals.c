#include "include/gui.h"

void gui_connect_signals( gui_context * context )
{
    //Check if GTK is initialized
    if( !gtk_is_init )
    {
        gui_set_status(context,  GTK_NOT_INIT);
        return;
    }
    
    // ###########
    // Main Window
    // ###########

    //Get window from builder
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
    
    //Control Home X Button
    context->control_home_x = GTK_BUTTON(
        gtk_builder_get_object(
            context->builder,
            "control_home_x"
        )
    );
    //Pressed signal
    g_signal_connect(
        context->control_home_x,
        "clicked",
        G_CALLBACK(on_control_home_x_pressed_callback),
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