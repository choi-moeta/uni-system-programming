#ifndef file_h
#define file_h

int writeOne(int fd, struct Person person);
int readOne(int fd, void* buf, int bufferSize);
int getSize(char filename[]);
int addData(char* argv[], char filename[]);
int removeData(char* argv[], int count, char filename[], char filename2[]);
int changeData(char* argv[], int count, char filename[]);
struct Person getMaxHeight(char* argv[], int count, char filename[]);
char** getAvgHeightList(char* argv[], int count, char filename[]);

#endif