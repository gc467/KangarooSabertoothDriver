/*
 * Kangaroo_Driver_Lib.h
 *
 *  Created on: Feb 27, 2016
 *      Author: MarkZhao
 */

#ifndef KANGAROO_DRIVER_LIB_H_
#define KANGAROO_DRIVER_LIB_H_
#include <stdio.h>
#include <stdlib.h>
#include "COMMAND_LIST.h"
#include "mraa.h"

	struct velocity_Data {
		char error;				// 0 if not error
		int32_t velocity;		// motor velocity
	};

    mraa_uart_context uart_setup();

    int uart_destroy(mraa_uart_context uart);

    uint16_t crc14(const uint8_t* data, size_t length);

    size_t bitpackNumber(uint8_t* buffer, int32_t number);

    int32_t unpackNumber(uint8_t* buffer, uint8_t dataLength);

    size_t write_kangaroo_command(uint8_t address, uint8_t command, const uint8_t* data,
                                  uint8_t length, uint8_t* buffer);

    void start_channel(mraa_uart_context uart, uint8_t address, uint8_t channel_name);

    void writeMoveSpeed(mraa_uart_context uart, uint8_t address, uint8_t channel_name, int32_t velocity);
    
    void power_down_channel(mraa_uart_context uart, uint8_t address, uint8_t channel_name);

    struct velocity_Data readMoveSpeed(mraa_uart_context uart, uint8_t address, uint8_t channel_name);

    void clearRead(mraa_uart_context uart);
#endif /* KANGAROO_DRIVER_LIB_H_ */


