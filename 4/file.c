/**
 * \file file.c
 * \brief Functions for work with files.
 *
 * \details Functions to read and write files.
 */

#include "stdlib.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "struct.h"
#include "file.h"

/** \brief Write one structure into file
 *
 * \param fd File descriptor
 * \param person structure
 * 
 * \return completion status.
 */

int writeOne(int fd, struct Person person)
{
    int count = sizeof (person);
    ssize_t leftToWrite = count;
    int emptyToWrite = 0;
    while (leftToWrite > emptyToWrite)
    {
        ssize_t written = write(fd, &person, count);
        if (written == ERROR_CODE)
        {
            return ERROR_CODE;
        }
        else
        {
            leftToWrite -= written;
        }
    }

    return count;
}

/** \brief Read one structure from file
 *
 * \param fd File descriptor
 * \param buf buffer for store
 * \param bufferSize in bites
 * 
 * \return completion status.
 */

int readOne(int fd, void* buf, int bufferSize)
{
    ssize_t leftToRead = bufferSize;
    int emptyToWrite = 0;
    while (leftToRead > emptyToWrite)
    {
        ssize_t readBytes = read(fd, buf, bufferSize);
        if (readBytes == ERROR_CODE)
        {
            return ERROR_CODE;
        }
        else
        {
            leftToRead -= readBytes;
        }
    }
    return STATUS_SUCCESS;
}

/** \brief Gets size of file
 *
 * \param filename filename name of file
 * 
 * \return size of file.
 */

int getSize(char filename[])
{
    int count = 0;
    int fd = open(filename, O_RDONLY);
    if (fd == ERROR_CODE)
        return ERROR_CODE;

    int end = lseek(fd, 0, SEEK_END);
    if (end == ERROR_CODE)
        return ERROR_CODE;
    int size = sizeof (struct Person);
    count = end / size;
    close(fd);
    return count;
}

/** \brief Write data into file
 *
 * \param argv list of arguments
 * \param filename name of file
 * 
 * \return completion status.
 */

int addData(char* argv[], char filename[])
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fd = open(filename, O_CREAT |O_WRONLY, mode);
    if (fd == ERROR_CODE)
        return ERROR_CODE;

    off_t offset = lseek(fd, 0, SEEK_END);
    if (offset == ERROR_CODE)
        return ERROR_CODE;

    struct Person person = getPerson(argv);
    ssize_t sizeWritten = writeOne(fd, person);
    if (sizeWritten == ERROR_CODE)
        return ERROR_CODE;
    
    close(fd);

    return STATUS_SUCCESS;
}

/** \brief Removes data from file
 *
 * \param argv list of arguments
 * \param count size of file
 * \param filename name of file
 * \param filename2 name of file for temporary store
 * 
 * \return completion status.
 */

int removeData(char* argv[], int count, char filename[], char filename2[])
{
    struct Person person;
    int delItem = 0;
    if (atoi(argv[2]))
    {
        delItem = atoi(argv[2]) - 1;
    }
    else
    {
        return ERROR_CODE;
    }

    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH;
    int fd = open(filename, O_CREAT | O_RDWR, mode);
    if (fd == ERROR_CODE)
        return ERROR_CODE;

    int fd2 = open(filename2, O_CREAT | O_RDWR, mode);
    if (fd2 == ERROR_CODE)
        return ERROR_CODE;

    for (int i = 0; i < count; ++i)
    {
        if (i == delItem)
        {
            off_t offset = lseek(fd, sizeof (struct Person), SEEK_CUR);
            if (offset == ERROR_CODE)
                return ERROR_CODE;
        }
        else
        {
            ssize_t sizeRead = readOne(fd, &person, sizeof (person));
            if (sizeRead == ERROR_CODE)
            {
                return ERROR_CODE;
            }
            ssize_t sizeWritten = writeOne(fd2, person);
            if (sizeWritten == ERROR_CODE)
            {
                return ERROR_CODE;
            }
        }
    }
    close(fd);
    close(fd2);
    remove(filename);
    rename(filename2, filename);
    return STATUS_SUCCESS;
}

/** \brief Change data in the file
 *
 * \param argv list of arguments
 * \param count size of file
 * \param filename name of file
 * 
 * \return completion status.
 */

