#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct maillon
{
	char *val;
	struct maillon *suiv;
} maillon;

int calculhach(char *mot,int taille);
int nbrlignes(char* fichier);
void ajoutMot(maillon **table, char *mot, int taille);
char** lire(char * nomfichier);
maillon **MappingToHashTable(char * fichier,int taille);
void afficher(maillon **t,int taille);
int Min(int a, int b);
int notegal(char a , char b);
int leven(char *x,char *y)   ;
int	max(int a,int b);
int		vide(char *t);
char** HashTolist(maillon** hashTab,int n,int N); 
char** purge(char *fichier,int n);

#endif
