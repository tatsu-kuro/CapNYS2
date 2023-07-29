// GetNewID.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "GetNewID.h"
#include "afxdialogex.h"
#include "Header.h"
//int m_down_x=-1,m_move_x=-1;
// CGetNewID ダイアログ

IMPLEMENT_DYNAMIC(CGetNewID, CDialogEx)

CGetNewID::CGetNewID(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GETNEWID, pParent)
{

	//  m_IDnum = 0;
	m_IDnum = 0;
	//  record_setid = 0;
	m_record_setid = 0;
}

CGetNewID::~CGetNewID()
{
}

void CGetNewID::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_STARTCAP, m_startcap);
	//  DDX_Control(pDX, IDC_IDNUMBER, m_id);
	DDX_Control(pDX, IDC_HIST1, m_hist1);
	DDX_Control(pDX, IDC_HIST10, m_hist10);
	DDX_Control(pDX, IDC_HIST9, m_hist9);
	DDX_Control(pDX, IDC_HIST8, m_hist8);
	DDX_Control(pDX, IDC_HIST7, m_hist7);
	DDX_Control(pDX, IDC_HIST6, m_hist6);
	DDX_Control(pDX, IDC_HIST5, m_hist5);
	DDX_Control(pDX, IDC_HIST4, m_hist4);
	DDX_Control(pDX, IDC_HIST3, m_hist3);
	DDX_Control(pDX, IDC_HIST2, m_hist2);
	DDX_Control(pDX, IDC_BUTTON9, m_num9);
	DDX_Control(pDX, IDC_BUTTON0, m_num0);
	DDX_Control(pDX, IDC_BUTTON1, m_num1);
	DDX_Control(pDX, IDC_BUTTON2, m_num2);
	DDX_Control(pDX, IDC_BUTTON3, m_num3);
	DDX_Control(pDX, IDC_BUTTON4, m_num4);
	DDX_Control(pDX, IDC_BUTTON5, m_num5);
	DDX_Control(pDX, IDC_BUTTON6, m_num6);
	DDX_Control(pDX, IDC_BUTTON7, m_num7);
	DDX_Control(pDX, IDC_BUTTON8, m_num8);
	DDX_Control(pDX, IDC_CLEARNUM, m_c);
	DDX_Control(pDX, IDC_ALLCLEARNUM, m_ac);
	DDX_Control(pDX, IDC_IDNUMBER, m_id);
}


BEGIN_MESSAGE_MAP(CGetNewID, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON7, &CGetNewID::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CGetNewID::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CGetNewID::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON4, &CGetNewID::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CGetNewID::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CGetNewID::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetNewID::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGetNewID::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGetNewID::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON0, &CGetNewID::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_CLEARNUM, &CGetNewID::OnBnClickedClearnum)
	ON_BN_CLICKED(IDC_ALLCLEARNUM, &CGetNewID::OnBnClickedAllclearnum)
	ON_STN_CLICKED(IDC_HIST1, &CGetNewID::OnStnClickedHist1)
	ON_STN_CLICKED(IDC_HIST10, &CGetNewID::OnStnClickedHist10)
	ON_STN_CLICKED(IDC_HIST9, &CGetNewID::OnStnClickedHist9)
	ON_STN_CLICKED(IDC_HIST8, &CGetNewID::OnStnClickedHist8)
	ON_STN_CLICKED(IDC_HIST7, &CGetNewID::OnStnClickedHist7)
	ON_STN_CLICKED(IDC_HIST6, &CGetNewID::OnStnClickedHist6)
	ON_STN_CLICKED(IDC_HIST4, &CGetNewID::OnStnClickedHist4)
	ON_STN_CLICKED(IDC_HIST5, &CGetNewID::OnStnClickedHist5)
	ON_STN_CLICKED(IDC_HIST3, &CGetNewID::OnStnClickedHist3)
	ON_STN_CLICKED(IDC_HIST2, &CGetNewID::OnStnClickedHist2)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_STARTCAP, &CGetNewID::OnBnClickedStartcap)
	ON_BN_CLICKED(IDOK, &CGetNewID::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CGetNewID::OnBnClickedCancel)
//	ON_WM_LBUTTONDOWN()
//	ON_WM_MBUTTONUP()
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CGetNewID メッセージ ハンドラー


void CGetNewID::OnBnClickedButton0()
{
	if (m_IDnum == 0)return;
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton1()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 1);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton2()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 2);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton3()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 3);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton4()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 4);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton5()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 5);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton6()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 6);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton7()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 7);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton8()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 8);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedButton9()
{
	if (m_IDnum>9999999)return;
	DispNum(m_IDnum = m_IDnum * 10 + 9);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedClearnum()
{
	DispNum(m_IDnum = m_IDnum / 10);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void CGetNewID::OnBnClickedAllclearnum()
{
	DispNum(m_IDnum = 0);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}



int GetNthID(char *ids, int n)
{
	int x;
	char buf[100];
	strcpy_s(buf, &ids[(n - 1) * 9]);
	buf[8] = '\0';
	sscanf_s(buf, "%d", &x);
	return x;
}

void CGetNewID::OnStnClickedHist1()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 1));
}


