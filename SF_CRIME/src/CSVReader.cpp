/*
 * CVSReader.cpp
 *
 *  Created on: 8 de nov. de 2015
 *      Author: joha
 */

#include "CSVReader.h"

using namespace std;

CSVReader::CSVReader() {

}

void CSVReader::open(char *nameFile,int &cantidadDeRowsTrain,map<string,float> &frecuenciaCrimenes,
		map<string,int> &crimenesPorDistrito,map<string,float> &probabilidadesCrimenes,
		map<string,float> probabilidadesDias[7],map<string,float> probabilidadesDistritos[10],
		map<string,float> probabilidadesHoras[24]){

	string line, csvItem,crimen,horaActual;
	ifstream myfile(nameFile);
	int nroItem = 0;

	map<string,int> horas;

	map<string,float> lunes;
	map<string,float> martes;
	map<string,float> miercoles;
	map<string,float> jueves;
	map<string,float> viernes;
	map<string,float> sabado;
	map<string,float> domingo;

	map<string,float> bayview;
	map<string,float> central;
	map<string,float> ingleside;
	map<string,float> mission;
	map<string,float> northern;
	map<string,float> park;
	map<string,float> richmond;
	map<string,float> southern;
	map<string,float> taraval;
	map<string,float> tenderloin;

	if (myfile.is_open()) {

		while (getline(myfile,line)) {
			nroItem = 0;
			cantidadDeRowsTrain++;
			istringstream myline(line);

			while(getline(myline, csvItem, ',')) {

				if(nroItem == 1){
					horaActual = csvItem;
				}
				if (nroItem == 2){
					crimen = csvItem;
					if (frecuenciaCrimenes.count(csvItem) < 1) frecuenciaCrimenes[csvItem] = 1; else
						frecuenciaCrimenes[csvItem] += 1;
					calcularCrimenesPorHora(horaActual,csvItem,probabilidadesHoras,horas);
				}
				if (nroItem == 3) calcularCrimenesPorDia(csvItem,crimen,lunes,martes,miercoles,jueves,viernes,sabado,domingo);
				if (nroItem == 4) calcularCrimenesPorDistrito(crimenesPorDistrito,csvItem,bayview,central,ingleside,mission,
								northern,park,richmond,southern,taraval,tenderloin,crimen);
				nroItem++;
			}
			//cout << frecuenciaCrimenes[crimen] << endl ;
		}

	}
	//cout << "fuera" << endl;
	//cout << frecuenciaCrimenes[crimen] << endl ;
	myfile.close();

	//se calculan las probabilidades de cada clase
	this->calcularProbabilidadesDeLosCrimenes(frecuenciaCrimenes,probabilidadesCrimenes,cantidadDeRowsTrain);

	//esto lo que hace es calcular las probabilidades de los crimenes por dia y distrito, y almacenarlos en un vector
	//para luego poder acceder a estos datos calculados
	this->calcularProbabilidadesDeCrimenesPorDia(lunes,martes,miercoles,jueves,viernes,sabado,domingo,frecuenciaCrimenes);
	this->calcularProbabilidadesDeCrimenesPorDistrito(bayview,central,ingleside,mission,northern,park,richmond,southern,taraval,
			tenderloin,frecuenciaCrimenes);
    this->calcularProbabilidadesDeCrimenesPorHora(probabilidadesHoras,frecuenciaCrimenes);

	probabilidadesDias[0] = lunes;
	probabilidadesDias[1] = martes;
	probabilidadesDias[2] = miercoles;
	probabilidadesDias[3] = jueves;
	probabilidadesDias[4] = viernes;
	probabilidadesDias[5] = sabado;
	probabilidadesDias[6] = domingo;

	probabilidadesDistritos[0] = bayview;
	probabilidadesDistritos[1] = central;
	probabilidadesDistritos[2] = ingleside;
	probabilidadesDistritos[3] = mission;
	probabilidadesDistritos[4] = northern;
	probabilidadesDistritos[5] = park;
	probabilidadesDistritos[6] = richmond;
	probabilidadesDistritos[7] = southern;
	probabilidadesDistritos[8] = taraval;
	probabilidadesDistritos[9] = tenderloin;

	cout << "Se calcularon correctamente las probabilidades necesarias" << endl;

}

