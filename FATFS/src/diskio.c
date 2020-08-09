/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "ff_2_SPI_Link.h"

/* Private variables ---------------------------------------------------------*/
extern MSD_CARDINFO CardInfo;

/* Definitions of physical drive number for each drive */
#define DEV_RAM		1	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		0	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
//	DSTATUS stat;
//	int result;

	switch (pdrv) {
	case DEV_RAM :
		return 0;

	case DEV_MMC :
		return 0;

	case DEV_USB :
		return 0;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
//	DSTATUS stat;
//	int result;
	int Status;

	switch (pdrv) {
	case DEV_RAM :
		return STA_NOINIT;

	case DEV_MMC :
	{
		Status = MSD_Init();
		if(Status == 0)
		  return 0;
		else 
		  return STA_NOINIT;
	}

	case DEV_USB :
		return STA_NOINIT;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
//	DRESULT res;
//	int result;
	int Status;
	if( !count )
	{    
		return RES_PARERR;  /* count不能等于0，否则返回参数错误 */
	}

	switch (pdrv) 
	{
	case DEV_RAM :
		break ;

	case DEV_MMC :
	{
	 if(count==1)                
		{       
		  Status =  MSD_ReadSingleBlock( sector ,buff );
		}                                                
		else                       
		{   
		  Status = MSD_ReadMultiBlock( sector , buff ,count);
		}                                                
		if(Status == 0)
		{
		  return RES_OK;
		}
		else
		{
		  return RES_ERROR;
		}
	}
	case DEV_USB :
		break ;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
#if _READONLY == 0
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
//	DRESULT res;
//	int result;
	int Status;
	if( !count )
	{    
		return RES_PARERR;  /* count不能等于0，否则返回参数错误 */
	}

	switch (pdrv) 
	{
	case DEV_RAM :
		break;

	case DEV_MMC :
		if(count==1)            /* 1个sector的写操作 */      
		{   
		   Status = MSD_WriteSingleBlock( sector , (uint8_t *)(&buff[0]) ); 
		}                                                
		else                    /* 多个sector的写操作 */    
		{   
		   Status = MSD_WriteMultiBlock( sector , (uint8_t *)(&buff[0]) , count );	  
		}                                                
		if(Status == 0)
		{
		   return RES_OK;
		}
		else
		{
		   return RES_ERROR;
		}

	case DEV_USB :
		break;
	}

	return RES_PARERR;
}
#endif /* _READONLY */


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
//	int result;
	
	if (pdrv)
    {    
        return RES_PARERR; 
    }

	MSD_GetCardInfo(&CardInfo);
	
	switch (pdrv) 
	{
		case DEV_RAM :

			// Process of the command for the RAM drive

			return res;

		case DEV_MMC :

			// Process of the command for the MMC/SD card
			switch (cmd) 
			{
			  case CTRL_SYNC :
				  
				return RES_OK;

			  case GET_SECTOR_COUNT : 
				*(DWORD*)buff = CardInfo.Capacity/CardInfo.BlockSize;
				return RES_OK;

			  case GET_BLOCK_SIZE :
				*(WORD*)buff = CardInfo.BlockSize;
				return RES_OK;	

			  case CTRL_POWER :
				break;

			  case CTRL_LOCK :
				break;

			  case CTRL_EJECT :
				break;

			  /* MMC/SDC command */
			  case MMC_GET_TYPE :
				break;

			  case MMC_GET_CSD :
				break;

			  case MMC_GET_CID :
				break;

			  case MMC_GET_OCR :
				break;

			  case MMC_GET_SDSTAT :
				break;	
			} 

		case DEV_USB :

			// Process of the command the USB drive

			return res;
	}

	return RES_PARERR;
}

/* User defined function to give a current time to fatfs module          */
/* 31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
/* 15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{
   
    return 0;
}
