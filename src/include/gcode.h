#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define GCODE_PARAMS_MAX_BUFFER 100

typedef enum gcode_axis
{
    GCODE_X = 0x01,
    GCODE_Y = 0x02,
    GCODE_Z = 0x04,
    GCODE_ALL = 0x00
}gcode_axis;

typedef struct gcode_params
{
    float x, y, z;
    float
        extrude,
        feedrate,
        millis,
        seconds,
        retract;
    bool
        is_linear;
    char buffer[GCODE_PARAMS_MAX_BUFFER];    
    gcode_axis active_axis;
}gcode_params;

gcode_params * gcode_create_params( void );
void gcode_set_linear( gcode_params * params, bool is_linear );
void gcode_free_params( gcode_params * params );

const char * gcode_home( gcode_params * params, gcode_axis axis );
const char * gcode_move( gcode_params * params );
const char * gcode_move_x( gcode_params * params, float x );
const char * gcode_move_y( gcode_params * params, float y );
const char * gcode_move_z( gcode_params * params, float z );
const char * gcode_move_to( gcode_params * params, float x, float y, float z );