/*Copyright (c) 2019, Artem Kashkanov
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted 
provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of 
conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list 
of conditions and the following disclaimer in the documentation and/or other materials 
provided with the distribution.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR 
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS 
BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT 
 OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/


#ifndef __IMAGELOADER_H__
#define __IMAGELOADER_H__

#include <stdint.h>

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

class ImageLoader
{

//functions
public:
	ImageLoader();
	~ImageLoader();
protected:
private:
	ImageLoader( const ImageLoader &c );
	ImageLoader& operator=( const ImageLoader &c );



}; //ImageLoader

#endif //__IMAGELOADER_H__
