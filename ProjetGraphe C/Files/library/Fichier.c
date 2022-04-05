#include "Fichier.h"
#include <string.h>

File **fetchDatas(char *filepath, int *nbrSommets)
{
    FILE *fichier = NULL;              // FILE * : pointeur vers un fichier
    File **tableau_contraintes = NULL; // File * : pointeur vers une file (File.h)
    char *valeur, *fileLine = malloc(TAILLE_MAX_FILE_READ * sizeof(char));
    fichier = fopen(filepath, "r");

    if (fichier == NULL)
    {
        perror("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    tableau_contraintes = (File **)malloc(1*sizeof(File *));
    while (fgets(fileLine, TAILLE_MAX_FILE_READ, fichier) != NULL)
    {
        if (i != 0)
        {
            if (!(tableau_contraintes = (File **)realloc(tableau_contraintes, (i + 1) * sizeof(File *))))
            {
                perror("Realloc failed on the realloc");
                exit(EXIT_FAILURE);
            }
        }
        tableau_contraintes[i] = initialisation();
        valeur = strtok(fileLine, " ");
        while (valeur != NULL)
        {
            if(atoi(valeur) > 0)
                enfiler(tableau_contraintes[i], atoi(valeur));
            valeur = strtok(NULL, " ");
            
        }
        i++;
    }

    (*nbrSommets) = i;
    fclose(fichier);

    return tableau_contraintes;
}
