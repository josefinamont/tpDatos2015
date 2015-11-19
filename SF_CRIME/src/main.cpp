//============================================================================
// Name        : SF_CRIME.cpp
// Author      : Joha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CSVReader.h"
#include "Bayes.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>

using namespace std;

int main() {

	map<string,float> frecuenciaDeCrimenes;//frecuencia de cada crimen
	map<string,float> probabilidadesDeCrimenes;//probabilidad de cada crimen
	map<string,int> frecuenciaDeCrimenesPorDistrito;//cada distrito con la # de crimenes ocurridos en el
	map<string,float> probabilidadesPorDias[7];//probabilidad de crimenes por dia
	map<string,float> probabilidadesPorDistrito[10];//probabilidades de crimenes por distrito
	map<string,float> probabilidadesPorHoras[24];

	CSVReader csv;
	Bayes clasificadorBayesiano;
	int cantidadDeRowsTrain = 0;

	char* train = "trainSpliteado.csv";
	char* test = "testSpliteado.csv";

	csv.open(train,cantidadDeRowsTrain,frecuenciaDeCrimenes,frecuenciaDeCrimenesPorDistrito,probabilidadesDeCrimenes,
			probabilidadesPorDias,probabilidadesPorDistrito,probabilidadesPorHoras);

	clasificadorBayesiano.train(frecuenciaDeCrimenes,frecuenciaDeCrimenes,frecuenciaDeCrimenesPorDistrito,
			probabilidadesPorDias,probabilidadesPorDistrito,probabilidadesPorHoras);

	clasificadorBayesiano.predecir(test);

	return 0;
}
