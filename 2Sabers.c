/**
 * File Name: 2Sabers.c
 * Description: Test controlling 2 Kangaroos using the Edison
 */

#include <stdio.h>
#include <stdlib.h>
#include "COMMAND_LIST.h"
#include "Kangaroo_Driver_Lib.h"
#include "mraa.h"
#include <unistd.h>

int main()
{

	//Set up the uart connection
	mraa_uart_context uart0 = uart_setup();

	//Set up Kangaroos parameters
	uint8_t address1 = 128;
	uint8_t channelName1_1 = '1';
	uint8_t channelName1_2 = '2';
	uint8_t address2 = 129;
	uint8_t channelName2_1 = '1';
	uint8_t channelName2_2 = '2';

	//Start the Kangaroos channels
	start_channel(uart0, address1, channelName1_1);
	start_channel(uart0, address1, channelName1_2);
	start_channel(uart0, address2, channelName2_1);
	start_channel(uart0, address2, channelName2_2);

	sleep(5);

	//readMoveSpeed(uart0, address, channelName);
	//Clear the Read buffer from the Kangaroos
	clearRead(uart0);

	int32_t vels[4] = {-4000, -2000, 2000, 4000};

	writeMoveSpeed(uart0, address1, channelName1_1, vels[0]);
	sleep(3);
	fprintf(stdout, "Read Speed on Kangaroo 128, channel 1: \n");
	readMoveSpeed(uart0, address1, channelName1_1);
	sleep(5);
	writeMoveSpeed(uart0, address1, channelName1_2, vels[2]);
	sleep(3);
	fprintf(stdout, "Read Speed on Kangaroo 128, channel 2: \n");
	readMoveSpeed(uart0, address1, channelName1_2);
	sleep(5);
	writeMoveSpeed(uart0, address2, channelName2_1, vels[3]);
	sleep(3);
	fprintf(stdout, "Read Speed on Kangaroo 129, channel 1: \n");
	readMoveSpeed(uart0, address2, channelName2_1);
	sleep(5);
	writeMoveSpeed(uart0, address2, channelName2_2, vels[1]);
	sleep(3);
	fprintf(stdout, "Read Speed on Kangaroo 129, channel 2: \n");
	readMoveSpeed(uart0, address2, channelName2_2);
	sleep(5);

	//Destroy the uart context
	uart_destroy(uart0);

	return 0;
}
