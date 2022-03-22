#include <stdio.h>
#include <bluetooth/conn.h>
#include <bluetooth/gatt.h>
#include <bluetooth/uuid.h>

#include "bluetooth.h"

/*
 *
 */
static bluetooth_cb_t _callbacks;

/*
 *
 */
static ssize_t _on_data_received(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                                void const *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    if (_callbacks.on_data != NULL) {
        _callbacks.on_data(buf, len);
    }

    return len;
}

/*
 *
 */
BT_GATT_SERVICE_DEFINE(_service,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_DECLARE_128(BT_SERVICE_UUID_128)),
    BT_GATT_CHARACTERISTIC(
        BT_UUID_DECLARE_128(BT_SERVICE_TX_UUID_128),
        BT_GATT_CHRC_NOTIFY,
        BT_GATT_PERM_READ,
        NULL, NULL, NULL
    ),
    BT_GATT_CCC(NULL, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
    BT_GATT_CHARACTERISTIC(
        BT_UUID_DECLARE_128(BT_SERVICE_RX_UUID_128),
        BT_GATT_CHRC_WRITE | BT_GATT_CHRC_WRITE_WITHOUT_RESP,
        BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
        NULL, _on_data_received, NULL
    ),
);

/*
 *
 */
static struct bt_data const adv_data[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_ADV_UUID_128),
};

/*
 *
 */
static struct bt_data const sr_data[] = {
    BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME, sizeof(CONFIG_BT_DEVICE_NAME) - 1),
};

/*
 *
 */
int bluetooth_init(bluetooth_cb_t const *callbacks)
{
    int ret = bt_enable(NULL);
    if (ret != 0) {
        printf("Bluetooth initialization error: %d\n", ret);
    }
    else {
        ret = bt_le_adv_start(BT_LE_ADV_CONN, adv_data, ARRAY_SIZE(adv_data), sr_data, ARRAY_SIZE(sr_data));
        if (ret != 0) {
            printf("Advertising start error: %d\n", ret);
        }
        else {
            if (callbacks != NULL) {
                _callbacks = *callbacks;
            }
        }
    }

    return ret;
}

/*
 *
 */
static void _send_to_connection(struct bt_conn *conn, void *data)
{
    struct bt_gatt_notify_params *params = (struct bt_gatt_notify_params *) data;
    if (bt_gatt_is_subscribed(conn, params->attr, BT_GATT_CCC_NOTIFY)) {
        size_t mtu = bt_gatt_get_mtu(conn) - 3; // 3 accounts for opcode and handle
        uint8_t *ptr = params->data;
        size_t len = params->len;
        while (len != 0) {
            params->data = ptr;
            params->len = len > mtu ? mtu : len;
            int ret = bt_gatt_notify_cb(conn, params);
            if (ret != 0) {
                printf("Failed to send data over BLE: %d, length: %u, effective MTU: %u\n", ret, len, mtu);
            }
            ptr += params->len;
            len -= params->len;
        }
    }
}

/*
 *
 */
int bluetooth_send(void const *data, size_t len)
{
    struct bt_gatt_notify_params params = { 0 };
    struct bt_gatt_attr const *attr = &_service.attrs[2];

    params.attr = attr;
    params.data = data;
    params.len = len;
    params.func = NULL;

    bt_conn_foreach(BT_CONN_TYPE_ALL, _send_to_connection, &params);

    return 0;
}
