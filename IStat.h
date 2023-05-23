#pragma once
template <typename T>
class IStat { //базовый класс
	virtual void readData(string puth)=0;
	virtual double calculateGrowth() = 0;
	protected: 
		T* data;
};