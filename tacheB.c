#include "tacheB.h"
#include "alignement.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Retourne la distance d'edition de deux mots
int DIST_1(char *x, char *y, int **T) {

  int n = strlen(x);
  int m = strlen(y);
  T[0][0] = 0;

  for (int i = 0; i <= n;
       i++) { // initialisation du tableau pour taille de longueur x
    T[i][0] = i * 2;
  }
  for (int j = 0; j <= m;
       j++) { // initialisation du tableau pour taille de longueur y
    T[0][j] = j * 2;
  }

  for (int i = 1; i <= n; i++) {   // parcours de n
    for (int j = 1; j <= m; j++) { // parcours de m
      int m1 = T[i - 1][j - 1] + csub(x[i - 1], y[j - 1]);
      int m2 = T[i - 1][j] + cdel();
      int m3 = T[i][j - 1] + cins();
      T[i][j] = min(m1, m2, m3); // recupère le minumum cout des 3 cas
    }
  }

  return T[n][m]; // retourne le cout minimum de l'alignement
}

// Retourne une alignement minimal de deux mots
Alignement *SOL_1(char *x, char *y, int **T) {

  int i = strlen(x);
  int j = strlen(y);
  // Allocation de l'alignemnt de retour
  Alignement *res = (Alignement *)malloc(sizeof(Alignement));
  char gap = '-';
  int dist;
  char tmp;
  char tmpp;
  res->cout = T[i][j];

  // parcours du tableau des distances d'edition en partant de la fin
  while (i > 0 && j > 0) {

    dist = T[i][j];  // //le cout de la distance d edition courante
    tmp = x[i - 1];  // caractere x
    tmpp = y[j - 1]; // caractere y

    if ((i > 0) &&
        dist == T[i - 1][j] +
                    cdel()) { // si le cout optimal provient d une supression
      ajout(&res, tmp, gap);
      i--;
    } else if ((j > 0) &&
               dist ==
                   T[i][j - 1] +
                       cins()) { // si le cout optimal provient d une insertion
      ajout(&res, gap, tmpp);
      j--;
    } else { // si le cout optimal provient d'une substitution
      ajout(&res, tmp, tmpp);
      i = i - 1;
      j = j - 1;
    }
  }

  // complete l'alignement x
  while (i > 0) {
    tmp = x[i - 1];

    ajout(&res, tmp, gap);
    i--;
  }
  // complete l'alignement de y
  while (j > 0) {
    tmpp = y[j - 1];
    ajout(&res, gap, tmpp);
    j--;
  }

  return res;
}

// Réalise le cout et l'alignement optimal
Alignement *PROG_DYN(char *x, char *y) {
  // creation du tableau de distance d'edition
  int **G = (int **)malloc(sizeof(int *) * (strlen(x) + 1));

  for (int i = 0; i < strlen(x) + 1; i++) {
    G[i] = (int *)malloc(sizeof(int) * (strlen(y) + 1));
  }
  int ress = DIST_1(x, y, G);
  if (ress < 0) // suppression warning
    printf("erreur \n");
  Alignement *a = SOL_1(x, y, G);
  // on libere le tableau qu on a allouer
  for (int i = 0; i < strlen(x) + 1; i++) {
    free(G[i]);
  }
  free(G);
  return a;
}
