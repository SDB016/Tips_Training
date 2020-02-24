
// ExamMFCDlg.h: 헤더 파일
//

#pragma once

#include "DB_Button.h"

// CExamMFCDlg 대화 상자
class CExamMFCDlg : public CDialogEx
{
private:
	DB_Button m_copy_btn;
	DB_Button m_ok_btn;

// 생성입니다.
public:
	CExamMFCDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXAMMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCopyButton();
	CListBox m_my_list;
	afx_msg void OnSelchangeList1();
protected:
	afx_msg LRESULT On32100(WPARAM wParam, LPARAM lParam);
};
