
// MyDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "RSA.h"
#include "MyDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно MyDlg



MyDlg::MyDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RSA_DIALOG, pParent)
	, n(527)
	, e(7)
	, d(343)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT3, n);
	DDX_Text(pDX, IDC_EDIT4, e);
	DDX_Text(pDX, IDC_EDIT5, d);
}

BEGIN_MESSAGE_MAP(MyDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &MyDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_DECODE, &MyDlg::OnBnClickedDecode)
	ON_BN_CLICKED(IDC_CODEEE, &MyDlg::OnBnClickedOk2)
	ON_BN_CLICKED(IDC_DECODE2, &MyDlg::OnBnClickedDecode2)
	ON_BN_CLICKED(IDC_CREATEKEY, &MyDlg::OnBnClickedCreatekey)
END_MESSAGE_MAP()


// Обработчики сообщений MyDlg

BOOL MyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	ihWnd = GetDlgItem(IDC_EDIT1)->GetSafeHwnd();
	chWnd = GetDlgItem(IDC_EDIT2)->GetSafeHwnd();
	OnBnClickedCreatekey();
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void MyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR MyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void MyDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	UpdateData();
	rsa.SetD(d);
	rsa.Sete(e);
	rsa.Setn(n);
	rsa.Code();
}


void MyDlg::OnBnClickedDecode()
{
	UpdateData();
	rsa.SetD(d);
	rsa.Sete(e);
	rsa.Setn(n);
	rsa.Decode();
}


void MyDlg::OnBnClickedOk2()
{
	UpdateData();
	rsa.SetD(d);
	rsa.Sete(e);
	rsa.Setn(n);


	int ilen(GetWindowTextLengthA(ihWnd));
	if (ilen == 0)
	{
		MessageBox(L"Заполните поле <<Изначальный текст>>", L"Пустое поле ввода", MB_OK);
		return;
	}


	char* itext = new char[ilen + 1];
	GetWindowTextA(ihWnd, itext, sizeof(char) * (ilen + 1));


	it = string(itext);
	ct = rsa.Code(it);


	SetWindowTextA(chWnd, ct.c_str());


	delete[]itext;
}


void MyDlg::OnBnClickedDecode2()
{
	UpdateData();
	rsa.SetD(d);
	rsa.Sete(e);
	rsa.Setn(n);
	it = rsa.Decode(ct);
	SetWindowTextA(ihWnd, it.c_str());
}


void MyDlg::OnBnClickedCreatekey()
{
	rsa.CreateKey();
	d = rsa.Getd();
	e = rsa.Gete();
	n = rsa.Getn();
	UpdateData(FALSE);
}
