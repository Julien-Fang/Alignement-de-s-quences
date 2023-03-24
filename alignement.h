#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tacheC.h"
typedef struct liste {
  char lettre;
  struct liste *prec;
  struct liste *suiv; // suivant

} Liste;



typedef struct alignement {
  Liste *x;
  Liste *y;
  int cout;
int taille;
} Alignement;

Liste *creer(char c);
void ajout(Alignement **a, char x1, char y1);
Alignement *creer_ali();
void afficher_ali(Alignement *l);
void ajout_chaine(Alignement **a, char *x1, char *y1);
void ajout_x(Alignement **a, char x1);
void ajout_y(Alignement **a, char y1);
void retirerEntete(Alignement **a);
char *chaine_x(Alignement *ali);
char *chaine_y(Alignement *ali);
void ajout_chaine_y(Alignement **a,  char *y1);
void ajout_chaine_x(Alignement **a,  char *x1);
void free_liste(Liste **l);
void free_ali(Alignement *a);
Alignement * fusion(Alignement *a1,Alignement *a2);
#endif