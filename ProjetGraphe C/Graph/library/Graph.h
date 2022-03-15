#ifndef GRAPH
#define GRAPH

    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #include "../../Files/library/File.h"

    typedef struct Graph Graph;

    struct Graph
    {
        int nbrSommets;
        int *durees;
        bool **matriceAdjacence;
    };

    Graph *initGraph(int nbrSommets, File **tab_Duree_Et_Contraintes);

    Graph *copie(Graph *model);
    void affichage(bool **File, int taille);

    File *detectPointEntree(Graph *graph);
    File *detectPointSortie(Graph *graph);
    bool detectionCircuit(Graph *graph);
    bool a_un_arc_negatif(Graph *graph);

    void calendrierAuPlusTot(Graph *graph);
    void calendrierAuPlusTard(Graph *graph);
    void marges(Graph *graph);

    void free_graph(Graph *graph);

#endif