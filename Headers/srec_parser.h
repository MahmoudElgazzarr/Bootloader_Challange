
#ifndef SREC_PARSER_H_
#define SREC_PARSER_H_
#include <stdint.h>



#define SREC_HEADER			(0U)
#define SREC_TYPE			(1U)

#define SREC_TWO_BYTE_ADDRESS	('1')
#define SREC_HEADER_RECORD		('0')
#define SREC_TERMINATION_RECORD	('9')
#define RECORD_OK				('O')
#define RECORD_CHECK_SUM_ERROR	('C')
#define RECORD_HEADER_ERROR		('H')
#define RECORD_TYPE_ERROR		('T')
#define RECORD_SIZE_ERROR		('Z')
#define RECORD_TERMINATION		('E')

typedef struct
{
	unsigned char Record_Header;
	unsigned char Record_Type;
	uint8_t  ByteCount;
	uint16_t Address;
	uint8_t Checksum;
}Srec_record_t;



// TRUE and FALSE
#define TRUE  1
#define FALSE 0

//record definitions
#define MAX_DATA_IN_RECORD			(67U)
#define CHECKSUM_NUMBER_OF_BYTES	(1U)
#define ADDRESS_NUMBER_OF_BYTES		(2U)






// function prototypes
uint8_t AsciiByteToNumber(uint8_t high_nibble, uint8_t low_nibble);				// convert hex character to unsigned integer
uint8_t AsciiNibbleToNumber(uint8_t nibble);			// convert hex byte (two characters) to unsigned integer
uint8_t Srec_Process_Record(uint8_t *Srec_Record_Buff);			// parse the current s-record in the buffer



#endif /* SREC_PARSER_H_ */