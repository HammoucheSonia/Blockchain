#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>



//structure exercice 3
typedef struct key
{  
    long val;
    long n;
}key;

typedef struct signature
{
    long *tableau;
    int size;
}Signature;

typedef struct protected
{
    key *pkey;
    char *mess;
    Signature *sign;
}Protected;

//fonctions exercice 1
int is_prime_naive(long p);
long modpow_naive(long a, long m, long n);
int modpow(long a, long m, long n);
int witness(long a, long b, long d, long p);
long rand_long(long low, long up);
int is_prime_miller(long p, int k);
long random_prime_number(int low_size, int up_size, int k);

//fonctions exercices 2 
int pgcd(long n, long p);
long *calcul(long p, long q);
long calcul_s(long t);
long calcul_u(long t, long s);
long extended_gcd(long s, long t, long *u, long *v);
void print_long_vector(long *result, int size);
long *encrypt(char *chaine, long s, long n);
char *decrypt(long* crypted, int size, long u, long n);
void generate_key_values(long p, long q, long* n, long *s, long *u);

//fonctions exercices 3 
void init_key(key *key, long val, long n);
void init_pair_keys(key *pkey, key *skey, long low_size, long up_size);
char *key_to_str(key *key);
key *str_to_key(char *str);
Signature *init_signature(long *content, int size);
Signature *sign(char *mess,key *skey);
char *signature_to_str(Signature *sgn);
Signature *str_to_signature(char *str);
Protected *init_protected(key *pkey, char *mess, Signature *sgn);
int verify(Protected *pr);
char *protected_to_str(Protected *pr);
Protected *str_to_protected(char *str);

//fonctions exercices 4
void generate_random_date(int nv, int nc);


//Fonction Utiles:
char *ft_itoa(long p, char *base);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_convert_base(char *nbr, char *base_from, char *base_to);
int		ft_atoi_base(char *str, char *base, int size);


//Fonctions et structure de l'exercice 5
typedef struct cellKey
{
    key *data;
    struct cellKey *next;
}CellKey;

CellKey *create_cell_key(key *key);
CellKey *insertion(CellKey *liste, key *key);
CellKey *read_public_keys(char *fichier);
void print_list_keys(CellKey *LCK);
void delete_cell_key(CellKey *c);

typedef struct cellProtected
{
    Protected *data;
    struct cellProtected *next;
}CellProtected;

CellProtected *create_cell_protected(Protected *pr);
CellProtected *insertion_liste(CellProtected *liste,Protected *key);
CellProtected *read_public_keys_liste(char *fichier);
void print_list_protected(CellProtected *LCK);
void delete_cell_protected(CellProtected *c);

//exercice 6
typedef struct hashcell{
    key *key;
    int val;
}HashCell;

typedef struct hashtable{
    HashCell **tab; 
    int size;
}HashTable;
HashCell *create_hashcell(key *key);
int hash_function(key *key, int size);
int find_position(HashTable *t, key *key);
HashTable *create_hashtable(CellKey *keys, int size);
void delete_hashtable(HashTable *t);
key* compute_winner(CellProtected* decl, CellKey* candidates, CellKey* voters, int sizeC, int sizeV);

//exercice 7
typedef struct block {
    key *author; 
    CellProtected *votes; 
    unsigned char *hash; 
    unsigned char *previous_hash; 
    int nonce; 
} Block;
void ecrire_block(Block *un_block);
Block *lire_block(char *filname);
char* block_to_str(Block* block);
void compute_proof_of_work(Block *B, int d);
int verify_block(Block*b, int d);
void delete_block(Block* b);


//exercice 8

typedef struct block_tree_cell {
    Block * block ;
    struct block_tree_cell *father ;
    struct block_tree_cell *firstChild ;
    struct block_tree_cell *nextBro ;
    int height ;
} CellTree ;
CellTree* create_node(Block* b);
int update_height(CellTree* father, CellTree* child);
void add_child(CellTree* father, CellTree* child);
void print_tree(CellTree *arbre);
void delete_node(CellTree* node);
CellTree* highest_child(CellTree* cell);
CellTree* last_node(CellTree* tree);

//exercice 9


