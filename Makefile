all : main

main: main.o Panneau.o Batterie.o Vehicule.o Compteur.o simulation.o
	g++ main.o Panneau.o Batterie.o Vehicule.o Compteur.o simulation.o -o main
	
simulation.o: simulation.cpp
	g++ -c simulation.cpp

main.o: main.cpp 
	g++ -c main.cpp

Panneau.o : Panneau.cpp
	g++ -c Panneau.cpp

Batterie.o : Batterie.cpp
	g++ -c Batterie.cpp
	
Vehicule.o : Vehicule.cpp
	g++ -c Vehicule.cpp

Compteur.o : Compteur.cpp
	g++ -c Compteur.cpp

clean:
	rm main *.o 