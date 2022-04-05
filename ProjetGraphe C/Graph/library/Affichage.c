#include "Graph.h"

/* Affichage matrice d'ajacence  */

void affichageMatAdjacence(Graph *graph)
{
    int len = graph->nbrSommets;
    char space = '\0';
    printf("-----------MATRICE D'ADJACENCE----------\n\n    ");
    for (int i = 0; i < len+2; i++)
    {
        if (i == 0)
            printf("%s ", ALPHA);
        else if (i == len+1 )
            printf("%s ", OMEGA);
        else
            printf("%d ", i );
    }
    printf("\n");
    for (int i = 0; i < len+2; i++)
    {
        if (i == 0)
            printf("%s  ", ALPHA);
        else if (i == len+1)
            printf("%s  ", OMEGA);
        else
        {
            if (i / 10 >= 1)
            {
                printf("%d ", i );
            }
            else
            {
                printf("%d  ", i );
            }
        }
        for (int j = 0; j < len+2; j++)
        {
            space = j/10 < 1 || j == len+1 ? '\0' : ' ';
            if (graph->matriceAdjacence[i][j] == true)
                printf("\033[1;31m %cO\033[0m", space);
            else
                printf(" %c*", space);
        }
        printf("\n");
    }
    printf("\n---------------------------------------\n\n");
}

void affichageMatriceValeurs(Graph *graph)
{
    int len = graph->nbrSommets,duree;
    char space = '\0';
    printf("-----------MATRICE DES VALEURS----------\n\n    ");
    for (int i = 0; i < len+2; i++)
    {
        if (i == 0)
            printf("%s ", ALPHA);
        else if (i == len+1 )
            printf("%s ", OMEGA);
        else
            printf("%d ", i );
    }
    printf("\n");
    for (int i = 0; i < len+2; i++)
    {
        if (i == 0)
            printf("%s  ", ALPHA);
        else if (i == len+1)
            printf("%s  ", OMEGA);
        else
        {
            if (i / 10 >= 1)
            {
                printf("%d ", i );
            }
            else
            {
                printf("%d  ", i );
            }
        }
        for (int j = 0; j < len+2; j++)
        {
            space = j/10 < 1 || j == len+1 ? '\0' : ' ';
            if (graph->matriceAdjacence[i][j] == true)
            {
                duree = (j == len+1) ? 0 : graph->durees[j-1];
                printf("\033[1;34m %c%d\033[0m", space, duree);
            }
            else
                printf(" %c*", space);
        }
        printf("\n");
    }
    printf("\n---------------------------------------\n\n");}
