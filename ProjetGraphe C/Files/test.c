#include "./library/Fichier.h"
#include "./library/File.h"

int main(int argc, char const *argv[])
{
    int nbrSommets =0;
    File **tableauContraintes = fetchDatas("/home/aurel-m02/Documents/OrdonnancementGraphe/ProjetGraphe C/test.txt",&nbrSommets);
    printf("%d\n",nbrSommets);

    for (int i = 0; i < nbrSommets; i++)
    {
        freeFile(tableauContraintes[i]);
    }
    if (tableauContraintes != NULL)
    {
        free(tableauContraintes);
    }
    

    return 0;
}
