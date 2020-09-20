/**
 * \file struct.c
 * \brief Person struct.
 *
 * \details Store person structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include <string.h>
#include "struct.h"

/** \brief Gets person struct
 *
 * \param argv List of arguments.
 * 
 * \return struct Person.
 */

struct Person getPerson(char* argv[])
{
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    strcpy(name, argv[2]);
    strcpy(surname, argv[3]);
    if (!atoi(argv[4]))
        exit(ERROR_CODE);
    int height = atoi(argv[4]);

    struct Person person;
    strcpy(person.name, name); // second arg
    strcpy(person.surname, surname); // second arg
    person.height = height;

    return person;
}