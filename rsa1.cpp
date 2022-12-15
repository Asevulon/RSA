#include"pch.h"
#include"rsa1.h"


RSA::RSA():n(0),e(0),d(0)
{
	srand(time(NULL));
}


void RSA::Setn(ui N)
{
	n = N;
}
void RSA::Sete(ui E)
{
	e = E;
}
void RSA::SetD(ui D)
{
	d = D;
}


ui RSA::Getn()
{
	return n;
}
ui RSA::Gete()
{
	return e;
}
ui RSA::Getd()
{
	return d;
}


ui RSA::CreateSimple()
{
	ui res = 3 + 253 * float(rand())/float(RAND_MAX);
	while(!IsSimple(res))res = 3 + 253 * float(rand()) / float(RAND_MAX);
	return res;
}
bool RSA::IsSimple(unsigned long data)
{
	if (data == 1)return true;


	for (int i = 0; i < 10; i++)
	{
		// берем а, которое не делится на р
		unsigned long a = 3 + 253 * float(rand()) / float(RAND_MAX);
		while((a%data)==0) a = 3 + 253 * float(rand()) / float(RAND_MAX);


		
		if (RSA::mod(a,data-1,data) != 1)return false;
	}
	return true;
}
ui RSA::_mod(ui x, ui pwr, ui md)
{
	if (pwr == 0)return 1;


	ui res = 1;
	if ((pwr % 2) != 0)
	{
		res *= x;
		res *= mod
		(
			(x * x)%md,
			(pwr - 1) / 2,
			md
		);
	}
	else
	{
		res *= mod
		(
			(x * x)%md,
			pwr / 2,
			md
		);
	}
	res = res % md;
	return res;
}
ui RSA::mod(ui x, ui pwr, ui md)
{
	if (pwr == 0)return 1;


	ui res = 1;
	if ((pwr % 2) != 0)
	{
		res *= x;
		res *= mod
		(
			(x * x) % md,
			(pwr - 1) / 2,
			md
		);
	}
	else
	{
		res *= mod
		(
			(x * x) % md,
			pwr / 2,
			md
		);
	}
	return res%md;
}
ui RSA::eulerfunc(ui left, ui right)
{
	return (left - 1) * (right - 1);
}
ui RSA::gcd(ui left, ui right)
{
	if (right == 0)return -1;


	ui r = left % right;
	while (r != 0)
	{
		left = right;
		right = r;
		r = left % right;
	}


	return right;
}
ui RSA::gcdext(ui left, ui right, int& l, int& m)
{
	if (right == 0)return -1;


	int l2(1), m2(0);
	int l1(0), m1(1);
	ui r = right;
	while (r != 0)
	{
		int qi = left / right;
		r = left % right;
		left = right;
		right = r;
		l = l2 - qi * l1;
		m = m2;
		m+=-qi * m1;

		l2 = l1;
		m2 = m1;
		l1 = l;
		m1 = m;
	}


	l = l2;
	m = m2;
	return right;
}
ui RSA::CreateE(ui cap)
{
	ui e = 3 + (cap - 3) * float(rand()) / float(RAND_MAX);
	while (gcd(cap, e) != 1)
	{
		e = 3 + (cap - 3) * float(rand()) / float(RAND_MAX);
	}
	return e;
}


void RSA::CreateKey()
{
	ui p = CreateSimple();
	ui q = CreateSimple();
	n = p * q;
	ui y = eulerfunc(p, q);
	e = CreateE(y);
	int temp = 0;
	gcdext(e, y, d, temp);
	d += y;
}


char* RSA::ToChar(ui data)
{
	char* res = new char[4]{ 0, 0, 0, 0 };
	
	ui temp = 255;
	res[0] |= data & temp;

	temp <<= 8;
	res[1] |= (data & temp) >> 8;

	temp <<= 8;
	res[2] |= (data & temp) >> 16;

	temp <<= 8;
	res[3] |= (data & temp) >> 24;


	return res;
}
ui RSA::ToUi(unsigned char* data)
{
	ui res = 0;
	res |= data[0];


	ui temp = data[1];
	temp <<= 8;
	res |= temp;


	temp = data[2];
	temp <<= 16;
	res |= temp;


	temp = data[3];
	temp <<= 24;
	res |= temp;


	return res;
}


void RSA::Code()
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ifstream istr(path, ios::binary);


	CFileDialog file2_dialog(1);
	file2_dialog.DoModal();
	path = file2_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ofstream ostr(path, ios::binary);


	while (1)
	{
		char c = 0;
		istr.read(&c, sizeof(c));
		if (istr.eof())break;


		ui temp = RSA::_mod(unsigned char(c), e, n);

		
		char* wr = ToChar(temp);
		for (int i = 0; i < 4; i++)
		{
			char cc = wr[i];
			ostr.write(&cc, sizeof(char));
		}
		delete[]wr;
	}


	istr.close();
	ostr.close();
}
void RSA::Decode()
{
	CFileDialog file1_dialog(1);
	file1_dialog.DoModal();

	CString path = file1_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ifstream istr(path, ios::binary);


	CFileDialog file2_dialog(1);
	file2_dialog.DoModal();
	path = file2_dialog.GetPathName();
	if (path.GetLength() == 0)return;
	ofstream ostr(path, ios::binary);


	while (1)
	{
		unsigned char in[4];
		for (int i = 0; i < 4; i++)
		{
			char c = 0;
			istr.read(&c, sizeof(char));
			if (istr.eof())break;
			in[i] = c;
		}
		if (istr.eof())break;

		ui dec = ToUi(in);
		ui temp = RSA::_mod(dec, d, n);


		char wr = temp;
		ostr.write(&wr, sizeof(char));
	}


	istr.close();
	ostr.close();
}


string RSA::Code(string in)
{
	string res = "";


	for (int i = 0; i < in.size(); i++)
	{
		ui temp = RSA::_mod(unsigned char(in[i]), e, n);
		char* wr = ToChar(temp);

		for (int g = 0; g < 4; g++)
		{
			res += wr[g];
		}
		delete[]wr;
	}


	return res;
}
string RSA::Decode(string in)
{
	string res = "";


	for (int i = 0; i < in.size(); i += 4)
	{
		unsigned char inc[4] = { 0,0,0,0 };
		inc[0] = in[i];
		inc[1] = in[i + 1];
		inc[2] = in[i + 2];
		inc[3] = in[i + 3];
		

		ui dec = ToUi(inc);
		ui temp = RSA::_mod(dec, d, n);

		
		res += char(temp);
	}


	return res;
}
