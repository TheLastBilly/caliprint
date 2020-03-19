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
#include "preferences.h"

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
        * main_window,
        * preferences_window;
    
    GtkButton
        * control_preferences,
        * control_connect,
        * control_home,
        * control_home_x,
        * control_home_y,
        * control_home_z,
        * control_raise_z,
        * control_lower_z,
        * control_top,
        * control_left,
        * control_right,
        * control_bottom,
        * control_top_left,
        * control_top_right,
        * control_bottom_left,
        * control_bottom_right,
        * control_center;
    
    GtkEntry
        * control_z_level,
        * preferences_serial_port,
        * preferences_serial_baudrate,
        * preferences_printer_height,
        * preferences_printer_width,
        * preferences_printer_length;
    
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

    preferences_object *
        preferences;
    
    gui_status status;
} gui_context;

extern bool gtk_is_init;

gui_status gui_init( gui_context * context, int * argc, const char *** argv );
void gui_end( gui_context * context );

gui_context * gui_create_context( );
void gui_free_context( gui_context * context );

gui_status gui_get_status( gui_context * context );

void gui_connect_signals( gui_context * context );

void gui_set_status(gui_context * context, gui_status status );

void gui_error_print_all( gui_context * context, const char * format, ... );
void gui_error_terminate( gui_context * context );
void gui_error_handle( gui_context * context );
void gui_error_handle_and_set( gui_context * context, int status );

void gui_apply_preferences( gui_context * context );

// ###################################
// ############ Callbacks ############
// ###################################

//Main Window
gboolean on_main_window_destroy_callback( GtkWidget *object, gpointer user_data );

//Panel Buttons
gboolean on_control_top_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_left_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_right_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_bottom_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_top_left_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_top_right_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_bottom_left_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_bottom_right_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_center_pressed_callback( GtkWidget *object, gpointer user_data );

//Home Buttons
gboolean on_control_home_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_home_x_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_home_y_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_home_z_pressed_callback( GtkWidget *object, gpointer user_data );

//Z's Widgets
gboolean on_control_raise_z_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_lower_z_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_control_z_level_edited( GtkWidget *object, gpointer user_data );

//Connect Button
gboolean on_control_connect_pressed_callback( GtkWidget *object, gpointer user_data );

//Preference Widgets
gboolean on_control_preferences_pressed_callback( GtkWidget *object, gpointer user_data );
gboolean on_preferences_serial_port_edited( GtkWidget *object, gpointer user_data );
gboolean on_preferences_serial_baudrate_edited( GtkWidget *object, gpointer user_data );
gboolean on_preferences_printer_height_edited( GtkWidget *object, gpointer user_data );
gboolean on_preferences_printer_width_edited( GtkWidget *object, gpointer user_data );
gboolean on_preferences_printer_length_edited( GtkWidget *object, gpointer user_data );