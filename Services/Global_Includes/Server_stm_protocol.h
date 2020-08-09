#ifndef LEAF_NRF_STM_PROTOCOL_H
#define LEAF_NRF_STM_PROTOCOL_H

#define TRUE			1
#define FALSE     0

typedef enum eMessageID
{
	eCONTROL_ON_OFF								=	11,
	eCONTROL_ON_OFF_ACK							=	22,
	eCHILD_LOCK                                 =	12,
	eCHILD_LOCK_ACK								=	23,
	eONE_TOUCH									=	13,
	eONE_TOUCH_ACK								=	13,
	eDEVICE_DIMMING_CONFIG						=	73,
	eDEVICE_DIMMING_CONFIG_ACK                  =	73,
	ePHASE_REGULATOR_LEVEL						=	101,
	ePHASE_REGULATOR_LEVEL_ACK					=	102,
	eREQUEST_DIMMING_CONFIG_LOAD_CONFIG			=	104,
	eREPLY_DIMMING_CONFIG_LOAD_CONFIG			=	105,
	eRequestLastSwitchStatusAll					=	108,
	eReplyLastSwitchStatusAll					=	109,
	eUpdateCurrentAlfredStatus					=	110,
	eAccessSTM_FlashQuery						=	131,
	eReplySTM_FlashQuery						=	132,
	eDiscreteRegulatorDimmingVal                =   133,
	eDiscreteRegulatorDimmingAck                =   134,
	eADC_5V_TEST_REQUEST						=	136,
	eADC_5V_TEST_FEEDBACK						=	137,
	eSTM_ERROR_LOG								=	140,
	eDoor_Lock									=	39,
	eDoor_Lock_Ack								=	39,
	eZCD_ISR_Test								=	135
}eMessageID_t ;



#endif
