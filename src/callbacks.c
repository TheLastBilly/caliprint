#include "include/gui.h"
#include "include/log.h"
/*
Callback template (might vary depending on the widget):
gboolean function( GtkWidget *object, gpointer user_data )
{
    return true;
}
*/

gboolean on_main_window_destroy_callback( GtkWidget *object, gpointer user_data )
{
    gui_end();
    return true;
}

gboolean on_control_home_x_pressed_callback( GtkWidget *object, gpointer user_data )
{
    gui_context * context = (gui_context *)user_data;
    log_printf(context->control_log, "Can't beleive it works!\n");
    return true;
}