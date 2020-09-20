#ifndef client_h
#define client_h

int initClient(char* socketname, int port);
int sendMessage(int sockfd, const char* msg);
void closeClient(int sockfd);

#endif