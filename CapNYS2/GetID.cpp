// GetID.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "GetID.h"
#include "afxdialogex.h"


// CGetID ダイアログ

IMPLEMENT_DYNAMIC(CGetID, CDialogEx)

CGetID::CGetID(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GETID, pParent)
//	, m_remaintxt(_T(""))
{

	oldIDnum = 0;
	m_IDnum = 0;
}

CGetID::~CGetID()
{
}

void CGetID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLCLEARNUM, m_ac);
	DDX_Control(pDX, IDC_BUTTON0, m_num0);
	DDX_Control(pDX, IDC_BUTTON1, m_num1);
	DDX_Control(pDX, IDC_BUTTON2, m_num2);
	DDX_Control(pDX, IDC_BUTTON3, m_num3);
	DDX_Control(pDX, IDC_BUTTON4, m_num4);
	DDX_Control(pDX, IDC_BUTTON5, m_num5);
	DDX_Control(pDX, IDC_BUTTON6, m_num6);
	DDX_Control(pDX, IDC_BUTTON7, m_num7);
	DDX_Control(pDX, IDC_BUTTON8, m_num8);
	DDX_Control(pDX, IDC_BUTTON9, m_num9);
	DDX_Control(pDX, IDC_CLEARNUM, m_c);
	DDX_Control(pDX, IDC_IDNUMBER, m_id);
	DDX_Control(pDX, IDC_IDNUMBEROLD, m_idold);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	//  DDX_Control(pDX, IDC_REMAINS, m_remains);
	//  DDX_Text(pDX, IDC_REMAINS, m_remaintxt);
}


BEGIN_MESSAGE_MAP(CGetID, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CGetID::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CGetID::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CGetID::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CGetID::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CGetID::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGetID::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetID::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGetID::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGetID::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON0, &CGetID::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_CLEARNUM, &CGetID::OnBnClickedClearnum)
	ON_BN_CLICKED(IDC_ALLCLEARNUM, &CGetID::OnBnClickedAllclearnum)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CGetID::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CGetID::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CGetID::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int y = 9;
	int nx = 20;
	int ny = y + 150;
	int dx = 86, dy = 61, nw = 85, nh = 60;

	CRect rect;
	GetWindowRect(&rect);
//	m_remains.MoveWindow(nx, y, dx * 3, 30);
	m_idold.MoveWindow(nx, ny - 2 * 71, nw * 3 + 2, 70, 1);
	m_id.MoveWindow(nx, ny - 71, nw * 3 + 2, 70, 1);
	m_num7.MoveWindow(nx, ny, nw, nh, 1);
	m_num8.MoveWindow(nx + dx, ny, nw, nh, 1);
	m_num9.MoveWindow(nx + 2 * dx, ny, nw, nh, 1);
	m_num4.MoveWindow(nx, ny + dy, nw, nh, 1);
	m_num5.MoveWindow(nx + dx, ny + dy, nw, nh, 1);
	m_num6.MoveWindow(nx + 2 * dx, ny + dy, nw, nh, 1);
	m_num1.MoveWindow(nx, ny + 2 * dy, nw, nh, 1);
	m_num2.MoveWindow(nx + dx, ny + 2 * dy, nw, nh, 1);
	m_num3.MoveWindow(nx + 2 * dx, ny + 2 * dy, nw, nh, 1);
	m_num0.MoveWindow(nx, ny + 3 * dy, nw, nh, 1);
	m_c.MoveWindow(nx + dx, ny + 3 * dy, nw, nh, 1);
	m_ac.MoveWindow(nx + 2 * dx, ny + 3 * dy, nw, nh, 1);
	m_cancel.MoveWindow(nx, ny + 4 * dy, dx + nw / 2 - 1, nh, 1);
	m_ok.MoveWindow(nx + dx + nw / 2 + 1, ny + 4 * dy, dx + nw / 2 - 1, nh, 1);
	//	DispNum(m_IDnum+100000000);
	//	DispNum(m_IDnum);//ここでは表示されない。onpaintに置くとDispNum()が働く
	oldIDnum = m_IDnum;
	MoveWindow(rect.left, rect.top, nx * 2 + 9 * 2 + nw * 3, ny + 4 * dy + nh + y * 2 + 20 * 2, 1);
	// TODO:  ここに初期化を追加してください
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CGetID::OnBnClickedButton0()
{
	if (m_IDnum == 0)return;
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton1()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 1);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton2()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 2);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton3()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 3);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton4()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 4);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton5()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 5);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton6()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 6);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton7()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 7);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton8()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 8);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedButton9()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 9);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedClearnum()
{
	DispNum(m_IDnum = m_IDnum / 10);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetID::OnBnClickedAllclearnum()
{
	DispNum(m_IDnum = 0);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}

void CGetID::DispNum(int id)
{
	int i, idn, x, x0 = 0, y0 = 0, dx = 33, dy = 45;
	bool zerof = false;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	if (id<100000000)pDC = m_id.GetDC();
	else pDC = m_idold.GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);

	if (id<100000000)pDC->FillSolidRect(0, 0, 255, 66, RGB(255, 255, 255));
	//if(idn>99999999)idn=0;
	idn = id % 100000000;
	sprintf_s(buf, "%08d", idn);//8桁未満は上のけたを０で埋める
	for (i = 0; i<8; i++) {//
		if (buf[i] >= '0'&&buf[i] <= '9') {
			if (id<100000000) {
				if (buf[i] != '0')zerof = true;//0以外が出てきたらフラグを立てる
			}
			else {
				if (buf[i] != '0' || i == 7)zerof = true;//0以外が出てきたらフラグを立てる
			}
			if (buf[i] == '0' && !zerof) {//０以外が出ていないときは空白
				x = 10 * dx + x0;
			}
			else {
				x = (buf[i] - '0')*dx + x0;
			}
		}
		else {
			x = 10 * dx + x0;
		}
		if (id<100000000)pDC->BitBlt(i*(dx - 3) + 3, 10, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
		else pDC->BitBlt(i*(dx - 3) + 3, 10, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


void CGetID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	DispNum(m_IDnum);
	DispNum(oldIDnum + 100000000);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。
}



void CGetID::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnOK();
}


void CGetID::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}


BOOL CGetID::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_RETURN:
			OnBnClickedOk();
			//			OnBnClickedStartcap();
			return true;// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		case '0':
		case  VK_NUMPAD0:
			OnBnClickedButton0();
			return true;
		case 'J':
		case '1':
		case  VK_NUMPAD1:
			OnBnClickedButton1();
			return true;
		case 'K':
		case '2':
		case  VK_NUMPAD2:
			OnBnClickedButton2();
			return true;
		case 'L':
		case '3':
		case  VK_NUMPAD3:
			OnBnClickedButton3();
			return true;
		case 'U':
		case '4':
		case  VK_NUMPAD4:
			OnBnClickedButton4();
			return true;
		case 'I':
		case '5':
		case  VK_NUMPAD5:
			OnBnClickedButton5();
			return true;
		case 'O':
		case '6':
		case  VK_NUMPAD6:
			OnBnClickedButton6();
			return true;
		case '7':
		case  VK_NUMPAD7:
			OnBnClickedButton7();
			return true;
		case '8':
		case  VK_NUMPAD8:
			OnBnClickedButton8();
			return true;
		case '9':
		case  VK_NUMPAD9:
			OnBnClickedButton9();
			return true;
		case VK_BACK:
		case VK_CLEAR:
			OnBnClickedClearnum();
			return true;
		case VK_DELETE:
			OnBnClickedAllclearnum();
			return true;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
