#include <stdlib.h> 
//Question 1 

/* renvoie 1 si p est premier 0 si non */
int is_prime_naive(long p)
{
    long i;
    i = 2;

    while (i<p)
    {
        if (p%i==0)
            return(0);
        i++;
    }
    return (1);
}

//Qestion 2 
/*le plus grand nombre prmier calculé en mois de 2 milisecondes est 13 */

/* EXPONENTIATION MODULAIRE RAPIDE 
Question 3 */

long modpow_naive(long a, long m, long n)
{
    long i;
    int res;

    res = 1;
    i = 0;
    while (i<m)
    {
        res = (res * a)%n;
        i++; 
    }
    return (res);
}

//Question 4

int modpow(long a, long m, long n)
{
    if (m == 0)
        return (1);
    else 
    {
        if (m % 2 == 0) //m est pair
            return ((modpow(a,m/2,n)*modpow(a,m/2,n))%n);
        else 
            return (a*(modpow(a,m/2,n)*modpow(a,m/2,n))%n);
    }
}

//Qestion 5 

//TEST MILLLER-RABIN 

int witness(long a, long b, long d, long p)
{
    long x = modpow(a,d,p);
    if (x==1)
        return (0);
    for (long i=0; i<b; i++)
    {
        if (x==p-1)
            return (0);
        x = modpow(x,2,p);
    }
    return (1);
}

long rand_long(long low, long up)
{
    return(rand()%(up-low+1)+low);
}

int is_prime_miller(long p, int k)
{
    if (p==2)
        return (1);
    if (!( p & 1) || p <= 1)
        return (0);
    long b=0;
    long d = p-1;
    while (!( d & 1))
    {
        d= d/2;
        b++;
    }
    long a;
    int i;
    for(i = 0; i < k ; i++)
    {
        a = rand_long (2 , p-1);
        if(witness (a,b,d,p))
            return (0);
    }
    return (1);
}

//Question 7
/* pour tout entier p non premier, au moins 3/4 des valeurs entre 2 p-1 sont temoins de Miller  pour p 
on donne une borne supérieur sur la probabilite d'erreur de l'algorithme 
itérant dans l'algorithme de Rabin-Miller sur tous les entiers <2(ln n)^2  */

//GENERATION DE NOMBRES PREMIERS

//Question 8
/* etant donné deux entier representant le max et le mon et le nombre de tests de MOller a realiser 
retourne un nombre premier de taille comprise enntre le max et le min */

long random_prime_number(int low_size, int up_size, int k)
{
    int i; 
    int n;
    int j;
    n = up_size - low_size;
    i = 0;
    while (n>i)
    {
        j = rand_long(low_size,up_size);
        if (is_prime_miller(j,k)==1)
            return (j);
        i++;
    }
    return (1);
}