/**
 * \file util.c
 * \brief Utility functions.
 */

#include <stdio.h>
#include "util.h"

/** \brief get string
 *
 *  \details gets string.
 *
 *  \return string
 */

char* getString()
{
    char* string;
    scanf("%s", &string);
    return string;
}

/** \brief get integear
 *
 *  \details gets integear
 * 
 *  \param max maximum number
 *  \param err error message
 *
 *  \return number
 */

int getInt(int max, char* err)
{
    int num;
    char check;

    while (scanf("%d%c", &num, &check) != 2 || check != '\n' || num <= 0 || num >= max)
    {
        while (getchar() != '\n');
        printf(" * Error! %s: ", err);
    }
    
    return num;
}