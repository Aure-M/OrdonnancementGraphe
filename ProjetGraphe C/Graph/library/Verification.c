#include "Graph.h"

/*---------------------détection de circuit--------------*/

File *detectPointEntree(Graph *graph)
{
    File *result = initialisation();
    bool isAnEntryPoint = true;
    for (int i = 0; i < graph->nbrSommets + 2; i++)
    {

        isAnEntryPoint = true;
        for (int j = 0; j < graph->nbrSommets + 2; j++)
        {
            if (graph->matriceAdjacence[j][i] == 1)
            {
                isAnEntryPoint = false;
                break;
            }
        }
        if (isAnEntryPoint)
        {
            enfiler(result, i);
        }
    }

    return result;
}

File *detectPointSortie(Graph *graph)
{
    File *result = initialisation();
    bool isAnEndPoint = true;
    for (int i = 0; i < graph->nbrSommets + 2; i++)
    {
        isAnEndPoint = true;
        for (int j = 0; j < graph->nbrSommets + 2; j++)
        {
            if (graph->matriceAdjacence[i][j] == 1)
            {
                isAnEndPoint = false;
                break;
            }
        }
        if (isAnEndPoint)
        {
            enfiler(result, i);
        }
    }
    return result;
}

bool detectionCircuit(Graph *graph)
{
    Graph *copieGraphe = copie(graph);
    File *f1 = NULL;
    int tmpNode, sommetsRestants = -1, sommetsRestants_prec;

    do
    {
        sommetsRestants_prec = sommetsRestants;
        f1 = detectPointEntree(copieGraphe);

        sommetsRestants = graph->nbrSommets + 2;
        /* Suppression des sommets présents dans f1 */

        while (f1->firstElement != NULL)
        {
            tmpNode = defiler(f1);
            for (int i = 0; i < graph->nbrSommets + 2; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode] = 0;
                copieGraphe->matriceAdjacence[tmpNode][i] = 0;
            }
            sommetsRestants--;
        }

        if (sommetsRestants == 0)
            return false;
    } while (sommetsRestants_prec != sommetsRestants);

    f1 = detectPointEntree(copieGraphe);
    afficherFile(f1);
    freeFile(f1);
    printf("Un circuit a été détecté\n");
    return true;
}

bool a_un_arc_negatif(Graph *graph)
{
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        if (graph->durees[i] < 0)
        {
            printf("Le sommet %d a une durée négative ( %d )\n", i , graph->durees[i]);
            return true;
        }
    }
    return false;
}

bool verificationSurGraphe(Graph *graph)
{
    return a_un_arc_negatif(graph) || detectionCircuit(graph);
}
