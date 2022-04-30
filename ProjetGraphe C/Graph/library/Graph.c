#include "Graph.h"
#include "Calendrier.c"
#include "Rangs.c"
#include "Affichage.c"

void remplirTabDurees(Graph *graph, File **tab_Duree_Et_Contraintes)
{
    int tache, duree;
    graph->durees = malloc((graph->nbrSommets) * sizeof(int));
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        if (i == 0 || i == graph->nbrSommets - 1)
        {
            graph->durees[i] = 0;
        }
        else
        {

            tache = defiler(tab_Duree_Et_Contraintes[i - 1]);
            duree = defiler(tab_Duree_Et_Contraintes[i - 1]);

            graph->durees[tache] = duree;
        }
    }
}

void remplirMatAdjacence(Graph *graph, File **tab_Duree_Et_Contraintes)
{

    int tache;
    int arcs = 0;
    bool isSelected;

    graph->matriceAdjacence = malloc((graph->nbrSommets) * sizeof(bool *));

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        graph->matriceAdjacence[i] = malloc((graph->nbrSommets) * sizeof(bool));
        for (int j = 0; j < graph->nbrSommets; j++)
        {
            graph->matriceAdjacence[i][j] = 0;
        }
    }

    for (int i = 1; i < graph->nbrSommets - 1; i++)
    {

        while (tab_Duree_Et_Contraintes[i - 1]->firstElement != NULL)
        {
            tache = defiler(tab_Duree_Et_Contraintes[i - 1]);
            graph->matriceAdjacence[tache][i] = 1;
            printf("\t%d -> %d\n", tache, i);
            arcs++;
        }
    }

    for (int i = 1; i < graph->nbrSommets - 1; i++)
    {
        isSelected = true;
        for (int j = 1; j < graph->nbrSommets - 1; j++)
        {
            if (graph->matriceAdjacence[j][i] == 1)
            {
                isSelected = false;
                break;
            }
        }
        if (isSelected)
        {
            graph->matriceAdjacence[0][i] = 1;
            printf("\t%s -> %i\n", ALPHA, i);
            arcs++;
        }
    }

    for (int i = 1; i < graph->nbrSommets - 1; i++)
    {
        isSelected = true;
        for (int j = 1; j < graph->nbrSommets - 1; j++)
        {
            if (graph->matriceAdjacence[i][j] == 1)
            {
                isSelected = false;
                break;
            }
        }
        if (isSelected)
        {
            graph->matriceAdjacence[i][graph->nbrSommets - 1] = true;
            printf("\t%d -> %s\n", i,OMEGA);
            arcs++;
        }
    }
    printf("\t%d arcs\n",arcs);
}

Graph *initGraph(int nbrSommets, File **tab_Duree_Et_Contraintes)
{
    Graph *graph = malloc(sizeof(*graph));
    bool isSelected = true;
    int tmpNode = -1;
    int index = -1;
    if (graph == NULL)
    {
        perror("Erreur pendant la création du graphe");
        exit(EXIT_FAILURE);
    }
    graph->nbrSommets = nbrSommets + 2;
    printf("* Création du graphe d’ordonnancement:\n");
    printf("\t%d sommets\n", nbrSommets);

    remplirTabDurees(graph, tab_Duree_Et_Contraintes);

    remplirMatAdjacence(graph, tab_Duree_Et_Contraintes);

    free(tab_Duree_Et_Contraintes);
    printf("\n* Fin de création du graphe d’ordonnancement:\n");

    return graph;
}

/*-----------------------copie----------------------*/

Graph *copie(Graph *model)
{
    int nbrSommets = model->nbrSommets;
    Graph *graph = malloc(sizeof(graph));

    graph->durees = malloc(nbrSommets * sizeof(int));

    graph->matriceAdjacence = malloc(nbrSommets * sizeof(bool *));

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
