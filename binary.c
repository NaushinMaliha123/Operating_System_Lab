#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

void printBinary(unsigned char byte)
{
    for (int bit = 7; bit >= 0; bit--)
    {
        printf("%d", (byte >> bit) & 1);
    }
}
void writeFile()
{
    char filename[100];
    char data[1000];

    FILE *fp;

    printf("\nEnter file name: ");
    scanf("%99s", filename);
    fp = fopen(filename, "ab");

    if (fp == NULL)
    {
        printf("Could not open file!\n");
        return;
    }

    getchar();

    printf("Enter data: ");
    fgets(data, sizeof(data), stdin);

    fwrite(data, sizeof(char), strlen(data), fp);

    fclose(fp);

    printf("Binary data written successfully.\n");
}
void readFile()
{
    char filename[100];

    unsigned char buffer[SIZE];

    size_t bytesRead;

    FILE *fp;

    printf("\nEnter file name: ");
    scanf("%99s", filename);

    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("\n----- Binary Data -----\n\n");

    long totalDisplayed = 0;

    while ((bytesRead = fread(buffer, 1, SIZE, fp)) > 0)
    {
        for (size_t i = 0; i < bytesRead; i++)
        {
            
            if (totalDisplayed >= 128)
                break;
            printBinary(buffer[i]);

            printf(" ");

            totalDisplayed++;

            if (totalDisplayed % 8 == 0)
            {
                printf("\n");
            }
        }

        if (totalDisplayed >= 128)
            break;
    }

    printf("\n--------------------------------\n");
    printf("Binary bytes displayed: %ld\n", totalDisplayed);

    fclose(fp);
}
void copyFile()
{
    char source[100];
    char destination[100];

    unsigned char buffer[SIZE];

    size_t bytesRead;
    size_t bytesWritten;

    FILE *src;
    FILE *dest;

    printf("\nEnter source file: ");
    scanf("%99s", source);

    printf("Enter destination file: ");
    scanf("%99s", destination);

    src = fopen(source, "rb");

    if (src == NULL)
    {
        printf("Source file not found!\n");
        return;
    }

    dest = fopen(destination, "wb");

    if (dest == NULL)
    {
        printf("Cannot create destination file!\n");
        fclose(src);
        return;
    }

    while ((bytesRead = fread(buffer, 1, SIZE, src)) > 0)
    {
        bytesWritten = fwrite(buffer, 1, bytesRead, dest);

        if (bytesWritten != bytesRead)
        {
            printf("Error while copying file!\n");

            fclose(src);
            fclose(dest);

            return;
        }
    }

    fclose(src);
    fclose(dest);

    printf("Binary file copied successfully.\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("       BINARY FILE OPERATIONS\n");
        printf("====================================\n");

        printf("1. Write File\n");
        printf("2. Read File as Binary\n");
        printf("3. Copy Binary File\n");
        printf("4. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            writeFile();
            break;

        case 2:
            readFile();
            break;

        case 3:
            copyFile();
            break;

        case 4:
            printf("Program terminated.\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}