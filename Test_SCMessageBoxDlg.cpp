﻿
// Test_SCMessageBoxDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_SCMessageBox.h"
#include "Test_SCMessageBoxDlg.h"
#include "afxdialogex.h"

#include "../../Common/Functions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestSCMessageBoxDlg 대화 상자



CTestSCMessageBoxDlg::CTestSCMessageBoxDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_SCMESSAGEBOX_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestSCMessageBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_edit_message);
	DDX_Control(pDX, IDOK, m_button_ok);
	DDX_Control(pDX, IDCANCEL, m_button_cancel);
	DDX_Control(pDX, IDC_BUTTON_TEST, m_button_test);
}

BEGIN_MESSAGE_MAP(CTestSCMessageBoxDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestSCMessageBoxDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestSCMessageBoxDlg::OnBnClickedCancel)
	ON_WM_WINDOWPOSCHANGED()
	ON_EN_CHANGE(IDC_EDIT_MESSAGE, &CTestSCMessageBoxDlg::OnEnChangeEditMessage)
	ON_REGISTERED_MESSAGE(Message_CSCMessageBox, &CTestSCMessageBoxDlg::on_message_CSCMessageBox)
END_MESSAGE_MAP()


// CTestSCMessageBoxDlg 메시지 처리기

BOOL CTestSCMessageBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	RestoreWindowPosition(&theApp, this, _T(""), false, false);

	m_message.create(this, _T("Title Text"), IDR_MAINFRAME, false);
	m_message.set_color_theme(CSCColorTheme::color_theme_linkmemine);
	m_message.use_typed_title_back_color();
	CString test_msg = _T("Test MessageBox\r\nNext Line");
	m_edit_message.SetWindowText(test_msg);

	m_message.set_message(test_msg, MB_YESNO | MB_ICONEXCLAMATION);// , 0, SS_CENTER | SS_CENTERIMAGE);
	//m_message.set_align(SS_LEFT | SS_CENTERIMAGE);
	//int res = m_message.DoModal(_T("Test MessageBox"));//, MB_OKCANCEL);
	//int res = m_message.DoModal(_T("Test MessageBox"), MB_OKCANCEL);
	//int res = m_message.DoModal(_T("Test MessageBox"), MB_YESNOCANCEL);
	//TRACE(_T("res = %d\n"), res);


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestSCMessageBoxDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestSCMessageBoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestSCMessageBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestSCMessageBoxDlg::OnBnClickedOk()
{
	//modeless로 create()했어도 DoModal()을 호출하면 modal로 동작한다.
	//int res = m_message.DoModal();
	//TRACE(_T("res = %d\n"), res);

	m_message.set_message(_T("OK Button Clicked"));
}

void CTestSCMessageBoxDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}

void CTestSCMessageBoxDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: Add your message handler code here
	SaveWindowPosition(&theApp, this);
}

void CTestSCMessageBoxDlg::OnEnChangeEditMessage()
{
	CString text;
	m_edit_message.GetWindowText(text);
	m_message.set_message(text);
}

LRESULT CTestSCMessageBoxDlg::on_message_CSCMessageBox(WPARAM wParam, LPARAM lParam)
{
	CSCMessageBox* msgBox = (CSCMessageBox*)wParam;
	int res = (int)lParam;

	TRACE(_T("msgBox = %p, res = %d\n"), msgBox, res);
	return 0;
}
