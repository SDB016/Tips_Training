#pragma once


// DB_Button

class DB_Button : public CButton
{
	DECLARE_DYNAMIC(DB_Button)

public:
	DB_Button();
	virtual ~DB_Button();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


