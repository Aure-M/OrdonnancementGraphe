#include "Graph.h"

/* Affichage matrice d'ajacence  */

void affichageMatAdjacence(bool **tab, int len)
{
    printf("-----------MATRICE D'ADJACENCE----------\n\n    ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < len; i++)
    {

        if ((i + 1) / 10 >= 1)
        {
            printf("%d ", i + 1);
        }
        else
        {
            printf("%d  ", i + 1);
        }

        for (int j = 0; j < len; j++)
        {
            if (tab[i][j] == true)
                printf("\033[1;31m O\033[0m");
            else
                printf(" X");
        }
        printf("\n");
    }
    printf("\n---------------------------------------\n\n");
}

void affichageMatriceValeurs(Graph *graph)
{
    printf("-----------MATRICE DES VALEURS----------\n\n    ");
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < graph->nbrSommets; i++)
    {

        if ((i + 1) / 10 >= 1)
        {
            printf("%d ", i + 1);
        }
        else
        {
            printf("%d  ", i + 1);
        }

        for (int j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[i][j] == true)
                printf("\033[1;34m %d\033[0m", graph->durees[i]);
            else
                printf(" *");
        }
        printf("\n");
    }
    printf("\n---------------------------------------\n\n");
}
