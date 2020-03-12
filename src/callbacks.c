#include "include/gui.h"
#include "include/log.h"
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
    gui_end();
    return true;
}

//Connect Button
gboolean on_control_connect_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}

//Preferences Button
gboolean on_control_preferences_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}

// Home Buttons
gboolean on_control_home_x_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}

gboolean on_control_home_y_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}

gboolean on_control_home_z_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Not implemented!\n");
    return true;
}

//Z's Buttons
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