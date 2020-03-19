#include <stdio.h>
#include <stdlib.h>

#include "include/gui.h"

int main(int argc, char const *argv[])
{
    gui_context * context = 
        gui_create_context( );
    gui_init( context, &argc, &argv );
    gui_free_context(context);
    return 0;
}
