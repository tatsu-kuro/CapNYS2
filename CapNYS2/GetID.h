#pragma once
#include "afxwin.h"


// CGetID ダイアログ

class CGetID : public CDialogEx
{
	DECLARE_DYNAMIC(CGetID)

public:
	CGetID(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CGetID();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETID };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CButton m_ac;
	CButton m_num0;
	CButton m_num1;
	CButton m_num2;
	CButton m_num3;
	int oldIDnum;
	int m_IDnum;
	CButton m_num4;
	CButton m_num5;
	CButton m_num6;
	CButton m_num7;
	CButton m_num8;
	CButton m_num9;
	CButton m_c;
	CStatic m_id;
	CStatic m_idold;
	CButton m_cancel;
	CButton m_ok;
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
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void DispNum(int id);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
//	CStatic m_remains;
//	CString m_remaintxt;
};
