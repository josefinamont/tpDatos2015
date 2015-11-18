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
		map<string,float> probabilidadesDias[7],map<string,float> probabilidadesDistritos[10]){

	string line, csvItem,crimen;
	ifstream myfile(nameFile);
	int nroItem = 0;

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
				if (nroItem == 2){
					crimen = csvItem;
					if (frecuenciaCrimenes.count(csvItem) < 1) frecuenciaCrimenes[csvItem] = 1; else
						frecuenciaCrimenes[csvItem] += 1;
				}
				if (nroItem == 3) calcularCrimenesPorDia(csvItem,crimen,lunes,martes,miercoles,jueves,viernes,sabado,domingo);
				if (nroItem == 4) calcularCrimenesPorDistrito(crimenesPorDistrito,csvItem,bayview,central,ingleside,mission,
								northern,park,richmond,southern,taraval,tenderloin,crimen);

				nroItem++;
			}
		}
	}

	//esto lo que hace es calcular las probabilidades de los crimenes por dia y distrito, y almacenarlos en un vector
	//para luego poder acceder a estos datos calculados
	calcularProbabilidadesDeCrimenesPorDia(lunes,martes,miercoles,jueves,viernes,sabado,domingo,frecuenciaCrimenes);
	calcularProbabilidadesDeCrimenesPorDistrito(bayview,central,ingleside,mission,northern,park,richmond,southern,taraval,
			tenderloin,frecuenciaCrimenes);

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

	/*float probabilidad = 0;

	probabilidadesCrimenes = frecuenciaCrimenes;
	map<string,float>::iterator iter2 = probabilidadesCrimenes.begin();
	while (iter2 != probabilidadesCrimenes.end() ){
		iter2->second = (iter2->second/cantidadDeRowsTrain);
		probabilidad += iter2->second;
	    cout << iter2->first + " " <<  iter2->second << endl;
	    iter2++;
	}

	float frecuenciaTotal = 0;

	map<string,float>::iterator iter1 = frecuenciaCrimenes.begin();
	while (iter1 != frecuenciaCrimenes.end() ){
		frecuenciaTotal += iter1->second;
		cout << iter1->first + " " <<  iter1->second << endl;
		iter1++;
	}
	cout << frecuenciaTotal << endl;
	cout << probabilidad << endl;*/


	/*map<string,float>::iterator iter = martes.begin();
	while (iter != martes.end() ){
		iter->second = (iter->second/cantidadDeRowsTrain);
		cout << iter->first + " " <<  iter->second << endl;
		iter++;
	}*/

	//cout << cantidadDeRowsTrain << endl;


	/*map<string,int>::iterator iter2 = crimenesPorDistrito.begin();
	while (iter2 != crimenesPorDistrito.end() ){
		cout << iter2->first + " " <<  iter2->second << endl;
		iter2++;
	}

	map<string,float>::iterator iter4 = northern.begin();
	while (iter4 != northern.end() ){
		//cout << iter4->first + " " <<  iter4->second << endl;
		iter4++;
	}*/
}

