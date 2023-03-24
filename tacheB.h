#ifndef TACHEB_H
#define TACHEB_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tacheA.h"
#include "alignement.h"


int DIST_1(char *x, char *y, int **T);
Alignement *SOL_1(char *x, char *y, int **T);
Alignement* PROG_DYN(char *x, char *y);

#endif