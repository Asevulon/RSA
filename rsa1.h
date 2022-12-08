#pragma once
#include<random>
#include<time.h>
#include<fstream>
using namespace std;


typedef unsigned long long int ui;


//класс шифровальщик
class RSA
{
private:
	ui
		n,//ключи
		e;//(e, n) - открытый ключ
	int d;//(d, n) - закрытый ключ


protected:
	unsigned long CreateSimple();
	bool IsSimple(unsigned long data);
	ui CreateE(ui cap);
	ui mod(ui x, ui pwr, ui md);
	ui RSA::_mod(ui x, ui pwr, ui md);
	ui eulerfunc(ui left, ui right);
	ui gcd(ui left, ui right);
	ui gcdext(ui left, ui right, int& l, int& m);
	char* ToChar(ui data);
	ui ToUi(unsigned char* data);


public:
	RSA();
	void CreateKey();


	void Setn(ui n);
	void Sete(ui e);
	void SetD(ui d);


	ui Getn();
	ui Gete();
	ui Getd();


	void Code();
	void Decode();
};