#include "blink.h"
#include "sdk_common.h"

/* Initialize the blink service */
ret_code_t blink_init(ble_blink_t *p_blink)
{
        ret_code_t err_code;
        ble_uuid_t ble_uuid;

        ble_uuid128_t base_uuid = {BLINK_UUID_BASE};

        if (!p_blink)
                return NRF_ERROR_INVALID_PARAM;

        /* Add the new service */
        err_code = sd_ble_uuid_vs_add(&base_uuid, &p_blink->service_type);
        VERIFY_SUCCESS(err_code);

        ble_uuid.type = p_blink->service_type;
        ble_uuid.uuid = BLINK_UUID_SERVICE;
        err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY,
                                            &ble_uuid,
                                            &p_blink->service_handle);

        VERIFY_SUCCESS(err_code);

        return err_code;
}

/* Event handler for the Blink BLE Service */
void blink_ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context)
{
        ble_blink_t *p_blink = (ble_blink_t *)p_context;

        if (!p_ble_evt || !p_blink)
                return;

        switch (p_ble_evt->header.evt_id)
        {
        case BLE_GAP_EVT_CONNECTED:
                break;
        default:
                return;
        }
}
