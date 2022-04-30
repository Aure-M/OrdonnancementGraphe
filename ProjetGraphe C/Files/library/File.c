/*
    Notre File chainée est un file
*/

#include "File.h"

File *initialisation()
{
    File *File = malloc(sizeof(File));

    if (File == NULL)
    {
        perror("Erreur d'initialisation\n");
        exit(EXIT_FAILURE);
    }

    File->firstElement = NULL;
    return File;
}


bool search(File *list,int a)
{
    Element *tmp = list->firstElement;
    while (tmp != NULL)
    {
        if (tmp->nombre == a)
        {
            return true;
        }
        
        tmp = tmp->suivant;
    }

    return false;
}

void enfiler(File *file, int numberToAdd)
{
    Element *newElement = malloc(sizeof(*newElement));
    if (file == NULL || newElement == NULL)
    {
        perror("Erreur lors de l'ajout de l'element\n");
        exit(EXIT_FAILURE);
    }

    newElement->nombre = numberToAdd;
    newElement->suivant = NULL;

    if (file->firstElement != NULL) /* La file n'est pas vide */
    {
        /* On se positionne à la fin de la file */
        Element *currentElement = file->firstElement;
        while (currentElement->suivant != NULL)
        {
            currentElement = currentElement->suivant;
        }
        currentElement->suivant = newElement;
    }
    else /* La file est vide, notre élément est le firstElement */
    {
        file->firstElement = newElement;
    }
}

int defiler(File *file)
{
    if (file == NULL)
    {
        exit(EXIT_FAILURE);
    }

    int nombreDefile = 0;

    if (file->firstElement != NULL)
    {
        Element *elementDefile = file->firstElement;

        nombreDefile = elementDefile->nombre;
        file->firstElement = elementDefile->suivant;
        elementDefile->suivant = NULL;
        free(elementDefile);
    }

    return nombreDefile;
}

void afficherFile(File *File)
{
    if (File == NULL)
    {
        printf("La file est vide\n");
        return;
    }

    Element *actuel = File->firstElement;

    while (actuel != NULL)
    {
        printf("%d -> ", actuel->nombre);
        actuel = actuel->suivant;
    }
    printf("NULL\n");
}

File *tab = NULL;

void freeFile(File *list)
{
    if (list->firstElement != NULL)
    {
        freeElement(list->firstElement);
    }
    free(list);
}

void freeElement(Element *el)
{
    if (el->suivant != NULL)
    {
        freeElement(el->suivant);
    }
    free(el);
}
