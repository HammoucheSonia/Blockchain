#include "projet.h"

// fonction suplementaire pour tranformer les nombre en str

int number(long n)
{
    int somme; 
    somme = 0; 

    while (n>0)
    {
        n = n/10;
        somme++;
    }
    return (somme);
}

char *ft_itoa(int p)
{
    int i;
    int n;
    char *str;

    i=0;
    n=number(i);
    str = malloc(sizeof(char)*(n+1));
    while (n>i)
    {
        str[n]=p/10;
        p = p/10;
        n--;    
    }
    str[n+1]='\0';
    return (str);
}
