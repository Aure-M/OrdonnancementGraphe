#include "Graph.h"
#include "Calendrier.c"
#include "Rangs.c"
#include "Affichage.c"


Graph *initGraph(int nbrSommets, File **tab_Duree_Et_Contraintes)
{
    Graph *graph = malloc(sizeof(*graph));
    int tmpNode = -1;
    int index = -1;
    if (graph == NULL)
    {
        perror("Erreur pendant la création du graphe");
        exit(EXIT_FAILURE);
    }
    graph->nbrSommets = nbrSommets;
    graph->durees = malloc((nbrSommets) * sizeof(int));

    /*
        Puisque le premier élément de chaque case de notre tableau(tab_Duree_Et_Contraintes)
        correspond à la duree de la tache représentée par ce noeud nous allons retirer pour chaque
        case le premier élément de sa liste pouur remplir le tableau de durée
    */

    for (int i = 0; i < nbrSommets; i++)
    {
        index = defiler(tab_Duree_Et_Contraintes[i]);
        graph->durees[index - 1] = defiler(tab_Duree_Et_Contraintes[i]);
    }

    graph->matriceAdjacence = malloc(nbrSommets * sizeof(bool *));

    printf("Remplissage de la matrice d'adjacence\n");

    /*
        Initialisation de la mattrice d'adjacence
    */

    for (int i = 0; i < nbrSommets; i++)
    {
        graph->matriceAdjacence[i] = malloc(nbrSommets * sizeof(bool));
        for (int j = 0; j < nbrSommets; j++)
        {
            graph->matriceAdjacence[i][j] = 0;
        }
    }
    /*
        Remplissage de la matrice d'adjacence
    */
    for (int i = 0; i < nbrSommets; i++)
    {
        while (tab_Duree_Et_Contraintes[i]->firstElement != NULL)
        {
            tmpNode = defiler(tab_Duree_Et_Contraintes[i]);
            graph->matriceAdjacence[tmpNode - 1][i] = 1;
        }
    }

    free(tab_Duree_Et_Contraintes);

    return graph;
}

/*-----------------------copie----------------------*/

Graph *copie(Graph *model)
{
    int nbrSommets = model->nbrSommets;
    Graph *graph = malloc(sizeof(graph));

    graph->durees = malloc(nbrSommets * sizeof(int));

    graph->matriceAdjacence = malloc(nbrSommets * sizeof(bool));

    graph->nbrSommets = model->nbrSommets;

    /* Copie du tableau de durées */
    for (int i = 0; i < nbrSommets; i++)
    {
        graph->durees[i] = model->durees[i];
    }

    /* Copie de la matrice d'adjacence */
    for (int i = 0; i < nbrSommets; i++)
    {
        graph->matriceAdjacence[i] = malloc(nbrSommets * sizeof(bool));
        for (int j = 0; j < nbrSommets; j++)
        {
            graph->matriceAdjacence[i][j] = model->matriceAdjacence[i][j];
        }
    }

    return graph;
}

/*--------------------liberer graphe-------------------*/
void free_graph(Graph *graph)
{

    if (graph->matriceAdjacence != NULL)
    {

        free(graph->matriceAdjacence);
    }
    if (graph->durees != NULL)
        free(graph->durees);

    free(graph);
}
