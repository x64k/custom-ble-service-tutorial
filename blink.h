#ifndef _BLINK_H
#define _BLINK_H

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"
#include "nrf_sdh_ble.h"

#define BLE_BLINK_OBSERVER_PRIO 2
/* Instantiate a new Blink service. */
#define BLE_BLINK_DEF(_name) \
    static ble_blink_t _name; \
    NRF_SDH_BLE_OBSERVER(_name ## _obs,                 \
    BLE_BLINK_OBSERVER_PRIO,  \
    blink_ble_evt_handler, &_name)

#define BLINK_UUID_BASE        {0x41, 0x55, 0x7A, 0xFD, 0x12, 0x94, 0x36, 0x25, \
                                0x81, 0x03, 0x41, 0x42, 0x00, 0x00, 0x00, 0x00}
#define BLINK_UUID_SERVICE     0x1969
#define BLINK_UUID_LED_ENA     0x196A
#define BLINK_UUID_LED_INT     0x196B

/**
 * BLE Blink Service
 */
struct ble_blink_s {
        /* Service handle assigned by the BLE stack */
        uint16_t service_handle;
        /* Service UUID type assigned by the BLE stack */
        uint8_t  service_type;        
};

typedef struct ble_blink_s ble_blink_t; /* Eww, but nRF likes this */

/* Initialize the blink service */
ret_code_t blink_init(ble_blink_t *p_blink);

/* Event handler for the Blink BLE Service */
void blink_ble_evt_handler(ble_evt_t const *p_ble_evt, void *p_context);

#endif
