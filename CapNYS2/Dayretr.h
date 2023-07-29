#pragma once
#include "afxwin.h"


// CDayretr ダイアログ

class CDayretr : public CDialogEx
{
	DECLARE_DYNAMIC(CDayretr)

public:
	CDayretr(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CDayretr();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DAYRETR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedN7();
	afx_msg void OnBnClickedN8();
	afx_msg void OnBnClickedN9();
	afx_msg void OnBnClickedN4();
	afx_msg void OnBnClickedN5();
	afx_msg void OnBnClickedN6();
	afx_msg void OnBnClickedN1();
	afx_msg void OnBnClickedN2();
	afx_msg void OnBnClickedN3();
	afx_msg void OnBnClickedN0();
	afx_msg void OnBnClickedClearnum();
	afx_msg void OnBnClickedAllclearnum();
	CButton m_ac;
	CButton m_c;
	CStatic m_ymd;
	CStatic m_day1;
	CStatic m_day10;
	CStatic m_day2;
	CStatic m_day3;
	CStatic m_day4;
	CStatic m_day5;
	CStatic m_day6;
	CStatic m_day7;
	CStatic m_day8;
	CStatic m_day9;
	CButton m_num0;
	CButton m_num1;
	CButton m_num2;
	CButton m_num3;
	CButton m_num4;
	CButton m_num5;
	CButton m_num6;
	CButton m_num7;
	CButton m_num8;
	CButton m_num9;
	CButton m_cancel;
	CButton m_ok;
	int ymd;
	int y1, y2, y3, y4, y5, y6, y7, y8, y9, y10;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	void DispNum(int ymd);
	void DispNum_sub(CStatic* id, int n);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedDay1();
	afx_msg void OnStnClickedDay2();
	afx_msg void OnStnClickedDay3();
	afx_msg void OnStnClickedDay4();
	afx_msg void OnStnClickedDay5();
	afx_msg void OnStnClickedDay6();
	afx_msg void OnStnClickedDay7();
	afx_msg void OnStnClickedDay8();
	afx_msg void OnStnClickedDay9();
	afx_msg void OnStnClickedDay10();
};
