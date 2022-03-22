#include <stdio.h>
#include <zephyr.h>

#include "bluetooth.h"
#include "sensor.h"

/*
 *
 */
static void _on_sensor_data(float_t pressure, float_t temperature)
{
    char buf[64];
    size_t len = snprintf(buf, sizeof(buf), "Pressure: %f Temperature: %f\n", pressure, temperature);
    (void) bluetooth_send(buf, len);
}

/*
 *
 */
void main(void)
{
    (void) bluetooth_init(NULL);

    sensor_cb_t sensor_cb = { .on_data = _on_sensor_data };
    (void) sensor_init(&sensor_cb);
}
