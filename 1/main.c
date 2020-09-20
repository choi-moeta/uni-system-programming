/**
 * \file    main.c
 * \brief   Main program.
 *
 * \details Program takes sequence of strings.
 *          Change register of english letters, swap tabs to 2 spaces and trim whitespaces,
 *          Everywhere execpt quote blocks.
 */

#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** \brief Main function
 *
 * \details Convert sequence of strings and show result into terminal.
 *
 * \param argc       Placeholder
 * \param argList    A sequence of strings.
 * \return           Integer 0 upon exit success.
 */

int main(int argc, char* const argv[])
{
    printf("\n<!> converted lines:\n");
    char* convertedLine;
    for (int i = 1;; i++)
    {
        if (!argv[i])
        {
            free(convertedLine);
            break;
        }
        convertedLine = convertLine(argv[i]);
        printf("<%d> '%s' -> '%s' \n", i, argv[i], convertedLine);
    }

    return 0;
}
