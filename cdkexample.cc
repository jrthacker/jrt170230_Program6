/*
 * Program by: John Thacker - CS 3377.501
 * jrt170230@utdallas.edu
 * 
 *
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdint.h>
#include "cdk.h"


#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

class BinaryFileHeader
{
	public:

	uint32_t magicNumber;	// should be 0xFEEDFACE
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

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Remember that matrix starts out at 1,1.
  // Since arrays start out at 0, the first entries
  // below ("R0", and "C0") are just placeholders
  // 
  // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /* Read header from binary file */

  BinaryFileHeader *myHeader = new BinaryFileHeader(); // instantiate header class

  ifstream binInfile ("cs3377.bin", ios::in | ios:: binary); // create ifstream object

  binInfile.read(reinterpret_cast<char *>(&myHeader->magicNumber), sizeof(myHeader->magicNumber)); // read from file
  binInfile.read(reinterpret_cast<char *>(&myHeader->versionNumber), sizeof(myHeader->versionNumber)); // read from file
  binInfile.read(reinterpret_cast<char *>(&myHeader->numRecords), sizeof(myHeader->numRecords)); // read from file

  /* Create strings for display */
	
  ostringstream outString;

  outString  << std::hex << myHeader->magicNumber; // create magic number string
  string magicNumber = "Magic: 0x" + outString.str();
  outString.str("");

  outString  << std::dec << myHeader->versionNumber; // create version number string
  string versionNumber = "Version: " + outString.str();
  outString.str("");

  outString  << std::dec << myHeader->numRecords; // create number count string
  string numRecords = "NumRecords: " + outString.str(); 
  outString.str("");


  /*
   * Dipslay matrix
   */
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber.c_str()); // display magic number
  setCDKMatrixCell(myMatrix, 1, 2, versionNumber.c_str()); // display version number
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str()); // display record count
  
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
