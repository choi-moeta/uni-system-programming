/**
 * \file struct.c
 * \brief Struct module.
 *
 * \details Struct inicialization and functions.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

/** \brief person list
 *
 *  \details linked list first entry
 */

struct Person* gPerson = NULL;

/** \brief struct size
 *
 *  \details size of struct.
 *
 *  \return size of struct
 */

int structSize()
{
    struct Person* p = gPerson;
    for (int i = 1;; i++)
    {
        if (p->next == NULL)
            return i;
        p = p->next;
    }
}

/** \brief is Empty
 *
 *  \details checks if list of people is empty.
 *
 *  \return 1 if empty else 0
 */

int isEmpty()
{
    if (gPerson == NULL)
        return 1;
    return 0;
}

/** \brief last
 *
 *  \details last person.
 *
 *  \return pointer to person
 */

struct Person* last()
{
    struct Person* p = gPerson;
    while(p->next != NULL)
    {
        p = p->next;
    }
    return p;
}

/** \brief get gPerson
 *
 *  \details gets gPerson by number.
 *
 *  \param num gPerson number.
 *  \return pointer to gPerson
 */

struct Person* get(int num)
{
    struct Person* p = gPerson;
    for (int i = 0; i < num; i++)
    {
        p = p->next;
    }
    return p;
}

/** \brief modify name
 *
 *  \details modifies name of person by number.
 *
 *  \param num person number.
 *  \param name person name.
 */

void modifyName(int num, char* name)
{
    get(num)->name = strdup(name);
}

/** \brief modify surname
 *
 *  \details modifies surname of person by number.
 *
 *  \param num person number.
 *  \param name person surname.
 */

void modifySurname(int num, char* surname)
{
    get(num)->surname = strdup(surname);
}

/** \brief modify height
 *
 *  \details modifies height of person by number.
 *
 *  \param num person number.
 *  \param name person height.
 */

void modifyHeight(int num, int height)
{
    get(num)->height = height;
}

/** \brief create
 *
 *  \details create person by given params.
 *
 *  \param name name of person.
 *  \param surname surname of person.
 *  \param height height of person.
 *  \return pointer to person
 */

struct Person* create(char* name, char* surname, int height)
{
    struct Person * p = malloc(sizeof(struct Person));

    p->name = malloc(sizeof(char));
    p->surname = malloc(sizeof(char));

    if (p == NULL || p->name == NULL || p->surname == NULL)
    {
        printf(" * Allocation error.");
        exit(0);
    }

    p->name = strdup(name);
    p->surname = strdup(surname);
    
    p->height = height;
    p->next = NULL;

    return p;
}

/** \brief append
 *
 *  \details appends list of people.
 *
 *  \param name name of person.
 *  \param surname surname of person.
 *  \param height height of person.
 */

void append(char* name, char* surname, int height)
{
    if (isEmpty())
        gPerson = create(name, surname, height);
    else
        last(gPerson)->next = create(name, surname, height);
}

/** \brief show
 *
 *  \details shows people.
 */

void show()
{
    struct Person* p = gPerson;
    for (int i = 0;; i++)
    {
        printf(" <%d> %s %s, %dsm\n", i+1, p->name, p->surname, p->height);

        if (p->next == NULL)
            break;

        p = p->next;
    }
}

/** \brief remove
 *
 *  \details removes gPerson by number.
 *
 *  \param num gPerson number.
 */

void rm(int num)
{
    struct Person* p = gPerson;
    struct Person* tmp;

    if (num == 0)
    {
        if (gPerson->next == NULL)
        {
            free(gPerson);
            gPerson = NULL;
        }
        else
        {
            tmp = gPerson;
            gPerson = gPerson->next;
            free(tmp);
        }
    }
    else
    {
        for (int i = 0; i < num - 1; i++)
        {
            p = p->next;
        }

        if (p->next->next == NULL)
        {
            free(p->next);
            p->next = NULL;
        }
        else
        {
            tmp = p->next;
            p->next = tmp->next;
            free(tmp);
        }
    }
}

/** \brief get max height
 *
 *  \details gets max height from number.
 *
 *  \param num person number.
 */

void getMaxHeight(int num)
{
    struct Person* p = get(num);
    int maxHeight = 0;
    int maxHeightIndex = 0;


    for (int i = num; i < structSize(); i++)
    {
        if (p->height > maxHeight)
        {
            maxHeight = p->height;
            maxHeightIndex = i;
        }
        p = p->next;
    }
    p = get(maxHeightIndex);
    printf(" # Person with max height is %s %s (%d) with %dsm height\n", p->name, p->surname, maxHeightIndex + 1, p->height);
}

/** \brief get average height list
 *
 *  \details gets list "name - average height"
 */

void getAverageHeightList()
{
    printf(" # List of names with average height:\n");
    int repeats[structSize()];
    int heights[structSize()];

    for(int i = 0; i < structSize(); i++)
    {
        repeats[i] = -1;
        heights[i] = -1;
    }

    struct Person* iP = gPerson;
    struct Person* jP = gPerson;
    
    for(int i = 0; i < structSize(); i++)
    {
        jP = iP->next;

        if (repeats[i] != 0)
        {
            repeats[i] = 1;
            heights[i] = iP->height;
        }

        for (int j = i + 1; j < structSize(); j++)
        {
            if (repeats[j] != 0)
            {
                if (strcmp(jP->name, iP->name) == 0)
                {
                    repeats[i] += 1;
                    heights[i] += jP->height;
                    heights[j] = 0;
                    repeats[j] = 0;
                }
                jP = jP->next;
            }
        }
        iP = iP->next;
    }

    struct Person* p = gPerson;

    for (int i = 0; i < structSize(); i++)
    {
        if (repeats[i] != 0)
        {
            float avg = ((float)heights[i]) / ((float)repeats[i]);
            printf(" <%d> %s: %.1f\n",i, p->name, avg);
        }
        p = p->next;
    }
}

/** \brief free struct
 *
 *  \details free memory.
 */

void structFree()
{
    struct Person* tmp;
    while(gPerson->next)
    {
        tmp = gPerson;
        gPerson = gPerson->next;
        free(tmp->name);
        free(tmp->surname);
        free(tmp);
    }
}