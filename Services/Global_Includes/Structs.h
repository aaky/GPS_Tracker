/**********************************************************************/
/*!
 * \copyright   All Rights Reserved. (C)2016 Leaf Technologies
 * \file        Leaf_structs.h
 * \brief       Defining strutures which will be used by all services   
 *              .
 * \author      Akash Patil 
 * \date        02-Feb-2016
 * \section     History
 * <pre>
 *              Date        Responsible         Description
 *              20160202    Akash Patil		      File Created
 * </pre>
 */
/**********************************************************************/
#ifndef LEAF_STRUCTS_H
#define LEAF_STRUCTS_H

#include<stdint.h>

#define MAX_I2C_BODY_SIZE					(40)

/*I2C packet for communication between between nrf51 and STM32*/
typedef struct{
	uint8_t 	start_byte;
	uint8_t 	length;
	uint16_t	protocol_version;
	uint8_t 	msg_type;
	uint8_t 	data[MAX_I2C_BODY_SIZE] ;
	uint8_t 	checksum;
	uint8_t 	stop_byte;
} nrf_stm_commn_i2c_t;

/* Phase regulator values */
typedef struct{
	uint32_t phase_on_period ;
	uint32_t phase_off_period ;
	uint32_t phase_duty_cycle ;
}phase_reg_t ;


typedef enum
{
	I2C_IDLE,
	I2C_DATA_SENDING_IN_PROGRESS,
	I2C_DATA_SENT,
	I2C_SYNC_PACKET_SENT,
	I2C_DATA_RECEIVE_IN_PROGRESS,
	I2C_DATA_RECEIVED,
	I2C_BUS_ERROR,
}i2c_bus_state;


#endif
