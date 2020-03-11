#include <stdio.h>
#include <stdlib.h>

#include "include/gui.h"

int main(int argc, char const *argv[])
{
    gui_context * context = 
        gui_create_context( "../assets/caliprint.glade" );
    if( gui_has_errors(context) )
    {
        printf("ERROR: %s\n", gui_get_internal_status_description(context));
        gui_free_context( context );
        return 1;
    }    
    gui_init( context, &argc, &argv );    
    if( gui_has_errors(context) )
    {
        printf("ERROR: %s\n", gui_get_internal_status_description(context));
        gui_free_context( context );
        return 1;
    }
    gui_free_context( context );
    gui_end();
    return 0;
}
