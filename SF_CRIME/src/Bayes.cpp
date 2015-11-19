/*
 * Bayes.cpp
 *
 *  Created on: 17/11/2015
 *      Author: josefina
 */

#include "Bayes.h"

using namespace std;

Bayes::Bayes() {

}

void Bayes::train(map<string,float> frecuenciaDeCrimenes,map<string,float> probabilidadesDeCrimenes,
		map<string,int> frecuenciaDeCrimenesPorDistrito,map<string,float> *probabilidadesPorDias,
		map<string,float> *probabilidadesPorDistrito,map<string,float> *probabilidadesPorHoras){

	this->frecuenciaDeCrimenes = frecuenciaDeCrimenes;
	this->probabilidadesDeCrimenes = probabilidadesDeCrimenes;
	this->frecuenciaDeCrimenesPorDistrito = frecuenciaDeCrimenesPorDistrito;
	this->probabilidadesPorDias = probabilidadesPorDias;
	this->probabilidadesPorDistrito = probabilidadesPorDistrito;
	this->probabilidadesPorHoras = probabilidadesPorHoras;

	cout << "Se entrenó correctamente el clasificador" << endl;
}

void Bayes::predecir(char* nameFile){

	/*struct Row {
			string hora;
			string diaDeLaSemana;
			string distrito;
	} row;*/

	string line, csvItem;
	ifstream myfile(nameFile);
	int nroItem = 0;
	Row row;

	ofstream probabilidades("probabilidades.txt");

	if (myfile.is_open()) {

		while (getline(myfile,line)) {
			nroItem = 0;
			istringstream myline(line);

			while(getline(myline, csvItem, ',')) {
				if (nroItem == 1) row.hora = csvItem; else
					if (nroItem == 2) row.diaDeLaSemana = csvItem; else
						if (nroItem == 3) row.distrito = csvItem;

				nroItem++;
			}

			this->predecirRow(row);

			cout << row.hora + " " + row.diaDeLaSemana + " " + row.distrito << endl;
		}
	}

	myfile.close();
	probabilidades.close();

}

void Bayes::predecirRow(Row row){

	int cantidadDeCrimenes = 0;
	float probabilidades[39];
	float probabilidadPriori,probabilidadPosteriori;

	/*probabilidadPriori = calcularProbabilidadPriori(frecuenciaDeCrimenes,probabilidadesDeCrimenes,
				frecuenciaDeCrimenesPorDistrito,probabilidadesPorDias,probabilidadesPorDistrito,probabilidadesPorHoras);

	while (cantidadDeCrimenes < 39){

		probabilidadPosteriori = calcularProbabilidadPosteriori(frecuenciaDeCrimenes,probabilidadesDeCrimenes,
				frecuenciaDeCrimenesPorDistrito,probabilidadesPorDias,probabilidadesPorDistrito,probabilidadesPorHoras);
		cantidadDeCrimenes++;
	}*/

}

float calcularProbabilidadPriori(map<string,float> frecuenciaDeCrimenes,map<string,float> probabilidadesDeCrimenes,
			map<string,int> frecuenciaDeCrimenesPorDistrito,map<string,float> *probabilidadesPorDias,
			map<string,float> *probabilidadesPorDistrito,map<string,float> *probabilidadesPorHoras){
	return 0;
}

float calcularProbabilidadPosteriori(map<string,float> frecuenciaDeCrimenes,map<string,float> probabilidadesDeCrimenes,
			map<string,int> frecuenciaDeCrimenesPorDistrito,map<string,float> *probabilidadesPorDias,
			map<string,float> *probabilidadesPorDistrito,map<string,float> *probabilidadesPorHoras){

	return 0;
}

Bayes::~Bayes() {

}
