// Dayretr.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "Dayretr.h"
#include "afxdialogex.h"
#include "Header.h"
// CDayretr ダイアログ

IMPLEMENT_DYNAMIC(CDayretr, CDialogEx)

CDayretr::CDayretr(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DAYRETR, pParent)
{

}

CDayretr::~CDayretr()
{
}

void CDayretr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ALLCLEARNUM, m_ac);
	DDX_Control(pDX, IDC_CLEARNUM, m_c);
	DDX_Control(pDX, IDC_DAY_YMD, m_ymd);
	DDX_Control(pDX, IDC_DAY1, m_day1);
	DDX_Control(pDX, IDC_DAY10, m_day10);
	DDX_Control(pDX, IDC_DAY2, m_day2);
	DDX_Control(pDX, IDC_DAY3, m_day3);
	DDX_Control(pDX, IDC_DAY4, m_day4);
	DDX_Control(pDX, IDC_DAY5, m_day5);
	DDX_Control(pDX, IDC_DAY6, m_day6);
	DDX_Control(pDX, IDC_DAY7, m_day7);
	DDX_Control(pDX, IDC_DAY8, m_day8);
	DDX_Control(pDX, IDC_DAY9, m_day9);
	DDX_Control(pDX, IDC_N0, m_num0);
	DDX_Control(pDX, IDC_N1, m_num1);
	DDX_Control(pDX, IDC_N2, m_num2);
	DDX_Control(pDX, IDC_N3, m_num3);
	DDX_Control(pDX, IDC_N4, m_num4);
	DDX_Control(pDX, IDC_N5, m_num5);
	DDX_Control(pDX, IDC_N6, m_num6);
	DDX_Control(pDX, IDC_N7, m_num7);
	DDX_Control(pDX, IDC_N8, m_num8);
	DDX_Control(pDX, IDC_N9, m_num9);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
}


BEGIN_MESSAGE_MAP(CDayretr, CDialogEx)
	ON_BN_CLICKED(IDC_N7, &CDayretr::OnBnClickedN7)
	ON_BN_CLICKED(IDC_N8, &CDayretr::OnBnClickedN8)
	ON_BN_CLICKED(IDC_N9, &CDayretr::OnBnClickedN9)
	ON_BN_CLICKED(IDC_N4, &CDayretr::OnBnClickedN4)
	ON_BN_CLICKED(IDC_N5, &CDayretr::OnBnClickedN5)
	ON_BN_CLICKED(IDC_N6, &CDayretr::OnBnClickedN6)
	ON_BN_CLICKED(IDC_N1, &CDayretr::OnBnClickedN1)
	ON_BN_CLICKED(IDC_N2, &CDayretr::OnBnClickedN2)
	ON_BN_CLICKED(IDC_N3, &CDayretr::OnBnClickedN3)
	ON_BN_CLICKED(IDC_N0, &CDayretr::OnBnClickedN0)
	ON_BN_CLICKED(IDC_CLEARNUM, &CDayretr::OnBnClickedClearnum)
	ON_BN_CLICKED(IDC_ALLCLEARNUM, &CDayretr::OnBnClickedAllclearnum)
	ON_WM_PAINT()
	ON_STN_CLICKED(IDC_DAY1, &CDayretr::OnStnClickedDay1)
	ON_STN_CLICKED(IDC_DAY2, &CDayretr::OnStnClickedDay2)
	ON_STN_CLICKED(IDC_DAY3, &CDayretr::OnStnClickedDay3)
	ON_STN_CLICKED(IDC_DAY4, &CDayretr::OnStnClickedDay4)
	ON_STN_CLICKED(IDC_DAY5, &CDayretr::OnStnClickedDay5)
	ON_STN_CLICKED(IDC_DAY6, &CDayretr::OnStnClickedDay6)
	ON_STN_CLICKED(IDC_DAY7, &CDayretr::OnStnClickedDay7)
	ON_STN_CLICKED(IDC_DAY8, &CDayretr::OnStnClickedDay8)
	ON_STN_CLICKED(IDC_DAY9, &CDayretr::OnStnClickedDay9)
	ON_STN_CLICKED(IDC_DAY10, &CDayretr::OnStnClickedDay10)
END_MESSAGE_MAP()

// CDayretr メッセージ ハンドラー

