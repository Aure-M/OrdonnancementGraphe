#include "Graph.h"


/* Affichage matrice d'ajacence  */

void affichage(bool **tab, int len)
{
    printf("-----------MATRICE D'ADJACENCE----------\n\n");
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
           if(tab[i][j]==true)
                printf("\033[1;31m O\033[0m");
            else
                printf(" X");
        }
        printf("\n");
    }
    printf("\n---------------------------------------\n\n");
}



Graph *initGraph(int nbrSommets, File** tab_Duree_Et_Contraintes)
{
    Graph *graph = malloc(sizeof(*graph));
    int tmpNode = -1;
    int index=-1;
    if (graph == NULL)
    {
        perror("Erreur pendant la création du graphe");
        exit(EXIT_FAILURE);
    }
    graph->nbrSommets = nbrSommets;
    graph->durees = malloc(nbrSommets * sizeof(int));

    /*
        Puisque le premier élément de chaque case de notre tableau(tab_Duree_Et_Contraintes) 
        correspond à la duree de la tache représentée par ce noeud nous allons retirer pour chaque 
        case le premier élément de sa liste pouur remplir le tableau de durée
    */

    for (int i = 0; i < nbrSommets; i++)
    {
        index=defiler(tab_Duree_Et_Contraintes[i]);
        graph->durees[index] = defiler(tab_Duree_Et_Contraintes[i]);
    }

    
    graph->matriceAdjacence = malloc(nbrSommets * sizeof(bool*));

    printf("Remplissage de la matrice d'adjacence\n");

    /*
        Les éléments restants correspondent pour chaque case à ses prédecesseurs
    */

    for (int i = 0; i < nbrSommets; i++)
    {
        graph->matriceAdjacence[i] = malloc(nbrSommets * sizeof(bool));
        tmpNode=defiler(tab_Duree_Et_Contraintes[i]);
        for (int j = 0; j < nbrSommets; j++)
        {
            if (tmpNode-1 == j)
            {
                graph->matriceAdjacence[i][tmpNode - 1] = 1;

                if (tab_Duree_Et_Contraintes[i]->firstElement != NULL)
                    tmpNode=defiler(tab_Duree_Et_Contraintes[i]);
            }
            else
            {
                graph->matriceAdjacence[i][j] = 0;
            }
            
            
        }
        
    }
    free(tab_Duree_Et_Contraintes);
    
    affichage(graph->matriceAdjacence, nbrSommets);
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


/*---------------------détection de circuit--------------*/

File *detectPointEntree(Graph *graph)
{
    File *result = initialisation();
    bool isAnEntryPoint = true;
    int i = 0, j = 0;
    for (i = 0; i < graph->nbrSommets; i++)
    {
        isAnEntryPoint = true;
        for (j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[j][i] == 1)
            {
                isAnEntryPoint = false;
                break;
            }
        }
        if (isAnEntryPoint)
        {
            enfiler(result, i + 1);
        }
    }
    return result;
}


File *detectPointSortie(Graph *graph)
{
    File *result = initialisation();
    bool isAnEndPoint = true;
    int i = 0, j = 0;
    for (i = 0; i < graph->nbrSommets; i++)
    {
        isAnEndPoint = true;
        for (j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[i][j] == 1)
            {
                isAnEndPoint = false;
                break;
            }
        }
        if (isAnEndPoint)
        {
            enfiler(result, i + 1);
        }
    }
    return result;
}

/*---------------------détection de circuit--------------*/
bool detectionCircuit(Graph *graph){
    Graph *cpGraph = copie(graph);
    File *FilePoint = initialisation();

    int i,j,k;
    for(i = 0; i < cpGraph->nbrSommets; i++){

        FilePoint = FileCat(FilePoint,FileCat(detectPointEntree(cpGraph),detectPointSortie(cpGraph)));

        Element *firstPoint = malloc(sizeof(Element));
        firstPoint = FilePoint->firstElement;

            while (firstPoint != NULL)
            {
                for (j = 0; j < cpGraph->nbrSommets; j++)
                {
                    if(j == (firstPoint->nombre-1)){
                        for (k = 0; k < cpGraph->nbrSommets; k++)
                        {
                            cpGraph->matriceAdjacence[j][k] = 0;
                            cpGraph->matriceAdjacence[k][j] = 0;
                            if (j == k)cpGraph->matriceAdjacence[j][k] = 1;
                    }
                }
            }
            firstPoint = firstPoint->suivant;
    }
}
    return (nbElements(FilePoint) < cpGraph->nbrSommets);
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
