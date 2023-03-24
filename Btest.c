#include "alignement.h"
#include "lire_fic.h"
#include "tacheA.h"
#include "tacheB.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  srand(time(NULL));
  struct dirent *dir;
  DIR *d = opendir("algo");
  FILE *f = fopen("temps_prog_dyn.txt", "w");
  char path[1024];
  int x;
  double z = 0.0;

  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {

        strcpy(path, "./algo/");
        strcat(path, dir->d_name);
        printf("%s\n ", path);
        x = taille_x(path);
        if (x < 50000) { // on limite la taille de x pour eviter les crash
          z = time_prog_dyn(path);
          fprintf(f, "x : %d temps : %lf\n", x, z);
          printf("temps : %lf | chemin :%s\n ", z, path);

          if (z >= 600) { // si l execution prend plus de 10m on arrete
            break;
          }
        }
      }
    }

    closedir(d);
    fclose(f);
  }

  return 0;
}