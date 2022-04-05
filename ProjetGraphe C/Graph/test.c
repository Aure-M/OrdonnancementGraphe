#include "./library/Graph.h"
#include "../Files/library/Fichier.h"

int main()
{
    int nbrSommets;
    File **tab_Contraintes_Durees = fetchDatas("../../Tests/table 4.txt", &nbrSommets);
    Graph *g1 = NULL;
    int *calendrierTot = NULL, *calendrierTard = NULL, *marge = NULL;



    g1 = initGraph(nbrSommets, tab_Contraintes_Durees);

    affichageMatriceValeurs(g1);

    if (true)/* (verificationSurGraphe(g1) == false) */ 
    {
        calendrierTot = calendrierAuPlusTot(g1);
        calendrierTard = calendrierAuPlusTard(calendrierTot[g1->nbrSommets-1],g1);
        marge = marges(g1, calendrierTard, calendrierTot);
    }

    if (calendrierTot != NULL)
    {
        free(calendrierTot);
    }
    if (calendrierTard != NULL)
    {
        free(calendrierTard);
    }
    if (marge != NULL)
    {
        free(marge);
    }
    if (g1 != NULL)
    {
        free_graph(g1);
    }
    return 0;
}