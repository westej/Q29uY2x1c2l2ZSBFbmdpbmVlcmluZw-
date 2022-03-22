#ifndef SENSOR_H_
#define SENSOR_H_

#include <math.h>

/*
 *
 */
typedef struct sensor_cb
{
    void (*on_data)(float_t pressure, float_t temperature);

} sensor_cb_t;

/*
 *
 */
int sensor_init(sensor_cb_t const *callbacks);

#endif // SENSOR_H_
