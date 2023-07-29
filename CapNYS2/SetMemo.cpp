// SetMemo.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "SetMemo.h"
#include "afxdialogex.h"
#include "Header.h"


// CSetMemo ダイアログ

IMPLEMENT_DYNAMIC(CSetMemo, CDialogEx)

CSetMemo::CSetMemo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MEMO, pParent)
	, m_memotxt(_T(""))
	, m_memohead(_T(""))
{

}

CSetMemo::~CSetMemo()
{
}

void CSetMemo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_MEMOHEAD, m_memohead);
	//  DDX_Control(pDX, IDC_MEMOTXT, m_memotxt);
	DDX_Text(pDX, IDC_MEMOTXT, m_memotxt);
	DDX_Text(pDX, IDC_MEMOHEAD, m_memohead);
	DDX_Control(pDX, IDC_MEMOTXT, m_memoctrl);
}


BEGIN_MESSAGE_MAP(CSetMemo, CDialogEx)
END_MESSAGE_MAP()


// CSetMemo メッセージ ハンドラー


BOOL CSetMemo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rect;
	if (Para1(FONT) > 0) {
		//char *font[10] = { "nonfont","Arial","Courier","Courier New","Times New Roman","Helvetica" };
		if (Para1(FONT) == 1)m_font.CreatePointFont(Para0(FONT), _T("ＭＳ ゴシック"));
		else if (Para1(FONT) == 2)m_font.CreatePointFont(Para0(FONT), _T("ＭＳ 明朝"));
		else if (Para1(FONT) == 3)m_font.CreatePointFont(Para0(FONT), _T("Arial"));
		else if (Para1(FONT) == 4)m_font.CreatePointFont(Para0(FONT), _T("Courier"));
		else if (Para1(FONT) == 5)m_font.CreatePointFont(Para0(FONT), _T("Courier New"));
		else if (Para1(FONT) == 6)m_font.CreatePointFont(Para0(FONT), _T("Times New Roman"));
		else if (Para1(FONT) == 7)m_font.CreatePointFont(Para0(FONT), _T("Helvetica"));
		m_memoctrl.SetFont(&m_font);
	}
	GetClientRect(&rect);
	//	int x,y,x1,y1;
	//x=rect.top;
	//	y=rect.bottom;
	//	x1=rect.left;
	//	y1=rect.right;
	MoveWindow(3, 3, rect.right - rect.left + 20, rect.bottom - rect.top + 30);// TODO:  ここに初期化を追加してください

	// TODO: ここに初期化を追加してください
	if(strstr(m_memohead,"http:"))SetWindowText("set the address of th ip camera");
	else SetWindowText("set the memo");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
