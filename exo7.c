#include "projet.h"
#include <string.h>
//structure d'un block et persistance 


//Question 1
//ecrire dasn un fichier un block

void ecrire_block(Block *un_block)
{
    FILE *fichier; 
    fichier = fopen("fichier.txt", "a");
    char *str1 = malloc(sizeof(char)*1000);
    char *str2 = malloc(sizeof(char)*1000);
    fprintf(fichier,"%s %s %s %s %d",str1,str2,un_block->hash, un_block->previous_hash,un_block->nonce);
    un_block->author = str_to_key(str1);
    un_block->votes->data = str_to_protected(str2);
    free(str1);
    free(str2);
    fclose(fichier);
}

Block *lire_block(char *filname)
{
    FILE* fichier = NULL;
    fichier = fopen(filname, "r");
    Block *bloc = malloc(sizeof(Block));
    char *str1 = malloc(sizeof(char)*1000);
    char *str2 = malloc(sizeof(char)*1000);
 
    if (fichier != NULL)
    {
        fscanf(fichier,"%s %s %s %s %d",str1,str2,bloc->hash,bloc->previous_hash,&bloc->nonce);
        bloc->author = str_to_key(str1);
        bloc->votes->data = str_to_protected(str2);
 
        fclose(fichier);
    }
    return (bloc);
}

//creation de block valide 
char* block_to_str(Block* block)
{
    char *str;
    str = strcat(str, key_to_str(block->author));
    while (block->votes->data)
    {
        str = strcat(str, protected_to_str(block->votes->data));
        block->votes = block->votes->next;
    }
    str = strcat(str, block->hash);
    str = strcat(str, block->previous_hash);
    str = strcat(str, ft_itoa(block->nonce, "0123456789ABCDEF"));
    return (str);
}

void compute_proof_of_work(Block *B, int d)
{
    char *str = malloc(sizeof(char)*100);
    char *s = malloc(sizeof(char)*100);
    str = ft_itoa(d, "0123456789ABCDEF");
    int i = 0;
    while (i<d)
    {
        s = strcat("0", s);
        i++;
    }
    str = strcat(s, str);
    B->nonce = atoi(str);


}

int verify_block(Block*b, int d)
{
    char *str = malloc(sizeof(char)*1000);
    str = ft_itoa(b->nonce,"0123456789ABCDEF");
    int i = 0;
    while (i<d)
    {
        if (str[i] != '0')
            return (0);
        i++;
    }
    return (1);
}

void delete_block(Block* b)
{
    free(b->author);
    free(b->hash);
    free(b->previous_hash);
    free(b->votes);
}