void CGetNewID::OnStnClickedHist2()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 2));
}


void CGetNewID::OnStnClickedHist3()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 3));
}


void CGetNewID::OnStnClickedHist4()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 4));
}


void CGetNewID::OnStnClickedHist5()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 5));
}


void CGetNewID::OnStnClickedHist6()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 6));
}


void CGetNewID::OnStnClickedHist7()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 7));
}


void CGetNewID::OnStnClickedHist8()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 8));
}


void CGetNewID::OnStnClickedHist9()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 9));
}


void CGetNewID::OnStnClickedHist10()
{
	DispNum(m_IDnum = GetNthID(ptxt[HIST], 10));
}

BOOL CGetNewID::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	int y = 12;
	int nx = 20;
	int ny = y + 80;
	int dx = 72, dy = 72, nw = 71, nh = 71;
	int histw = 103, histh = 35;
	m_id.MoveWindow(nx, ny - 71, nw * 3 + histw + 3, 70, 1);
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
	//	m_cancel.MoveWindow(nx,ny+4*dy,nw,nh,1);
	//	m_startcap.MoveWindow(nx+dx,ny+4*dy,nw,nh,1);
	//	m_ok.MoveWindow(nx+2*dx,ny+4*dy,nw,nh,1);
	//m_cancel.ShowWindow(SW_HIDE);
	//	m_cancel.MoveWindow(nx,ny+4*dy,nw,nh,1);
	if (m_record_setid == 0) {
		m_startcap.MoveWindow(nx + 3 * dx / 2 + 1, ny + 4 * dy, 3 * nw / 2, nh, 1);//startcap
		m_ok.ShowWindow(SW_HIDE);
		m_cancel.SetWindowTextA("SET ID");
	}
	else {
		m_startcap.ShowWindow(SW_HIDE);
		m_ok.MoveWindow(nx + 3 * dx / 2 + 1, ny + 4 * dy, 3 * nw / 2, nh, 1);//setid
	}
	m_cancel.MoveWindow(nx, ny + 4 * dy, 3 * nw / 2, nh, 1);//setid
	m_hist1.MoveWindow(nx + 3 * dx, ny, histw, histh);
	m_hist2.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 1, histw, histh);
	m_hist3.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 2, histw, histh);
	m_hist4.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 3, histw, histh);
	m_hist5.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 4, histw, histh);
	m_hist6.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 5, histw, histh);
	m_hist7.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 6, histw, histh);
	m_hist8.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 7, histw, histh);
	m_hist9.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 8, histw, histh);
	m_hist10.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 9, histw, histh);
	//	m_cancel.MoveWindow(nx,ny+4*dy,dx+nw/2-1,nh,1);
	//	m_ok.MoveWindow(nx+dx+nw/2+1,ny+4*dy,dx+nw/2-1,nh,1);

	//	m_currentid.MoveWindow(nx+2*dx,ny+4*dy,nw,20,1);
	bmp_button_start.LoadBitmapA(IDB_BM_START);
	m_startcap.SetBitmap(bmp_button_start);//ok をスタート
										   //	bmp_button_alllist.LoadBitmapA(IDB_BUTTON_ALLLIST);
										   //	m_cancel.SetBitmap(bmp_button_alllist);
										   //	bmp_button_curplay.LoadBitmapA(IDB_BUTTON_CURPLAY);
										   //	m_start.SetBitmap(bmp_button_curplay);
										   // TODO:  ここに初期化を追加してください

	if (Para0(NEWD) == 0 && Para1(NEWD) == 0) {
		MoveWindow(Winw / 2 - (nw * 3 + 2 + 20 * 2 + 10 * 2) / 2, Winh / 2 - (ny + 4 * dy + 20 + nw + 20 * 2) / 2, nw * 3 + 2 + 20 * 2 + 10 * 2 + histw, ny + 5 * dy + 20 + 20 * 2, 1);// dlgrect.right - dlgrect.left, dlgrect.bottom - dlgrect.top, 1);// 0, 0, 100, 200, 1);
	}
	else {
		MoveWindow(Para0(NEWD), Para1(NEWD), nw * 3 + 2 + 20 * 2 + 10 * 2 + histw, ny + 5 * dy + 20 + 20 * 2, 1);// dlgrect.right - dlgrect.left, dlgrect.bottom - dlgrect.top, 1);// 0, 0, 100, 200, 1);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CGetNewID::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10;
	sscanf_s(ptxt[HIST], "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d2", &i1, &i2, &i3, &i4, &i5, &i6, &i7, &i8, &i9, &i10);
	DispNum(m_IDnum);

	DispNum_sub(&m_hist1, i1);
	DispNum_sub(&m_hist2, i2);
	DispNum_sub(&m_hist3, i3);
	DispNum_sub(&m_hist4, i4);
	DispNum_sub(&m_hist5, i5);
	DispNum_sub(&m_hist6, i6);
	DispNum_sub(&m_hist7, i7);
	DispNum_sub(&m_hist8, i8);
	DispNum_sub(&m_hist9, i9);
	DispNum_sub(&m_hist10, i10);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
	// 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。
}

