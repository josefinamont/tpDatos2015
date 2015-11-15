/*
 * CVSReader.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: joha
 */

#include "CVSReader.h"
#include <map>

using namespace std;

CVSReader::CVSReader() {

	this->colums = 0;
	this->rows = 0;
}

void CVSReader::open(char *nameFile){

	string line, csvItem;
	ifstream myfile(nameFile);
	int nroItem = 0, denominador = 0;
	map<string,float> probabilidades;

	if (myfile.is_open()) {

		while (getline(myfile,line)) {
			nroItem = 0;
			denominador++;
			istringstream myline(line);
			while(getline(myline, csvItem, ',')) {
				if (nroItem == 2){
					if (probabilidades.count(csvItem)<1) {
						probabilidades[csvItem] = 1;
					} else probabilidades[csvItem] += 1;
				}
				nroItem++;
			}
		}
		myfile.close();
	}

	//imprime el pseudo diccionario
	map<string, float>::iterator iter = probabilidades.begin();
	while (iter != probabilidades.end() ){
		iter->second = (iter->second)/denominador;
	    cout << iter->first + " " <<  iter->second << endl;
	    iter++;
	}
	cout << denominador << endl;



}

void CVSReader::readLine(string line){

}

CVSReader::~CVSReader() {

}

