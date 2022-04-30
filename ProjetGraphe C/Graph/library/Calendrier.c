#include "Graph.h"
#define FIN false
#define DEBUT true

int recursive(Graph *graph, int *calendrier, int sommet, int date_ALAP_DerniereTache)
{

    printf("\ndateAuPlusTard de %d :", sommet);
    File *datesAuplusTardSucesseurs = NULL;
    int min, tmp;
    if (calendrier[sommet] == -1)
    {
        printf("\tA calculer\n");
        if (sommet == graph->nbrSommets - 1)
        {
            calendrier[sommet] = date_ALAP_DerniereTache;
            return date_ALAP_DerniereTache;
        }
        else
        {

            datesAuplusTardSucesseurs = initialisation();
            for (int i = 0; i < graph->nbrSommets; i++)
            {
                if (graph->matriceAdjacence[sommet][i] == true)
                {
                    if (calendrier[i] == -1)
                        recursive(graph, calendrier, i, date_ALAP_DerniereTache);

                    enfiler(datesAuplusTardSucesseurs, calendrier[i] - graph->durees[i]);
                }
            }

            printf("\tLes datesAuplusTard des successeurs de (%d) : ", sommet);
            afficherFile(datesAuplusTardSucesseurs);
            min = defiler(datesAuplusTardSucesseurs);
            while (datesAuplusTardSucesseurs->firstElement != NULL)
            {
                tmp = defiler(datesAuplusTardSucesseurs);

                min = tmp < min ? tmp : min;
            }

            calendrier[sommet] = min;
            printf("\tDateAuplusTard (%d) = %d\n", sommet, min);
            freeFile(datesAuplusTardSucesseurs);
            return min;
        }
    }
    else
    {
        return calendrier[sommet];
    }
}

int *calendrierAuPlusTot(Graph *graph)
{
    printf("\n------------------Calcul du calendrier au plus tôt----------------------------\n");
    int *durees = graph->durees, *calendrier = malloc(graph->nbrSommets * sizeof(int));
    int tmp;
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        calendrier[i] = 0;
    }
    printf("La date au plus tôt d'un sommet 'i' s'obtient en déterminant le maximum des (valeurs des dates au plus tôt de ses prédecesseurs + la durée de réalisation de 'i')\n");
    for (int i = 0; i < graph->nbrSommets; i++)
    {
        tmp = 0;
        printf("\n-> DateAuPlusTot du sommet (%d) = MAX(", i);
        for (int j = 0; j < graph->nbrSommets; j++)
        {
            if (graph->matriceAdjacence[j][i] == true)
            {
                printf("%d,", (calendrier[j] + durees[i]));
                tmp = (calendrier[j] + durees[i]) > tmp ? (calendrier[j] + durees[i]) : tmp;
            }
        }
        printf(")\n");
        calendrier[i] = tmp;
        printf("DateAuPlusTot du sommet (%d) = %d\n", i, tmp);
    }

    printf("------------CALENDRIER AU PLUS TOT--------------\n");

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d(%d) ", i, calendrier[i]);
    }

    printf("\n-----------------------------------------------\n");

    return calendrier;
}

int *calendrierAuPlusTard(int dateDerniereTache, Graph *graph)
{
    printf("\n------------------Calcul du calendrier au plus tard----------------------------\n");

    printf("\nLa date au plus tard d'un sommet 'i' s'obtient en déterminant le minimum des (valeurs des dates au plus tard de ses successeurs - la durée de réalisation de chacun d'eux)\n");
    printf("Si la date au plus tard d'un des successeurs de 'i' n'est pas connue on la détermine d'abord en procédant comme avec 'i'\n");
    printf(" Le sommet Ψ fait exception et sa date au plus tard s'obtient avec sa date au plus tôt\n");
    int *calendrier = malloc(graph->nbrSommets * sizeof(int));

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        calendrier[i] = -1;
    }

    recursive(graph, calendrier, 0, dateDerniereTache);

    printf("------------CALENDRIER AU PLUS TARD--------------\n");

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d(%d) ", i, calendrier[i]);
    }

    printf("\n-----------------------------------------------\n");

    return calendrier;
}

int *marges(Graph *graph, int *calendrierTard, int *calendrierTot)
{
    int *result = malloc(graph->nbrSommets * sizeof(int));

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        result[i] = calendrierTard[i] - calendrierTot[i];
    }

    printf("-----------------------MARGES------------------------\n");

    for (int i = 0; i < graph->nbrSommets; i++)
    {
        printf("%d(%d) ", i, result[i]);
    }

    printf("\n-----------------------------------------------------\n");

    return result;
}

File *cheminCritique(Graph *graph, int *marges)
{
    printf("----------------------- Chemin critique ------------------------\n");

    File *chemin = initialisation();
    int sommetActuel = 0;
    enfiler(chemin, 0);
    printf("On part de 0\n");
    do
    {
        for (int i = 0; i < graph->nbrSommets; i++)
        {
            if (graph->matriceAdjacence[sommetActuel][i] == true & marges[i] <= 0)
            {
                printf("on va vers %d\n",i);
                enfiler(chemin, i);
                sommetActuel = i;
                break;
            }
        }

    } while (sommetActuel != graph->nbrSommets - 1); /* Tant que sommetActuel différent de omega*/
    printf("Fin\nLe chemin critique est : ");
    afficherFile(chemin);
    printf("----------------------- Fin Chemin critique ------------------------\n");

    return chemin;
}