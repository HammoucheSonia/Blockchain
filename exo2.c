#include "projet.h"
#include <string.h>
//Implemrntation du protocole RSA

//Generartion d'une paire (clé publique, clé secrete)

int pgcd(long n, long p)
{
    int i; 
    i = 1;

    int k; 
    if (n>=p)
        k = p;
    if (p>=n)
        k = n;
    while (k>=i)
    {
        if (n%k==0 && p%k==0)
            return(k);
        k--;
    }
    return(1);
}


long extended_gcd(long s, long t, long *u, long *v)
{
    if (s==0)
    {
        *u = 0;
        *v = 1;
        return (t);
    }
    long uPrim, vPrim;
    long gcd = extended_gcd(t%s, s, &uPrim, &vPrim);
    *u = vPrim;
    *v= uPrim;
    return (gcd);
}

void generate_key_values(long p, long q, long* n, long *s, long *u)
{
    *n = p * q;
    long t = (p - 1) * (q - 1);
    long v;
    *s = rand_long(0, t);
    long gcd = extended_gcd(*s, t, u, &v);

    if(gcd != 1) {  //on appelle la fonction récursivement tant que PGCD(s, t) != 1
        generate_key_values(p, q, n, s, u);
    }
}

void print_long_vector(long *result, int size)
{
    printf("vector : [");
    for (int i = 0; i<size; i++)
    {
        printf("%lx ", result[i]);
    }
    printf("]\n");
}

long *encrypt(char *chaine, long s, long n)
{
    long *crypt; 
    int k; 
    int i; 
    i = 0; 
    k = strlen(chaine);
    crypt = malloc(sizeof(long)*strlen(chaine));
    while (chaine[i])
    {
        crypt[i] = modpow((int)chaine[i],s,n);
        i++; 
    }
    return crypt;
}

char *decrypt(long* crypted, int size, long u, long n)
{
    char    *chaine;
    int     i;
    int     k;

    k = 0;
    i = 0;
    chaine = malloc(sizeof(char) * (size + 1));
    while (i<size)
    {
        //k = modpow(crypted[i],u,n);
        chaine[i] = (char)modpow(*(crypted + i), u, n);
        i++; 
    }
    chaine[i] = '\0';
    return (chaine);
}

/*int main()
{
    srand(time(NULL));

    //Géneratiuon de cle 
    long p = random_prime_number(3,7,5000);
    long q = random_prime_number(3,7,5000);
    long n, s, u;
    generate_key_values(p,q,&n,&s,&u);

    while (p==q)
        q = random_prime_number(3, 7, 5000);
    
    //Pour avoir des cles positives 
    if (u<0)
    {
        long t = (p-1)*(q-1);
        u = u+t; //On aura toujours s*u mod 1 = 1
    }

    //Affichage des cles en hexadecimal 
    printf("cle_pubique =(%lx, %lx)\n",s,n);
    printf("cle prive = (%lx, %lx) \n",u,n);
    
    // chiffrement 
    char mess[10]="aaaaaaabcd";
    int len = strlen(mess);
    long *crypted=encrypt(mess, s, n);
    printf("initial message : %s \n", mess);
    printf("Encoded_representation \n");
    print_long_vector(crypted, len);

    //Dechifrement 
    char *decoded = decrypt(crypted, len, u,n);
    printf("Decoded : %s \n", decoded);
    return (0);
}*/

