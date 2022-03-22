#include <stdio.h>
#include <bluetooth/conn.h>
#include <bluetooth/gatt.h>
#include <bluetooth/uuid.h>

#include "bluetooth.h"

/*
 *
 */
static void _on_ccc_cfg_changed(const struct bt_gatt_attr *attr, uint16_t value)
{

}

/*
 *
 */
static ssize_t _on_data_received(struct bt_conn *conn, const struct bt_gatt_attr *attr,
                                const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
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
    BT_GATT_CCC(_on_ccc_cfg_changed, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
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
int bluetooth_init(void)
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
    }

    return ret;
}