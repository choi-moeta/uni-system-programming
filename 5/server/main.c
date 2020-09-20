/**
 * \file main.c
 * \brief Main functionality program.
 *
 * \details Listen for client connection.
 */

#include <stdio.h>
#include <stdlib.h>
#include "server.h"
#include "convert.h"

/**\brief Main function
 *
 * \details Listen for words then show converted.
 *
 * \return Integer 0 upon exit success.
 */

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("\n Error : Not enought arguments\n");
        printf(" Example : %s <port> [strings...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int port = 0;
    if ((port = atoi(argv[1])) == 0)
    {
        printf("\n Error : Incorrect port \n");
        exit(EXIT_FAILURE);
    }

    int sockfd = initServer(port);
    printf(" Server is working\n");
    while (!0)
    {
        int clientfd = initConnection(sockfd);
        while (!0)
        {
            char* text = readMessage(clientfd);
            if (text == NULL)
                break;

            if (isExitMessage(text))
                exit(EXIT_SUCCESS);

            char* convertedText = convertText(text);
            printf("\"%s\"\n", convertedText);


            free(text);
            free(convertedText);
        }
        closeConnection(clientfd);

    }

    closeServer(sockfd);

    return EXIT_SUCCESS;
}