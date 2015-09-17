/*
 * JsonParser.cpp
 *
 *  Created on: Sep 17, 2015
 *      Author: Gianluca Tiepolo <tiepolo.gian@gmail.com>
 */

#include "JsonParser.h"

using namespace rapidjson;

// Questa struct definisce il metodo di ordinamento usato dalla struttura dati verso la fine del file
struct sort_pred {
	bool operator()(const std::pair<std::string,int> &left, const std::pair<std::string,int> &right) {
		return left.second < right.second;
	}
};

/*
 * Costruttore - viene chiamato quando JsonParser viene creato
 */
JsonParser::JsonParser(FILE *fp) {
	// Creiamo un buffer in memoria per contenere il file
	_readBuffer = new char[65536]();
	this->_fp = fp;
	_hasLoaded = false;
	// !!!!!!! IMPORTANTISSIMO !!!!!!!
	// NON ASSUMERE MAI CHE UNA VARIABILE INT APPENA CREATA ABBIA VALORE 0
	// DEVI IMPOSTARLA TU A ZERO MANUALMENTE
	_numElements = 0;
	_averageAge = 0;
}

/*
 * Distruttore - viene chiamato quando JsonParser viene eliminato
 */
JsonParser::~JsonParser() {
	// Eliminiamo le variabili create con new() e impostiamo i puntatori a zero
	delete _readBuffer;
	_readBuffer = nullptr;
	_fp = nullptr;
}

/*
 * Questo metodo carica il file e crea un oggetto JSON in memoria
 */
bool JsonParser::load() {
	FileReadStream is(_fp, _readBuffer, sizeof(_readBuffer));
	if(_document.ParseStream(is).HasParseError()) {
		std::cout << "PARSE ERROR" << std::endl;
		return false;
	}
	_hasLoaded = true;
	return true;
}

/*
 * Questo metodo esegue le nostre due 'analisi'
 */
void JsonParser::analyze() {
	// Verifichiamo se e' gia' stato caricato il file JSON
	if(!_hasLoaded) std::exit(1);
	WordCounter names;

	// Questo ciclo analizza il documento JSON
	for (Value::ConstValueIterator itr = _document.Begin(); itr != _document.End(); ++itr) {
		Value::ConstMemberIterator itr2 = itr->FindMember("name");
		// Aggiungiamo il nome della persona alla nostra struttura dati 'map'
		names[itr2->value.GetString()]++;
		Value::ConstMemberIterator itr3 = itr->FindMember("age");
		// Aggiungiamo l'eta' della persona alla variabile che conterra' l'eta' media
		_averageAge += itr3->value.GetInt();
		// Incrementiamo il contatore che tiene traccia del numero totale di persone analizzate
		_numElements++;
	}

	// I nomi ed il numero di ripetizioni sono salvati in una STL Map, ma una Map non puo' essere ordinata
	// Pertanto, trasferiamo i dati in un STL vector
	std::vector< std::pair<std::string,int> > result(names.begin(), names.end());
	// Ordiniamo il vector usando la funzione sort_pred() definita in alto a questo file
	std::sort(result.begin(), result.end(), sort_pred());
	// Salviamo il nome ed il numero di ripetizioni nella variabile topName di tipo 'pair'
	_topName = std::make_pair(result.front().first, result.front().second);
}

/*
 * Questo metodo restituisce il numero di elementi utilizzati
 */
int JsonParser::getNumElements() {
	return _numElements;
}

/*
 * Questo metodo restituisce un 'pair' contenente nome e numero di ripetizioni del nome più comune
 */
std::pair<std::string,int> JsonParser::getTopName() {
	return _topName;
}

/*
 * Questo metodo restituisce l'eta' media
 */
int JsonParser::getAverageAge() {
	return _averageAge / getNumElements();
}
