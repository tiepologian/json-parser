all:
	g++ -std=c++11 -O4 -I src/rapidjson/ src/JsonParser.cpp src/main.cpp -o dist/jsonParser

clean:
	rm dist/jsonParser
