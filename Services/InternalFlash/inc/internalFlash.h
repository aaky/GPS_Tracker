#ifndef INTERNALFLASH_H
#define INTERNALFLASH_H

#include <stdint.h>
#include "Leaf_error_codes.h"



#define FLASH_USER_START_ADDR		0x0800FC00
#define FLASH_ERROR_CODE_ADDR		0x0800F800			

#define FLASH_READ			1
#define FLASH_WRITE			0

leaf_error_t UnblockFlash( void );
leaf_error_t LockFlash( void );
leaf_error_t WritePage(uint8_t * ) ;

leaf_error_t WritePacket(uint8_t * ) ;
leaf_error_t ReadPacket(uint8_t * ) ;


leaf_error_t WriteErrorCodeToFlash(uint8_t ) ;
leaf_error_t EraseErrorCodeSector( void ) ;

#endif

