#include "include/gcode.h"

gcode_params * gcode_create_empty( )
{
    gcode_params * g = (gcode_params *) calloc( 1, sizeof(gcode_params) );
    g->is_ready = true;
    return g;
}

gcode_params * gcode_create( float max_x, float max_y, float max_z )
{
    gcode_params * params = gcode_create_empty();
    if(max_x < 0.0)
        max_x *= -1;
    if(max_y < 0.0)
        max_y *= -1;
    if(max_z < 0.0)
        max_z *= -1;
    params->max_x = max_x;
    params->max_y = max_y;
    params->max_z = max_z;
    params->is_ready = true;
    return params;
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
        params->x = 0.0;
    }

    if((axis & GCODE_Y) == GCODE_Y)
    {
        a[a_i] = 'Y';
        a_i += 2;
        params->y = 0.0;
    }

    if((axis & GCODE_Z) == GCODE_Z)
    {
        a[a_i] = 'Z';
        params->z = 0.0;
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
        if(params->x > params->max_x)
            params->x = params->max_x;
        else if(params->x < 0.0)
            params->x = 0.0;
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
        if(params->y > params->max_y)
            params->y = params->max_y;
        else if(params->y < 0.0)
            params->y = 0.0;
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
        if(params->z > params->max_z)
            params->z = params->max_z;
        else if(params->z < 0.0)
            params->z = 0.0;
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
const char * gcode_translate( gcode_params * params, gcode_axis axis, float var )
{

    if(axis == GCODE_ALL)
    {
        axis = GCODE_X | GCODE_Y | GCODE_Z;
    }

    if((axis & GCODE_X) == GCODE_X)
    {
        params->x += var;
    }

    if((axis & GCODE_Y) == GCODE_Y)
    {
        params->y += var;
    }

    if((axis & GCODE_Z) == GCODE_Z)
    {
        params->z += var;
    }

    return gcode_move(params);
}

gcode_status gcode_send( gcode_params * params, serial_driver * serial, const char * command )
{
    if(!params->is_ready)
    {
        if(serial_receive( serial ) != SERIAL_OK)
            return GCODE_RECEIVE_ERROR;
        
        if( strcmp("OK", serial_get_buffer(serial, NULL)) == 0 )
            params->is_ready = true;
        else
            return GCODE_NOT_READY;
    }

    if(serial_printf( serial, (char *) command ) != SERIAL_OK)
        return GCODE_SERIAL_SEND_ERROR;
    
    return GCODE_OK;
}