void CSVReader::calcularProbabilidadesDeLosCrimenes(map<string,float> frecuenciaCrimenes,map<string,float> &probabilidadesCrimenes,
		int cantidadDeRowsTrain){

	probabilidadesCrimenes = frecuenciaCrimenes;
	map<string,float>::iterator iter = probabilidadesCrimenes.begin();
	while (iter != probabilidadesCrimenes.end() ){
		iter->second = (iter->second/cantidadDeRowsTrain);
		iter++;
	}
}

void CSVReader::calcularProbabilidad(map<string,float> &nombreMap,map<string,float> frecuenciaCrimenes){

	map<string,float>::iterator iter = nombreMap.begin();
	while (iter != nombreMap.end() ){
		//cout << iter->first + " " <<  iter->second << frecuenciaCrimenes[iter->first] <<endl;
		iter->second = (iter->second/frecuenciaCrimenes[iter->first]);
		cout << iter->first + " " <<  iter->second << endl;
		iter++;
	}
}

void CSVReader::calcularProbabilidadesDeCrimenesPorHora(map<string,float> crimenesPorHora[24],
	map<string,float>frecuenciaCrimenes){

    //this->imprimirCrimenesPorHora(crimenesPorHora);
	int numero = 0;
	while(numero <24){
		calcularProbabilidad(crimenesPorHora[numero], frecuenciaCrimenes);
		numero++;
	}
	this->imprimirCrimenesPorHora(crimenesPorHora);
}

void CSVReader::imprimirCrimenesPorHora(map<string,float>crimenesPorHora[24]){

	int numero = 0;
	long int cantidadDeDelitosTotales = 0;
	long int cantidadDeDelitosPorHora;
	map<string, float>::iterator iter; //= probabilidades[numero].begin();
	while(numero <24){
		iter = crimenesPorHora[numero].begin();
		cout<< "hora " << numero<<endl;
		cantidadDeDelitosPorHora = 0;
		while (iter != crimenesPorHora[numero].end() ){
			      cout << iter->first + " " <<  iter->second << endl;
			      //cantidadDeDelitosPorHora= cantidadDeDelitosPorHora + iter->second;
			      iter++;
		}
		//cout << cantidadDeDelitosPorHora << endl;
		//cantidadDeDelitosTotales= cantidadDeDelitosTotales + cantidadDeDelitosPorHora;
		numero++;
	}
	cout << cantidadDeDelitosTotales << endl;
}

void CSVReader::calcularProbabilidadesDeCrimenesPorDia(map<string,float> &lunes,map<string,float> &martes,
		map<string,float> &miercoles,map<string,float> &jueves,map<string,float> &viernes,map<string,float> &sabado,
		map<string,float> &domingo,map<string,float> frecuenciaCrimenes){

	this->calcularProbabilidad(lunes,frecuenciaCrimenes);
	this->calcularProbabilidad(martes,frecuenciaCrimenes);
	this->calcularProbabilidad(miercoles,frecuenciaCrimenes);
	this->calcularProbabilidad(jueves,frecuenciaCrimenes);
	this->calcularProbabilidad(viernes,frecuenciaCrimenes);
	this->calcularProbabilidad(sabado,frecuenciaCrimenes);
	this->calcularProbabilidad(domingo,frecuenciaCrimenes);

}

void CSVReader::calcularProbabilidadesDeCrimenesPorDistrito(map<string,float> &bayview,map<string,float> &central,
		map<string,float> &ingleside,map<string,float> &mission,map<string,float> &northern,map<string,float> &park,
		map<string,float> &richmond,map<string,float> &southern,map<string,float> &taraval,
		map<string,float> &tenderloin,map<string,float> frecuenciaCrimenes){

	this->calcularProbabilidad(bayview,frecuenciaCrimenes);
	this->calcularProbabilidad(central,frecuenciaCrimenes);
	this->calcularProbabilidad(ingleside,frecuenciaCrimenes);
	this->calcularProbabilidad(mission,frecuenciaCrimenes);
	this->calcularProbabilidad(northern,frecuenciaCrimenes);
	this->calcularProbabilidad(park,frecuenciaCrimenes);
	this->calcularProbabilidad(richmond,frecuenciaCrimenes);
	this->calcularProbabilidad(southern,frecuenciaCrimenes);
	this->calcularProbabilidad(taraval,frecuenciaCrimenes);
	this->calcularProbabilidad(tenderloin,frecuenciaCrimenes);

}

