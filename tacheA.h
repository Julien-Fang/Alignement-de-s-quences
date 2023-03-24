#ifndef TACHEA_H
#define TACHEA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cins();
int cdel();
int csub(char x, char y);
int min(int a, int b, int c);
int DIST_NAIF_REC(char *x, char *y, int i, int j, int c, int *dist);
int DIST_NAIF(char *x, char *y);

#endif