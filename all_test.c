#include "tacheB.h"
#include "tacheC.h"
#include "tacheD.h"
#include <dirent.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {

  printf("Création d'un alignement de longueur 1\n");
  Alignement *a = (Alignement *)malloc(sizeof(Alignement));
  ajout(&a, 'A', '-');
  afficher_ali(a);

  printf("\nAjouter une chaine pour la chaine x et y dans l'alignement\n");
  ajout_chaine(&a, "A--", "TGG");
  afficher_ali(a);

  printf(
      "\nUtilisation de align_lettre_mot sur une même chaine du précédent\n");
  Alignement *ali = align_lettre_mot("A", "CACTA");
  printf("afficher\n");
  afficher_ali(ali);

  printf("\nCréation d'un second alignement\n");
  printf("\nUtilisation de SOL_2\n");
  Alignement *a2 = SOL_2("AAATTC", "CACTA");
  afficher_ali(a2);

  printf("\nFusion de nos 2 alignements\n");
  Alignement *a3 = fusion(a, a2);
  afficher_ali(a3);

  printf("\ncoupure de l'exemple de l enonce :\n");
  printf("pour x : ATTGTA et y : ATCTTA, coupure de : %d \n",
         coupure("ATTGTA", "ATCTTA"));

  printf("\nUtilisation de PROG_DYN pour connaitre le meilleur alignement et "
         "cout\n");
  Alignement *prog = PROG_DYN("AAATTC", "CACTA");
  afficher_ali(prog);
  int z = DIST_NAIF("AAATTC", "CACTA");
  printf("Le coût est de z %d\n", z);

  printf("\nUtilisation de DIST_2 pour avoir le meilleur cout et complexité, "
         "en reprenant la même chaine du précédent test\n");
  int i = DIST_2("AAATTC", "CACTA");
  printf("Le coût est de %d\n", i);

  /*
    char *x="AATCGATGCAGTCGTACGTGCGATCGATCGTGACGATCGCATGGCATGTACGACTGGATCGT";
    char *y="ATTGC";
    printf("Bonus question 30 ! avec x de longueur : %ld et y :
    %ld\n",strlen(x),strlen(y)); if(DIST_2(x,y)==(strlen(x)-strlen(y))*cdel())
    printf("On obtient bien le resultat souhaité lorsque |x|>>|y| on a
    dist(x,y)=(|x|-|y|).cdel\n");
  */

  return 0;
}