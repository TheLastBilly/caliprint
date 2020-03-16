#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include <gtk/gtk.h>
#include <gmodule.h>

#include "serial.h"
#include "log.h"
#include "gcode.h"

typedef enum gui_status
{
    GTK_NOT_INIT = 0x05,
    GTK_NO_FILE_ERROR = 0x06,
    GTK_FILE_ACCESS_ERROR = 0x07,
    GUI_OK = 0x08,
} gui_status;

typedef enum gui_error_type
{
    GTK_TRIVIAL_ERROR = 0x09,
    GTK_ERROR = 0x0a,
}gui_error_type;

typedef struct gui_context
{
    char 
        * builder_file_path;
    
    GtkBuilder
        * builder;
    
    GtkWindow
        * main_window;
    
    GtkButton
        * control_preferences,
        * control_connect,
        * control_home,
        * control_home_x,
        * control_home_y,
        * control_home_z,
        * control_raise_z,
        * control_lower_z;
    
    GtkEntry
        * control_z_level;
    
    GtkTextView
        * control_log;
    
    GtkScrolledWindow
        * control_log_sw;

    bool
        is_initialized,
        is_connected;
    
    serial_driver *
        serial;

    gcode_params *
        gcode;    
    
    gui_status status;
} gui_context;

extern bool gtk_is_init;

gui_status gui_init( gui_context * context, int * argc, const char *** argv );
void gui_end();

gui_context * gui_create_context( const char * builder_file_path );
void gui_free_context( gui_context * context );

gui_status gui_get_status( gui_context * context );

void gui_connect_signals( gui_context * context );

void gui_set_status(gui_context * context, gui_status status );

void gui_error_print_all( gui_context * context, const char * format, ... );
void gui_error_terminate( gui_context * context );
void gui_error_handle( gui_context * context );
void gui_error_handle_and_set( gui_context * context, int status );

// ###################################
// ############ Callbacks ############
// ###################################

//Main Window
gboolean on_main_window_destroy_callback( GtkWidget *object, gpointer user_data );

//Home Buttons
gboolean on_control_home_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_home_x_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_home_y_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_home_z_pressed_callback( GtkWidget *object, gpointer user_data );

//Z's Buttons
gboolean on_control_raise_z_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_lower_z_pressed_callback( GtkWidget *object, gpointer user_data );

//Connect button
gboolean on_control_connect_pressed_callback( GtkWidget *object, gpointer user_data );

//Preference Button
gboolean on_control_preferences_pressed_callback( GtkWidget *object, gpointer user_data );