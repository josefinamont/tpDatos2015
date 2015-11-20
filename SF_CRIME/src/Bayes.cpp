/*
 * Bayes.cpp
 *
 *  Created on: 17/11/2015
 *      Author: josefina
 */

#include "Bayes.h"

using namespace std;

Bayes::Bayes() {

	this->probabilidadesPorDias = 0;
	this->probabilidadesPorDistrito = 0;
	this->probabilidadesPorHoras = 0;

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

	string line, csvItem;
	ifstream myfile(nameFile);
	int nroItem = 0;
	Row row;

	ofstream probabilidades("probabilidades.csv");

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

			float* rowPredecido = this->predecirRow(row);

			for (int i = 0; i < 39; i++){
				probabilidades <<  rowPredecido[i];
				probabilidades << ",";
			}
			probabilidades << "\n";
		}
	}

	myfile.close();
	probabilidades.close();

}

int Bayes::calcularDistritoCorrespondiente(string distrito){

	if (distrito == "BAYVIEW") return 0; else
		if (distrito == "CENTRAL") return 1; else
			if (distrito == "INGLESIDE") return 2; else
				if (distrito == "MISSION") return 3; else
					if (distrito == "NORTHERN") return 4; else
						if (distrito == "PARK") return 5; else
							if (distrito == "RICHMOND") return 6; else
								if (distrito == "SOUTHERN") return 7; else
									if (distrito == "TARAVAL") return 8; else
										if (distrito == "TENDERLOIN") return 9; else
											cout << "Distrito no válido" << endl;
}

int Bayes::calcularDiaCorrespondiente(string dia){

	if (dia == "Monday") return 0; else
		if (dia == "Tuesday") return 1; else
			if (dia == "Wednesday") return 2; else
				if (dia == "Thursday") return 3; else
					if (dia == "Friday") return 4; else
						if (dia == "Saturday") return 5; else
							if (dia == "Sunday") return 6; else
								cout << "Día no válido" << endl;
}

float Bayes::calcularProbabilidadPriori(Row row){

	int cantidadDeCrimenes = 0;
	float probabilidadPriori,probabilidadPosteriori,resultado = 0;

	map<string,float>::iterator iter = frecuenciaDeCrimenes.begin();
	while ((iter != frecuenciaDeCrimenes.end()) && (cantidadDeCrimenes < 39)){
		resultado += this->calcularProbabilidadPosteriori(row,iter->first);
		iter++;
		cantidadDeCrimenes++;
	}

	return resultado;
}

float Bayes::calcularProbabilidadPosteriori(Row row,string nombreDelCrimen){

	double p1,p2,p3;

	int indiceDeHoras = atoi((row.hora).c_str());
	int indiceDeDias = calcularDiaCorrespondiente(row.diaDeLaSemana);
	int indiceDeDistritos = calcularDistritoCorrespondiente(row.distrito);

	p1 = (probabilidadesPorHoras[indiceDeHoras][nombreDelCrimen]);//de 0 a 23
	p2 = (probabilidadesPorDias[indiceDeDias][nombreDelCrimen]);//de 0 a 6
	p3 = (probabilidadesPorDistrito[indiceDeDistritos][nombreDelCrimen]);//de 0 a 9

	/*cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << "termina el row" << endl;*/

	return p1*p2*p3;

}

float Bayes::calcularProbabilidadDelRow(float probabilidadDeClase,float probabilidadPriori,float probabilidadPosteriori){

	return (probabilidadDeClase*probabilidadPosteriori)/probabilidadPriori;
}

float* Bayes::predecirRow(Row row){

	int cantidadDeCrimenes = 0;
	float probabilidades[39];
	float probabilidadDeClase,probabilidadPriori,probabilidadPosteriori;

	probabilidadPriori = this->calcularProbabilidadPriori(row);//probabilidad del denominador

	map<string,float>::iterator iter = frecuenciaDeCrimenes.begin();
	while ((iter != frecuenciaDeCrimenes.end()) && (cantidadDeCrimenes < 39)){
		probabilidadPosteriori = this->calcularProbabilidadPosteriori(row,iter->first);//probabilidad del numerador
		probabilidadDeClase = probabilidadesDeCrimenes[iter->first];
		probabilidades[cantidadDeCrimenes] = calcularProbabilidadDelRow(probabilidadDeClase,
				probabilidadPriori,probabilidadPosteriori);
		iter++;
		cantidadDeCrimenes++;
	}
	//cout << "Se predijo el row correspondiente" << endl;
	return probabilidades;
}

Bayes::~Bayes() {

}
