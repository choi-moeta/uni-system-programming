/**
 * \file main.c
 * \brief Main functionality program.
 *
 * \details Send argument words to the server.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"

/**\brief Main function
 *
 * \details Send argument words to the server.
 *
 * \return Integer 0 upon exit success.
 */

int main(int argc, char** argv)
{
    if (argc < 4)
    {
        printf("\n Error : Not enought arguments\n");
        printf(" Example : %s <name> <port> [strings...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* socketname = argv[1];
    int port = 0;
    if ((port = atoi(argv[2])) == 0)
    {
        printf("\n Error : Incorrect port \n");
        exit(EXIT_FAILURE);
    }

    int sockfd = initClient(socketname, port);

    for (int i = 3; i < argc; i++)
    {
        if (sendMessage(sockfd, argv[i]) == -1)
        {
            printf("\n Error : Send message \n");
            exit(EXIT_FAILURE);
        }
    }

    closeClient(sockfd);
    return EXIT_FAILURE;
}