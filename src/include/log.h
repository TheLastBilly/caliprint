#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include <gtk/gtk.h>
#include <gmodule.h>

void log_printf( GtkTextView * tv, const char * format, ... );