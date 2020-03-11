#include "include/gui.h"

bool gtk_is_init = false;

gui_status gui_init( gui_context * context, int * argc, const char *** argv )
{
    //Check for any errors
    if( gui_has_errors(context) )
        return gui_get_status( context );
    
    //Initialize GTK3
    gtk_init( argc, (char ***) argv );
    gtk_is_init = true;

    //Get builder from file
    context->builder = gtk_builder_new_from_file(
        context->builder_file_path
    );

    //Connect widget signals
    gui_connect_signals( context );

    //Check for any errors
    if( gui_has_errors(context) )
        return gui_error_handler( context, GTK_ERROR );
    
    //Display main window
    gtk_widget_show_all(
        GTK_WIDGET(
            context->main_window
        )
    );    

    gtk_main();

    return A_OK;
}

void gui_end()
{
    if( gtk_is_init )
    {
        gtk_main_quit();
        gtk_is_init = false;
    }
}

gui_context * gui_create_context( const char * builder_file_path )
{
    //Allocate and return context
    gui_context * context =
        ( gui_context * ) malloc( sizeof(gui_context) );
    
    //Check for glade file    
    if( builder_file_path == NULL )
    {
        gui_set_status(context, NO_FILE_ERROR);
        return context;
    }
    if( access( builder_file_path, F_OK ) == -1 )
    {
        gui_set_status(context, FILE_ACCESS_ERROR);
        return context;
    }
    

    //Allocate string in context    
    size_t fp_s = strlen( builder_file_path );
    context->builder_file_path = 
        malloc( sizeof(char) * (fp_s + 2) );
    snprintf( 
        context->builder_file_path, 
        fp_s+1, 
        "%s", 
        builder_file_path
    );

    return context;
}

void gui_free_context( gui_context * context )
{
    if(context == NULL)
        return;
    
    if(context->builder_file_path != NULL)
    {
        free( context->builder_file_path );
    }

    free( context );
}

void gui_set_status( gui_context * context, gui_status status )
{
    context->status = status;
}

gui_status gui_get_status( gui_context * context )
{
    return context->status;
}

const char * gui_get_status_description( gui_status status )
{
    switch (status)
    {
    case IS_INIT:
        return "GUI is initialized";
        break;
    case NOT_INIT:
        return "GUI is not initialized";
        break;
    case GTK_NOT_INIT:
        return "GTK is not initialized";
        break;
    case NO_FILE_ERROR:
        return "GUI (builder) file not specified";
        break;    
    case FILE_ACCESS_ERROR:
        return "Cannot access GUI (builder) file";
        break;    
    case A_OK:
        return "GUI OK";
        break;    
    }
    return NULL;
}

const char * gui_get_internal_status_description( gui_context * context )
{
    return gui_get_status_description( gui_get_status( context ) );
}

gui_status gui_error_handler( gui_context * context, gui_error_type type )
{
    bool end_gtk = false;
    
    switch (type)
    {
    case GTK_ERROR:
        end_gtk = true;
        break;
    case TRIVIAL_ERROR:
        break;    
    }

    if( end_gtk && gtk_is_init )
    {
        gtk_main_quit();
        gtk_is_init = false;
    }

    return context->status;
}

bool gui_has_errors( gui_context * context )
{
    gui_status st = context->status;
    if(st == NOT_INIT || st == GTK_NOT_INIT || st == NO_FILE_ERROR || st == FILE_ACCESS_ERROR )
        return true;
    return false;        
}