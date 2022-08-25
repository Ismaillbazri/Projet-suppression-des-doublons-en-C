#include"hash.h"

int main()
{
	int n,i=0;
	float pluslong;
	char** k;
	maillon **tab;
	char **l;
	printf("entrer taille:");
	scanf("%d",&n);
   //	k=purge("hash17.txt",n);
    tab=MappingToHashTable("hash17.txt",n);
    afficher(tab,n);
    //printf("%d",nbrlignes("hash17.txt"));
//    k=HashTolist(tab,n,nbrlignes("hash17.txt"));
//    for(i=0;k[i];i++)
//    {
//    	printf("\n%s",k[i]);
//	}
 return 0; 
}
