#include <stdio.h>
#include <stdlib.h>
#include "../Headers/inform.h"

#define PATH 300

FILE * UserFile;                            //!Stream to user file for reading

//!Get address and open stream for reading
//!Return: 0 - if read, -1 if error
int OpenFile(void)
{
    char *path;
    path = (char *)malloc(PATH* sizeof(char));                   //!Address to user file
    if(path == NULL)
    {
        printf("Not enough memory\n");
        return -1;
    }
    printf("Write path to your file:\n");
    gets(path);                                                      //!Get address
    UserFile = fopen(path,"r");                                   //!Open stream
    free(path);
    if(UserFile == NULL)
    {
        printf("File not found\n");
        return -1;
    }
    printf("File opened\n");
    return 0;
}

//!Read real numbers from user file
//!Return: real number
double ReadDataFromFile(void)
{
    double temp = 0;
    while (1)
    {
        if(fscanf(UserFile, "%lf", &temp) == 1)
        {
             if(temp < 100)                                                //!The number must have 2 digits in the integer part
                 return ((double)((int)(temp * 10)) / 10.0);             //!and 1 digit after the dot
        }
        if(feof(UserFile))
        {
            printf("All data in file read\n");
            return -1;
        }
    }
}

//!Close user file after getting numbers
void CloseFile(void)
{
    if(fclose(UserFile) != 0)
        printf("File can't be closed!\n");
    printf("File closed!\n");
}
