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

File *FileCat(File *file1, File *file2)
{
    if (file1 == NULL || file2 == NULL)
    {
        perror("Erreur lors de la concatenation\n");
        exit(EXIT_FAILURE);
    }
    File *file = initialisation();
    file->firstElement = file1->firstElement;
    if (file->firstElement != NULL) /* La file n'est pas vide */
    {
        Element *currentElement = malloc(sizeof(Element));
        currentElement = file->firstElement;
        /* On se positionne à la fin de la file */
        while (currentElement->suivant != NULL)
        {
            currentElement = currentElement->suivant;
        }
        currentElement->suivant = file2->firstElement;
    }
    else /* La file est vide, notre élément est le firstElement */
    {
        file->firstElement = file2->firstElement;
    }
    return file;
}

int nombreElements(File *file)
{
    int nb = 0;
    if (file == NULL)
    {
        perror("Erreur lors de l'operation\n");
        exit(EXIT_FAILURE);
    }

    if (file->firstElement == NULL)
        return 0; /* La file est vide */

    Element *currentElement = file->firstElement;
    /*  On compte le nombre d'elements*/
    while (currentElement != NULL)
    {
        currentElement = currentElement->suivant;
        nb++;
    }

    return nb;
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
        perror("La file est vide\n");
        exit(EXIT_FAILURE);
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
