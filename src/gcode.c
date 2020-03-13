#include "include/gcode.h"

gcode_params * gcode_create_params()
{
    return (gcode_params *) calloc( 1, sizeof(gcode_params) );
}

void gcode_set_linear( gcode_params * params, bool is_linear )
{
    if(params == NULL)
        return;

    params->is_linear = is_linear;
}

void gcode_free_params( gcode_params * params )
{
    if(params == NULL)
        return;

    free( params );
}

const char * gcode_home( gcode_params * params, gcode_axis axis )
{
    if(params == NULL)
        return NULL;
    char a[5] = {0};
    a[1] = a[3] = ' ';
    short a_i = 0;
    if((axis & GCODE_X) == GCODE_X)
    {
        a[a_i] = 'X';
        a_i += 2;
    }

    if((axis & GCODE_Y) == GCODE_Y)
    {
        a[a_i] = 'Y';
        a_i += 2;
    }

    if((axis & GCODE_Z) == GCODE_Z)
    {
        a[a_i] = 'Z';
    }

    if(axis == GCODE_ALL)
        a[0] = a[2] = a[4] = 0;

    snprintf( 
        params->buffer,
        GCODE_PARAMS_MAX_BUFFER,
        "G28 %s",
        a
    );

    return params->buffer;
}

const char * gcode_move( gcode_params * params )
{
    if(params == NULL)
        return NULL;

    bool for_all = params->active_axis == GCODE_ALL;    

    size_t index = 
        snprintf( 
            params->buffer, 
            GCODE_PARAMS_MAX_BUFFER,
            "G%d ", 
            (params->is_linear ? 1 : 0) 
        );

    if(for_all || (params->active_axis & GCODE_X) == GCODE_X)
    {
        index +=
            snprintf(
                &params->buffer[index],
                GCODE_PARAMS_MAX_BUFFER,
                "X%f ",
                params->x
            );
    }
    if(for_all || (params->active_axis & GCODE_Y) == GCODE_Y)
    {
        index +=
            snprintf(
                &params->buffer[index],
                GCODE_PARAMS_MAX_BUFFER,
                "Y%f ",
                params->y
            );
    }
    if(for_all || (params->active_axis & GCODE_Z) == GCODE_Z)
    {
        index +=
            snprintf(
                &params->buffer[index],
                GCODE_PARAMS_MAX_BUFFER,
                "Z%f ",
                params->z
            );
    }

    return params->buffer;
}

const char * gcode_move_to( gcode_params * params, float x, float y, float z )
{
    if(params == NULL)
        return NULL;
    
    params->x = x;
    params->y = y;
    params->z = z;
    params->active_axis = GCODE_ALL;

    return gcode_move( params );
}

const char * gcode_move_x( gcode_params * params, float x )
{
    if(params == NULL)
        return NULL;
    params->x = x;
    params->active_axis = GCODE_X;
    return gcode_move(params);
}

const char * gcode_move_y( gcode_params * params, float y )
{
    if(params == NULL)
        return NULL;
    params->y = y;
    params->active_axis = GCODE_Y;
    return gcode_move(params);
}

const char * gcode_move_z( gcode_params * params, float z )
{
    if(params == NULL)
        return NULL;
    params->z = z;
    params->active_axis = GCODE_Z;
    return gcode_move(params);
}