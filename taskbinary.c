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

void createFile()
{
    char filename[100];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%99s", filename);
    fp = fopen(filename, "wb");

    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }
    fclose(fp);
    printf("Binary file created successfully.\n");
}

void writeFile()
{
    char filename[100];
    char data[1000];
    FILE *fp;
    printf("Enter file name: ");
    scanf("%99s", filename);

    fp = fopen(filename, "ab");

    if (fp == NULL)
    {
        printf("File not found!\n");
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

    printf("Enter file name: ");
    scanf("%99s", filename);
    fp = fopen(filename, "rb");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("\n----- Binary Data -----\n");
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

    printf("\n");
    printf("--------------------------------\n");
    printf("Binary bytes displayed: %ld\n", totalDisplayed);

    fclose(fp);
}
void updateFile()
{
    char filename[100];
    char data[100];
    long position;

    FILE *fp;

    printf("Enter file name: ");
    scanf("%99s", filename);
     fp = fopen(filename, "rb+");
    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("Enter byte position: ");
    scanf("%ld", &position);

    getchar();

    printf("Enter new data: ");
    fgets(data, sizeof(data), stdin);

    if (fseek(fp, position, SEEK_SET) != 0)
    {
        printf("Could not move to position!\n");
        fclose(fp);
        return;
    }

    fwrite(data, sizeof(char), strlen(data), fp);

    fclose(fp);

    printf("File updated successfully.\n");
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

     printf("Enter source file: ");
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

void renameFile()
{
    char oldname[100];
    char newname[100];

    printf("Enter current file name: ");
    scanf("%99s", oldname);

    printf("Enter new file name: ");
    scanf("%99s", newname);

    if (rename(oldname, newname) == 0)
    {
        printf("File renamed successfully.\n");
    }
    else
    {
        printf("Rename failed!\n");
    }
}

void deleteFile()
{
    char filename[100];

    printf("Enter file name: ");
    scanf("%99s", filename);

    if (remove(filename) == 0)
    {
        printf("File deleted successfully.\n");
    }
    else
    {
        printf("Delete failed!\n");
    }
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("     BINARY FILE MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File as Binary\n");
        printf("4. Update File\n");
        printf("5. Copy File\n");
        printf("6. Rename File\n");
        printf("7. Delete File\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createFile();
            break;

        case 2:
            writeFile();
            break;

        case 3:
            readFile();
            break;

        case 4:
            updateFile();
            break;

        case 5:
            copyFile();
            break;

        case 6:
            renameFile();
            break;

        case 7:
            deleteFile();
            break;

        case 8:
            printf("Program terminated.\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

