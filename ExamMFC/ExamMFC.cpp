
// ExamMFC.cpp: 애플리케이션에 대한 클래스 동작을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "ExamMFC.h"
#include "ExamMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExamMFCApp

BEGIN_MESSAGE_MAP(CExamMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CExamMFCApp 생성

CExamMFCApp::CExamMFCApp()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}


// 유일한 CExamMFCApp 개체입니다.

CExamMFCApp theApp; //winmain보다 먼저 실행됨


// CExamMFCApp 초기화

BOOL CExamMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	CExamMFCDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal(); //DoModal=자식윈도우가 떠있으면 부모윈도우 클릭이 안됨, ModalList=떠있어도 클릭가능

	return FALSE;
}