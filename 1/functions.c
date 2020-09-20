/**
 * \file lab.c
 * \brief Functions.
 *
 * \details Functions needed in main program.
 */

#include "functions.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/** \brief Convert String
 *
 * \details Change register of english letters, swap tabs to 2 spaces and trim whitespaces,
 *          Everywhere execpt quote blocks.
 *
 * \param pureLine   String that need to be converted
 * \return           Converted string.
 */

char* convertLine(char const pureLine[])
{
    char* line = (char *) malloc(1 * sizeof(char*));
    if (line == NULL)
    {
        printf("<!> Error! Memory allocation failed\n");
        exit(-1);
    }
    int trimSpace = 0;
    int inQuotes = 0;
    int inApostrophes = 0;
        
    for (int i = 0, j = 0;; i++, j++)
    {
        if (pureLine[i] == '\'')
        {
            inQuotes = !inQuotes;
        }
        if (pureLine[i] == '`')
        {
            inApostrophes = !inApostrophes;
        }

        if (!inQuotes && !inApostrophes && pureLine[i] >= 'A' && pureLine[i] <= 'Z')
        {
            line = (char *) realloc(line, (j+1) * sizeof(char*));
            line[j] = (char)(pureLine[i] + 32);
        }
        else if (!inQuotes && !inApostrophes && pureLine[i] >= 'a' && pureLine[i] <= 'z')
        {
            line = (char *) realloc(line, (j+1) * sizeof(char*));
            line[j] = (char)(pureLine[i] - 32);
        }
        else if (!inQuotes && !inApostrophes && pureLine[i] == 9) // TAB
        {
            j++;
            line = (char *) realloc(line, (j+1) * sizeof(char*));
            line[j-1] = ' ';
            line[j] = ' ';
        }
        else if (pureLine[i] == 0)
        {
            break;
        }
        else
        {
        line = (char *) realloc(line, (j+1) * sizeof(char*));
        line[j] = (char)(pureLine[i]);
        }
        if (line == NULL)
        {
            printf("<!> Error! Memory allocation failed\n");
            exit(-1);
        }
    }

    for (int i = 0; i < strlen(line); i++)
    {
        if (line[i] == 32)
        {
            trimSpace++;
        }
        else
        {
            trimSpace = 0;
        }
    }
    
    if (trimSpace)
    {
        char *trimmedLine = malloc(0);
        strncpy(trimmedLine, line, strlen(line) - trimSpace);
        return trimmedLine;
    }
    return line;
}