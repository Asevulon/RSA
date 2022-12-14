
// MyDlg.h: файл заголовка
//

#pragma once
#include"rsa1.h"

// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RSA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	unsigned long long n;
	ui e;
	ui d;
	RSA rsa;
	string it;
	string ct;
	afx_msg void OnBnClickedDecode();
	afx_msg void OnBnClickedOk2();


	HWND ihWnd;
	HWND chWnd;
	afx_msg void OnBnClickedDecode2();
	afx_msg void OnBnClickedCreatekey();
};
