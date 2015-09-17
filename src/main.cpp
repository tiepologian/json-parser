/*
 * main.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: Gianluca Tiepolo <tiepolo.gian@gmail.com>
 */

#include "JsonParser.h"

int main(int argc, char *argv[]) {
	// Leggiamo il file json
	FILE* fp = fopen("data.json", "rb");
	if(!fp) {
		// Se si verifica un errore durante la lettura del file, terminiamo il software
		std::cout << "ERROR OPENING FILE" << std::endl;
		// Quando il valore di return e' > 0 significa che c'e' un errore
		return 1;
	}

	// Creiamo un'istanza della nostra classe JsonParser e gli passiamo il file come parametro
	JsonParser* parser = new JsonParser(fp);
	// Chiamiamo la funzione load che costruisce l'oggetto JSON in memoria
	if(!parser->load()) {
		// Se si verifica un errore, usciamo
		return 1;
	}

	// Facciamo partire le analisi
	parser->analyze();

	// Stampiamo il numero di elementi utilizzati chiamando il metodo pubblico getNumElements() della nostra classe
	std::cout << "Read " << parser->getNumElements() << " records" << std::endl << std::endl;
	// Stampiamo il numero di elementi utilizzati chiamando i metodi pubblici della nostra classe
	std::cout << "The most common name is " << parser->getTopName().first << " with " << parser->getTopName().second << " occurencies" << std::endl;
	std::cout << "The average age is " << parser->getAverageAge() << std::endl;

	// Chiudiamo il file ed eliminiamo il parser visto che e' stato creato con new
	fclose(fp);
	delete parser;

	// Passando 0 come valore di return diciamo al sistema operativo che il software si e' chiuso correttamente
    return 0;
}
