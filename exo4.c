#include "projet.h"

//Création de donnees pour simuler le processus de vote 

//Question 1
void generate_random_date(int nv, int nc)
{
    FILE *fichier; 
    //ouverture du fichier en ecriture 
    fichier = fopen("keys.txt","w");
    if (fichier != NULL)
    {
        fprintf(fichier,"%d",nc);
        fprintf(fichier,"%d",nv);
        fclose(fichier);
    }
    int candidat=rand();
    if (candidat == nc)
    {
        FILE*fichierC;
        if (fichierC != 0)
        {
            fprintf(fichierC,"%d",nc);
            fclose(fichierC);
        }
    }
    //creer une declarartion de vote
}