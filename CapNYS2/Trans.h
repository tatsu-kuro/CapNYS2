#pragma once


// Trans ダイアログ

class Trans : public CDialogEx
{
	DECLARE_DYNAMIC(Trans)

public:
	Trans(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~Trans();
	char title[100], ymd[20];
// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CString str0;
	CString str1;
	CString str2;
	CString str3;
	CString str4;
	CString str5;
//	CString str6;
	CButton OKctrl;
//	CListCtrl *m_listavi;
	char ymdfns[1000][301];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	CString str_timer;
//	afx_msg void OnStnClickedStatic5();
};
