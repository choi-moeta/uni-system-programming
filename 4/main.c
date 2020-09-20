/**
 *  \file main.c
 *  \brief Main functionality program.
 *
 *  \details Executes menu.
 */

#include "struct.h"
#include "file.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "stdlib.h"
#include "fcntl.h"

/** \brief Main function
 *
 *  \details Choose option.
 *
 *  \return Integer 0 upon exit success.
 */

int main(int argc, char* argv[])
{
    char filename[] = "file.bin";
    char filename2[] = "temp.bin";
    int fd = -1;
    int fd2 = -1;
    int count = getSize(filename);
    int status = -1;

    if (argc == 1)
    {
        printf("OHH! HELLO THERE! Just to say hi, that's so lovely. But you should choose one of options bellow\n");
        printf(" \"add\" <name> <surname> <heigh>\n");
        printf(" \"show\"\n");
        printf(" \"remove\" <index>\n");
        printf(" \"change\" <name> <surname> <heigh> (use \"-\" for not changing field)\n");
        printf(" \"maxHeight\" <startFromIndex> -> shows max height\n");
        printf(" \"avgHeight\" -> show list name: average height\n");
        printf(" blank -> shows commands\n");
    }
    else if (!strcmp(argv[1], "add"))
    {
        if (argc < 5)
            printf(" <*> Error! Not enough arguments. \n");
        else
            status = addData(argv, filename);
    }
    else if (!strcmp(argv[1], "remove"))
    {
        if (argc < 3)
            printf(" <*> Error! Not enough arguments.\n");
        else if (count == 0)
            printf(" <*> Error! Empty file\n");
        else if (!atoi(argv[2]))
            printf(" <*> Error! Wrong argument\n");
        else if (atoi(argv[2]) > count)
            printf(" <*> Error! Too big index\n");
        else
            status = removeData(argv, count, filename, filename2);
    }
    else if (!strcmp(argv[1], "show"))
    {
        if (count == 0)
        {
            printf(" <*> Error! Empty file\n");
        }
        else
        {
            struct Person person;
            fd = open(filename, O_RDONLY);
            if (fd == ERROR_CODE)
                return ERROR_CODE;

            for (int i = 0; i < count; ++i)
            {
                ssize_t sizeRead = readOne(fd, &person, sizeof (person));
                if (sizeRead == ERROR_CODE)
                    return ERROR_CODE;

                printf(" <%d>-------------------<\n", i + 1);
                printf("   \\> name:    %s\n", person.name);
                printf("   \\> surname: %s\n", person.surname);
                printf("   \\> height:  %d\n", person.height);
            }
            printf(" <x>-------------------<\n");
        }
    }
    else if (!strcmp(argv[1], "change"))
    {
        if (argc < 6)
        {
            printf(" <*> Error! Not enough arguments.\n");
        }
        else if (count == 0)
        {
            printf(" <*> Error! Empty file.\n");
        }
        else if (atoi(argv[2]) > count)
        {
            printf(" <*> Error! Too big index.\n");
        }
        else
        {
            status = changeData(argv, count, filename);
        }
    }
    else if (!strcmp(argv[1], "maxHeight"))
    {
        if (argc < 3)
        {
            printf(" <*> Error! Not enough arguments.\n");
        }
        else if (count == 0)
        {
            printf(" <*> Error! Empty file.\n");
        }
        else if (atoi(argv[2]) > count)
        {
            printf(" <*> Error! Too big index\n");
        }
        else
        {
            struct Person person = getMaxHeight(argv, count, filename);

            printf(" <>----------------------<>\n");
            printf("  \\> name:    %s\n", person.name);
            printf("  \\> surname: %s\n", person.surname);
            printf("  \\> height:  %d\n", person.height);
            printf(" <>----------------------<>\n");
        }
    }
    else if (!strcmp(argv[1], "avgHeight"))
    {
        if (count == 0)
        {
            printf(" <*> Error! Empty file.\n");
        }
        else
        {
            printf(" < >-------------------<\n");
            char** arr = getAvgHeightList(argv, count, filename);
            for (int i = 0, n = 1; i < count; i++)
            {
                if (strcmp(arr[i + count], "0"))
                {
                    printf(" <%d> %s: %scm\n", n, arr[i], arr[i + count]);
                    n++;
                }
            }
            printf(" < >-------------------<\n");
        }
        
    }
    else 
    {
        printf(" <*> Error! Unrecogized task.\n");
    }
    
    if (status == STATUS_SUCCESS)
    {
        printf(" <!> Success. <\n");
    }
    return STATUS_SUCCESS;
}