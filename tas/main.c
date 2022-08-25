#include <stdio.h>
#include <stdlib.h>
#include <string.h>  
#include "tas.h" 

main()
{
	char **N=calloc(1,sizeof(char*)); 
    char *tmp=malloc(30*sizeof(char)); 
	int i=0,n; 
N=purge("mar.txt"); 
	while(N[i]) {
		puts(N[i]);
		i++; 
	} 

	
}
