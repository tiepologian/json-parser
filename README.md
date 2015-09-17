# json-parser
A C++ project that demonstrates importing and analyzing a JSON document

#### Libraries:
* rapidjson (included)

#### Requirements:
* C++11 compatible compiler

#### Installation & Usage:
```bash
make
cd dist/
./jsonParser
```

The program will import and analyze a JSON file containing 30,000 records (+180,000 lines).
Each record contains these fiels: name, surname, email and age. The program will calculate the most common name and the average age.

This software has been optimized for speed: importing and analyzing 30,000 JSON records takes about 35ms on an average 64-bit CPU.
