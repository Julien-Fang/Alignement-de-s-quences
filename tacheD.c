#include "alignement.h"
#include "tacheA.h"
#include "tacheB.h"
#include "tacheC.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Fonction qui renvoie une coupure de x et y
int coupure(char *x, char *y) {
  int n = strlen(x);
  int m = strlen(y);
  // tableau des distances d'edition
  int T[2][m + 1];
  // tableau des coupures
  int I[2][m + 1];
  int id = (n) / 2;
  I[0][0] = 0;

  // on remplie la colonne de y
  for (int j = 0; j < m + 1; j++) {
    T[1][j] = j * cins();
    I[1][j] = j;
  }
  // double boucle for pour créer les 2 tableaux
  for (int i = 1; i < n + 1; i++) {
    T[0][0] = i * cdel();
    for (int j = 1; j < m + 1; j++) {
      // on prend le minimum entre la supppresion l'insertion et la subsitution
      T[0][j] = min(T[1][j] + cins(), T[0][j - 1] + cdel(),
                    T[1][j - 1] + csub(x[i - 1], y[j - 1]));
      // si i est superieur a id on peut commencer a remplir notre tableau de
      // coupure
      if (i > id) {
        if (T[0][j] == T[0][j - 1] + cdel()) {
          I[0][j] = I[0][j - 1];
        } else if (T[0][j] == T[1][j] + cins()) {
          I[0][j] = I[1][j];
        } else if (T[0][j] == T[1][j - 1] + csub(x[i - 1], y[j - 1])) {
          I[0][j] = I[1][j - 1];
        }
      }
    }
    // T[i] = T[i-1]
    for (int z = 0; z < m + 1; z++) {
      T[1][z] = T[0][z];
      if (i > id) // I[i] = I[i-1] si i est superieur a id
        I[1][z] = I[0][z];
    }
  }
  return I[0][m];
}

// Fonction qui renvoie k gaps
char *mot_gaps(int k) {
  char *mot = (char *)malloc(sizeof(char) * k);
  while (k > 0) {
    strcat(mot, "-");
    k--;
  }
  return mot;
}
// Fonction qui renvoie un alignement de mot pour un caractere x et une chaine
// de caractere y
Alignement *align_lettre_mot(char *x, char *y) {
  Alignement *res = creer_ali();
  int m = strlen(y);
  int indice = 0;
  int mi = 100; // cout maximal
  // on parcourt les differents indices de y
  for (int i = 0; i < m; i++) {
    if (csub(x[0], y[i]) <
        mi) { // si on trouve un meilleur cout de substitution qu'avant on garde
              // l indice de i et on met a jour le meilleur cout
      mi = csub(x[0], y[i]);
      indice = i;
    }
  }

  char *tmp = malloc(sizeof(char) * (strlen(y) + strlen(x) + 1));
  strcat(tmp, mot_gaps(indice)); // on ajoute indice gaps
  strcat(tmp, x);                // on ajoute x
  strcat(tmp,
         mot_gaps(m - indice - 1)); // on termine par ajouter les gaps manquants
  ajout_chaine(&res, tmp, y); // on ajoute la chaine de caractere dans noter
                              // liste doublement chainee res
  res->cout = DIST_2(
      x, y); // on attribut le cout de la distance d edition a notre alignement
  return res;
}

// Fonction qui renvoie l'alignement optimal pour x et y avec une methode
// diviser pour regner
Alignement *SOL_2(char *x, char *y) {

  int n = strlen(x);
  int m = strlen(y);

  Alignement *a1 = creer_ali();
  a1->taille = n + m;

  if (n > 0 && m == 0) {
    ajout_chaine(&a1, x, mot_gaps(n));

    return a1;
  }
  if (n == 1 && m > 1) {

    return align_lettre_mot(x, y);
  }
  if (n == 1 && m == 1) {

    ajout_chaine(&a1, x, y);

    return a1;
  }
  // on recupere la coupure de x et y
  int j = coupure(x, y);
  // l indice ou on divise i par 2
  int i = (n) / 2;
  // x[0..i]
  char *x2 = malloc(sizeof(char) * (n + 1));
  char t[2];

  for (int z = 0; z < i; z++) {
    t[0] = x[z];
    strcat(x2, t);
  }
  // y [0..j]
  char *y2 = (char *)malloc(sizeof(char) * (m + 1));
  for (int z = 0; z < j; z++) {
    t[0] = y[z];
    strcat(y2, t);
  }
  // on cree le deuxieme alignement
  Alignement *a2 = creer_ali();
  a2->taille = n + m;
  // on attribut le cout a chaque alignement

  a1 = SOL_2(x2, y2);
  a2 = SOL_2(x + i, y + j);
  // on fusionne les 2 alignements cree au prealable

  return fusion(a1, a2);
}
