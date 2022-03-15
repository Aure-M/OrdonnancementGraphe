#include "Fichier.h"
#include <string.h>

File **fetchDatas(char *filepath, int *nbrSommets)
{
    FILE *fichier = NULL;              // FILE * : pointeur vers un fichier
    File **tableau_contraintes = NULL; // File * : pointeur vers une file (File.h)
    char *token, *fileLine = malloc(TAILLE_MAX_FILE_READ * sizeof(char));
    fichier = fopen(filepath, "r");

    if (fichier == NULL)
    {
        perror("Impossible d'ouvrir le fichier");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    tableau_contraintes = (File **) malloc(sizeof(File*));
    while (fgets(fileLine, TAILLE_MAX_FILE_READ, fichier) != NULL)
    {
        if (i != 0)
        {
            if(!(tableau_contraintes = (File **) realloc(tableau_contraintes, (i+1)*sizeof(File*))))
            {
                perror("Realloc failed on the realloc");
                exit(EXIT_FAILURE);
            }

        }
        tableau_contraintes[i] = initialisation();
        token = strtok(fileLine, " ");
        while (token != NULL)
        {
            enfiler(tableau_contraintes[i],atoi(token));
            token = strtok(NULL, " ");
        }
        i++;
    }

    (*nbrSommets) = i;
    fclose(fichier);

    return tableau_contraintes;
}
