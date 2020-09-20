/**
 * \file server.c
 * \brief Socket functions.
 *
 * \details Functions for interaction with socket connection.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include "server.h"
#include "constants.h"

/**\brief Read message
 *
 * \details Read incoming message.
 *
 * \param clientfd Client file descripter.
 * \return Pointer to message text.
 */

char* readMessage(int clientfd)
{
    int length = 0;
    char* text = NULL;

    if (recv(clientfd, &length, sizeof (length), 0) == 0)
        return NULL;

    text = (char*) malloc(length);
    bzero(text, length);

    recv(clientfd, text, length, 0);

    return text;
}

/**\brief Is exit message
 *
 * \details Checks if message is exit.
 *
 * \param message Message text.
 * \return 1 upon exit.
 */

int isExitMessage(char* message)
{
    if (strcmp(message, EXIT_MESSAGE) == 0)
        return 1;
    return 0;
}

/**\brief Init server
 *
 * \details Initialize server.
 *
 * \param port Port.
 * \return Socket file descripter.
 */

int initServer(int port)
{
    int sockfd = -1;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        printf("\n Error : Socket \n");
        exit(EXIT_FAILURE);
    }

    int i = 1;
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char *)&i, sizeof (i));

    struct sockaddr_in name;
    bzero((char *)&name, sizeof(name));
    name.sin_family = AF_INET;
    name.sin_addr.s_addr = INADDR_ANY;
    name.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr*)&name, sizeof(name)) == -1)
    {
        printf("\n Error : Bind \n");
        closeServer(sockfd);
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 10) == -1)
    {
        printf("\n Error : Listen \n");
        closeServer(sockfd);
        exit(EXIT_FAILURE);
    }

    return sockfd;
}

/**\brief Init connection
 *
 * \details Initialize connection betweew server and client.
 *
 * \param sockfd Socket file descripter.
 * \return Client file descripter.
 */

int initConnection(int sockfd)
{
    struct sockaddr_in clientName;
    socklen_t clientNameLength = sizeof (clientName);
    int clientSockfd;
    clientSockfd = accept(sockfd, (struct sockaddr *)&clientName, &clientNameLength);
    return clientSockfd;
}

/**\brief Close connection.
 *
 * \details Closes client connection.
 *
 * \param clientfd Client socket file descripter.
 */

void closeConnection(int clientfd)
{
    close(clientfd);
}

/**\brief Close connection.
 *
 * \details Closes client connection.
 *
 * \param sockfd Socket file descripter.
 */

void closeServer(int sockfd)
{
    shutdown(sockfd, SHUT_RD);
    close(sockfd);
}