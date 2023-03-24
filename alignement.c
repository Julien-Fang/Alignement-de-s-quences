#include "alignement.h"
#include "tacheC.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Liste *creer(char c) {
  Liste *l = (Liste *)malloc(sizeof(Liste));
  if (l == NULL)
    return NULL;
  // on associe la lettre au caractere c
  l->lettre = c;
  // on initialise prec et suiv a null
  l->prec = NULL;
  l->suiv = NULL;

  return l;
}

Alignement *creer_ali() {
  Alignement *res = (Alignement *)malloc(sizeof(Alignement));
  res->cout = 0;
  res->taille = 0;
  return res;
}

void ajout(Alignement **a, char x1, char y1) {
  Liste *l1 = creer(x1);
  Liste *l2 = creer(y1);
  (*a)->cout = csub(x1, y1);
  l1->suiv = (*a)->x;
  (*a)->x = l1;
  l2->suiv = (*a)->y;
  (*a)->y = l2;
}

void ajout_x(Alignement **a, char x) {
  Liste *l1 = creer(x);
  l1->suiv = (*a)->x;
  (*a)->x = l1;
}

void ajout_y(Alignement **a, char y) {

  Liste *l2 = creer(y);
  l2->suiv = (*a)->y;
  (*a)->y = l2;
}

void ajout_chaine(Alignement **a, char *x, char *y) {
  // on ajoute la chaine x
  for (int i = strlen(x) - 1; i >= 0; i--) {
    char tmp = x[i];
    ajout_x(a, tmp);
  }
  // on ajotue la chaine y
  for (int i = strlen(y) - 1; i >= 0; i--) {
    char tmp = y[i];
    ajout_y(a, tmp);
  }
}

void ajout_chaine_y(Alignement **a, char *y) {
  // on ajoute que la chaine y
  for (int i = strlen(y) - 1; i >= 0; i--) {
    char tmp = y[i];
    ajout_y(a, tmp);
  }
}

void ajout_chaine_x(Alignement **a, char *x1) {
  // on ajoute que la chaine x
  for (int i = strlen(x1) - 1; i >= 0; i--) {
    char tmp = x1[i];
    ajout_x(a, tmp);
  }
}
// Pour retirer en tete un la lettre d un alignement
void retirerEntete(Alignement **a) {
  Liste *l1 = (*a)->x;
  Liste *l2 = (*a)->y;
  (*a)->x = (*a)->x->suiv;
  l1->suiv = NULL;

  (*a)->y = (*a)->y->suiv;
  l2->suiv = NULL;
  free(l1);
  free(l2);
}

void afficher_ali(Alignement *ali) {
  printf("Affichage alignement : \n");
  Liste *tmp = ali->x;

  printf("le mot x : ");
  while (tmp != NULL) {
    printf("%c ", tmp->lettre);
    tmp = tmp->suiv;
  }
  printf("\n");

  Liste *tmp2 = ali->y;
  printf("le mot y : ");
  while (tmp2 != NULL) {
    printf("%c ", tmp2->lettre);
    tmp2 = tmp2->suiv;
  }
}
// Renvoie la liste x sous forme de chaine de caractere
char *chaine_x(Alignement *ali) {
  Liste *tmp1 = ali->x;
  char *res = malloc(sizeof(char) * ((ali->taille) * 2 + 20));
  strcat(res, "");
  char tmp2[2];
  // tant que x n est pas null
  while (tmp1 != NULL) {
    tmp2[0] = tmp1->lettre;
    strcat(res, tmp2);
    tmp1 = tmp1->suiv;
  }

  return res;
}

// Renvoie la liste y sous forme de chaine de caractere
char *chaine_y(Alignement *ali) {
  Liste *tmpl = ali->y;

  char *res = malloc(sizeof(char) * ((ali->taille) * 2 + 20));

  strcat(res, "");

  char tmp[2];
  // tant que y n est pas null
  while (tmpl != NULL) {
    tmp[0] = tmpl->lettre;
    strcat(res, tmp);
    tmpl = tmpl->suiv;
  }

  return res;
}
// Fonction pour liberer la memoire d un alignement
void free_ali(Alignement *a) {
  Liste *tmp = NULL;
  // tant que la liste x n est pas null
  while ((a->x) != NULL) {
    tmp = a->x->suiv;
    free(a->x);
    a->x = tmp;
  }
  while ((a->y) != NULL) {
    tmp = a->y->suiv;
    free(a->y);
    a->y = tmp;
  }
}

Alignement *fusion(Alignement *a1, Alignement *a2) {
  Alignement *res = creer_ali();
  // on ajoute la chaine de x a res
  ajout_chaine_x(&res, strcat(chaine_x(a1), chaine_x(a2)));
  // on ajoute la chaine de y a res
  ajout_chaine_y(&res, strcat(chaine_y(a1), chaine_y(a2)));
  // on met a jour le cout
  res->cout = a1->cout + a2->cout;
  // on met a jour la taille
  res->taille = a1->taille + a2->taille;
  return res;
}