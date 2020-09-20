/**
 * \file menu_functions.c
 * \brief Main menu functions.
 *
 * \details Functions for use in menu.c.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu_functions.h"
#include "struct.h"
#include "util.h"

/** \brief max height of person
 *
 *  \details height of tallest person in the world.
 */

int gMaxHeight = 251;

/** \brief menu Append
 *
 *  \details Appends person in list.
 */

void menuAppend()
{
    char* name = malloc(sizeof(char));
    char* surname = malloc(sizeof(char));
    if (name == NULL || surname == NULL)
    {
        printf(" * Allocation error.");
        exit(0);
    }

    int height;

    printf(" <> Name: ");
    char _name[256];
    while(!0)
    {
        scanf("%s", &_name);

        if (_name != NULL)
            break;

        printf("Error! Input correct name: ");
    }
    strcpy(name, _name);

    printf(" <> Surname: ");
    char _surname[256];
    while(!0)
    {
        scanf("%s", &_surname);

        if (_surname != NULL)
            break;

        printf(" * Error! Input correct name: ");
    }
    strcpy(surname, _surname);

    printf(" <> Height: ");
    height = getInt(gMaxHeight, "Input correct height");

    append(name, surname, height);
}

/** \brief menu modify
 *
 *  \details Changes person in list.
 */

void menuModify()
{
    show();
    printf(" # Choose person to modify: ");
    int pNum = getInt(structSize() + 1, "Choose correct person to modify") - 1;

    printf(" <1> Name \n");
    printf(" <2> Surame \n");
    printf(" <3> Height \n");
    printf(" # Choose field to modify: ");
    // number of options + 1
    int fNum = getInt(4, "Choose correct field to modify") - 1;

    if (fNum == 2)
    {
        printf(" # Type new height: ");
        int h = getInt(gMaxHeight, "Input correct height");
        modifyHeight(pNum, h);
    }
    else
    {
        if (fNum == 0)
        {
            printf(" # Type new name: ");
            char name[256];
            while(!0)
            {
                scanf("%s", &name);

                if (name != NULL)
                    break;

                printf(" * Error! Input correct name: ");
            }
            char* n = malloc(sizeof(char));
            if (n == NULL)
            {
                printf(" * Allocation error.");
                exit(0);
            }

            strcpy(n, name);
            modifyName(pNum, n);
        }
        else
        {
            printf(" # Type new surname: %d", fNum);
            char name[256];
            while(!0)
            {
                scanf("%s", &name);

                if (name != NULL)
                    break;

                printf(" * Error! Input correct name: ");
            }
            char* n = malloc(sizeof(char));
            if (n == NULL)
            {
                printf(" * Allocation error.");
                exit(0);
            }

            strcpy(n, name);
            modifySurname(pNum, n);
        }
    }
}

/** \brief menu remove
 *
 *  \details Removes person in list.
 */

void menuRemove()
{
    show();
    printf(" # Choose person to remove: ");
    int pNum = getInt(structSize() + 1, "Choose correct person to remove") - 1;

    rm(pNum);
}

/** \brief menu get max height
 *
 *  \details Gets max height of person in list
 */

void menuGetMaxHeight()
{
    show();
    printf(" # Choose person to start from: ");
    int startFrom = getInt(structSize() + 1, "person to start from") - 1;

    getMaxHeight(startFrom);
}