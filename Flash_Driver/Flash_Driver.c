

 #include "Flash_Driver.h"
 
 
 
 void Write_Mem_Page (uint8_t page_number, uint8_t page_buffer[],uint8_t buffer_fill_level)
 {
	 uint8_t index;
	 uint16_t word_To_Write;													
	 uint32_t page_Base_Address = 	page_number * MEM_PAGE_SIZE;				
	 Erase_Page (page_Base_Address);
	 Wait_For_Mem_Ready();			
	 
	 for (index=0; index < buffer_fill_level; index+=2)
	 {
		 
		 word_To_Write  = /* Academy: Take each two bytes then store them here as little endian*/
		 page_buffer+=2;
		 
		 Fill_Page ((page_Base_Address + (uint32_t)index), word_To_Write);
	 }
	 
	 Write_Page (page_Base_Address);     
	 Wait_For_Mem_Ready();					
	 Enable_Mem_Reading();
	
 }



 uint8_t Read_Mem_Byte (uint32_t address)
 {
	uint8_t byte_Value = pgm_read_byte(address);			
	return byte_Value;
 }


 void  Read_Mem_Page (uint8_t page_number, uint8_t buffer[])
 {
	 uint8_t index = 0;
	 uint32_t address = (page_number * MEM_PAGE_SIZE);			
	
		for (index = 0; index < MEM_PAGE_SIZE; index++)
		{
			buffer[index] = Read_Mem_Byte(address + index);
			Wait_For_Mem_Ready();
		}
 }
 
 
 void Clear_Buffer(uint8_t buffer[],uint8_t BufferSize)
 {
     uint8_t index;
	 for(index=0;index < BufferSize;index++)
	 {
		 buffer[index] = 0;
	 }
 }