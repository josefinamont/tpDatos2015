/*
 * Bayes.h
 *
 *  Created on: 17/11/2015
 *      Author: josefina
 */

#ifndef BAYES_H_
#define BAYES_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

namespace std {

class Bayes {

private:

	struct Row {
		string hora;
		string diaDeLaSemana;
		string distrito;
	} row;

	map<string,float> frecuenciaDeCrimenes;
	map<string,float> probabilidadesDeCrimenes;
	map<string,int> frecuenciaDeCrimenesPorDistrito;
	map<string,float> *probabilidadesPorDias;
	map<string,float> *probabilidadesPorDistrito;
	map<string,float> *probabilidadesPorHoras;

	void predecirRow(Row row);

	float calcularProbabilidadPosteriori(map<string,float> frecuenciaDeCrimenes,map<string,float> probabilidadesDeCrimenes,
			map<string,int> frecuenciaDeCrimenesPorDistrito,map<string,float> *probabilidadesPorDias,
			map<string,float> *probabilidadesPorDistrito,map<string,float> *probabilidadesPorHoras);

	float calcularProbabilidadPriori(map<string,float> frecuenciaDeCrimenes,map<string,float> probabilidadesDeCrimenes,
			map<string,int> frecuenciaDeCrimenesPorDistrito,map<string,float> *probabilidadesPorDias,
			map<string,float> *probabilidadesPorDistrito,map<string,float> *probabilidadesPorHoras);

public:

	Bayes();

	void train(map<string,float> frecuenciaDeCrimenes,map<string,float> probabilidadesDeCrimenes,
		map<string,int> frecuenciaDeCrimenesPorDistrito,map<string,float> *probabilidadesPorDias,
		map<string,float> *probabilidadesPorDistrito,map<string,float> *probabilidadesPorHoras);

	void predecir(char* nameFile);

	virtual ~Bayes();

};

} /* namespace std */

#endif /* BAYES_H_ */
