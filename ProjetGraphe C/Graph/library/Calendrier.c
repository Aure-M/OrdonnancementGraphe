#include "Graph.h"

int *calendrierAuPlusTot(Graph *graph)
{
    int *durees = graph->durees, *calendrier = malloc(graph->nbrSommets * sizeof(int));
    int tmp;

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        tmp = 0;
        for (int j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[j][i] == true)
            {
                tmp = (calendrier[j] + durees[j]) > tmp ? (calendrier[j] + durees[j]) : tmp;
            }
        }
        calendrier[i] = tmp;
    }

    printf("------------CALENDRIER AU PLUS TOT--------------\n");

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d(%d) ", i + 1, calendrier[i]);
    }

    printf("\n-----------------------------------------------\n");

    return calendrier;
}




int *calendrierAuPlusTard(int dateDerniereTache, Graph *graph)
{
    int *durees = graph->durees, *calendrier = malloc(graph->nbrSommets * sizeof(int));
    int tmp = dateDerniereTache, derniere_DateAuPlusTard = dateDerniereTache;

    calendrier[graph->nbrSommets - 1] = dateDerniereTache;
    for (int i = (graph->nbrSommets - 2); i >= 0; i--)
    {
        for (int j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[i][j] == true)
            {
                tmp = tmp > (calendrier[j] - durees[i]) ? (calendrier[j] - durees[i]) : tmp;
            }
        }

        calendrier[i] = tmp;
    }

    printf("------------CALENDRIER AU PLUS TARD--------------\n");

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d(%d) ", i + 1, calendrier[i]);
    }

    printf("\n-----------------------------------------------\n");
    return calendrier;
}

int *marges(Graph *graph, int *calendrierTard, int *calendrierTot)
{
    int *result = malloc(graph->nbrSommets * sizeof(int));

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        result[i] = calendrierTard[i] /* - calendrierTot[i] */;
    }

    printf("-----------------------MARGES------------------------\n");

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d(%d) ", i + 1, result[i]);
    }

    printf("\n-----------------------------------------------------\n");

    return result;
}
