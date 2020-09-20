int initServer(int port);

int initConnection(int sockfd);

char* readMessage(int clientfd);

int isExitMessage(char* message);

int sendMessage(int clientfd, char* message);

void closeConnection(int clientfd);

void closeServer(int sockfd);