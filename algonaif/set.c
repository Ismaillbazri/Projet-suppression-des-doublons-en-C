#include "naif.h"

char** MappingToSet(char * nomfichier)
{
    FILE* f;  
    int i=0;
    char **noms=calloc(1,sizeof(char*));
    char *tmp=malloc(30*sizeof(char));
    f=fopen(nomfichier,"r"); 
    while(!feof(f))
    {
            fscanf(f,"%s ",tmp);
            noms[i]=calloc(strlen(tmp),sizeof(char));
            strcpy(noms[i],tmp);
            i++;
            noms=realloc(noms,(i+1)*sizeof(char*));
    }
    fclose(f); 
    noms[i]=NULL;
    return noms;  
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
int	max(int a,int b)
{
	if (a > b)
	return (a);
	else
	return (b);
}
char** purge(char* nomfichier)
{
    int c,k=1,b;
    int j,i,dbl;
    float pluslong,g;
    char  **res=malloc(sizeof(char*));
    char **noms;  
    FILE *f;
    
    noms=MappingToSet(nomfichier);
    res[0]=malloc(strlen(noms[0])*sizeof(char));
    strcpy(res[0],noms[0]);
    i=1;
            while(noms[i])
            {
                for(j=i-1;j>=0;j--) 
                {
                    dbl=0;
                     pluslong=(float)(max(strlen(noms[i]),strlen(noms[j])));
                     g=(1-(Leven(noms[i],noms[j])/pluslong));
                    if (g>=0.8) 
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
