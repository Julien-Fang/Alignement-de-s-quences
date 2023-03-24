#include "alignement.h"
#include "tacheB.h"
#include "tacheC.h"
#include "tacheD.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int taille_x(char *fic) {
  FILE *f = fopen(fic, "r");
  if (f == NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier1");
    return 0;
  }

  char buffer[256];
  int n = 0;
  if (fgets(buffer, 256, f) == NULL)
    return 0;
  if (sscanf(buffer, "%d", &n) == 1) {
    fclose(f);
    return n;
  }

  fclose(f);
  return n;
}

double time_prog_dyn(char *fic) {

  FILE *f = fopen(fic, "r");
  if (f == NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier2");
    return 0;
  }
  int n = 0;
  int m = 0;
  if (fscanf(f, "%d \n", &n) == 0)
    printf("Erreur\n");
  if (fscanf(f, "%d \n", &m) == 0)
    printf("Erreur\n");
  char *x = (char *)malloc(sizeof(char) * (2 * n + 1));
  for (int i = 0; i < n; i++) {
    if (fscanf(f, "%s \n", &x[i]) == 0)
      printf("Erreur\n");
  }

  char *y = (char *)malloc(sizeof(char) * (2 * m + 1));
  for (int i = 0; i <= m; i++) {
    if (fscanf(f, "%s \n", &y[i]) == 0)
      printf("Erreur\n");
  }

  clock_t temps_i1;
  clock_t temps_f1;
  double temps_cpu1;

  temps_i1 = clock();
  Alignement *a = PROG_DYN(x, y);
  temps_f1 = clock();
  temps_cpu1 = ((double)(temps_f1 - temps_i1)) / CLOCKS_PER_SEC;
  free(x);
  free(y);

  fclose(f);
  if (a==NULL) printf("erreur\n");
  return temps_cpu1;
}

double time_dist2(char *fic) {

  FILE *f = fopen(fic, "r");
  if (f == NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier");
    return 0;
  }

  int n = 0;
  int m = 0;
  if (fscanf(f, "%d \n", &n) == 0)
    printf("Erreur\n");
  if (fscanf(f, "%d \n", &m) == 0)
    printf("Erreur\n");
  char *x = (char *)malloc(sizeof(char) * (2 * n + 1));
  for (int i = 0; i < n; i++) {
    if (fscanf(f, "%s \n", &x[i]) == 0)// suppression warning
      printf("Erreur\n");
  }

  char *y = (char *)malloc(sizeof(char) * (2 * m + 1));
  for (int i = 0; i <= m; i++) {
    if (fscanf(f, "%s \n", &y[i]) == 0)// suppression warning
      printf("Erreur\n"); 
  }

  clock_t temps_i1;
  clock_t temps_f1;
  double temps_cpu1;
  temps_i1 = clock();
  int res= DIST_2(x, y);
  temps_f1 = clock();
  temps_cpu1 = ((double)(temps_f1 - temps_i1)) / CLOCKS_PER_SEC;
  free(x);
  free(y);
  fclose(f);
  if (res<0) printf("erreur\n");
  return temps_cpu1;
}

double time_sol2(char *fic) {

  FILE *f = fopen(fic, "r");
  if (f == NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier");
    return 0;
  }
  int n = 0;
  int m = 0;
  if (fscanf(f, "%d \n", &n) == 0)
    printf("Erreur\n");
  if (fscanf(f, "%d \n", &m) == 0)
    printf("Erreur\n");
  char *x = (char *)malloc(sizeof(char) * (2 * n + 1));
  for (int i = 0; i < n; i++) {
    if (fscanf(f, "%s \n", &x[i]) == 0)
      printf("Erreur\n");
  }

  char *y = (char *)malloc(sizeof(char) * (2 * m + 1));
  for (int i = 0; i <= m; i++) {
    if (fscanf(f, "%s \n", &y[i]) == 0)
      printf("Erreur\n");
  }

  clock_t temps_i1;
  clock_t temps_f1;
  double temps_cpu1;
  temps_i1 = clock();

  Alignement *ali = SOL_2(x, y);
  temps_f1 = clock();
  temps_cpu1 = ((double)(temps_f1 - temps_i1)) / CLOCKS_PER_SEC;
  free(x);
  free(y);
  // free_ali(ali);
  fclose(f);
  if (ali==NULL) printf("erreur\n");
  return temps_cpu1;
}

double time_dist1(char *fic) {

  FILE *f = fopen(fic, "r");
  if (f == NULL) { // s'il y a probleme de fichier
    printf("Probleme ouverture fichier");
    return 0;
  }

  int n = 0;
  int m = 0;
  if (fscanf(f, "%d \n", &n) == 0)
    printf("Erreur\n");
  if (fscanf(f, "%d \n", &m) == 0)
    printf("Erreur\n");
  char *x = (char *)malloc(sizeof(char) * (2 * n + 1));
  for (int i = 0; i < n; i++) {
    if (fscanf(f, "%s \n", &x[i]) == 0)// suppression warning
      printf("Erreur\n");
  }

  char *y = (char *)malloc(sizeof(char) * (2 * m + 1));
  for (int i = 0; i <= m; i++) {
    if (fscanf(f, "%s \n", &y[i]) == 0)// suppression warning
      printf("Erreur\n");
  }
  int **G = (int **)malloc(sizeof(int *) * (strlen(x) + 1));

  for (int i = 0; i < strlen(x) + 1; i++) {
    G[i] = (int *)malloc(sizeof(int) * (strlen(y) + 1));
  }

  clock_t temps_i1;
  clock_t temps_f1;
  double temps_cpu1;
  temps_i1 = clock();
  int res = DIST_1(x, y, G);
  temps_f1 = clock();
  temps_cpu1 = ((double)(temps_f1 - temps_i1)) / CLOCKS_PER_SEC;
  free(x);
  free(y);

  for (int i = 0; i < strlen(x) + 1; i++) {
    free(G[i]);
  }
  free(G);
  fclose(f);
  if (res<0) printf("erreur\n");// suppression warning
  return temps_cpu1;
}
