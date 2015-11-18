//============================================================================
// Name        : SF_CRIME.cpp
// Author      : Joha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CSVReader.h"
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
	CSVReader csv;
	int cantidadDeRowsTrain = 0;

	char* archivo = "trainSpliteado.csv";
	csv.open(archivo,cantidadDeRowsTrain,frecuenciaDeCrimenes,frecuenciaDeCrimenesPorDistrito,probabilidadesDeCrimenes,
			probabilidadesPorDias,probabilidadesPorDistrito);

	return 0;
}
