//============================================================================
// Name        : SF_CRIME.cpp
// Author      : Joha
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "CVSReader.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main() {

	CVSReader csv;
	char *archivo = "trainSpliteado.csv";
	csv.open(archivo);

	return 0;
}
