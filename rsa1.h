#pragma once
#include<random>
#include<time.h>
#include<fstream>
using namespace std;


typedef unsigned int ui;


//����� ������������
class RSA
{
private:
	ui
		n,//�����
		e;//(e, n) - �������� ����
	int d;//(d, n) - �������� ����


protected:
	unsigned long CreateSimple();
	bool IsSimple(unsigned long data);
	ui CreateE(ui cap);
	unsigned int mod(unsigned int x, unsigned int pwr, unsigned int md);
	ui eulerfunc(ui left, ui right);
	ui gcd(ui left, ui right);
	ui gcdext(ui left, ui right, int& l, int& m);
	char* ToChar(ui data);
	ui ToUi(char* data);


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