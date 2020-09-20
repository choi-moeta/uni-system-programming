#ifndef struct_h
#define struct_h

struct Person
{
    char* surname;
    char* name;
    int height;
    struct Person* next;
};

int structSize();
int isEmpty();
struct Person* get(int num);
void modifyName(int num, char* name);
void modifySurname(int num, char* surname);
void modifyHeight(int num, int height);
struct Person* create(char*, char*, int);
void append(char* name, char* surname, int height);
void show();
void rm(int num);
void getMaxHeight(int num);
void getAverageHeightList();
void structFree();

#endif