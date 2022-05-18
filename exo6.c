#include "projet.h"

HashCell *create_hashcell(key *key)
{
    HashCell *cellule; 

    cellule = malloc(sizeof(HashCell));
    cellule->val = 0;
    cellule->key = key;
    return (cellule);
}

int hash_function(key *key, int size)
{
    long val;
    long n;
    val = key->val; 
    n = key->n;
    return ((val+n)/size);
}

int find_position(HashTable *t, key *key)
{
    long val;
    long n;
    val = key->val; 
    n = key->n;
    int size = t->size;
    int i = ((val+n)/size);
    int k = size;
    while (i<k)
    {
        if ((t->tab[i]->key->val) == key->val)
            return (i);
        i++;
    }
    return ((val+n)/size);
}
int nb_liste(CellKey *cell)
{
    int s=0;
    while(cell)
    {
        s++;
        cell = cell->next;
    }
    return (s);
}

HashTable *create_hashtable(CellKey *keys, int size)
{
    int nb = nb_liste(keys);
    HashTable *tab_hash = malloc(sizeof(HashTable));
    HashCell **tableau = malloc(sizeof(HashCell)*nb);
    int i = 0;
    int k;
    while (nb>i)
    {
        k = hash_function(keys->data, size);
        if (!tableau[k])
        {
            tableau[k]->key = keys->data;
            tableau[k]->val = keys->data->val;
        }
        else
        {
            tableau[k++]->key = keys->data;
            tableau[k++]->val = keys->data->val;

        }
        keys = keys->next;
        i++;
    }
    tab_hash->tab = tableau;
    tab_hash->size = size; 
    return (tab_hash);
}

void delete_hashtable(HashTable *t)
{
    int i = 0;
    int n = t->size; 
    while (i<n)
    {
        free(t->tab[i]->key);
        free(t->tab[i]);
        i++;
    }
    free(t->tab);
    free(t);
}

static int key_in_tab(CellKey *CellKey, key *cle)
{
    while (CellKey)
    {
        if ((cle->val == CellKey->data->val)&&(cle->n == CellKey->data->n))
            return (1);
        CellKey = CellKey->next;
    }
    return (0);
}

key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV)
{
    HashTable *Hc = create_hashtable(candidates, sizeC);
    HashTable *Hv = create_hashtable(voters, sizeV);
    Protected *un_vote = malloc(sizeof(Protected));
    un_vote = decl->data;
    int *scrutin;
    int i;
    while (!un_vote)
    {
        if (verify(decl->data) && key_in_tab(voters,un_vote->pkey) == 1 && key_in_tab(candidates, str_to_key(un_vote->mess))==1)
        {
            i = find_position(Hc, str_to_key(un_vote->mess));
            scrutin[i] = scrutin[i]++;
        }
        decl= decl->next;
    }
    int max = 0;
    i = 0;
    int pos; 
    while (scrutin[i])
    {
        if (scrutin[i>max])
        {
            max = scrutin[i];
            pos =i;
        }
    }
    return (Hc->tab[pos]->key);
}