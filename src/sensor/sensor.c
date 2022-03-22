#include <device.h>
#include <stdio.h>
#include <zephyr.h>
#include <drivers/sensor.h>
#include <sys/util.h>

#include "sensor.h"

/*
 *
 */
static sensor_cb_t _callbacks;

/*
 *
 */
static K_THREAD_STACK_DEFINE(_sensor_thread_stack, CONFIG_SENSOR_THREAD_STACK_SIZE);
static struct k_thread _sensor_thread_data;
static uint32_t _sensor_thread_period = CONFIG_SENSOR_THREAD_PERIOD_DEFAULT_VALUE;

/*
 *
 */
static void _sensor_thread_fn(void *p1, void *p2, void *p3)
{
    struct device const *dev = (struct device const *) p1;
    (void) p2;
    (void) p3;

    struct sensor_value pressure, temperature;
    float_t pressure_f, temperature_f;

    while (1) {
        int64_t start = k_uptime_get();

        int ret = sensor_sample_fetch(dev);
        if (ret != 0) {
            printf("Sensor sample update error: %d\n", ret);
        }
        else {
            ret = sensor_channel_get(dev, SENSOR_CHAN_PRESS, &pressure);
            if (ret != 0) {
                printf("Pressure channel error: %d\n", ret);
            }
            else {
                pressure_f = sensor_value_to_double(&pressure);
                ret = sensor_channel_get(dev, SENSOR_CHAN_AMBIENT_TEMP, &temperature);
                if (ret != 0) {
                    printf("Temperature channel error: %d\n", ret);
                }
                else {
                    temperature_f = sensor_value_to_double(&temperature);
                }
            }
        }

        if (ret == 0 && _callbacks.on_data != NULL) {
            _callbacks.on_data(pressure_f, temperature_f);
        }

        int64_t end = k_uptime_get();
        uint32_t time_to_sleep = end - start >= _sensor_thread_period? 0 : _sensor_thread_period - (uint32_t)(end - start);
        k_sleep(K_MSEC(time_to_sleep));
    }
}

/*
 *
 */
int sensor_init(sensor_cb_t const *callbacks)
{
    int ret;
    struct device const *dev = device_get_binding(DT_LABEL(DT_INST(0, st_lps22hb_press)));

    if (dev == NULL) {
        printf("Could not get LPS22HB device\n");
        ret = -EIO;
    }
    else {
        k_tid_t thread_id = k_thread_create(&_sensor_thread_data, _sensor_thread_stack,
                                            K_THREAD_STACK_SIZEOF(_sensor_thread_stack),
                                            _sensor_thread_fn,
                                            (void *) dev, NULL, NULL,
                                            CONFIG_SENSOR_THREAD_PRIORITY, 0, K_NO_WAIT);
        if (thread_id == 0) {
            printf("Could not initialize sensor thread\n");
            ret = -EAGAIN;
        }
        else {
            if (callbacks != NULL) {
                _callbacks = *callbacks;
            }
        }
    }

    return ret;
}