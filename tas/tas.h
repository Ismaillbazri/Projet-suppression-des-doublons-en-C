#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef TAS_H
#define TAS_H 

int Min(int a, int b);
int notegal(char a , char b);
int Leven(char *x,char *y)   ;
int nbre(char ** t);
void permuter(char *s,char *q);
void Ajout(char *s, char **t);
char *  ExtraireMin(char **t) ;
char **LireToTas(char *nomfichier);
char **MappingToTable(char *nomfichier);
char** purge(char* nomfichier);
 
 
 
 #endif
 


