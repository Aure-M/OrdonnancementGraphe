#include "./Graph/library/Graph.h"
#include "./Files/library/Fichier.h"

void askForFilePath(char *filePath)
{
    printf("--> Entrez un chemin vers le fichier de contraintes :\n");
    fgets(filePath, TAILLE_MAX_FILE_PATH, stdin);
}

bool is_DoneTesting()
{
    char continu;

    printf("--> Voulez-vous continuer les tests avec un autre fichier ? (o/n) :");
    do
    {
        scanf("%c", &continu);
        if (continu != 'o' & continu != 'n')
        {
            printf("Choississez entre 'o' et 'n' pour continuer ou arrêter les tests\n");
        }
        else
            return continu == 'o' ? false : true;
    } while (continu != 'o' & continu != 'n');
}
void removeAdditionalCaracter(char *filePath)
{
    for (int i = 0; i < TAILLE_MAX_FILE_PATH; i++)
    {
        if (filePath[i] == '\n')
        {
            filePath[i] = '\0';
        }
    }
}
int main()
{

    bool isDoneTesting = true;
    int nbrSommets;
    int *calendrierTot = NULL, *calendrierTard = NULL, *marge = NULL, *rangs = NULL;
    char filePath[TAILLE_MAX_FILE_PATH];
    File **tab_Contraintes_Durees = NULL, *chemin_critique = NULL;
    Graph *graph = NULL;
    do
    {
    beginning:
        askForFilePath(filePath);
        removeAdditionalCaracter(filePath);
        tab_Contraintes_Durees = fetchDatas(filePath, &nbrSommets);
        graph = initGraph(nbrSommets, tab_Contraintes_Durees);

        affichageMatAdjacence(graph);
        affichageMatriceValeurs(graph);

        if (verificationSurGraphe(graph) == false)
        {
            rangs = rangsSommets(graph);
            calendrierTot = calendrierAuPlusTot(graph);
            calendrierTard = calendrierAuPlusTard(calendrierTot[graph->nbrSommets - 1], graph);
            marge = marges(graph, calendrierTard, calendrierTot);
            chemin_critique = cheminCritique(graph, marge);

            printf("\n\n-----------------------------------------------------------------\n");
            printf("\n\n----------------------  RECAPITULATIF -------------------------\n");

            affichageRangsSommets(graph->nbrSommets, rangs);
            affichage_Cal_Marges(calendrierTot, graph->nbrSommets, "Calendrier au plus tôt");
            affichage_Cal_Marges(calendrierTard, graph->nbrSommets, "Calendrier au plus tard");
            affichage_Cal_Marges(marge, graph->nbrSommets, "Marges");
            printf("\n----------------------  Chemin Critique -------------------------\n");

            afficherFile(chemin_critique);
        }
        else
        {
            printf("\033[1;31mLe tableau de contraintes n'a pas passé le test de vérification.\033[0m\nChoississez un nouveau tableau de contraintes\n");
            goto beginning;
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
        if (rangs != NULL)
        {
            free(rangs);
        }
        if (chemin_critique != NULL)
        {
            freeFile(chemin_critique);
        }

        if (graph != NULL)
        {
            free_graph(graph);
        }

        isDoneTesting = is_DoneTesting();
    } while (!isDoneTesting);

    return 0;
}
