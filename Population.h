#pragma once
//класс численности населения
#include <cmath> //в другой класс
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include "IStat.h"
#include <malloc.h>
using namespace std;
class Population : public IStat{ // наследник 
public:
	Population(int i) {
		data = new double[i];
	}
	string sgetValue();
	double* getValue();
	//ежегодный процент прироста населения 
	double calculateGrowth();
	//чтение из файла
	void readData(string puth);
};
string Population::sgetValue() {
	string str = "";
	char psz[6];
	for (int i = 0; i < 16; i++) {
		sprintf_s(psz, "%.1f", data[i]);
		str += to_string(2008 + i) + " year - ";
		str += psz;
		str += "m\n";
	}
	return str;
}

double* Population::getValue() {
	return data;
}

double Population::calculateGrowth(){
	double s = data[0];
	int len = _msize(data) / sizeof(data[0]);
	double f = data[len - 1];
	int y = len;
	return (pow(f / s, 1.0/y) - 1) * 100;
}
void Population::readData(string puth) {
	ifstream out;
	out.open(puth);      // открываем файл для записи
	int i = 0;
	string year = "";
	data = new double[16];
	while (getline(out, year))   //пока не достигли конца файла
	{
		data[i++] = stod(year);//получаем строку, переводим в массив
	}
	out.close();
}