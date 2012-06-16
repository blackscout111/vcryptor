#ifndef vcryptor_h
#define vcryptor_h

#define BLOCK_DIM 256
#define TRUE 1
#define FALSE 0

// Checks if a file is opened
void isFileOpen(FILE* filePtr, const char* fileName);

// Fills the encryption and decryption blocks
void fill_blocks(
        char eblock[BLOCK_DIM][BLOCK_DIM],
        char dblock[BLOCK_DIM][BLOCK_DIM]
        );

// Prints the encryption block
void printBlock(const char* fileName, const char block[BLOCK_DIM][BLOCK_DIM]);

// Performs the encryption or decryption process on file
void transform(    
        FILE* filePtr,
        const char* password,
        char block[BLOCK_DIM][BLOCK_DIM]
        );

// Encrypts or decrypts the file
void cryption(
        const char* fileName,
        const char* password,
        const unsigned char  do_encrypt     // If TRUE then encryption
        );                                  // If FALSE then decryption

#endif