void CSVReader::calcularProbabilidadesDeCrimenesPorDia(map<string,float> &lunes,map<string,float> &martes,
		map<string,float> &miercoles,map<string,float> &jueves,map<string,float> &viernes,map<string,float> &sabado,
		map<string,float> &domingo,map<string,float> frecuenciaCrimenes){

	/*float p1,p2,p3,p4,p5,p6,p7,f1,f2,f3,f4,f5,f6,f7;
	p1 = 0;
		p2 = 0;
		p3 = 0;
		p4 = 0;
		p5 = 0;
		p6 = 0;
		p7 = 0;
		f1 = 0;
		f2 = 0;
		f3 = 0;
		f4 = 0;
		f5 = 0;
		f6 = 0;
		f7 = 0;*/

	map<string,float>::iterator iter = lunes.begin();
	while (iter != lunes.end() ){
		//f1 += iter->second;
		iter->second = (iter->second/frecuenciaCrimenes[iter->first]);
		//p1 += iter->second;
		//cout << iter->first + " " <<  iter->second << endl;
		iter++;
	}

	map<string,float>::iterator iter1 = martes.begin();
	while (iter1 != martes.end() ){
		//f2 += iter1->second;
		iter1->second = (iter1->second/frecuenciaCrimenes[iter1->first]);
		//p2 += iter1->second;
		//cout << iter1->first + " " <<  iter1->second << endl;
		iter1++;
	}

	map<string,float>::iterator iter2 = miercoles.begin();
	while (iter2 != miercoles.end() ){
		//f3 += iter2->second;
		iter2->second = (iter2->second/frecuenciaCrimenes[iter2->first]);
		//p3 += iter2->second;
		//cout << iter2->first + " " <<  iter2->second << endl;
		iter2++;
	}

	map<string,float>::iterator iter3 = jueves.begin();
	while (iter3 != jueves.end() ){
		//f4 += iter3->second;
		iter3->second = (iter3->second/frecuenciaCrimenes[iter3->first]);
		//p4 += iter3->second;
		//cout << iter3->first + " " <<  iter3->second << endl;
		iter3++;
	}

	map<string,float>::iterator iter4 = viernes.begin();
	while (iter4 != viernes.end() ){
		//f5 += iter4->second;
		iter4->second = (iter4->second/frecuenciaCrimenes[iter4->first]);
		//p5 += iter4->second;
		//cout << iter4->first + " " <<  iter4->second << endl;
		iter4++;
	}

	map<string,float>::iterator iter5 = sabado.begin();
	while (iter5 != sabado.end() ){
		//f6 += iter5->second;
		iter5->second = (iter5->second/frecuenciaCrimenes[iter5->first]);
		//p6 += iter5->second;
		//cout << iter5->first + " " <<  iter5->second << endl;
		iter5++;
	}

	map<string,float>::iterator iter6 = domingo.begin();
	while (iter6 != domingo.end() ){
		//f7 += iter6->second;
		iter6->second = (iter6->second/frecuenciaCrimenes[iter6->first]);
		//p7 += iter6->second;
		//cout << iter6->first + " " <<  iter6->second << endl;
		iter6++;
	}

	/*cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;
	cout << p5 << endl;
	cout << p6 << endl;
	cout << p7 << endl;

	cout << f1+f2+f3+f4+f5+f6+f7 << endl;*/

}

