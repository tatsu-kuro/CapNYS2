#pragma once


// CMakeDB ダイアログ

class CMakeDB : public CDialogEx
{
	DECLARE_DYNAMIC(CMakeDB)

public:
	CMakeDB(CWnd* pParent = nullptr);   // 標準コンストラクター
	virtual ~CMakeDB();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAKEDB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_filesnum;
	CString m_setumei;
	afx_msg void OnBnClickedOk();
	bool initf;
};
