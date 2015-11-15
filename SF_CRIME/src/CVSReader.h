/*
 * CVSReader.h
 *
 *  Created on: 8 de nov. de 2015
 *      Author: joha
 */

#ifndef CVSREADER_H_
#define CVSREADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>

using namespace std;

class CVSReader {

private:
	int rows;
	int colums;

public:
	CVSReader();

	void open(char *nameFile);

	void readLine(string line);

	virtual ~CVSReader();
};

#endif /* CVSREADER_H_ */
