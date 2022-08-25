#include"naif.h"

 main()
{   int i=0;
     
    char **c;
      
     c=purge("noms17.txt") ; 
     for(i=0;c[i];i++) { 
    puts(c[i]);  
     }   
} 
