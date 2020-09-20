/**
 * \file menu.c
 * \brief Main menu of the program.
 *
 * \details Have options 6 options to work with list and exit option.
 */

#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "menu_functions.h"
#include "struct.h"
#include "util.h"

/** \brief Menu
 *
 *  \details Main menu of the program.
 */

void menu()
{
    // menu devider
    char* br = ".~~~~~~~~~~~\n";
    printf(br);

    while(!0)
    {
        if (isEmpty())
        {
            printf(" # First of all add entry bellow.\n");
            menuAppend();
            printf(br);
        }
        else
        {
            printf(" # Choose one of options bellow.\n");
            printf(" <1> Append\n");
            printf(" <2> Modify\n");
            printf(" <3> Remove\n");
            printf(" <4> Show\n");
            printf(" <5> Get max height\n");
            printf(" <6> Get average height list\n");
            printf(" <7> Exit\n");
            printf(">>");
            int choice = getInt(8, "Input correct number (1-7)");
            printf(br);

            switch (choice)
            {
                case 1:
                    menuAppend();
                    printf(br);
                    break;
                case 2:
                    menuModify();
                    printf(br);
                    break;
                case 3:
                    menuRemove();
                    printf(br);
                    break;
                case 4:
                    show();
                    printf(br);
                    break;
                case 5:
                    menuGetMaxHeight();
                    printf(br);
                    break;
                case 6:
                    getAverageHeightList();
                    printf(br);
                    break;
                case 7:
                    structFree();
                    exit(0);
                    break;
            }
        }
    }
}