void CSVReader::calcularProbabilidadesDeCrimenesPorDistrito(map<string,float> &bayview,map<string,float> &central,
		map<string,float> &ingleside,map<string,float> &mission,map<string,float> &northern,map<string,float> &park,
		map<string,float> &richmond,map<string,float> &southern,map<string,float> &taraval,
		map<string,float> &tenderloin,map<string,float> frecuenciaCrimenes){

	/*float p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,f1,f2,f3,f4,f5,f6,f7,f8,f9,f10;
	p1 = 0;
	p2 = 0;
	p3 = 0;
	p4 = 0;
	p5 = 0;
	p6 = 0;
	p7 = 0;
	p8 = 0;
	p9 = 0;
	p10 = 0;
	f1 = 0;
	f2 = 0;
	f3 = 0;
	f4 = 0;
	f5 = 0;
	f6 = 0;
	f7 = 0;
	f8 = 0;
	f9 = 0;
	f10 = 0;*/

	map<string,float>::iterator iter = bayview.begin();
	while (iter != bayview.end() ){
		//f1 += iter->second;
		iter->second = (iter->second/frecuenciaCrimenes[iter->first]);
		//p1 += iter->second;
		//cout << iter->first + " " <<  iter->second << endl;
		iter++;
	}

	map<string,float>::iterator iter1 = central.begin();
	while (iter1 != central.end() ){
		//f2 += iter1->second;
		iter1->second = (iter1->second/frecuenciaCrimenes[iter1->first]);
		//p2 += iter1->second;
		//cout << iter1->first + " " <<  iter1->second << endl;
		iter1++;
	}

	map<string,float>::iterator iter2 = ingleside.begin();
	while (iter2 != ingleside.end() ){
		//f3 += iter2->second;
		iter2->second = (iter2->second/frecuenciaCrimenes[iter2->first]);
		//p3 += iter2->second;
		//cout << iter2->first + " " <<  iter2->second << endl;
		iter2++;
	}

	map<string,float>::iterator iter3 = mission.begin();
	while (iter3 != mission.end() ){
		//f4 += iter3->second;
		iter3->second = (iter3->second/frecuenciaCrimenes[iter3->first]);
		//p4 += iter3->second;
		//cout << iter3->first + " " <<  iter3->second << endl;
		iter3++;
	}

	map<string,float>::iterator iter4 = northern.begin();
	while (iter4 != northern.end() ){
		//f5 += iter4->second;
		iter4->second = (iter4->second/frecuenciaCrimenes[iter4->first]);
		//p5 += iter4->second;
		//cout << iter4->first + " " <<  iter4->second << endl;
		iter4++;
	}

	map<string,float>::iterator iter5 = park.begin();
	while (iter5 != park.end() ){
		//f6 += iter5->second;
		iter5->second = (iter5->second/frecuenciaCrimenes[iter5->first]);
		//p6 += iter5->second;
		//cout << iter5->first + " " <<  iter5->second << endl;
		iter5++;
	}

	map<string,float>::iterator iter6 = richmond.begin();
	while (iter6 != richmond.end() ){
		//f7 += iter6->second;
		iter6->second = (iter6->second/frecuenciaCrimenes[iter6->first]);
		//p7 += iter6->second;
		//cout << iter6->first + " " <<  iter6->second << endl;
		iter6++;
	}

	map<string,float>::iterator iter7 = southern.begin();
	while (iter7 != southern.end() ){
		//f8 += iter7->second;
		iter7->second = (iter7->second/frecuenciaCrimenes[iter7->first]);
		//p8 += iter7->second;
		//cout << iter7->first + " " <<  iter7->second << endl;
		iter7++;
	}

	map<string,float>::iterator iter8 = taraval.begin();
	while (iter8 != taraval.end() ){
		//f9 += iter8->second;
		iter8->second = (iter8->second/frecuenciaCrimenes[iter8->first]);
		//p9 += iter8->second;
		//cout << iter8->first + " " <<  iter8->second << endl;
		iter8++;
	}

	map<string,float>::iterator iter9 = tenderloin.begin();
	while (iter9 != tenderloin.end() ){
		//f10 += iter9->second;
		iter9->second = (iter6->second/frecuenciaCrimenes[iter9->first]);
		//p10 += iter9->second;
		//cout << iter9->first + " " <<  iter9->second << endl;
		iter9++;
	}

	/*cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;
	cout << p5 << endl;
	cout << p6 << endl;
	cout << p7 << endl;

	cout << f1+f2+f3+f4+f5+f6+f7+f8+f9+f10 << endl;*/

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

/*void calcularProbabilidades(char *nameFile){

	string line, csvItem;
	ifstream myfile(nameFile);
	int nroItem = 0;
	map<string,float> probabilidades;
	struct Row {
		string hora;
		string diaDeLaSemana;
		string distrito;
	} row;

	if (myfile.is_open()) {

		while (getline(myfile,line)) {
			nroItem = 0;
			istringstream myline(line);

			while(getline(myline, csvItem, ',')) {
				if (nroItem == 2) row.hora = csvItem; else
					if (nroItem == 3) row.diaDeLaSemana = csvItem; else
						if (nroItem == 4) row.distrito = csvItem;

				nroItem++;
			}
		}
		myfile.close();
	}

}*/


CSVReader::~CSVReader() {

}

