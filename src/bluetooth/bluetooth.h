#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

#include <stddef.h>

/*
 *
 */
#define BT_ADV_UUID_128 BT_UUID_128_ENCODE( \
                            CONFIG_BT_ADV_UUID_TIME_LOW, \
                            CONFIG_BT_ADV_UUID_TIME_MID, \
                            CONFIG_BT_ADV_UUID_TIME_HIGH_AND_VERSION, \
                            CONFIG_BT_ADV_UUID_CLOCK_SEQUENCE_HI_AND_RES_CLOCK_SEQUENCE_LOW, \
                            CONFIG_BT_ADV_UUID_NODE \
                        )

/*
 *
 */
#define BT_SERVICE_UUID_128 BT_UUID_128_ENCODE( \
                                CONFIG_BT_SERVICE_UUID_TIME_LOW, \
                                CONFIG_BT_SERVICE_UUID_TIME_MID, \
                                CONFIG_BT_SERVICE_UUID_TIME_HIGH_AND_VERSION, \
                                CONFIG_BT_SERVICE_UUID_CLOCK_SEQUENCE_HI_AND_RES_CLOCK_SEQUENCE_LOW, \
                                CONFIG_BT_SERVICE_UUID_NODE \
                            )

/*
 *
 */
#define BT_SERVICE_RX_UUID_128  BT_UUID_128_ENCODE( \
                                    CONFIG_BT_SERVICE_RX_UUID_TIME_LOW, \
                                    CONFIG_BT_SERVICE_RX_UUID_TIME_MID, \
                                    CONFIG_BT_SERVICE_RX_UUID_TIME_HIGH_AND_VERSION, \
                                    CONFIG_BT_SERVICE_RX_UUID_CLOCK_SEQUENCE_HI_AND_RES_CLOCK_SEQUENCE_LOW, \
                                    CONFIG_BT_SERVICE_RX_UUID_NODE \
                                )

/*
 *
 */
#define BT_SERVICE_TX_UUID_128  BT_UUID_128_ENCODE( \
                                    CONFIG_BT_SERVICE_TX_UUID_TIME_LOW, \
                                    CONFIG_BT_SERVICE_TX_UUID_TIME_MID, \
                                    CONFIG_BT_SERVICE_TX_UUID_TIME_HIGH_AND_VERSION, \
                                    CONFIG_BT_SERVICE_TX_UUID_CLOCK_SEQUENCE_HI_AND_RES_CLOCK_SEQUENCE_LOW, \
                                    CONFIG_BT_SERVICE_TX_UUID_NODE \
                                )

/*
 *
 */
typedef struct bluetooth_cb
{
    void (*on_data)(void const *buf, size_t len);

} bluetooth_cb_t;

/*
 *
 */
int bluetooth_init(bluetooth_cb_t const *callbacks);

/*
 *
 */
int bluetooth_send(void const *data, size_t len);

#endif // BLUETOOTH_H_