#include <stdio.h>
#include <zephyr.h>

#include "sensor.h"

/*
 *
 */
static void _on_sensor_data(float_t pressure, float_t temperature)
{
    static int64_t time;
    int64_t new_time = k_uptime_get();
    if (time == 0) {
        time = new_time;
    }

    printf("Time: %d Pressure: %f Temperature: %f\n", (int) (new_time - time), pressure, temperature);
    time = new_time;
}

/*
 *
 */
void main(void)
{
    sensor_cb_t sensor_cb = { .on_data = _on_sensor_data };
    (void) sensor_init(&sensor_cb);
}
