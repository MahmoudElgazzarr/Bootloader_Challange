
 #include "srec_parser.h"
 #include "Flash_Driver.h"
 #include "uart_driver.h"
 
 #define DEBUG_ENABLE (0)
 
 static uint8_t Mem_Page_To_Write = 0x0000;
 volatile static char received_Record_Counter = 0;	

uint8_t AsciiNibbleToNumber(uint8_t nibble)
{
	uint8_t nibble_Number = 0;
	if(nibble <= '9')
	{
		nibble_Number = nibble - '0';
	}
	else
	{
		nibble_Number = nibble - 'A' + 10;
	}
	
	return nibble_Number ;
}


uint8_t AsciiByteToNumber(uint8_t high_nibble, uint8_t low_nibble)
{
	uint8_t high_Nibble_Number = 0;
	uint8_t low_Nibble_Number = 0;
	uint8_t number = 0;
	/* Academy: Make an algorith m to convert two hex-converted chars into one hex byte */
	/*Todo*/
	return number;
}

 uint8_t Srec_Process_Record(uint8_t Srec_Record_Buff[])
 {
	static uint8_t page_Buffer_Fill_Level = 0;
	 Srec_record_t s_record;
	 uint8_t page_Buffer[128];
	 uint8_t high_Nibble_temp = 0;
	 uint8_t low_Nibble_temp  = 0;
	 uint8_t temp_byte = 0;
	
	 uint8_t result = RECORD_OK;

	 s_record.Record_Header = Srec_Record_Buff[SREC_HEADER];
	 s_record.Record_Type	= Srec_Record_Buff[SREC_TYPE];
	 Srec_Record_Buff+=2;
	 if(s_record.Record_Header == 0 )
	 {
		 
		 if((s_record.Record_Type == SREC_TWO_BYTE_ADDRESS))
		 {
			 high_Nibble_temp = Srec_Record_Buff[0];
			 low_Nibble_temp  = Srec_Record_Buff[1];
			 Srec_Record_Buff+=2;
			 temp_byte = AsciiByteToNumber(high_Nibble_temp, low_Nibble_temp);
			 s_record.ByteCount = temp_byte;
			 #if DEBUG_ENABLE
			 UART_Write_String("ByteCount: ");
			 UART_Write_Byte(high_Nibble_temp);
			 UART_Write_Byte(low_Nibble_temp);
			 #endif
			 if(s_record.ByteCount <= 19)
			 {
				
				/* Academy: Here means it a Srec data record then take each two ASCII char and convert them into 
				one hex byte in a buffer called "page_Buffer" and their counts in "page_Buffer_Fill_Level" */
				
				
				if(s_record.Checksum != 0xFF)
				{
					
					result =  RECORD_CHECK_SUM_ERROR;
				}
				 
			 }
			 else
			 {
				 result = RECORD_SIZE_ERROR;
			 }
			 
			 
			 
		 }
		 else if ((s_record.Record_Type == SREC_HEADER_RECORD) || (s_record.Record_Type == SREC_TERMINATION_RECORD))
		 {
		 }
		 else
		 {
			result = RECORD_TYPE_ERROR;
		 }
		
		 if((s_record.Record_Type == SREC_TERMINATION_RECORD))
		 {
			 result = RECORD_TERMINATION;
		 }
		 
		 
	 }
	 else
	 {
		 result = RECORD_HEADER_ERROR;
	 }
	 
	 // get page size ==> 16(data in one record) * 8 records = 128 (size of one page)
	 // or get the termination record
	 if((received_Record_Counter == 8) || (result == RECORD_TERMINATION))
	 {
		received_Record_Counter = 0;
		Write_Mem_Page (Mem_Page_To_Write,page_Buffer,page_Buffer_Fill_Level);
		page_Buffer_Fill_Level = 0;
		Mem_Page_To_Write ++;
		 
	 }
	 return result;
 }


 



