// DB_Button.cpp: 구현 파일
//

#include "pch.h"
#include "ExamMFC.h"
#include "DB_Button.h"


// DB_Button

IMPLEMENT_DYNAMIC(DB_Button, CButton)

DB_Button::DB_Button()
{

}

DB_Button::~DB_Button()
{
}


BEGIN_MESSAGE_MAP(DB_Button, CButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// DB_Button 메시지 처리기



void DB_Button::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetParent()->PostMessage(32100);

	CButton::OnLButtonDown(nFlags, point);
	
}


void DB_Button::OnPaint()
{
	CPaintDC dc(this); 
	CRect r;
	GetClientRect(r);
	if (m_toggle_flag)
	{
		dc.FillSolidRect(r, RGB(240, 0, 0));
		dc.SetTextColor(RGB(255, 255, 255));
	}
	else
	{
		dc.FillSolidRect(r, RGB(130, 0, 0));
		dc.SetTextColor(RGB(0,0,0));
	}

	CString str;
	GetWindowText(str);
	
	
	dc.DrawText(str, r,DT_CENTER | DT_VCENTER | DT_SINGLELINE); //DT_VCENTER를 쓰려면 DT_SINGLELINE도 함께 써야함!!
	
}


void DB_Button::PreSubclassWindow()
{
	SetTimer(1,500,NULL);
	CButton::PreSubclassWindow();
}


void DB_Button::OnTimer(UINT_PTR nIDEvent)
{
	m_toggle_flag = !m_toggle_flag;
	Invalidate();
	CButton::OnTimer(nIDEvent);
}
