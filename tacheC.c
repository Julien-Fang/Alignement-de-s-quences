#include "tacheA.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Retour le cout minimal de deux mots avec une meilleure complexité
int DIST_2(char *x, char *y) {
  int n = strlen(x);
  int m = strlen(y);
  int T[2][m + 1];
  for (int j = 0; j <= m; j++) {
    T[1][j] = j * cins();
  }

  for (int i = 1; i <= n; i++) {
    T[0][0] = i * cdel();
    for (int j = 1; j <= m; j++) {
      T[0][j] = min(T[1][j] + cins(), T[0][j - 1] + cdel(),
                    T[1][j - 1] + csub(x[i - 1], y[j - 1]));
    }
    for (int z = 0; z <= m; z++) {
      T[1][z] = T[0][z];
    }
  }

  return T[1][m];
}