BOOL CDayretr::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	int y = 12;
	int nx = 20;
	int ny = y + 80;
	int dx = 72, dy = 72, nw = 71, nh = 71;
	int histw = 103, histh = 35;
	m_ymd.MoveWindow(nx, ny - 71, nw * 3 + histw + 3, 70, 1);
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

	m_ok.MoveWindow(nx + 3 * dx / 2 + 1, ny + 4 * dy, 3 * nw / 2, nh, 1);
	m_cancel.MoveWindow(nx, ny + 4 * dy, 3 * nw / 2, nh, 1);

	m_day1.MoveWindow(nx + 3 * dx, ny, histw, histh);
	m_day2.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 1, histw, histh);
	m_day3.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 2, histw, histh);
	m_day4.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 3, histw, histh);
	m_day5.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 4, histw, histh);
	m_day6.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 5, histw, histh);
	m_day7.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 6, histw, histh);
	m_day8.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 7, histw, histh);
	m_day9.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 8, histw, histh);
	m_day10.MoveWindow(nx + 3 * dx, ny + (histh + 1) * 9, histw, histh);
	// TODO:  ここに初期化を追加してください
	MoveWindow(Winw / 2 - (nw * 3 + 2 + 20 * 2 + 10 * 2) / 2, Winh / 2 - (ny + 4 * dy + 20 + nw + 20 * 2) / 2, nw * 3 + 2 + 20 * 2 + 10 * 2 + histw, ny + 5 * dy + 20 + 20 * 2, 1);// dlgrect.right - dlgrect.left, dlgrect.bottom - dlgrect.top, 1);// 0, 0, 100, 200, 1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CDayretr::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN){
		switch(pMsg->wParam) {
		case VK_RETURN:
//			OnBnClickedStartcap();
			OnOK();
			return true;// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		case '0':
		case  VK_NUMPAD0:
			OnBnClickedN0();
			return true;
		case 'J':
		case '1':
		case  VK_NUMPAD1:
			OnBnClickedN1();
			return true;
		case 'K':
		case '2':
		case  VK_NUMPAD2:
			OnBnClickedN2();
			return true;
		case 'L':
		case '3':
		case  VK_NUMPAD3:
			OnBnClickedN3();
			return true;
		case 'U':
		case '4':
		case  VK_NUMPAD4:
			OnBnClickedN4();
			return true;
		case 'I':
		case '5':
		case  VK_NUMPAD5:
			OnBnClickedN5();
			return true;
		case 'O':
		case '6':
		case  VK_NUMPAD6:
			OnBnClickedN6();
			return true;
		case '7':
		case  VK_NUMPAD7:
			OnBnClickedN7();
			return true;
		case '8':
		case  VK_NUMPAD8:
			OnBnClickedN8();
			return true;
		case '9': 
		case  VK_NUMPAD9:
			OnBnClickedN9();
			return true;
		case VK_BACK:
		case VK_CLEAR:
			OnBnClickedClearnum();
			return true;
		case VK_DELETE:
			OnBnClickedAllclearnum();
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDayretr::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CTime    cTime;
	CTimeSpan    cTimeSpan1(1, 0, 0, 0);//1日
	cTime = CTime::GetCurrentTime();    // 現在時刻
	if (ymd == 0)DispNum(ymd = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	else DispNum(ymd);
	//	cTime-=cTimeSpan1;
	DispNum_sub(&m_day1, y1 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day2, y2 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day3, y3 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day4, y4 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day5, y5 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day6, y6 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day7, y7 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day8, y8 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day9, y9 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	cTime -= cTimeSpan1;
	DispNum_sub(&m_day10, y10 = cTime.GetYear() * 10000 + cTime.GetMonth() * 100 + cTime.GetDay());
	// 描画メッセージで CDialogEx::OnPaint() を呼び出さないでください。
}


void CDayretr::DispNum(int ymd)
{
	int i, idn, x, x0 = 0, y0 = 0, dx = 33, dy = 45;
	bool zerof = false;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC = m_ymd.GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);

	pDC->FillSolidRect(0, 0, 315, 66, RGB(255, 255, 255));
	idn = ymd;
	//	sprintf_s(buf,"%08d",idn);//8桁未満は上のけたを０で埋める
	sprintf_s(buf, "%d", idn);
	strcat_s(buf, "????????");
	buf[8] = '\0';
	for (i = 0; i<8; i++) {//
		if (buf[i] >= '0'&&buf[i] <= '9') {
			x = (buf[i] - '0')*dx + x0;
		}
		else {
			x = 790;
		}
		pDC->BitBlt(i*(dx + 2) + 20, 10, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
																		//else pDC->BitBlt(i*(dx-3)+3,10,dx,dy,&MemDC,x,y0,SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	//	ReleaseDC(pDC);
	m_ymd.ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


void CDayretr::DispNum_sub(CStatic* id, int idn)
{
	int i, x, x0 = 0, y0 = 46, dx = 11, dy = 20;//x0:267 y0:49
	bool zerof = false;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC = id->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	pDC->FillSolidRect(0, 0, 98, 33, RGB(255, 255, 255));
	sprintf_s(buf, "%08d", idn);//8桁未満は上のけたを０で埋める
	for (i = 0; i<8; i++) {//
		if (buf[i] >= '0'&&buf[i] <= '9') {
			if (buf[i] != '0' || i == 7)zerof = true;//0以外が出てきたらフラグを立てる
			if (buf[i] == '0' && !zerof) {//０以外が出ていないときは空白
				x = 13 * dx + x0;
			}
			else {
				x = (buf[i] - '0')*dx + x0;
			}
		}
		else {
			x = 13 * dx + x0;
		}
		pDC->BitBlt(2 + i*(dx + 1), 5, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	id->ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


// CDayretr メッセージ ハンドラー

void CDayretr::OnBnClickedN7()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+7);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN8()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+8);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN9()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+9);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN4()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+4);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN5()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+5);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN6()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+6);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN1()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+1);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN2()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+2);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN3()
{
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10+3);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedN0()
{
	if(ymd==0)return;
	if(ymd>9999999)return;
	DispNum(ymd=ymd*10);
}


void CDayretr::OnBnClickedClearnum()
{
	DispNum(ymd=ymd/10);	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnBnClickedAllclearnum()
{
	DispNum(ymd=0);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay1()
{
	DispNum(ymd=y1);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay2()
{
	DispNum(ymd=y2);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay3()
{
	DispNum(ymd=y3);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay4()
{
	DispNum(ymd=y4);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay5()
{
	DispNum(ymd=y5);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay6()
{
	DispNum(ymd=y6);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay7()
{
	DispNum(ymd=y7);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay8()
{
	DispNum(ymd=y8);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay9()
{
	DispNum(ymd=y9);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CDayretr::OnStnClickedDay10()
{
	DispNum(ymd=y10);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
