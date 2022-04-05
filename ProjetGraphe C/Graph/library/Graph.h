#ifndef GRAPH
#define GRAPH

#define ALPHA "\u0391"
#define OMEGA "\u03a8"

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

void affichageMatAdjacence(Graph *graph);
void affichageMatriceValeurs(Graph *graph);

File *detectPointEntree(Graph *graph);
File *detectPointSortie(Graph *graph);
bool detectionCircuit(Graph *graph); // a revoir
bool a_un_arc_negatif(Graph *graph); // a revoir
bool verificationSurGraphe(Graph* graph); //a revoir


int *rangsSommets(Graph *graph); //Ok
void affichageRangsSommets(Graph *graph); //Ok

int *calendrierAuPlusTot(Graph *graph);
int *calendrierAuPlusTard(int dateDerniereTache,Graph *graph);
int *marges(Graph *graph,int *calendrierAuPlusTard,int *calendrierAuPlusTot); 

void free_graph(Graph *graph);

#endif