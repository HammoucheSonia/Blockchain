#include "projet.h"
#include <string.h>
//Déclarations sécurisées

//Manipulation de structure sécurisé 
//Manipulation de clés 

//Question 2 
void init_key(key *key, long val, long n)
{

    key->val=val; 
    key->n=n;
}

//Question 3
void init_pair_keys(key *pkey, key *skey, long low_size, long up_size)
{
    long p = random_prime_number(low_size, up_size, 5000);
    long q = random_prime_number(low_size, up_size, 5000);
    long s,u,n; 
    generate_key_values(p,q,&n,&s,&u);
    skey->n=n;
    pkey->n=n;
    skey->val=u;
    pkey->val=s;
}

//Question 4
char *key_to_str(key *key)
{
    char base[16]="0123456789abcdef";
    char *str;
    str = strdup("");
    str = strcat(str,"(");
    str = strcat(str,ft_itoa(key->val,base));
    str = strcat(str,",");
    str = strcat(str, ft_itoa(key->n,base));
    str = strcat(str,")");
    return(str);

}

key *str_to_key(char *str)
{
    key *cle;
    cle = malloc(sizeof(key));
    char base[16]="0123456789abcdef";
    char *valeur= malloc (sizeof(char) * 100);
    char *nombre= malloc (sizeof(char) * 100) ;
    sscanf(str,"(%s,%s)",valeur,nombre);
    valeur = ft_convert_base(valeur,"0123456789ABCDEF","0123456789");
    nombre = ft_convert_base(nombre,"0123456789ABCDEF","0123456789");
    int n = atoi(nombre);
    int val = atoi(valeur);
    cle->val = val;
    cle->n = n;
    free(valeur);
    free(nombre);
    return (cle);
}

//Exercice 6
Signature *init_signature(long *content, int size)
{
    Signature *first;
    first = malloc(sizeof(Signature));
    int i;
    i = 0;
    while (i < size)
    {
        first->tableau[i] = content[i];
        i++;
    }
    return(first);
}

//Exercice 7
Signature *sign(char *mess,key *skey)
{
    int s = skey->val;
    int n = skey->n; 
    Signature *sign; 
    sign = malloc(sizeof(Signature));
    sign->tableau = encrypt(mess,s,n);
    return (sign);
}

//Exercice 8
char *signature_to_str(Signature *sign)
{
    char *result = malloc(10*sign->size*sizeof(char));
    result[0]='#';
    int pos = 1;
    char buffer[165];
    for (int i=0; i<sign->size;i++)
    {
        sprintf(buffer,"%lx",sign->tableau[i]);
        for(int j= 0; j<strlen(buffer); j++)
        {
            result[pos]= buffer[j];
            pos++;
        }
        result[pos] = '#';
        pos++;
    }
    result[pos] = '\0';
    result = realloc(result,(pos+1)*sizeof(char));
    return(result);
}

Signature *str_to_signature(char *str)
{
    int len = strlen(str);
    long *content = (long*)malloc(sizeof(long)*len);
    int num = 0;
    char buffer[256];
    int pos = 0;
    for (int i = 0;i<len; i++)
    {
        if (str[i]= '#')
        {
            buffer[pos]= str[i];
            pos = pos +1;
        }
        else
        {
            if(pos !=0)
            {
                buffer[pos] = '\0';
                sscanf(buffer,"%lx", &(content[num]));
                num = num +1 ;
                pos =0;
            }

        }
    }
    content = realloc(content, num * sizeof(long));
    return (init_signature(content, num));
}

//Question 10
Protected *init_protected(key *pkey, char *mess, Signature *sign)
{
    Protected *protege; 
    protege = malloc(sizeof(Protected));
    protege->pkey=pkey;
    protege->mess=mess;
    protege->sign=sign;
    return(protege);
}

//Exercice 11
int verify(Protected *pr)
{
    if(pr->sign->tableau == encrypt(pr->mess, pr->pkey->val,pr->pkey->n))
        return(1);
    return(0);
}

//Exercice 12
char *protected_to_str(Protected *pr)
{
    char *str; 
    char base[16]="0123456789ABCDEF";
    int i; 
    int n; 
    i = 0; 
    n = pr->sign->size; 
    str = strcat(key_to_str(pr->pkey)," ");
    str = strcat(str,pr->mess);
    str = strcat(str," ");
    while (i<n)
    {
        str = strcat(str, ft_itoa(pr->sign->tableau[i],base));
        i++;
    }
    return (str);
}

Protected *str_to_protected(char *str)
{
    Protected *protege; 
    protege = malloc(sizeof(Protected));
    char base[16]="0123456789ABCDEF";
    char *mess = malloc(sizeof(char)*10000);
    char *Signature = malloc(sizeof(char)*10000);
    char *cle = malloc(sizeof(char)*10000);
    int i = 0;
    int n;
    sscanf(str,"%s %s %s ",cle,mess,Signature);
    protege->pkey = malloc(sizeof(key));
    protege->pkey = str_to_key(cle);
    protege->mess = strdup(mess);
    n = protege->sign->size;
    protege->sign->tableau = malloc(sizeof(int)*n);
    char *NB = malloc(sizeof(char)*100000);
    while (i<n)
    {
        NB = ft_convert_base(Signature,"01234567789ABCDEF","0123456789");
        protege->sign->tableau[i] = atoi(NB);
        i++;
    }
    free(NB);   
    return(protege);
}

int main()
{
    srand(time(NULL));

    //Testing Init Keys
    key *pkey = malloc(sizeof(key));
    key *skey = malloc(sizeof(key));
    init_pair_keys(pkey,skey,3,7);
    printf("pKey : %lx, %lx \n", pkey->val,pkey->n);
    printf("sKey : %lx, %lx \n", skey->val,skey->n);

    //Testing Key Serialisation 
    char *chaine = key_to_str(pkey);
    printf("key_to_str: %s\n", chaine);
    key *k= str_to_key(chaine);
    printf("str_to_key: %lx, %lx \n", k->val, k->n);

    //Testing Signature 
    //Candidate keys
    key *pKeyC = malloc(sizeof(key));
    key *sKeyC = malloc(sizeof(key));
    init_pair_keys(pKeyC,sKeyC,3,7);

    //Declaration 
    char *mess = key_to_str(pKeyC);
    printf("%s vote pour %s\n", key_to_str(pkey), mess);
    Signature *sig = sign(mess, skey);
    printf("Signature :");
    print_long_vector(sig->tableau,sig->size);
    chaine = signature_to_str(sig);
    printf("Signature to str : %s \n", chaine);
    sig = str_to_signature(chaine);
    printf("str_to_signature :");
    print_long_vector(sig->tableau,sig->size);

    //Testing protected 
    Protected *pr = init_protected(pkey,mess,sig);

    //Verification 
    if (verify(pr))
        printf("Signature valide\n");
    else
        printf("Signature non valide \n");
    chaine = protected_to_str(pr);
    printf("protected to str %s \n", chaine);
    //pr = str_to_protected(chaine);
    printf("str to perotected %s %s %s \n", key_to_str(pr->pkey),pr->mess, signature_to_str(pr->sign));

    free(pkey);
    free(skey);
    free(pKeyC);
    free(sKeyC);
    return (0);
}



/*int main ()
{
    printf("bonjour");
    return (0);
}*/