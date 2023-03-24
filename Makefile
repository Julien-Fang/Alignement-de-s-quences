PROGRAMS = Atest Btest Ctest Dtest tacheA.o tacheB.o tacheC.o tacheD.o all_test temps_sol2.txt temps_dist2.txt temps_dist1.txt temps_dist_naif.txt temps_prog_dyn.txt

all : Atest Btest Ctest Dtest all_test

Atest : Atest.o tacheA.o
	gcc -o Atest Atest.o tacheA.o

Btest : Btest.o tacheB.o alignement.o tacheA.o lire_fic.o tacheC.o tacheD.o
	gcc -o Btest Btest.o tacheB.o alignement.o tacheA.o lire_fic.o tacheC.o tacheD.o

Ctest : Ctest.o tacheC.o tacheA.o lire_fic.o alignement.o tacheD.o tacheB.o
	gcc -o Ctest Ctest.o tacheC.o tacheA.o lire_fic.o alignement.o tacheD.o tacheB.o

Dtest : Dtest.o tacheC.o tacheA.o tacheD.o alignement.o tacheB.o lire_fic.o
	gcc -o Dtest Dtest.o tacheD.o tacheA.o alignement.o tacheC.o tacheB.o lire_fic.o

all_test : all_test.o tacheC.o tacheA.o tacheD.o alignement.o tacheB.o lire_fic.o
	gcc -o all_test all_test.o tacheD.o tacheA.o alignement.o tacheC.o tacheB.o lire_fic.o


Atest.o : Atest.c tacheA.h
	gcc -Wall -c Atest.c

Btest.o : Btest.c tacheB.h alignement.h tacheA.h
	gcc -Wall -c Btest.c 

Ctest.o : Ctest.c tacheC.h tacheB.h tacheA.h
	gcc -Wall -c Ctest.c 

Dtest.o : Dtest.c tacheC.h tacheB.h tacheA.h tacheD.h
	gcc -Wall -c Dtest.c 

all_test.o : all_test.c tacheC.h tacheB.h tacheA.h tacheD.h
	gcc -Wall -c all_test.c 

lire_fic.o : lire_fic.c tacheA.h lire_fic.h alignement.h tacheB.h tacheC.h tacheD.h
	gcc -Wall -c lire_fic.c

alignement.o : alignement.c tacheA.h alignement.h tacheC.h tacheB.h tacheC.h
	gcc -Wall -c alignement.c

tacheA.o : tacheA.c tacheA.h
	gcc -Wall -c tacheA.c

tacheB.o : tacheB.c tacheB.h alignement.h tacheA.h alignement.h
	gcc -Wall -c tacheB.c 

tacheC.o : tacheC.c tacheA.h tacheB.h tacheC.h alignement.h
	gcc -Wall -c tacheC.c

tacheD.o : tacheD.c tacheD.h tacheA.h tacheB.h tacheC.h alignement.h
	gcc -Wall -c tacheD.c

clean :
	rm -f *.o $(PROGRAMS)