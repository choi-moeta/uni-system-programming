/**
 * \file client.c
 * \brief Socket functions.
 *
 * \details Functions for interaction with socket connection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h> 
#include "client.h"

/**\brief Initialize client socket
 *
 * \details Initialize client socket connection.
 *
 * \param socketname Socketname for connection.
 * \param port Port for connection.
 * \return Socket file descripter.
 */

int initClient(char* socketname, int port)
{
    int sockfd = -1;
    int i = 1;
    struct sockaddr_in name;
    memset((char *) &name, 0, sizeof (name));

    bzero((char *)&name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = inet_addr(socketname);
    name.sin_port = htons(port);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        exit(EXIT_FAILURE);
    }

    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&i, sizeof (i));

    if (connect(sockfd, (struct sockaddr *) &name, sizeof (name)) < 0)
    {
        printf("\n Error : Connect Failed \n");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}

/**\brief Send message.
 *
 * \details Sends message to the server.
 *
 * \param sockfd Socket file descripter.
 * \param message Message to send.
 * \return socket file descripter.
 */

int sendMessage(int sockfd, const char* message)
{
    int length = strlen(message) + 1;
    send(sockfd, &length, sizeof (length), 0);
    send(sockfd, message, length, 0);
    return EXIT_SUCCESS;
}

/**\brief Close connection.
 *
 * \details Closes client connection.
 *
 * \param sockfd Socket file descripter.
 */

void closeClient(int sockfd)
{
    shutdown(sockfd, SHUT_WR);
    close(sockfd);
}