/**
 * \file convert.c
 * \brief Converts text.
 *
 * \details Convert text functions.
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "convert.h"

/** \brief convert text
 *
 *  \details convert text. change register, trim spaces, converts tabs to 2 spaces.
 *
 *  \param text Text to convert.
 *  \return Pointer to converted word.
 */

char* convertText(char* text)
{
    char* convertedText = (char *) malloc(1 * sizeof(char*));
    if (convertedText == NULL)
    {
        printf("\n Error : Malloc \n");
        exit(EXIT_FAILURE);
    }
    int trimSpace = 0;
    int spaceCount = 0;
    int inQuotes = 0;
    int inApostrophes = 0;

    for (int i = 0, j = 0;; i++, j++)
    {
        int spaceCount = 0;
        if (text[i] == '\'')
        {
            inQuotes = !inQuotes;
        }
        if (text[i] == '`')
        {
            inApostrophes = !inApostrophes;
        }

        if (!inQuotes && !inApostrophes && text[i] >= 'A' && text[i] <= 'Z')
        {
            convertedText = (char *) realloc(convertedText, (j+1) * sizeof(char*));
            convertedText[j] = (char)(text[i] + 32);
        }
        else if (!inQuotes && !inApostrophes && text[i] >= 'a' && text[i] <= 'z')
        {
            convertedText = (char *) realloc(convertedText, (j+1) * sizeof(char*));
            convertedText[j] = (char)(text[i] - 32);
        }
        else if (!inQuotes && !inApostrophes && text[i] == 9) // TAB
        {
            j++;
            convertedText = (char *) realloc(convertedText, (j+1) * sizeof(char*));
            convertedText[j-1] = ' ';
            convertedText[j] = ' ';
        }
        else if (text[i] == 0)
        {
            break;
        }
        else
        {
            convertedText = (char *) realloc(convertedText, (j+1) * sizeof(char*));
            convertedText[j] = (char)(text[i]);
        }
        if (convertedText == NULL)
        {
            printf("\n Error : Malloc \n");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < strlen(convertedText); i++)
    {
        if (convertedText[i] == 32)
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
        char *trimmedConvertedText = malloc(0);
        if (trimmedConvertedText == NULL)
        {
            printf("\n Error : Malloc \n");
            exit(EXIT_FAILURE);
        }
        strncpy(trimmedConvertedText, convertedText, strlen(convertedText) - trimSpace);
        return trimmedConvertedText;
    }
    return convertedText;
}