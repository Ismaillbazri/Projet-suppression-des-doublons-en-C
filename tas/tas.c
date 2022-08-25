#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"tas.h" 
 
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

int Leven(char *x,char *y)   
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
int nbre(char ** t)
{
	int n=0;
	while(t[n])
	{
		n++;
	}
	return n;
}
void permuter(char *s,char *q)
{
   char *tmp=malloc(10*sizeof(char));
		  strcpy(tmp,s);
          strcpy(s,q);
          strcpy(q,tmp);
    free(tmp);
} 

void Ajout(char *s, char **t)
{
	int i,n=0;
    while(t[n])
	{
		n++; 
	}	
	t[n]=(char*)malloc(strlen(s)*sizeof(char));
	strcpy(t[n],s);
	i=n;
	while((i>0)&&(strcmp(t[i],t[i/2])<0)) 
	{      
	      permuter(t[i],t[i/2]);  
	      i=i/2; 
	}
	t[n+1]=(char*)malloc(sizeof(char));
	t[n+1]=NULL;
} 
char *  ExtraireMin(char **t) 
{
	int i,j,n=0;
	char *temp=(char*)malloc(10*sizeof(char));
	n=nbre(t);
	n--; 
	strcpy(temp,t[0]);
	strcpy(t[0],t[n]);
	i=0;
	while((i<n/2)&&((strcmp(t[i],t[2*i+1])>0)||(strcmp(t[i],t[2*i+2])>0)))
	{
		if(strcmp(t[2*i+1],t[2*i+2])>0)
		permuter(t[i],t[2*i+2]);
		else if(strcmp(t[2*i+1],t[2*i+2])<0)
		{permuter(t[i],t[2*i+1]);}
		i=2*i+1;
	}
	t[n]=NULL;
	return temp;
} 
char **LireToTas(char *nomfichier){
    char** tas=calloc(1,sizeof(char*)); 
    FILE* f;  
    f=fopen(nomfichier,"r");  
    int k=1; 
    while(!feof(f)){  
            char *nom=malloc(30*sizeof(char)); 
            tas=realloc(tas,(k+1)*sizeof(char*));
            k++;
            fscanf(f,"%s\n",nom);
            Ajout(nom,tas);   
            free(nom); 
              }  
    fclose(f);
    return tas; 
}  
char **MappingToTable(char *nomfichier){
    char**tas=LireToTas(nomfichier);
    char **tab=malloc(sizeof(char*)); 
    int k=0;
    while(tas[0]){
        tab=realloc(tab,(k+2)*sizeof(char*));
        tab[k]=ExtraireMin(tas); 
        k++;  
    }
    tab[k]=NULL;
    return tab; 
}  
char** purge(char* nomfichier)
{
    
    int j,i,g,dbl,k=1; 
    char  **res=malloc(sizeof(char*));
    char **noms;  
    FILE *f;
    
    noms=MappingToTable(nomfichier);
    res[0]=malloc(strlen(noms[0])*sizeof(char));
    strcpy(res[0],noms[0]);
    i=1;
            while(noms[i])
            {
                for(j=i-1;j>=0;j--) 
                {
                    dbl=0;
                     g=Leven(noms[i],noms[j]);
                    if (g<=1) 
                    {
                        dbl=1; 
                        break;
                    }
                }
                if(dbl==0)
                {
                    res=realloc(res,(k+1)*sizeof(char*));
                    res[k]=malloc(strlen(noms[i])*sizeof(char));
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
		   remove(nomfichier);
		   rename("temp.txt",nomfichier);
            return res;  
} 

