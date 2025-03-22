// namelist.h

#include <stdbool.h>

#include "binarytree.h"

typedef struct nameList{
    char aName[LENGTH];
    int *size;
    struct nameList *pNext;
} NAME_LIST;

NAME_LIST* createNameList(const char* name, int* size);

void append(NAME_LIST* root, const char* name);
bool nameExists(NAME_LIST* root, const char* name);
char* getNames(NAME_LIST* root);