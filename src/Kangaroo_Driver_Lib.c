/*
 * Kangaroo_Driver_Lib.c
 *
 *  Created on: Feb 27, 2016
 *      Author: Yuqi (Mark) Zhao and Gustavo Olveira
 */

#include "Kangaroo_Driver_Lib.h"
#include <stdio.h>
#include <stdlib.h>

#include "COMMAND_LIST.h"
#include "mraa.h"
#include <unistd.h>


/* This function should be called at the initialization of the setup.
 * This configures the Intel Edison to communicate with sabertooth through uart (8N1, 9600 baud).
 * Returns the uart context that is setup.
 */
mraa_uart_context uart_setup() {

    mraa_uart_context uart0 = mraa_uart_init(0);
    if (uart0 == NULL) {
    	fprintf(stderr, "UART failed to setup\n");
    	return EXIT_FAILURE;
        }
    else{
    	printf("UART initialized\n");
    }
    mraa_uart_set_mode(uart0, 8,MRAA_UART_PARITY_NONE , 1);
  	mraa_uart_set_baudrate(uart0, 9600);

	return uart0;
}

/**
 * Stops the uart connection and returns EXIT_SUCCESS if successful
 */
int uart_destroy(mraa_uart_context uart){
    mraa_uart_stop(uart);
    mraa_deinit();
    return EXIT_SUCCESS;
}

/*
 * Generates the crc from the array of commands to be sent. The crc must be generated
 * and sent in order to confirm the command. The Kangaroo will not work without reading crc.
 * Input: data - array of uint8_t that contains the command to be sent
 * 		   length - length of command buffer
 * Output: uint16_t corresponding to the generated crc.
 */
uint16_t crc14(const uint8_t* data, size_t length) {
	uint16_t crc = 0x3fff; size_t i, bit;
	for (i = 0; i < length; i ++){
		crc ^= data[i] & 0x7f;
		for (bit = 0; bit < 7; bit ++){
			if (crc & 1) {
				crc >>= 1; crc ^= 0x22f0;
			}
			else{
				crc >>= 1;
			}
		}
	}
	return crc ^ 0x3fff;
}


/**********************************************************************************************
 * Function:        write_kangaroo_command(uint8_t address, uint8_t command, const uint8_t* data,
                                           uint8_t length, uint8_t* buffer)
 * Input:           address: the address of the Kangaroo.
 *                  command: the command number.
 *                  data: the command data.
 *                  length: the number of bytes of the data.
 *                  buffer: the buffer to write into.
 * Output:          How many bytes were written.
 * Notes:           Use this function to write a command into a buffer. The buffer can be
 *                  used to send the command to the Kangaroo using the mraa_uart_write function.
 *********************************************************************************************/

size_t write_kangaroo_command(uint8_t address, uint8_t command, const uint8_t* data,
                              uint8_t length, uint8_t* buffer){

    size_t i;
    uint16_t crc;

    buffer[0] = address;
    buffer[1] = command;
    buffer[2] = length;
    for (i = 0; i < length; i++) {
        buffer[3 + i] = data[i];
    }
    crc = crc14(buffer, length + 3);
    buffer[3 + length] = crc & 0x7F;		// crc low byte
    buffer[4 + length] = (crc >> 7) & 0x7F; // crc high byte

    return 5 + length;
}

/**********************************************************************************************
 * Function:        start_channel(uint8_t address, uint8_t channel_name)
 * Input:           address: the address of the Kangaroo.
 *                  channel_name: the name of the channel that will be initialized.
 *                  uart: the uart context to be written to
 * Output:          None.
 * Notes:           Starts a channel. The Kangaroo LED will shine brightly for a third of a
 *                  second. You must call this before Units, Home or Move commands will work.
 *********************************************************************************************/
void start_channel(mraa_uart_context uart, uint8_t address, uint8_t channel_name){
	fprintf(stdout, "Initializing channel!\n");

    uint8_t buffer[7];
    uint8_t data[2];
    // data for start command
    data[0] = channel_name;         // channel name, usually "1" or "2"
    data[1] = 0;                    // flags

    write_kangaroo_command(address, CMD_START, data, 2, buffer);

    mraa_uart_write(uart, buffer, 7);

    fprintf(stdout, "Channel Initialized!\n");
}
