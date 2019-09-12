#include "blink.h"
#include "sdk_common.h"

static ret_code_t add_led_ena_char(ble_blink_t *p_blink)
{
    ret_code_t err_code;
    ble_add_char_params_t add_char_params;
    ble_add_char_user_desc_t add_char_user_desc;
    static char *user_desc_text = "LED Enable";
    uint8_t initial_ena_val = 0;

    /* Add the LED enable characteristic */
    memset(&add_char_params, 0, sizeof add_char_params);
    add_char_params.uuid = BLINK_UUID_LED_ENA;
    add_char_params.uuid_type = p_blink->service_type;
    add_char_params.init_len = sizeof(uint8_t);
    add_char_params.p_init_value = &initial_ena_val;
    add_char_params.max_len = sizeof(uint8_t);
    add_char_params.char_props.read = 1;
    add_char_params.char_props.write = 1;

    add_char_params.read_access = SEC_OPEN;
    add_char_params.write_access = SEC_OPEN;

    memset(&add_char_user_desc, 0, sizeof add_char_user_desc);
    add_char_user_desc.max_size = strlen(user_desc_text);
    add_char_user_desc.size = strlen(user_desc_text);
    add_char_user_desc.p_char_user_desc = (uint8_t *)user_desc_text;
    add_char_user_desc.is_var_len = false;
    add_char_user_desc.read_access = SEC_OPEN;
    add_char_user_desc.write_access = SEC_NO_ACCESS;
    
    add_char_params.p_user_descr = &add_char_user_desc;

    err_code = characteristic_add(p_blink->service_handle,
                                  &add_char_params,
                                  &p_blink->led_ena_handle);
    VERIFY_SUCCESS(err_code);

    return err_code;
}

static ret_code_t add_led_int_char(ble_blink_t *p_blink)
{
    ret_code_t err_code;
    ble_add_char_params_t add_char_params;
    ble_add_char_user_desc_t add_char_user_desc;
    static char *user_desc_text = "LED blinking interval";
    uint8_t initial_int_val = 5;

    /* Add the blinking interval characteristic */
    memset(&add_char_params, 0, sizeof add_char_params);
    add_char_params.uuid = BLINK_UUID_LED_INT;
    add_char_params.uuid_type = p_blink->service_type;
    add_char_params.init_len = sizeof(uint8_t);
    add_char_params.p_init_value = &initial_int_val;
    add_char_params.max_len = sizeof(uint8_t);
    add_char_params.char_props.read = 1;
    add_char_params.char_props.write = 1;

    add_char_params.read_access = SEC_OPEN;
    add_char_params.write_access = SEC_OPEN;

    memset(&add_char_user_desc, 0, sizeof add_char_user_desc);
    add_char_user_desc.max_size = strlen(user_desc_text);
    add_char_user_desc.size = strlen(user_desc_text);
    add_char_user_desc.p_char_user_desc = (uint8_t *)user_desc_text;
    add_char_user_desc.is_var_len = false;
    add_char_user_desc.read_access = SEC_OPEN;
    add_char_user_desc.write_access = SEC_NO_ACCESS;
    add_char_params.p_user_descr = &add_char_user_desc;

    err_code = characteristic_add(p_blink->service_handle,
                                  &add_char_params,
                                  &p_blink->led_int_handle);
    VERIFY_SUCCESS(err_code);

    return err_code;
}

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

        err_code = add_led_ena_char(p_blink);
        VERIFY_SUCCESS(err_code);

        err_code = add_led_int_char(p_blink);
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
