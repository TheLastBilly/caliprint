#include <stdio.h>
#include <stdlib.h>

#include "include/gui.h"

int main(int argc, char const *argv[])
{
    gui_context * context = 
        gui_create_context( "../assets/caliprint.glade" );
    gui_init( context, &argc, &argv );
    return 0;
}
