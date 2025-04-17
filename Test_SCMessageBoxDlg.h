
// Test_SCMessageBoxDlg.h: 헤더 파일
//

#pragma once

#include "../../Common/messagebox/CSCMessageBox/SCMessageBox.h"

// CTestSCMessageBoxDlg 대화 상자
class CTestSCMessageBoxDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestSCMessageBoxDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

protected:
	CSCMessageBox	m_message;
	LRESULT			on_message_CSCMessageBox(WPARAM wParam, LPARAM lParam);

public:
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_SCMESSAGEBOX_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	CEdit m_edit_message;
	afx_msg void OnEnChangeEditMessage();
	CGdiButton m_button_ok;
	CGdiButton m_button_cancel;
	CGdiButton m_button_test;
};
