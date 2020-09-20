#define NAME_LENGTH 16
#define STATUS_SUCCESS 0
#define ERROR_CODE -1

#ifndef struct_h
#define struct_h

struct Person
{
    char name[NAME_LENGTH];
    char surname[NAME_LENGTH];
    int height;
};
struct Person getPerson(char* argv[]);

#endif