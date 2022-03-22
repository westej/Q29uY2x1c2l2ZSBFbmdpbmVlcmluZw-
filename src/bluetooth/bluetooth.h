#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

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

#endif // BLUETOOTH_H_