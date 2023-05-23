#pragma once
//����� ����������� ���������
#include <cmath> //� ������ �����
#include <iostream>
#include <fstream>
#include <windows.h>
#include <string>
#include "IStat.h"
#include <malloc.h>
#include <algorithm>
using namespace std;
class Migration : public IStat<int> { // ��������� 
public:
	Migration(int i) {
		data = new int[i];
	}
	string sgetValue();
	int** getValue();
	////��������� ������� �������� ��������� 
	double calculateGrowth();
	////������ �� �����
	void readData(string puth);
};
string Migration::sgetValue() {
	string str = "";
	char data_im[8];//���������
	char data_em[8];//���������
	
	for (int i = 0; i < 16; i++) {
		sprintf_s(data_im, "%d", data[i]);
		sprintf_s(data_em, "%d", data[i+16]);
		str += to_string(2008 + i) + " year - ";
		str += data_im;
		str += " immigration; ";
		str += data_em;
		str += " emigration.";
		str += '\n';
	}
	return str;
}


int** Migration::getValue() {
	int** data_m= new int*[2];
	data_m[0] = new int[_msize(data) / sizeof(data[0])/2];
	data_m[1] = new int[_msize(data) / sizeof(data[0])/2];
	for (int i = 0; i < _msize(data) / sizeof(data[0])/2; i++) {
		data_m[0][i] = data[i];
		data_m[1][i] = data[i+(_msize(data) / sizeof(data[0])) / 2];
	}
	return data_m;
}

void Migration::readData(string puth) {
	ifstream out;
	out.open(puth);      // ��������� ���� ��� ������
	int i = 0;
	string year = "";
	//data = new double[32];
	while (getline(out, year))   //���� �� �������� ����� �����
	{
		data[i++] = stoi(year);//�������� ������, ��������� � ������
	}
	out.close();
}