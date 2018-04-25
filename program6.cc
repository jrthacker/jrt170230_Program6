/*
 * Program by: John Thacker - CS 3377.501
 * jrt170230@utdallas.edu
 * 
 *
 * 
 */

#include "program6.h"

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

  const char 		*rowTitles[MATRIX_HEIGHT + 1] = {"0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_WIDTH + 1] = {"0", "a", "b", "c"};
  int		boxWidths[MATRIX_WIDTH + 1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH + 1] = {vMIXED, vMIXED, vMIXED, vMIXED};

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

  ifstream binInfile (BINARY_FILE_NAME, ios::in | ios:: binary); // create ifstream object

  if (binInfile.fail()){				// verify file is opened
  	printf("Error opening file\n");
	_exit(1);
  }

  binInfile.read(reinterpret_cast<char *>(&myHeader->magicNumber), sizeof(myHeader->magicNumber)); // read from file
  binInfile.read(reinterpret_cast<char *>(&myHeader->versionNumber), sizeof(myHeader->versionNumber)); // read from file
  binInfile.read(reinterpret_cast<char *>(&myHeader->numRecords), sizeof(myHeader->numRecords)); // read from file

  /* Create strings for display */
	
  ostringstream outString;

  outString  << std::hex << myHeader->magicNumber; // create magic number string
  string magicNumber = "Magic: 0x" + outString.str();
  outString.str("");

  outString  << std::dec <<  myHeader->versionNumber; // create version number string
  string versionNumber = "Version: " + outString.str();
  outString.str("");

  outString  << std::dec <<  myHeader->numRecords; // create number count string
  string numRecords  = outString.str();
  int recCount = atoi(numRecords.c_str());	// convert string to int
  numRecords = "NumRecords: " + outString.str();
  outString.str("");

  // Display the header in the matrix
  setCDKMatrixCell(myMatrix, 1, 1, magicNumber.c_str()); // display magic number
  setCDKMatrixCell(myMatrix, 1, 2, versionNumber.c_str()); // display version number
  setCDKMatrixCell(myMatrix, 1, 3, numRecords.c_str()); // display record count



  /* Read records from file */

  BinaryFileRecord myRecord;

  if (recCount > 4)
  	recCount = 4; 						// only loop for 4 records

  for (int i = 0; i < recCount; i++) 					// loop for up to first four records
  {
  	binInfile.read(reinterpret_cast<char *>(&myRecord), sizeof(myRecord)); // read a file record

	outString << strlen(myRecord.stringBuffer);  // create string length output
	string strlen = "strlen: " + outString.str();
	outString.str("");

	outString << myRecord.stringBuffer;		// create string output
	string recordString = outString.str();
	outString.str("");

	setCDKMatrixCell(myMatrix, i+2, 1, strlen.c_str()); // display string length
	setCDKMatrixCell(myMatrix, i+2, 2, recordString.c_str()); // display string record buffer

  }
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
