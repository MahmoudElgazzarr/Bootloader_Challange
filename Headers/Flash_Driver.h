

#ifndef FLASH_DRIVER_H_
#define FLASH_DRIVER_H_


#include <avr/boot.h>
#include <avr/pgmspace.h>

#include <stdint.h>

#define MEM_PAGE_SIZE	SPM_PAGESIZE


#define	Wait_For_Mem_Ready()				boot_spm_busy_wait()
#define Fill_Page(ADDRESS,WORD)			boot_page_fill(ADDRESS,WORD)
#define Erase_Page(START_ADDRESS)		boot_page_erase(START_ADDRESS)
#define Write_Page(START_ADDRESS)		boot_page_write(START_ADDRESS)
#define Enable_Mem_Reading()				boot_rww_enable()



void Write_Mem_Page (uint8_t PageNumber, uint8_t page_buffer[],uint8_t buffer_fill_level);
uint8_t Read_Mem_Byte (uint32_t address);
void Read_Mem_Page (uint8_t FlashPageNumber,uint8_t  buffer[]);
void Clear_Buffer  (uint8_t buffer[],uint8_t BufferSize);


#endif /* FLASH_DRIVER_H_ */