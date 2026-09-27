#include <stdio.h>
#include <stdlib.h>

// 1. Create File
void createFile()
{
    char filename[100];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Error creating file!\n");
        return;
    }

    fclose(fp);
    printf("File created successfully.\n");
}

// 2. Write File
void writeFile()
{
    char filename[100];
    char ch;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "a");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    getchar(); // remove newline

    printf("Enter text: ");

    while ((ch = getchar()) != '\n')
    {
        fputc(ch, fp);
    }

    fputc('\n', fp);

    fclose(fp);

    printf("Data written successfully.\n");
}

// 3. Read File
void readFile()
{
    char filename[100];
    int ch;
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("\n----- File Content -----\n\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }

    printf("\n");

    fclose(fp);
}

// 4. Copy File
void copyFile()
{
    char source[100], destination[100];
    int ch;
    FILE *src, *dest;

    printf("Enter source file: ");
    scanf("%s", source);

    printf("Enter destination file: ");
    scanf("%s", destination);

    src = fopen(source, "r");

    if (src == NULL)
    {
        printf("Source file not found!\n");
        return;
    }

    dest = fopen(destination, "w");

    if (dest == NULL)
    {
        printf("Cannot create destination file!\n");
        fclose(src);
        return;
    }

    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copied successfully.\n");
}

// 5. Rename File
void renameFile()
{
    char oldname[100], newname[100];

    printf("Enter current file name: ");
    scanf("%s", oldname);

    printf("Enter new file name: ");
    scanf("%s", newname);

    if (rename(oldname, newname) == 0)
        printf("File renamed successfully.\n");
    else
        printf("Rename failed!\n");
}

// 6. Delete File
void deleteFile()
{
    char filename[100];

    printf("Enter file name: ");
    scanf("%s", filename);

    if (remove(filename) == 0)
        printf("File deleted successfully.\n");
    else
        printf("Delete failed!\n");
}

int main()
{
    int choice;

    while (1)
    {
        printf("\n=============================\n");
        printf("   FILE MANAGEMENT SYSTEM\n");
        printf("=============================\n");
        printf("1. Create File\n");
        printf("2. Write File\n");
        printf("3. Read File\n");
        printf("4. Copy File\n");
        printf("5. Rename File\n");
        printf("6. Delete File\n");
        printf("7. Exit\n");

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
            copyFile();
            break;

        case 5:
            renameFile();
            break;

        case 6:
            deleteFile();
            break;

        case 7:
            printf("Program terminated.\n");
            return 0;

        default:
            printf("Invalid choice!\n");
        }
    }
}