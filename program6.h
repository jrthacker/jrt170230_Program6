// Program by: John Thacker - CS3377.501
// jrt170230@utdallas.edu
//
# ifndef _PROGRAM6_H_
# define _PROGRAM6_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Binary File Contents"
#define BINARY_FILE_NAME "cs3377.bin"

using namespace std;

class BinaryFileHeader
{
        public:
	uint32_t magicNumber;   // should be 0xFEEDFACE
	uint32_t versionNumber;
	uint64_t numRecords;
};

	const int maxRecordStringLength = 25;

class BinaryFileRecord
{
	public:
	uint8_t strLength;						        
	char stringBuffer[maxRecordStringLength];
};

#endif //_PROGRAM6_H_
