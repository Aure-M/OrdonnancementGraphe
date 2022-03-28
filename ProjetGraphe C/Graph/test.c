#include "./library/Graph.h"
#include "../Files/library/Fichier.h"

int main()
{
    int nbrSommets = 5;
    File **tab_Contraintes_Durees = fetchDatas("/home/aurel-m02/Documents/OrdonnancementGraphe/ProjetGraphe C/test.txt", &nbrSommets);
    Graph *g1 = NULL;
    int *calendrierTot = NULL, *calendrierTard = NULL, *marge = NULL;

    g1 = initGraph(nbrSommets, tab_Contraintes_Durees);

    affichageMatriceValeurs(g1);

    affichageRangsSommets(g1);

    calendrierTot = calendrierAuPlusTot(g1);
    printf("\n------------------------------------------\n");
    calendrierTard = calendrierAuPlusTard(20, g1);

    marge = marges(g1,calendrierTard,calendrierTot);
    /* if (calendrierTot != NULL)
    {
        printf("%p",calendrierTot);
        sleep(2);
        free(calendrierTot);
    }
    if (calendrierTard != NULL)
    {
        printf("%p",calendrierTard);
        sleep(2);
        free(calendrierTard);
    } 
    if (marge != NULL)
    {
        printf("%p",marge);
        free(marge);
    }*/
    if (g1 != NULL)
    {
        free_graph(g1);
    }
    return 0;
}