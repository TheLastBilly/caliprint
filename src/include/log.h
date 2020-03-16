#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#include <gtk/gtk.h>
#include <gmodule.h>
#include <glib.h>
#include <glib/gprintf.h>

//1000 for buffer size (+1 for the \0) and +12 for the time
#define LOG_BUFFER_SIZE 1013

void log_printf( GtkTextView * tv, const char * format, ... );
void log_vprintf( GtkTextView * tv, const char * format, va_list arg);