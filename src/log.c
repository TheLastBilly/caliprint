#include "include/log.h"
#include "include/utils.h"

static void log_append_to_textview( GtkTextView * tv, char * msg );

void log_printf( GtkTextView * tv, const char * format, ... )
{
    va_list arg;
    va_start( arg, format );

    //1000 for buffer size (+1 for the \0) and +12 for the time
    static char buffer[1013] = {0};
    char * tgt = get_time( buffer );
    vsnprintf( tgt, 1000, format, arg );

    log_append_to_textview( tv, buffer );
}

void log_append_to_textview( GtkTextView * tv, char * msg )
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