#include "tacheA.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calcul_time(char *fic) {

  FILE *f = fopen(fic, "r");
  if (f == NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier");
    return 0;
  }
  int n = 0;
  int m = 0;
  if (fscanf(f, "%d \n", &n) == 0)
    return 0;
  if (fscanf(f, "%d \n", &m) == 0)
    return 0;
  char *x = (char *)malloc(sizeof(char) * (2 * n + 1));
  for (int i = 0; i < n; i++) {
    if (fscanf(f, "%s \n", &x[i]) == 0)
      return 0;
  }

  char *y = (char *)malloc(sizeof(char) * (2 * m + 1));
  for (int i = 0; i <= m; i++) {
    if (fscanf(f, "%s \n", &y[i]) == 0)
      return 0;
  }

  clock_t temps_i1;
  clock_t temps_f1;
  double temps_cpu1;

  temps_i1 = clock();
  int dist = DIST_NAIF(x, y);
  temps_f1 = clock();

  temps_cpu1 = ((double)(temps_f1 - temps_i1)) / CLOCKS_PER_SEC;
  free(x);
  free(y);
  if (dist < 0)
    printf("erreur\n");
  return temps_cpu1;
}

int main() {

  srand(time(NULL));
  struct dirent *dir;
  DIR *d = opendir("algo");
  FILE *f = fopen("temps_dist_naif.txt", "w");
  char path[1024];

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {

        strcpy(path, "./algo/");
        strcat(path, dir->d_name);

        double tmp = calcul_time(path);

        printf("%lf %s\n ", tmp, path);
        if (tmp >= 60) { // si le temps depasse 1 minute on arrete

          break;
        }
      }
    }
    closedir(d);
    fclose(f);
  }

  return 0;
}