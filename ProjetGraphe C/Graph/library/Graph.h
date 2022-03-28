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

Graph *initGraph(int nbrSommets, File **tab_Duree_Et_Contraintes);Graph *copie(Graph *model);

void affichageMatAdjacence(bool **File, int taille);
void affichageMatriceValeurs(Graph *graph);

File *detectPointEntree(Graph *graph);
File *detectPointSortie(Graph *graph);
bool detectionCircuit(Graph *graph);
bool a_un_arc_negatif(Graph *graph);

int *rangsSommets(Graph *graph);
void affichageRangsSommets(Graph *graph);

int *calendrierAuPlusTot(Graph *graph);
int *calendrierAuPlusTard(int dateDerniereTache,Graph *graph);
int *marges(Graph *graph,int *calendrierAuPlusTard,int *calendrierAuPlusTot); 

void free_graph(Graph *graph);

#endif