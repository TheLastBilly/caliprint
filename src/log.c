#include "include/log.h"
#include "include/utils.h"

static void log_append_to_textview( GtkTextView * tv, char * msg, size_t size );

void log_vprintf( GtkTextView * tv, const char * format, va_list arg)
{
    char buffer[LOG_BUFFER_SIZE] = {0};

    //Get the time 
    GDateTime * time = g_date_time_new_now_local();
    char * tgt = g_date_time_format(time, "[%k:%M:%S] ");
    size_t size = snprintf( buffer, 12, "%s", tgt );
    if(size > 12) size = 12;
    
    //Free time objects
    g_free( tgt );
    g_date_time_unref( time );
    
    size = vsnprintf( &buffer[size], 1000, format, arg );

    printf( "%s", buffer );
    if( tv != NULL )
        log_append_to_textview( tv, buffer, size );
}

void log_printf( GtkTextView * tv, const char * format, ... )
{
    va_list arg;
    va_start( arg, format );

    log_vprintf( tv, format, arg );

    va_end(arg);
}

void log_append_to_textview( GtkTextView * tv, char * msg, size_t size )
{
    GtkTextBuffer * buff =
        gtk_text_view_get_buffer(tv);

    GtkTextMark *mark = 
        gtk_text_buffer_get_insert( buff );

    GtkTextIter end;
    gtk_text_buffer_get_end_iter(
        buff,
        &end
    );

    gtk_text_buffer_move_mark( buff, mark, &end );
    gtk_text_buffer_insert_at_cursor( 
        buff, 
        msg, 
        -1 
    );
    gtk_text_view_scroll_to_mark( 
        tv,
        mark, 
        0.0,
        TRUE, 
        0.5, 
        1 
    );
}