void Waku1(CDC *pDC, int x, int y, int x1, int y1)
{
	pDC->FillSolidRect(x, y, x1, 1, RGB(0, 0, 0));
	pDC->FillSolidRect(x, y, 1, y1, RGB(0, 0, 0));
	pDC->FillSolidRect(x + x1, y, 1, y1, RGB(0, 0, 0));
	pDC->FillSolidRect(x, y + y1, x1 + 1, 1, RGB(0, 0, 0));
}

void CGetNewID::DispNum_sub(CStatic *id, int idn)
{
	int i, x, x0 = 0, y0 = 46, dx = 11, dy = 20;
	bool zerof = false;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC = id->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	pDC->FillSolidRect(0, 0, 98, 33, RGB(255, 255, 255));
	if (idn>99999999)idn = 0;
	sprintf_s(buf, "%08d", idn);//8桁未満は上のけたを０で埋める
	for (i = 0; i<8; i++) {//
		if (buf[i] >= '0'&&buf[i] <= '9') {
			if (buf[i] != '0' || i == 7)zerof = true;//0以外が出てきたらフラグを立てる
			if (buf[i] == '0' && !zerof) {//０以外が出ていないときは空白
				x = 14 * dx + x0;
			}
			else {
				x = (buf[i] - '0')*dx + x0;
			}
		}
		else {
			x = 14 * dx + x0;
		}
		pDC->BitBlt(2 + i*(dx + 1), 8, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
																	  //		Waku1(pDC,0,0,101,35);
	}
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


BOOL CGetNewID::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_RETURN:
			OnBnClickedStartcap();
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

		case VK_DOWN:
			m_hist++;
			if (m_hist > 10)m_hist = 10;
			if (m_hist != 0)DispNum(m_IDnum = GetNthID(ptxt[HIST], m_hist));
			return true;
		case VK_UP:
			m_hist--;
			if (m_hist < 0)m_hist = 0;
			if (m_hist != 0)DispNum(m_IDnum = GetNthID(ptxt[HIST], m_hist));
			return true;



		}
	}	return CDialogEx::PreTranslateMessage(pMsg);
}

void CGetNewID::DispNum(int id)
{
	int i, idn, x, x0 = 0, y0 = 0, dx = 33, dy = 45;
	bool zerof = false;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC = m_id.GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);

	Resetheadfcnt = 5;
	cq0 = nq0; cq3 = -nq3;


	pDC->FillSolidRect(0, 0, 315, 66, RGB(255, 255, 255));
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
		pDC->BitBlt(i*(dx + 2) + 20, 10, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
																		//else pDC->BitBlt(i*(dx-3)+3,10,dx,dy,&MemDC,x,y0,SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


void CGetNewID::OnBnClickedStartcap()
{
	CRect rect;
	int x, y, dx, dy;

	GetClientRect(&rect);
	ClientToScreen(&rect);
	dx = GetSystemMetrics(SM_CXBORDER) + GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CXSIZEFRAME);
	dy = GetSystemMetrics(SM_CYBORDER) + GetSystemMetrics(SM_CYEDGE) + GetSystemMetrics(SM_CYSIZEFRAME) + GetSystemMetrics(SM_CYCAPTION);
	sprintf_s(ptxt[NEWD], "%d,%d", x = rect.left - dx, y = rect.top - dy);

	CDialogEx::OnOK();
}


void CGetNewID::OnBnClickedOk()
{
	CRect rw, rc;
	int x, y, dx, dy;
	GetWindowRect(&rw); // ウィンドウ全体のサイズ
	GetClientRect(&rc);
	dx = ((rw.right - rw.left) - (rc.right - rc.left)) / 2;
	dy = (rw.bottom - rw.top) - (rc.bottom - rc.top) - dx;
	ClientToScreen(&rc);
	sprintf_s(ptxt[NEWD], "%d,%d", x = rc.left - dx, y = rc.top - dy);
	CDialogEx::OnOK();
}
void CGetNewID::OnBnClickedCancel()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CDialogEx::OnCancel();
}

