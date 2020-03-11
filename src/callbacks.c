#include "include/gui.h"

gboolean on_main_window_destroy_callback( GtkWidget *object, gpointer user_data )
{
    gui_end();
    return true;
}