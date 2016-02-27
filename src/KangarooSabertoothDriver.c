#include <stdio.h>
#include <stdlib.h>


#include <stdio.h>
#include <stdlib.h>
#include "COMMAND_LIST.h"
#include "Kangaroo_Driver_Lib.h"
#include "mraa.h"
#include <unistd.h>

int main(){
	//Set up the uart connection
	mraa_uart_context uart0 = uart_setup();

	//Set up kangaroo params
	uint8_t address = 128;
	uint8_t channelName = '1';


	start_channel(uart0, address, channelName);


	int32_t vel = -3000;

	writeMoveSpeed(uart0, address, channelName, vel);
	fprintf(stdout,"yo");


	//Destroy the uart context
	uart_destroy(uart0);


	return 0;
}
