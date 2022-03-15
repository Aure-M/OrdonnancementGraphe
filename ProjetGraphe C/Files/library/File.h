#ifndef FIL
#define FIL

#include <stdio.h>
#include <stdlib.h>

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
File *FileCat(File *file1, File *file2);
int nbElements(File *file);
void enfiler(File *file, int numberToAdd);
int defiler(File *file);
void afficherFile(File *File);
void freeFile(File *list);
void freeElement(Element *el);


#endif