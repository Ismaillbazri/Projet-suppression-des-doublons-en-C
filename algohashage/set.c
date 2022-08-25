#include "hash.h"

int calculhach(char *mot,int taille)
{
	int c,s=0,i=0;
	while(mot[i]!='\0')
	{
		s=s+mot[i];
		i++;
	}
	c=s%taille;
	return c;
}
int nbrlignes(char* fichier)
{
	FILE* f;
	char *tmp=(char*)malloc(30*sizeof(char));
	int s=0;
	f=fopen(fichier,"r");
	while(!feof(f))
	{fscanf(f,"%s",tmp);
    	s++;}
	fclose(f);
	return s-1;
	
}
void ajoutMot(maillon **table, char *mot, int taille)
{
    int cle;
    cle= calculhach(mot, taille);
    maillon *t;
    maillon *tn;
    t = (maillon *)malloc(sizeof(maillon));
    tn = (maillon *)malloc(sizeof(maillon));
    t->val=strdup(mot);
    t->suiv=NULL;
    if(strcmp(table[cle]->val,"") == 0)
        table[cle] =t;
    else
    {
        tn = table[cle];
        while(tn->suiv != NULL)
        { tn = tn->suiv;}
       tn->suiv =t;
    }
}
char** lire(char * nomfichier)
{   
    char** t;
    FILE *f;
    f=fopen(nomfichier,"r");
    int i=0;
    int n=nbrlignes(nomfichier);
    char *tmp=(char*)malloc(30*sizeof(char));
     t=(char**)malloc(nbrlignes(nomfichier)*sizeof(char*));
    while(i<n)
    {
            fscanf(f,"%s",tmp);
            t[i]=(char*)malloc(strlen(tmp)*sizeof(char));
            strcpy(t[i],tmp);
            i++;
    }
    fclose(f);
    t[i]=NULL;
    return t; 
} 
maillon **MappingToHashTable(char * fichier,int taille)
{
    maillon   **table;
	int i;
	char **noms;
    i = 0;
    table = (maillon **)malloc(sizeof(maillon*)*taille);
    while (i < taille)
    {
        table[i] = (maillon *)malloc(sizeof(maillon));
        table[i]->val = strdup("");
        table[i]->suiv = NULL;
        i++;
    }
    noms=lire( fichier);
    i = 0;
    while(i<nbrlignes(fichier))
    {
        ajoutMot(table, noms[i],taille);
        i++;
    }
    free(noms);
	return (table);
}
void afficher(maillon **t,int taille)
{
	int i;
	struct maillon *m;
	printf("cle\tval\n");
	for(i=0;i<taille;i++)
	{   
		printf("%d\t%s",i,t[i]->val);
		m=t[i]->suiv;
		while(m!=NULL)
		{
			printf("\t%s",m->val);
			m=m->suiv;
		}
		printf("\n");
	}
}
int Min(int a, int b)
{
    if (a>=b) return b;
    else return a;
}
int notegal(char a , char b)
{
    return (a==b)? 0:1;
    if (a==b)
     return 0;
    else return 1; 
}
int leven(char *x,char *y)   
{ 
    int n,m,i,j;
    n = strlen(x); 
    m = strlen(y);
    int T[n+1][m+1]; 
    T[0][0] = 0;
    for( i=1;i < n+1;i++)
    {
        T[i][0] = T[i-1][0] + 1;
    }
    for( j=1;j < m+1;j++)
    {
        T[0][j] = T[0][j-1] + 1;
    }
    for( i=1;i<n+1;i++)
    {
        for( j=1;j<m+1;j++)
        {    
            T[i][j]=Min(T[i-1][j-1]+notegal(x[i-1],y[j-1]),Min(T[i-1][j]+1,T[i][j-1]+1));
        }
    }
    
    return T[n][m]; 
}
int	max(int a,int b)
{
	if (a > b)
	return (a);
	else
	return (b);
}
int		vide(char *t)
{
	int i;
	int l;

	i= 0;
	l = strlen(t);
	while (i < l)
	{
		if (!(t[i] == '\0' || t[i] == ' ' || t[i] == '\n' || t[i] == '\t'||
			 t[i] == '\v' ||t[i] == '\f' || t[i] == '\r'))
			return (0);
		i++;
	}
	return (1);
}
char** HashTolist(maillon** hashTab,int n,int N) 
{
    //printf("%d\n",lentab); 
    char** tab=(char**)malloc(N*sizeof(char*));
    int j=0;
    int i;
    for(i=0;i<n;i++)
    {
        if(hashTab[i]!=NULL)  
        {
            tab[j]=(char*)malloc(strlen(hashTab[i]->val)*sizeof(char));
            strcpy(tab[j],hashTab[i]->val);
            j++;
            maillon* temp=(maillon*)malloc(sizeof(maillon));
            temp=hashTab[i]->suiv;
           
            while(temp!=NULL)
            {
                
                tab[j]=(char*)malloc(strlen(hashTab[i]->val)*sizeof(char));
                strcpy(tab[j],temp->val);
                j++;
                temp=temp->suiv;
            }
        }
    }
    return tab;
}
char** purge(char *fichier,int n)
{   
    maillon **tab; 
    FILE *f;
    char** res=(char**)malloc(sizeof(char*));
    char **noms;
    int i,j,k=0,N,dbl;
    float pluslong,g;
    maillon *m;
    N=nbrlignes(fichier);
    tab=MappingToHashTable(fichier,n);
    noms=HashTolist(tab,n,N);
    res[0]=(char*)malloc(strlen(noms[0])*sizeof(char));
    strcpy(res[0],noms[0]);
    i=1;
            while(noms[i])
            {
                j=i+1;
				while((j-i)<=5 && j<N) 
                {
                    dbl=0;
                    pluslong=(float)(max(strlen(noms[i]),strlen(noms[j])));
                     g=(1-(leven(noms[i],noms[j])/pluslong));
                    if (g>=0.8) 
                    {
                        dbl=1;
                        break;
                    }
                    j++;
                }
                if(dbl==0)
                {
                    res=(char**)realloc(res,(k+1)*sizeof(char*));
                    res[k]=(char*)malloc(strlen(noms[i])*sizeof(char));
                    strcpy(res[k],noms[i]);
                    k++;
                }
                i++; 
            } 
            free(noms);
            res[k]=NULL;  
            f=fopen("temp.txt","w");
           for(i=0;res[i];i++)
           {
           	fprintf(f,"%s\n",res[i]);
		   }
		   fclose(f);
		   remove(fichier);
		   rename("temp.txt",fichier);
            return res; 


}
