#include "./library/Graph.h"
#include "../Files/library/Fichier.h"

int main()
{
    int nbrSommets = 5;
    File **tab_Contraintes_Durees = fetchDatas("/home/aurel-m02/Documents/OrdonnancementGraphe/ProjetGraphe C/test.txt", &nbrSommets);
    Graph *g1 = NULL;

    g1 = initGraph(nbrSommets, tab_Contraintes_Durees);

    affichageRangsSommets(g1);    
    if (g1 != NULL)
        free_graph(g1);
    return 0;
}