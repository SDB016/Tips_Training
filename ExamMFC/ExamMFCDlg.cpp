
// ExamMFCDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ExamMFC.h"
#include "ExamMFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamMFCDlg 대화 상자



CExamMFCDlg::CExamMFCDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXAMMFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExamMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_my_list);
}

BEGIN_MESSAGE_MAP(CExamMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_COPY_BUTTON, &CExamMFCDlg::OnBnClickedCopyButton)
	ON_LBN_SELCHANGE(IDC_LIST1, &CExamMFCDlg::OnSelchangeList1)
	ON_MESSAGE(32100, &CExamMFCDlg::On32100)
END_MESSAGE_MAP()


// CExamMFCDlg 메시지 처리기

BOOL CExamMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	m_copy_btn.SubclassDlgItem(IDC_COPY_BUTTON, this);
	m_ok_btn.SubclassDlgItem(IDOK, this);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	//int index = m_my_list.AddString(L"안녕하세요"); // Addstring이나 insertstring의 반환값은 추가된 인덱스 값
	//m_my_list.InsertString(-1, L"감사합니다");  // 인덱스가 -1이면 마지막에 추가
	//m_my_list.SetCurSel(index);
	

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CExamMFCDlg::OnPaint()
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
HCURSOR CExamMFCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CExamMFCDlg::OnBnClickedCopyButton()
{
	CString str;

	GetDlgItemText(IDC_VALUE_EDIT, str);
	double num = _wtof(str);
	num += 0.2;
	str.Format(L"%g", num);
	SetDlgItemText(IDC_SHOW_EDIT, str);
	int index = m_my_list.InsertString(0, str); //에디트 컨트롤에 있는 값을 리스트박스에 복사
	m_my_list.SetCurSel(index);
	
}


void CExamMFCDlg::OnSelchangeList1()  //ListBoxNotify 일때 발생하는 이벤트
{
	int index = m_my_list.GetCurSel();
	CString str;
	m_my_list.GetText(index, str);

	SetDlgItemText(IDC_VALUE_EDIT, str);

}

//콤보박스는 리스트박스와 동일하지만 GetText하면 선택된 정보(맨 위의 정보)
//GetLBText하면 세부 설정에서 선택된 정보 (아래 화살표 눌렀을 때 밑의 정보)

afx_msg LRESULT CExamMFCDlg::On32100(WPARAM wParam, LPARAM lParam)
{

	int index = m_my_list.InsertString(-1, L"버튼 눌러짐");
	m_my_list.SetCurSel(index);
	return 0;
}
