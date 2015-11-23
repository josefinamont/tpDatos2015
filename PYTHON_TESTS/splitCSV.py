#!/usr/bin/python
import csv

def splitDate(stringDate):
	
	dateTime = stringDate.split(" ")
	date = dateTime[0].split("-")
	month= date[1]
	
	timeString= dateTime[1].split(":")
	hour= timeString[0]
	return (month,hour)

def splitTest(nameFile, outputFile):
	archivo_input = open(nameFile)
	archivo_input_csv = csv.reader (archivo_input, delimiter = ",")
	archivo_input_csv.next()
	
	registros = []
	
	for ids, date, dayOfWeek, district, address, x, y  \
	in archivo_input_csv:
		
		(month, hour) = splitDate(date)
		registro = (ids,month, hour, dayOfWeek, district, x, y)
		registros.append(registro)
	
	archivo_input.close()
	archivo_output = open (outputFile,"w")
	archivo_output_csv = csv.writer(archivo_output)
	archivo_output_csv.writerows(registros)
	archivo_output.close()
	
def splitTrain(nameFile, outPutFile):
	archivo_input = open(nameFile)
	archivo_input_csv = csv.reader (archivo_input, delimiter = ",")
	archivo_input_csv.next()
	
	registros = []
	
	for date, category, descript, dayOfWeek, district, resolution, \
	address, x, y  in archivo_input_csv:
		
		(month, hour) = splitDate(date)
		registro = (month, hour,category,dayOfWeek, district,x,y)
		registros.append(registro)
	
	archivo_input.close()
	archivo_output = open (outPutFile,"w")
	archivo_output_csv = csv.writer(archivo_output)
	archivo_output_csv.writerows(registros)
	archivo_output.close()

def main():
	
	testFile  = "test.csv"
	outputTest = "testSpliteado.csv"
	
	splitTest(testFile, outputTest)
	
	trainFile = "train.csv"
	outputTrain  = "trainSpliteado.csv"
	
	splitTrain(trainFile, outputTrain)
	
	
main()
