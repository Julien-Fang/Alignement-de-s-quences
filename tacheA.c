#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Le coût d'une insertion
int cins() { return 2; }

// Le coût d'une suppression
int cdel() { return 2; }

// Le coût d'une substitution
int csub(char x, char y) {
  int csub = 4;
  if (((x == 'A' && y == 'T') || (x == 'T' && y == 'A')) ||
      ((x == 'G' && y == 'C') || (x == 'C' && y == 'G'))) {
    csub = 3;
  }
  if (x == y) {

    csub = 0;
  }
  return csub;
}

// Rentourne la valeur minimal entre trois entiers
int min(int a, int b, int c) {
  if (a <= b && a <= c) {
    return a;
  } else if (b <= a && b <= c) {
    return b;
  }

  return c;
}

// Retourne le coût d'un alignements possible de deux mots
int DIST_NAIF_REC(char *x, char *y, int i, int j, int c, int *dist) {

  if (i == strlen(x) && j == strlen(y)) {
    if (c < (*dist)) {
      *dist = c;
    }
  } else {
    if (i < strlen(x) && j < strlen(y)) {

      *dist = DIST_NAIF_REC(x, y, i + 1, j + 1, c + csub(x[i], y[j]), dist);
    }

    if (i < strlen(x)) {

      *dist = DIST_NAIF_REC(x, y, i + 1, j, c + cdel(), dist);
    }

    if (j < strlen(y)) {
      *dist = DIST_NAIF_REC(x, y, i, j + 1, c + cins(), dist);
    }
  }

  return *dist;
}

// Appelle la fonction DIST_NAIF_REC pour retourner le coût de l'alignement
int DIST_NAIF(char *x, char *y) {
  int i = 2147483647;
  return DIST_NAIF_REC(x, y, 0, 0, 0, &i);
}
