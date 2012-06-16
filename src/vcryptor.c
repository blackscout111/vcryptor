#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vcryptor.h>

//______________________________________________________________________________
// Checks if a file is opened
void isFileOpen(FILE* filePtr, const char* fileName)
{
    if (filePtr == NULL)
    {
        printf("ERROR: Could not open %s\n",fileName);
        exit(EXIT_FAILURE);
    }
}


//______________________________________________________________________________
// Fills the encryption and decryption blocks
void fill_blocks(
        char eblock[BLOCK_DIM][BLOCK_DIM],
        char dblock[BLOCK_DIM][BLOCK_DIM]
        )
{
    int row, col;    // index variables
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


//______________________________________________________________________________
void printBlock(const char* fileName, const char block[BLOCK_DIM][BLOCK_DIM])
{
    // File pointer to csv file
    FILE *csvPtr = fopen(fileName, "wb+");
    isFileOpen(csvPtr, fileName);    // check if file is open

    // Writes block to file in csv format
    printf("Printing %s...\n", fileName);
    int row, col;    // loop variables
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


//______________________________________________________________________________
// Performs the encryption or decryption process on file
void transform(
        FILE* filePtr,
        const char* password,
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
    int numRead = 0;

    // Read in and edit file data
    while ((numRead = fread(buf, sizeof(char), passlen, filePtr)) != 0)
    {
        // Returns file position to where it was before last read
        fseek(filePtr, filePos, SEEK_SET);

        // Transforms buffer data
        for (bufPos = 0; bufPos < numRead; bufPos++)
        {
            unsigned char    index1 = password[bufPos],
                    index2 = buf[bufPos];

            buf[bufPos] = block[index1][index2];
        }

        // Writes transformed buffer back to file
        fwrite(buf, sizeof(char), numRead, filePtr);

        // Get file position
        filePos = ftell(filePtr);
    }
}


//______________________________________________________________________________
// Encrypts or decrypts the file
void cryption(
        const char* fileName,
        const char* password,
        const unsigned char  do_encrypt     // If TRUE then encryption
        )                                   // If FALSE then decryption
{
    // Pointer to file
    FILE *filePtr;
    
    // Block used for encryption and decryption
    char    eblock[BLOCK_DIM][BLOCK_DIM],
            dblock[BLOCK_DIM][BLOCK_DIM];
            
    // Open file
    filePtr = fopen(fileName, "rb+");
    isFileOpen(filePtr, fileName);

    // Initializes encryption and decryption blocks
    fill_blocks(eblock, dblock);

    // Prints eblock to eblock.txt and dblock ot dblock.txt 
/*    printBlock("eblock.csv", eblock);*/
/*    printBlock("dblock.csv", dblock);*/

    // Encrypts or decrypts file
    if (do_encrypt)
    {
        printf("Encrypting file...\n");
        transform(filePtr, password, eblock); 
        printf("File encrypted successfully!\n");
    }
    else
    {
        printf("Decrypting file...\n");
        transform(filePtr, password, dblock); 
        printf("File decrypted successfully!\n");
    }

    // Closes file
    fclose(filePtr);
}
