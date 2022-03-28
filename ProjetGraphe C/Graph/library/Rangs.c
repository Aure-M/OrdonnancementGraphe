#include "Graph.h"
#include "Verification.c"



int *rangsSommets(Graph *graph)
{
    Graph *copieGraphe = copie(graph);
    File *f1 = NULL;
    Element *parcoursF1 = NULL, *parcoursF1_prec = NULL;
    int tmpNode = -1, rangActuel = 0, sommetsEffaces_len = 0;
    int *rangs = malloc(graph->nbrSommets * sizeof(int)), *sommetsEffaces = NULL;
    bool isF1Modified;

    f1 = detectPointEntree(copieGraphe);

    while (f1->firstElement != NULL)
    {

        while (f1->firstElement != NULL)
        {
            tmpNode = defiler(f1);
            sommetsEffaces_len++;
            sommetsEffaces = sommetsEffaces == NULL ? malloc(sizeof(int)) : realloc(sommetsEffaces, (sommetsEffaces_len) * sizeof(int));

            sommetsEffaces[sommetsEffaces_len - 1] = tmpNode;

            for (int i = 0; i < graph->nbrSommets; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode - 1] = 0;
                copieGraphe->matriceAdjacence[tmpNode - 1][i] = 0;
            }
            rangs[tmpNode - 1] = rangActuel;
        }

        f1 = detectPointEntree(copieGraphe);

        /*Epurage je vais en faire une fonction*/
        parcoursF1 = f1->firstElement;
        parcoursF1_prec = f1->firstElement;

        while (parcoursF1 != NULL)
        {
            isF1Modified = false;
            for (int i = 0; i < sommetsEffaces_len; i++)
            {
                if (parcoursF1->nombre == sommetsEffaces[i])
                {
                    if (parcoursF1 == f1->firstElement)
                    {
                        defiler(f1);
                        parcoursF1 = f1->firstElement;
                        parcoursF1_prec = f1->firstElement;
                    }
                    else
                    {
                        parcoursF1_prec->suivant = parcoursF1->suivant;
                        free(parcoursF1);
                        parcoursF1 = parcoursF1_prec->suivant;
                    }
                    isF1Modified = true;
                    break;
                }
            }
            if (!isF1Modified)
            {
                parcoursF1_prec = parcoursF1;
                parcoursF1 = parcoursF1->suivant;
            }
        }

        rangActuel++;
    }

    freeFile(f1);

    return rangs;
}
void affichageRangsSommets(Graph *graph)
{
    int *rangs = rangsSommets(graph);
    printf("------ Rangs des sommets -----\n");
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d -> %d\n", i + 1, rangs[i]);
    }
    printf("----------------------------\n");
}
