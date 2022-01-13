#!/usr/bin/env bash

g++ -c src/centre_radio.cpp -o src/centre_radio.o && g++ -c src/personne.cpp -o src/personne.o && g++ -c src/radiographie.cpp -o src/radiographie.o && g++ -o main src/main.cpp src/centre_radio.o src/personne.o src/radiographie.o #génération des différents fichiers.o et de l'executable

if [ $? -eq 0 ]; then #si la compilation a été effectuée avec le code d'erreur 0
	echo "[SUCCESS] Compilation effectuée avec succès."
fi

echo "REACHED END OF \"$0\""


