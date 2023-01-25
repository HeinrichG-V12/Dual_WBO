/*
 * Dual_WBO.c
 *
 * Created: 12.12.2021 20:00:16
 * Author : Heinrich
 */ 

#include <avr/io.h>

#include "can/can_lib.h"

int main(void)
{
	uint8_t data[] = "Hallo";
	can_init(0);
	
	st_cmd_t canMsg;
	
	canMsg.id.ext = 0x180;
	canMsg.pt_data = &data[0];
	canMsg.dlc = 5;
	canMsg.cmd = CMD_TX_DATA;
	
	while(can_cmd(&canMsg) != CAN_CMD_ACCEPTED); // wait for MOb to configure
	
	while(can_get_status(&canMsg) == CAN_STATUS_NOT_COMPLETED); // wait for a transmit request to come in, and send a response
	
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

