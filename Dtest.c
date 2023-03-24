#include "lire_fic.h"
#include "tacheB.h"
#include "tacheC.h"
#include "tacheD.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  srand(time(NULL));
  struct dirent *dir;
  DIR *d = opendir("algo");
  char path[1024];
  int x = 0;
  FILE *f = fopen("temps_sol2.txt", "w");
  if (d) {
    while ((dir = readdir(d)) != NULL) {
      if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0) {
        strcpy(path, "./algo/");
        strcat(path, dir->d_name);
        printf("path : %s \n", path);
        double z = time_sol2(path);
        x = taille_x(path);
        fprintf(f, "x : %d temps : %lf\n", x, z);
        printf("temps : %lf  | chemin : %s\n", z, path);
        if (z >= 600) // si l execution prend plus de 10m on arrete
          break;
      }
    }
  }
  fclose(f);
  closedir(d);

  return 0;
}