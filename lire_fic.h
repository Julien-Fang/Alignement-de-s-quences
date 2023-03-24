#ifndef LIRE_FIC_H
#define LIRE_FIC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tacheB.h"
#include "tacheC.h"
#include "tacheD.h"

int taille_x(char *fic);
double time_prog_dyn(char *fic);
double time_dist2(char *fic);
double time_sol2(char *fic);
double time_dist1(char *fic);
#endif