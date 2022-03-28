#include "Graph.h"

/*---------------------détection de circuit--------------*/

File *detectPointEntree(Graph *graph)
{
    File *result = initialisation();
    bool isAnEntryPoint = true;
    int i = 0, j = 0;
    for (i = 0; i < graph->nbrSommets; i++)
    {
        isAnEntryPoint = true;
        for (j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[j][i] == 1)
            {
                isAnEntryPoint = false;
                break;
            }
        }
        if (isAnEntryPoint)
        {
            enfiler(result, i + 1);
        }
    }
    return result;
}

File *detectPointSortie(Graph *graph)
{
    File *result = initialisation();
    bool isAnEndPoint = true;
    int i = 0, j = 0;
    for (i = 0; i < graph->nbrSommets; i++)
    {
        isAnEndPoint = true;
        for (j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[i][j] == 1)
            {
                isAnEndPoint = false;
                break;
            }
        }
        if (isAnEndPoint)
        {
            enfiler(result, i + 1);
        }
    }
    return result;
}



bool detectionCircuit(Graph *graph)
{
    Graph *copieGraphe = copie(graph);
    File *f1 = NULL, *f2 = NULL;
    int tmpNode = -1, sommetsRestants = graph->nbrSommets;

    f1 = detectPointEntree(copieGraphe);
    f2 = detectPointSortie(copieGraphe);

    while (f1->firstElement != NULL || f2->firstElement != NULL)
    {

        /* Suppression des sommets présents dans f1 */
        while (f1->firstElement != NULL)
        {
            tmpNode = defiler(f1);
            for (int i = 0; i < graph->nbrSommets; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode - 1] = 0;
                copieGraphe->matriceAdjacence[tmpNode - 1][i] = 0;
            }
            sommetsRestants--;
        }

        /* Suppression des sommets présents dans f1 */
        while (f2->firstElement != NULL)
        {
            tmpNode = defiler(f2);
            for (int i = 0; i < graph->nbrSommets; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode - 1] = 0;
                copieGraphe->matriceAdjacence[tmpNode - 1][i] = 0;
            }
            sommetsRestants--;
        }

        /* Si il ne reste qu'un seul sommet le graphe ne peut pas être un circuit */
        if (sommetsRestants <= 1)
            return false;

        f1 = detectPointEntree(copieGraphe);
        f2 = detectPointSortie(copieGraphe);
    }

    freeFile(f1);
    freeFile(f2);

    return true;
}

bool a_un_arc_negatif(Graph *graph)
{
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        if (graph->durees[i] < 0)
        {
            printf("Le sommet %d a une durée négative ( %d )\n", i + 1, graph->durees[i]);
            return true;
        }
    }
    printf("Ce graphe n'a pas d'arc négatif ^^ \n");
    return false;
}
