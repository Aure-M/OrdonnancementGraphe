#include "Graph.h"

/* Affichage matrice d'ajacence  */

void affichageMatAdjacence(bool **tab, int len)
{
    printf("-----------MATRICE D'ADJACENCE----------\n\n    ");
    for (int i = 0; i < len; i++)
    {
        printf("%d ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < len; i++)
    {

        if ((i + 1) / 10 >= 1)
        {
            printf("%d ", i + 1);
        }
        else
        {
            printf("%d  ", i + 1);
        }

        for (int j = 0; j < len; j++)
        {
            if (tab[i][j] == true)
                printf("\033[1;31m O\033[0m");
            else
                printf(" X");
        }
        printf("\n");
    }
    printf("\n---------------------------------------\n\n");
}

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
    graph->durees = malloc(nbrSommets * sizeof(int));

    /*
        Puisque le premier élément de chaque case de notre tableau(tab_Duree_Et_Contraintes)
        correspond à la duree de la tache représentée par ce noeud nous allons retirer pour chaque
        case le premier élément de sa liste pouur remplir le tableau de durée
    */

    for (int i = 0; i < nbrSommets; i++)
    {
        index = defiler(tab_Duree_Et_Contraintes[i]);
        graph->durees[index] = defiler(tab_Duree_Et_Contraintes[i]);
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
bool detectionCircuit(Graph *graph)
{
    Graph *copieGraphe = copie(graph);
    File *f1 = NULL, *f2 = NULL;
    int tmpNode = -1, sommetsRestants = graph->nbrSommets;

    f1 = detectPointEntree(copieGraphe);
    f2 = detectPointSortie(copieGraphe);

    while (f1->firstElement != NULL || f2->firstElement != NULL)
    {

        /* Suppression des sommets présents dans f1 */
        while (f1->firstElement != NULL)
        {
            tmpNode = defiler(f1);
            for (int i = 0; i < graph->nbrSommets; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode - 1] = 0;
                copieGraphe->matriceAdjacence[tmpNode - 1][i] = 0;
            }
            sommetsRestants--;
        }

        /* Suppression des sommets présents dans f1 */
        while (f2->firstElement != NULL)
        {
            tmpNode = defiler(f2);
            for (int i = 0; i < graph->nbrSommets; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode - 1] = 0;
                copieGraphe->matriceAdjacence[tmpNode - 1][i] = 0;
            }
            sommetsRestants--;
        }

        /* Si il ne reste qu'un seul sommet le graphe ne peut pas être un circuit */
        if (sommetsRestants <= 1)
            return false;

        f1 = detectPointEntree(copieGraphe);
        f2 = detectPointSortie(copieGraphe);
    }

    freeFile(f1);
    freeFile(f2);

    return true;
}

bool a_un_arc_negatif(Graph *graph)
{
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        if (graph->durees[i] < 0)
        {
            printf("Le sommet %d a une durée négative ( %d )\n", i + 1, graph->durees[i]);
            return true;
        }
    }
    printf("Ce graphe n'a pas d'arc négatif ^^ \n");
    return false;
}

int *rangsSommets(Graph *graph)
{
    Graph *copieGraphe = copie(graph);
    File *f1 = NULL;
    Element *parcoursF1 = NULL, *parcoursF1_prec = NULL;
    int tmpNode = -1, rangActuel = 0, sommetsEffaces_len = 0;
    int *rangs = malloc(graph->nbrSommets * sizeof(int)), *sommetsEffaces = NULL;
    bool isF1Modified;
    
    f1 = detectPointEntree(copieGraphe);
    printf("\nF1 = ");
    afficherFile(f1);
    //    affichageMatAdjacence(copieGraphe->matriceAdjacence, copieGraphe->nbrSommets);
    sleep(3);
    while (f1->firstElement != NULL)
    {

        while (f1->firstElement != NULL)
        {
            tmpNode = defiler(f1);
            sommetsEffaces = sommetsEffaces == NULL ? malloc(sizeof(int)) : realloc(sommetsEffaces, (sommetsEffaces_len + 1) * sizeof(int));
            sommetsEffaces_len++;

            sommetsEffaces[sommetsEffaces_len - 1] = tmpNode;

            for (int i = 0; i < graph->nbrSommets; i++)
            {
                copieGraphe->matriceAdjacence[i][tmpNode - 1] = 0;
                copieGraphe->matriceAdjacence[tmpNode - 1][i] = 0;
            }
            rangs[tmpNode - 1] = rangActuel;
        }

        f1 = detectPointEntree(copieGraphe);

        printf("\navant épurage F1 = ");
        afficherFile(f1);
        /*Epurage je vais en faire une fonction*/
        parcoursF1 = f1->firstElement;
        parcoursF1_prec = f1->firstElement;

        printf("\nSommets effacés\n");
        for (int i = 0; i < sommetsEffaces_len; i++)
        {
            printf("%d ", sommetsEffaces[i]);
        }
        printf("\n");
        sleep(2);
        while (parcoursF1 != NULL)
        {
            isF1Modified = false;
            for (int i = 0; i < sommetsEffaces_len; i++)
            {
                if (parcoursF1->nombre == sommetsEffaces[i])
                {
                    printf("%d,%d on efface %d\n",sommetsEffaces[i],parcoursF1->nombre,parcoursF1->nombre);
                    if (parcoursF1 == f1->firstElement)
                    {
                        defiler(f1);
                        parcoursF1 = f1->firstElement;
                        parcoursF1_prec = f1->firstElement;

                        afficherFile(f1);
                    }
                    else
                    {
                        parcoursF1_prec->suivant = parcoursF1->suivant;
                        free(parcoursF1);
                        parcoursF1 = parcoursF1_prec->suivant;
                        afficherFile(f1);
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
            
            sleep(2);


        }

        printf("\naprès épurage F1 = ");
        afficherFile(f1);
        sleep(3);
        rangActuel++;
    }

    freeFile(f1);

    return rangs;
}
void affichageRangsSommets(Graph *graph)
{
    int *rangs = rangsSommets(graph);
    printf("------ Rangs des sommets -----");
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d -> %d\n", i + 1, rangs[i]);
    }
    printf("----------------------------\n");
}

int *calendrierAuPlusTot(Graph *graph)
{
    int *durees = graph->durees, *calendrier = malloc(graph->nbrSommets * sizeof(int));
    int tmp;

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        tmp = 0;
        for (int j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[j][i] == true)
            {
                tmp = (calendrier[j] + durees[j]) > tmp ? (calendrier[j] + durees[j]) : tmp;
            }
        }

        calendrier[i] = tmp;
    }

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d = %d\n", i + 1, calendrier[i]);
    }

    free(calendrier);
    return calendrier;
}
int *calendrierAuPlusTard(int dateDerniereTache, Graph *graph)
{
    int *durees = graph->durees, *calendrier = malloc(graph->nbrSommets * sizeof(int));
    int tmp = dateDerniereTache, derniere_DateAuPlusTard = dateDerniereTache;

    calendrier[graph->nbrSommets - 1] = dateDerniereTache;
    for (int i = graph->nbrSommets - 2; i >= 0; i++)
    {
        for (int j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[j][i] == true)
            {
                tmp = tmp > (derniere_DateAuPlusTard - durees[i]) ? (derniere_DateAuPlusTard - durees[i]) : tmp;
            }
        }

        calendrier[i] = tmp;
        derniere_DateAuPlusTard = tmp;
    }

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d = %d\n", i + 1, calendrier[i]);
    }

    free(calendrier);
    return NULL;
}
int *marges(Graph *graph)
{

    return NULL;
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