int changeData(char* argv[], int count, char filename[])
{
    struct Person person;
    int editItem = 0;
    if (atoi(argv[2]))
    {
        editItem = atoi(argv[2]) - 1;
    }
    else
    {
        return ERROR_CODE;
    }

    int fd = open(filename, O_RDWR);
    off_t offset = lseek(fd, sizeof (struct Person) * editItem, SEEK_SET);
    if (offset == ERROR_CODE)
        return ERROR_CODE;
    
    ssize_t sizeRead = readOne(fd, &person, sizeof (person));
    if (sizeRead == ERROR_CODE)
        return ERROR_CODE;

    if (strcmp(argv[3], "-"))
    {
        strcpy(person.name, argv[3]);
    }
    if (strcmp(argv[4], "-"))
    {
        strcpy(person.surname, argv[4]);
    }
    if (strcmp(argv[5], "-"))
    {
        if (!atoi(argv[5]))
            return ERROR_CODE;

        person.height = atoi(argv[5]);
    }
    offset = lseek(fd, sizeof (struct Person) * editItem, SEEK_SET);
    if (offset == ERROR_CODE)
        return ERROR_CODE;
    
    ssize_t sizeWritten = writeOne(fd, person);
    if (sizeWritten == ERROR_CODE)
        return ERROR_CODE;

    return STATUS_SUCCESS;
}

/** \brief Gets max height from specific index
 *
 * \param argv list of arguments
 * \param count size of file
 * \param filename name of file
 * 
 * \return completion status.
 */

struct Person getMaxHeight(char* argv[], int count, char filename[])
{
    struct Person person;
    struct Person maxPerson;
    maxPerson.height = 0;
    int startItem = 0;
    if (atoi(argv[2]))
    {
        startItem = atoi(argv[2]) - 1;
    }
    else
    {
        exit(ERROR_CODE);
    }

    int fd = open(filename, O_RDONLY);
    if (fd == ERROR_CODE)
        exit(ERROR_CODE);

    for (int i = 0; i < count; ++i)
    {
        ssize_t sizeRead = readOne(fd, &person, sizeof (person));
        if (sizeRead == ERROR_CODE)
            exit(ERROR_CODE);

        if (i >= startItem && person.height > maxPerson.height)
        {
            maxPerson.height = person.height;
            strcpy(maxPerson.name, person.name);
            strcpy(maxPerson.surname, person.surname);
        }
    }
    return maxPerson;
}

/** \brief Gets list [name: average height]
 *
 * \param argv list of arguments
 * \param count size of file
 * \param filename name of file
 * 
 * \return completion status.
 */

char** getAvgHeightList(char* argv[], int count, char filename[])
{
    char names[count][NAME_LENGTH];
    int heights[count];
    int repeats[count];
    float avgHeights[count];
    struct Person person;

    int fd = open(filename, O_RDONLY);

    for (int i = 0; i < count; i++)
    {
        ssize_t sizeRead = readOne(fd, &person, sizeof (person));
        if (sizeRead == ERROR_CODE)
            exit(ERROR_CODE);

        heights[i] = person.height;
        strcpy(names[i], person.name);
    }

    for(int i = 0; i < count; i++)
    {
        repeats[i] = -1;
    }

    for (int i = 0; i < count; i++)
    {
        if (repeats[i] != 0)
            repeats[i] = 1;

        for (int j = i + 1; j < count; j++)
        {
            if (repeats[j] != 0 && strcmp(names[i], names[j]) == 0)
            {
                repeats[i] += 1;
                heights[i] += heights[j];
                heights[j] = 0;
                repeats[j] = 0;
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        if (repeats[i] != 0)
        {
            avgHeights[i] = ((float)heights[i]) / ((float)repeats[i]);
            // printf(" <%d> %s: %.1f\n", i, names[i], avg);
        }
        else
        {
            avgHeights[i] = 0;
        }
    }
    char** arr = malloc(sizeof (char));
    for (int i = 0; i < count * 2; i++)
    {
        if (i < count)
        {
            arr[i] = malloc(NAME_LENGTH * sizeof (char));
            strcpy(arr[i], names[i]);
        }
        else
        {
            arr[i] = malloc(NAME_LENGTH * sizeof (char));
            char stringNum[NAME_LENGTH];
            gcvt (avgHeights[i - count], 5, stringNum);
            strcpy(arr[i], stringNum);
        }
        arr = realloc(arr, (i + 1) * NAME_LENGTH * sizeof (char) );
    }

    return arr;
}

