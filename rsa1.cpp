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


unsigned long RSA::CreateSimple()
{
	unsigned long res = 2 + 65531 * float(rand())/float(RAND_MAX);
	while(!IsSimple(res))res = 2 + 65531 * float(rand()) / float(RAND_MAX);
	return res;
}
bool RSA::IsSimple(unsigned long data)
{
	if (data == 1)return true;


	for (int i = 0; i < 10; i++)
	{
		// ����� �, ������� �� ������� �� �
		unsigned long a = 2 + 256 * float(rand()) / float(RAND_MAX);
		while((a%data)==0) a = 2 + 256 * float(rand()) / float(RAND_MAX);


		
		if (RSA::mod(a,data-1,data) != 1)return false;
	}
	return true;
}
unsigned int RSA::mod(unsigned int x, unsigned int pwr, unsigned int md)
{
	if (pwr == 0)return 1;


	unsigned int res = 1;
	if ((pwr % 2) != 0)
	{
		res *= x % md;
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
	res = res % md;
	return res;

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
	ui l = cap * float(rand()) / float(RAND_MAX);
	while(gcd(cap,l)!=1)l = cap * float(rand()) / float(RAND_MAX);


	return l;
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
}


char* RSA::ToChar(ui data)
{
	char res[4] = { 0,0,0,0 };
	
	
	res[0] |= data & 255;
	res[1] |= (data & 65280) >> 8;
	res[2] |= (data & 16711680) >> 16;
	res[3] |= (data & 4278190080) >> 24;


	return res;
}
ui RSA::ToUi(char* data)
{
	ui res = 0;
	res |= data[0];
	res |= data[1] << 8;
	res |= data[2] << 16;
	res |= data[3] << 24;



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


		ui temp = RSA::mod(c, e, n);

		char* wr = ToChar(temp);
		ostr.write(wr,4*sizeof(char));
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
		char in[4];
		for (int i = 0; i < 4; i++)
		{
			char c = 0;
			istr.read(&c, sizeof(char));
			if (istr.eof())break;
			in[i] = c;
		}
		if (istr.eof())break;


		ui temp = RSA::mod(ToUi(in), d, n);


		char wr = temp;
		ostr.write(&wr, sizeof(char));
	}


	istr.close();
	ostr.close();
}