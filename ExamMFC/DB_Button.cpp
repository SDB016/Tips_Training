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
END_MESSAGE_MAP()



// DB_Button 메시지 처리기



void DB_Button::OnLButtonDown(UINT nFlags, CPoint point)
{
	GetParent()->SendMessage(32100);

	CButton::OnLButtonDown(nFlags, point);
}
