#include "projet.h"
#include <sys/types.h>
#include <sys/stat.h>
//Base de declarartion centralise 
//Lecture de stokage des donnees dans une liste chainnees 

//Question 1
CellKey *create_cell_key(key *key)
{
    CellKey *liste;
    liste = malloc(sizeof(CellKey));
    if (!liste)
        return (NULL);
    liste->data=key;
    liste->next=NULL;
    return(liste);
}

//Question 2
//ajouter en tete dans une liste
CellKey *insertion(CellKey *liste, key *key)
{
   CellKey *listeN;
   listeN = malloc(sizeof(CellKey));
   listeN->data=key;
   listeN->next=liste; 
   return (listeN);
}

//Question 3
CellKey *read_public_keys(char *fichier)
{
    CellKey *liste;
    liste = malloc(sizeof(CellKey));
        FILE *in_file = fopen(fichier, "r");
    if (!in_file) 
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(fichier, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);
    key *cle;
    cle = liste->data;

    while (fscanf(in_file, "%[^\n]", file_contents) != EOF) 
    {
        char *file_contents = malloc(sb.st_size);
        cle = str_to_key(file_contents);
        liste = liste->next;
        free(file_contents);
    }
    return (liste);    
}

//Question 4
void print_list_keys(CellKey *LCK)
{
    key *cle;
    cle = LCK->data;
    if (cle == NULL)
        return;
    printf("(%ld,%ld)", cle->val,cle->n);
    print_list_keys(LCK->next);
}

//Question 5
void delete_cell_key(CellKey *c)
{
    key *cle;
    cle=c->data;
    if (cle == NULL)
        return; 
    free(cle);
    delete_cell_key(c->next);
}

//Liste chinee de declaration signees

//Question 6
CellProtected *create_cell_protected(Protected *pr)
{
    CellProtected *liste; 
    liste = malloc(sizeof(CellProtected));
    liste->data = pr;
    liste->next = NULL;
    return (liste);
}

//Question 7
CellProtected *insertion_liste(CellProtected *liste,Protected *key)
{
   CellProtected *listeN;
   listeN = malloc(sizeof(CellProtected));
   listeN->data=key;
   listeN->next=liste; 
   return (listeN);
}

//Question 8
CellProtected *read_public_keys_liste(char *fichier)
{
    CellProtected *liste;
    liste = malloc(sizeof(CellProtected));
        FILE *in_file = fopen(fichier, "r");
    if (!in_file) 
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(fichier, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);
    Protected *cle;
    cle = liste->data;

    while (fscanf(in_file, "%[^\n]", file_contents) != EOF) 
    {
        char *file_contents = malloc(sb.st_size);
        cle = str_to_protected(file_contents);
        liste = liste->next;
        free(file_contents);
    }
    return (liste);    
}

//Question 9
void print_list_protected(CellProtected *LCK)
{
    Protected *cle;
    cle = LCK->data;
    if (cle==NULL)
        return;
    printf("(%ld,%ld), %s", cle->pkey->val,cle->pkey->n, cle->mess);
    print_list_protected(LCK->next);
}


void delete_cell_protected(CellProtected *c)
{
    Protected *cle;
    cle=c->data;
    if (cle == NULL)
        return;
    delete_cell_protected(c->next);
}