/*
 * BEheader.h
 *
 * Created: 03.09.2017 23:09:47
 *  Author: radiolok
 */ 


#ifndef BFHEADER_H_
#define BFHEADER_H_



#define BF_MAGIC 0x4246
#define BF_INDENT 0x10

#define MEMORY_PTR_MAX 65535

#define SECTION_CODE 0x01
#define SECTION_DATA 0x02
#define SECTION_VIDEO 0x03


typedef struct _BfSection_t{
	uint16_t FileBase;//Relative shift from the beginning of file
	uint16_t MemoryBase;//Physical address to load
	uint16_t FileSize;//How much Bytes of data can be loaded to memory
	uint16_t MemorySize;//How much Words in Memory should be allocated
	uint8_t type;
	uint8_t pad;
}BfSection_t;

typedef struct _BfHeader_t{
	uint16_t Magic;//BF should contain "BF" symbols
	uint8_t Machine;//8bit of 16bit mode
	uint8_t HeaderSize;
	uint8_t SectionNum;
	uint8_t flags;
	uint16_t IpEntry;//IP start address
	uint16_t ApEntry;//AP start address
} BfHeader_t;




#endif /* BFHEADER_H_ */