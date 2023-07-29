#pragma once
#include "afxwin.h"


// CGetNewID ダイアログ

class CGetNewID : public CDialogEx
{
	DECLARE_DYNAMIC(CGetNewID)

public:
	CGetNewID(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CGetNewID();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETNEWID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ok;
	CButton m_cancel;
	CButton m_startcap;
//	CStatic m_id;
	CStatic m_hist1;
	CStatic m_hist10;
	CStatic m_hist9;
	CStatic m_hist8;
	CStatic m_hist7;
	CStatic m_hist6;
	CStatic m_hist5;
	CStatic m_hist4;
	CStatic m_hist3;
	CStatic m_hist2;
	CButton m_num9;
	CButton m_num0;
	CButton m_num1;
	CButton m_num2;
	CButton m_num3;
	CButton m_num4;
	CButton m_num5;
	CButton m_num6;
	CButton m_num7;
	CButton m_num8;
	CButton m_c;
	CButton m_ac;
	CBitmap bmp_button_start;
	CBitmap bmp_button_curplay;
	CBitmap bmp_button_alllist;
//	CStatic m_id;
//	int m_IDnum;
	int m_hist;

	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedClearnum();
	afx_msg void OnBnClickedAllclearnum();
	afx_msg void OnStnClickedHist1();
	afx_msg void OnStnClickedHist10();
	afx_msg void OnStnClickedHist9();
	afx_msg void OnStnClickedHist8();
	afx_msg void OnStnClickedHist7();
	afx_msg void OnStnClickedHist6();
	afx_msg void OnStnClickedHist4();
	afx_msg void OnStnClickedHist5();
	afx_msg void OnStnClickedHist3();
	afx_msg void OnStnClickedHist2();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	void DispNum(int num);
	void DispNum_sub(CStatic* id, int num);
	afx_msg void OnBnClickedStartcap();
	CStatic m_id;
//	int m_IDnum;
	int m_IDnum;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
//	int record_setid;
	int m_record_setid;
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
