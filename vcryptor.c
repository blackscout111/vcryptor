#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////////////////////////////////////////////
// Function prototypes
///////////////////////////////////////////////////////////////

#define BLOCK_DIM 256
#define TRUE 1
#define FALSE 0

// Checks if a file is opened
void isFileOpen(FILE* filePtr, char* fileName);

// Fills the encryption and decryption blocks
void fill_blocks(
		char eblock[BLOCK_DIM][BLOCK_DIM],
		char dblock[BLOCK_DIM][BLOCK_DIM]
		);

// Prints the encryption block
void printBlock(char* fileName, char block[BLOCK_DIM][BLOCK_DIM]);

// Encrypts or decrypts the file
void transform(	
		FILE* filePtr,
		char* password,
		char block[BLOCK_DIM][BLOCK_DIM]
		);

///////////////////////////////////////////////////////////////
// Main
///////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	// Encrypt or decrypt
	char	do_encrypt = FALSE,
		do_decrypt = FALSE;
	
	// Name of file and password
	char *fileName, *password;

	// Pointer to file
	FILE *filePtr;
	
	// Block used for encryption and decryption
	char	eblock[BLOCK_DIM][BLOCK_DIM],
		dblock[BLOCK_DIM][BLOCK_DIM];

	// Checks to see the number of arguments is correct and then sets
	// the status of the program (encryption or decryption)
	if (argc == 4)
	{
		// Check the flag status
		// -e for encrypt
		// -d for decrypt
		if (strcmp(argv[3],"-e") == 0)
		{
			do_encrypt = TRUE;
		}
		else if (strcmp(argv[3],"-d") == 0)
		{
			do_decrypt = TRUE;
		}
		else
		{
			printf("Incorrect number of arguments.\n");
			printf("For help try vcryptor -h\n");
			exit(EXIT_FAILURE);
		}
	}
	else if (argc == 2 && (strcmp(argv[1],"-h") == 0))
	{
		printf("\n|vcryptor help|\n");
		printf("vcryptor.exe [file name] [password] [flag]\n");
		printf("For encryption: set flag equal to -e\n");
		printf("For decryption: set flag equal to -d\n");
		exit(EXIT_SUCCESS);
	}
	else
	{	printf("Incorrect number of arguments.\n");
		printf("For help try vcryptor -h\n");
		exit(EXIT_FAILURE);
	}


	// Get file name
	fileName = argv[1];

	// Get password
	password = argv[2];
	
	// Open file
	filePtr = fopen(fileName, "rb+");
	isFileOpen(filePtr, fileName);

	// Initializes encryption and decryption blocks
	fill_blocks(eblock, dblock);

	// Prints eblock to eblock.txt and dblock ot dblock.txt 
/*	printBlock("eblock.csv", eblock);
	printBlock("dblock.csv", dblock);
*/

	// Encrypts or decrypts file
	if (do_encrypt)
	{
		printf("Encrypting file...\n");
		transform(filePtr, password, eblock); 
		printf("File encrypted successfully!\n");
	}
	else if (do_decrypt)
	{
		printf("Decrypting file...\n");
		transform(filePtr, password, dblock); 
		printf("File decrypted successfully!\n");
	}

	// Closes file
	fclose(filePtr);

	// Pauses console before closing
	printf("Press <ENTER> to continue...");
	getchar();

	return 0;
}


///////////////////////////////////////////////////////////////
// Function Definitions
///////////////////////////////////////////////////////////////

void isFileOpen(FILE* filePtr, char* fileName)
{
	if (filePtr == NULL)
	{
		printf("ERROR: Could not open %s\n",fileName);
		exit(EXIT_FAILURE);
	}
}



void fill_blocks(
		char eblock[BLOCK_DIM][BLOCK_DIM],
		char dblock[BLOCK_DIM][BLOCK_DIM]
		)
{
	int row, col;	// index variables
	for (row = 0; row < BLOCK_DIM; row++)
	{
		for (col = 0; col < BLOCK_DIM; col++)
		{
			int sum = col + row;
			if (sum < BLOCK_DIM)
			{
				eblock[row][col] = sum;
				dblock[row][sum] = col;
			}
			else
			{
				eblock[row][col] = sum % BLOCK_DIM;
				dblock[row][sum % BLOCK_DIM] = col;
			}
		}
	}
}



void printBlock(char* fileName, char block[BLOCK_DIM][BLOCK_DIM])
{
	// File pointer to csv file
	FILE *csvPtr = fopen(fileName, "wb+");
	isFileOpen(csvPtr, fileName);	// check if file is open

	// Writes block to file in csv format
	printf("Printing %s...\n", fileName);
	int row, col;	// loop variables
	for (row = 0; row < BLOCK_DIM; row++)
	{
		for (col = 0; col < BLOCK_DIM; col++)
		{
			// The delimeter between entries
			char delim;
			if (col == (BLOCK_DIM - 1))
			{
				delim = '\n';
			}
			else
			{
				delim = ',';
			}

			// Print the entry and the delimeter to file
			fprintf(csvPtr, "%d %c",
				(unsigned char)block[row][col], delim);
		}
	}
	printf("Printed successfully!\n");

	// Close the file
	fclose(csvPtr);
}



void transform(
		FILE* filePtr,
		char* password,
		char block[BLOCK_DIM][BLOCK_DIM]
		)
{
	// Password length
	int passlen = strlen(password);

	// Buffer for file data and sets all of buf to 0
	char *buf = (char*)calloc(passlen, sizeof(char));
	memset(buf, 0, passlen);

	// Position in buffer
	int bufPos = 0;

	// File position
	long filePos = ftell(filePtr);

	// Number of bytes read and number of bytes written
	int	numRead = 0,
		numWrit = 0;

	// Read in and edit file data
	while ((numRead = fread(buf, sizeof(char), passlen, filePtr)) != 0)
	{
		// Returns file position to where it was before last read
		int seekStatus = fseek(filePtr, filePos, SEEK_SET);

		// Transforms buffer data
		for (bufPos = 0; bufPos < numRead; bufPos++)
		{
			unsigned char	index1 = password[bufPos],
					index2 = buf[bufPos];

			buf[bufPos] = block[index1][index2];
		}

		// Writes transformed buffer back to file
		numWrit = fwrite(buf, sizeof(char), numRead, filePtr);

		// Get file position
		filePos = ftell(filePtr);
	}
}
