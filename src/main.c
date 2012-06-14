#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vcryptor.h>

int main(int argc, char* argv[])
{
    // Encrypt or decrypt
    char    do_encrypt = FALSE;
    
    // Name of file and password
    char *fileName, *password;

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
            do_encrypt = FALSE;
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
        printf("For decryption: set flag equal to -d\n\n");
        exit(EXIT_SUCCESS);
    }
    else
    {   printf("Incorrect number of arguments.\n");
        printf("For help try vcryptor -h\n");
        exit(EXIT_FAILURE);
    }

    // Get file name
    fileName = argv[1];

    // Get password
    password = argv[2];
    
    // Encrypt or decrypt the file
    cryption(fileName, password, do_encrypt);
    
    // Pauses console before closing
    printf("Press <ENTER> to continue...");
    getchar();

    return 0;
}
