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
	sleep(5);
	//readMoveSpeed(uart0, address, channelName);
	//Clear the Read buffer from the Kangaroo
	clearRead(uart0);

	int32_t vels[11] = {-1000, -4000, -3000, -2000, -1000, 0 ,1000 ,2000, 3000, 4000, 1000};

	writeMoveSpeed(uart0, address, channelName, vels[5]);
		sleep(3);
		readMoveSpeed(uart0, address, channelName);
		sleep(5);
		writeMoveSpeed(uart0, address, channelName, vels[6]);
			sleep(3);
			readMoveSpeed(uart0, address, channelName);
			sleep(5);
			writeMoveSpeed(uart0, address, channelName, vels[7]);
				sleep(3);
				readMoveSpeed(uart0, address, channelName);
				sleep(5);
				writeMoveSpeed(uart0, address, channelName, vels[8]);
					sleep(3);
					readMoveSpeed(uart0, address, channelName);
					sleep(5);
					readMoveSpeed(uart0, address, channelName);
					sleep(5);
	//Power down channel
	power_down_channel(uart0, address, channelName);

	//Destroy the uart context
	uart_destroy(uart0);


	return 0;
}
