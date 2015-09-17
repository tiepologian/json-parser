/*
 * JsonParser.h
 *
 *  Created on: Sep 17, 2015
 *      Author: Gianluca Tiepolo <tiepolo.gian@gmail.com>
 */

#ifndef SRC_JSONPARSER_H_
#define SRC_JSONPARSER_H_

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "rapidjson/filereadstream.h"
#include "rapidjson/document.h"

/*
 *	Questa classe carica in memoria un file JSON ed esegue delle analisi
 */
class JsonParser {
public:
	JsonParser(FILE *);
	virtual ~JsonParser();
	// Usiamo un typedef per non dover scrivere ogni volta std::map<std::string,int>
	typedef std::map<std::string,int> WordCounter;
	bool load();
	int getNumElements();
	int getAverageAge();
	void analyze();
	std::pair<std::string,int> getTopName();
private:
	// Nota 'stilistica': si usa mettere un _ davanti alle variabili 'member', cioe' quelle private
	FILE *_fp;
	int _numElements;
	char *_readBuffer;
	bool _hasLoaded;
	std::pair<std::string,int>_topName;
	int _averageAge;
	rapidjson::Document _document;
};

#endif /* SRC_JSONPARSER_H_ */
