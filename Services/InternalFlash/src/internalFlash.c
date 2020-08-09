#include "stm32f0xx_hal.h"
#include "cmsis_os.h"
#include "internalFlash.h"
#include "Leaf_error_codes.h"
#include "Leaf_structs.h"


static FLASH_EraseInitTypeDef EraseInitStruct;
static uint32_t PAGEError;

static leaf_error_t ErasePage( uint32_t memoryAddress );

/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t UnblockFlash( void )
{
	if( HAL_OK != HAL_FLASH_Unlock() )
	{
		return LEAF_STM_FLASH_UNLOCK_FAIL ; 
	}
	return LEAF_SUCCESS ;
}


/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t LockFlash( void )
{
	if( HAL_OK != HAL_FLASH_Lock() )
	{
		return LEAF_STM_FLASH_LOCK_FAIL ; 
	}
	return LEAF_SUCCESS ;
}


/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
static leaf_error_t ErasePage( uint32_t memoryAddress )
{
	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.PageAddress = memoryAddress; // FLASH_USER_START_ADDR;
	EraseInitStruct.NbPages     = 1;
	
	HAL_FLASHEx_Erase(&EraseInitStruct, &PAGEError);
	
	return LEAF_SUCCESS ;
} 

/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t WritePage(uint8_t *WritePtr)
{
	if( HAL_OK != HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR , ( (*(WritePtr+2) << 16) | (*(WritePtr+1) << 8) | *WritePtr) ) )
		return LEAF_STM_FLASH_WRITE_FAIL ;
			
	return LEAF_SUCCESS ;
}

/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t WritePacket(uint8_t *ptrData)
{
	UnblockFlash( );
	ErasePage( FLASH_USER_START_ADDR );
	WritePage( ptrData );
	LockFlash( );
	
	return LEAF_SUCCESS ;
}

/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t ReadPacket(uint8_t *ptrData)
{
	*ptrData++ = *((uint8_t *)FLASH_USER_START_ADDR) ;
	*ptrData++ = *((uint8_t *)(FLASH_USER_START_ADDR+1)) ;
	*ptrData   = *((uint8_t *)(FLASH_USER_START_ADDR+1)) ;
	
	return LEAF_SUCCESS ;
}

/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t WriteErrorCodeToFlash(uint8_t errorCode)
{
	UnblockFlash( );
	ErasePage( FLASH_ERROR_CODE_ADDR );
	HAL_FLASH_Program( FLASH_TYPEPROGRAM_WORD, FLASH_USER_START_ADDR , FLASH_ERROR_CODE_ADDR ) ; 
	LockFlash( );
	
	return LEAF_SUCCESS ;
}



/*!
 * \fn      
 * 
 * \param[in] 
 * \param[in] 
 * 
 * \brief   
 * \details 
 * \note    
 * \return  None.
 */
leaf_error_t EraseErrorCodeSector( void )
{
	UnblockFlash( );
	ErasePage( FLASH_ERROR_CODE_ADDR );
	LockFlash( );
	
	return LEAF_SUCCESS ;
}

