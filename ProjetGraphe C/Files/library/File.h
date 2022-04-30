#ifndef FIL
#define FIL

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Element Element;
struct Element
{
    int nombre;
    Element *suivant;
};

typedef struct File File;
struct File
{
    Element *firstElement;
};

File *initialisation();
bool search(File *list,int a);
void enfiler(File *file, int numberToAdd);
int defiler(File *file);
void afficherFile(File *File);
void freeFile(File *list);
void freeElement(Element *el);

#endif