void CSVReader::calcularCrimenesPorHora(string horaActual,string delitoActual,map<string,float> crimenesPorHora[24],map<string,int> &horas){

	if(horas.count(horaActual)<1){
		if (crimenesPorHora[atoi(horaActual.c_str())].count(delitoActual)<1){
			crimenesPorHora[atoi(horaActual.c_str())][delitoActual] = 1;
		}
		else crimenesPorHora[atoi(horaActual.c_str())][delitoActual] += 1;
	}
	else {
		horas[horaActual] = atoi(horaActual.c_str());
		crimenesPorHora[atoi(horaActual.c_str())][delitoActual] = 1;
	}
}

void CSVReader::calcularCrimenesPorDia(string &csvItem,string &crimen,map<string,float> &lunes,map<string,float> &martes,map<string,float> &miercoles,
						map<string,float> &jueves,map<string,float> &viernes,map<string,float> &sabado,map<string,float> &domingo){

	if (csvItem == "Monday"){
		if (lunes.count(crimen) < 1) lunes[crimen] = 1; else lunes[crimen] += 1;
	} else if (csvItem == "Tuesday"){
		if (martes.count(crimen) < 1) martes[crimen] = 1; else martes[crimen] += 1;
	} else if (csvItem == "Wednesday"){
		if (miercoles.count(crimen) < 1) miercoles[crimen] = 1; else miercoles[crimen] += 1;
	} else if (csvItem == "Thursday"){
		if (jueves.count(crimen) < 1) jueves[crimen] = 1; else jueves[crimen] += 1;
	} else if (csvItem == "Friday"){
		if (viernes.count(crimen) < 1) viernes[crimen] = 1; else viernes[crimen] += 1;
	} else if (csvItem == "Saturday"){
		if (sabado.count(crimen) < 1) sabado[crimen] = 1; else sabado[crimen] += 1;
	} else if (csvItem == "Sunday"){
		if (domingo.count(crimen) < 1) domingo[crimen] = 1; else domingo[crimen] += 1;
	}

}

void CSVReader::calcularCrimenesPorDistrito(map<string,int> &crimenesPorDistrito,string &csvItem,map<string,float> &bayview,
										map<string,float> &central,map<string,float> &ingleside,map<string,float> &mission,
										map<string,float> &northern,map<string,float> &park,map<string,float> &richmond,
										map<string,float> &southern,map<string,float> &taraval,map<string,float> &tenderloin,
										string &crimen){

	if (crimenesPorDistrito.count(csvItem) < 1) crimenesPorDistrito[csvItem] = 1; else
		crimenesPorDistrito[csvItem] += 1;
	if (csvItem == "BAYVIEW"){
		if (bayview.count(crimen) < 1) bayview[crimen] = 1; else bayview[crimen] += 1;
	} else if (csvItem == "CENTRAL"){
		if (central.count(crimen) < 1) central[crimen] = 1; else central[crimen] += 1;
	} else if (csvItem == "INGLESIDE"){
		if (ingleside.count(crimen) < 1) ingleside[crimen] = 1; else ingleside[crimen] += 1;
	} else if (csvItem == "MISSION"){
		if (mission.count(crimen) < 1) mission[crimen] = 1; else mission[crimen] += 1;
	} else if (csvItem == "NORTHERN"){
		if (northern.count(crimen) < 1) northern[crimen] = 1; else northern[crimen] += 1;
	} else if (csvItem == "PARK"){
		if (park.count(crimen) < 1) park[crimen] = 1; else park[crimen] += 1;
	} else if (csvItem == "RICHMOND"){
		if (richmond.count(crimen) < 1) richmond[crimen] = 1; else richmond[crimen] += 1;
	} else if (csvItem == "SOUTHERN"){
		if (southern.count(crimen) < 1) southern[crimen] = 1; else southern[crimen] += 1;
	} else if (csvItem == "TARAVAL"){
		if (taraval.count(crimen) < 1) taraval[crimen] = 1; else taraval[crimen] += 1;
	} else if (csvItem == "TENDERLOIN"){
		if (tenderloin.count(crimen) < 1) tenderloin[crimen] = 1; else tenderloin[crimen] += 1;
	}
}

CSVReader::~CSVReader() {

}

