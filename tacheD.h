#ifndef TACHED_H
#define TACHED_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tacheA.h"
#include "alignement.h"

char *mot_gaps(int k);
int coupure(char *x, char *y);
Alignement *align_lettre_mot(char *x, char *y);
Alignement *SOL_2(char *x, char *y);
#endif