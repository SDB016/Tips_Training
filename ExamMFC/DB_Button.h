#pragma once


// DB_Button

class DB_Button : public CButton
{
	DECLARE_DYNAMIC(DB_Button)
	char m_toggle_flag = 0;

public:
	DB_Button();
	virtual ~DB_Button();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual void PreSubclassWindow();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


