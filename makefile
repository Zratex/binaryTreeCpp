a.out : main.o arbre.o noeud.o variables.o
	g++ -std=gnu++11 main.o arbre.o noeud.o variables.o

main.o: main.cc variables.o
	g++ -std=gnu++11 -c main.cc

noeud.o: noeud.h noeud.cc
	g++ -std=gnu++11 -c noeud.cc

arbre.o: arbre.h arbre.cc variables.cc
	g++ -std=gnu++11 -c arbre.cc

variables.o: variables.h variables.cc
	g++ -std=gnu++11 -c variables.cc