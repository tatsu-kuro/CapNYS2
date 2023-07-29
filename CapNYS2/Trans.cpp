// Trans.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "Trans.h"
#include "afxdialogex.h"
#include "Header.h"

UINT BackupThread(LPVOID dummy);
UINT RestoreThread(LPVOID dummy);
bool cancelFlag;
bool doneFlag;
static bool endFlag = false;
static int lasttotal = -1;
static int lastfit = -1;
int fit, total;
char ymdstr[100];
char fns[1000][301];

// Trans ダイアログ

IMPLEMENT_DYNAMIC(Trans, CDialogEx)

Trans::Trans(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRANS, pParent)
	, title(_T(""))
	, ymd(_T(""))
	, str0(_T(""))
	, str1(_T(""))
	, str2(_T(""))
	, str3(_T(""))
	, str4(_T(""))
	, str5(_T(""))
//	, str6(_T(""))
	, str_timer(_T(""))
{

}

Trans::~Trans()
{
}

void Trans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Text(pDX, IDC_STATIC0, title);
	//  DDX_Text(pDX, IDC_STATIC1, ymd);
	DDX_Text(pDX, IDC_STATIC0, str0);
	DDX_Text(pDX, IDC_STATIC1, str1);
	DDX_Text(pDX, IDC_STATIC2, str2);
	DDX_Text(pDX, IDC_STATIC3, str3);
	DDX_Text(pDX, IDC_STATIC4, str4);
	DDX_Text(pDX, IDC_STATIC5, str5);
	//  DDX_Text(pDX, IDC_STATIC6, str6);
	DDX_Control(pDX, IDOK, OKctrl);
	DDX_Text(pDX, IDC_STATIC6, str_timer);
}


BEGIN_MESSAGE_MAP(Trans, CDialogEx)
	ON_WM_TIMER()
//	ON_STN_CLICKED(IDC_STATIC5, &Trans::OnStnClickedStatic5)
END_MESSAGE_MAP()

int timercnt = 0;
void Trans::OnTimer(UINT_PTR nIDEvent)
{
	char buf[50];
	if (!endFlag)
	{
		sprintf_s(buf, "%d", total);
		str3 = buf;
		sprintf_s(buf, "%d", fit);
		str5 = buf;
		bool updateF = false;

		if (timercnt % 10 == 0) {
			str_timer = "  ";
			updateF = true;
		}
		else if (timercnt % 10 == 5) {
			str_timer = "*  ";
			updateF = true;
		}
		//		sprintf_s(buf, "%d", timercnt);
		//		str_timer = buf;
		if (doneFlag) {
			//cancelCtrl.ShowWindow(SW_HIDE);
			OKctrl.SetWindowTextA("OK");
			endFlag = true;
			updateF = true;
			str_timer = "done !";
			//	UpdateData(false);
		}
		if (lasttotal != total || lastfit != fit) {
			updateF = true;
			//			UpdateData(false);
		}
		lasttotal = total;
		lastfit = fit;
		timercnt++;
		if (updateF)UpdateData(false);
	}

	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します	CDialogEx::OnTimer(nIDEvent);
}
bool strstr_match(char *str1, char *str2);

BOOL Trans::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//	char fn[301];
	int i;
	cancelFlag = false;
	doneFlag = false;
	endFlag = false;
	OKctrl.SetWindowTextA("Cancel");
	//	cancelCtrl.ShowWindow(SW_HIDE);
	lasttotal = -1;
	lastfit = -1;
	//cancelCtrl.ShowWindow(SW_SHOW);
	str1 = title;// TODO: ここに初期化を追加してください
	str3 = "0";
	str5 = "0";
	strcpy_s(ymdstr, ymd);
	strcat_s(ymdstr, "?????????");
	ymdstr[8] = '\0';
	str0 = ymdstr;
	int tm;
	strcpy_s(ymdstr, ymd);
	for (i = 0; strlen(ymdfns[i]) > 0; i++) {
		strcpy_s(fns[i], ymdfns[i]);
	}
	strcpy_s(fns[i], "");
/*	//	backupfit = backuptotal = 0;
	int sc = m_listavi->GetItemCount();
	if (sc == 0)return true;
	int cnt = 0;
	for (int i = 0; i < sc; i++) {
		m_listavi->GetItemText(i, 4, fn, 300);
		if (strstr_match(&fn[strlen(fn) - 18], ymd)) {
			strcpy_s(ymdfns[cnt], fn);
			strcpy_s(ymdfns[cnt + 1], "");
//			SetEN(buf, fn);//SetEN(path,fullpath)
			cnt ++ ;
		}
		if (cnt > 999)break;
	}
	*/
	
	if (strstr(title, "Back")) {//backup------------------
		str2 = "local(all):";
		str4 = "to remote:";
		UpdateData(false);
		AfxBeginThread(BackupThread, &tm);
	}
	else {
		//restore--------------------------------
		str2 = "remote(all):";
		str4 = "to local:";
		UpdateData(false);
		AfxBeginThread(RestoreThread, &tm);
	}
	SetTimer(1, 100, NULL);	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

UINT RestoreThread(LPVOID dummy) {
	CStdioFile fall, flocal, fremote;
/*	cancelFlag = false;
	bool fitF;
	total = 0;
	fit = 0;
	char ymd4[30], fn[300], buf[301], buf1[301], buf2[301];

	strcpy_s(ymd4, ymdstr);
	ymd4[4] = '\0';
	sprintf_s(buf1, "%s\\%s\\", ptxt[BKUP], ymd4);
	sprintf_s(fn, "%s\\ymd_remote.txt", CurDir);//ymd_remote.txtを作る//\\になってしまっている
	if (!fremote.Open(fn, CFile::modeCreate | CFile::modeWrite | CFile::modeRead | CFile::typeText)) {
		AfxMessageBox("ymd_remote.txtがオープンできません");
		return 0;
	}
//	total = Ymd_make(&fremote, buf1, ymdstr);//ymd_remote.txtにymdに合致するファイルを書き込む,buf1は年号フォルダ
	fremote.Abort();
//	sprintf_s(fn, "%s\\%s", CurDir, DATA_FN);
	fall.Open(fn, CFile::modeRead | CFile::typeText);
	sprintf_s(fn, "%s\\ymd_local.txt", CurDir);
	if (!flocal.Open(fn, CFile::modeCreate | CFile::modeWrite | CFile::modeRead | CFile::typeText)) {
		AfxMessageBox("ymd_local.txtがオープンできません");
		return 0;
	}
	while (fall.ReadString(buf, 99)) {
		buf[strlen(buf) - 1] = '\0';//\nを削除
//		if (strstr_match(&buf[strlen(buf) - 18], ymdstr)) {
			flocal.WriteString(buf);
			flocal.WriteString("\n");
	//	}
	}
	fall.Abort();
	flocal.Abort();
//	sprintf_s(fn, "%s\\%s", CurDir, DATA_FN);
	fall.Open(fn, CFile::modeWrite | CFile::modeRead | CFile::typeText);
	fall.SeekToEnd();
	sprintf_s(fn, "%s\\ymd_local.txt", CurDir);
	flocal.Open(fn, CFile::modeRead | CFile::typeText);
	sprintf_s(fn, "%s\\ymd_remote.txt", CurDir);
	fremote.Open(fn, CFile::modeRead | CFile::typeText);
	fit = 0;
	total = 0;
	while (fremote.ReadString(buf, 99)) {
		total++;
		if (cancelFlag)break;
		buf[strlen(buf) - 1] = '\0';
		fitF = false;
		while (flocal.ReadString(buf1, 99)) {
			if (cancelFlag)break;
			buf1[strlen(buf1) - 1] = '\0';
			if (strstr(buf1, buf)) {
				fitF = true;
				break;
			}
		}
		if (!fitF) {
			fall.WriteString(buf);//2019\\になってしまっている
			fall.WriteString("\n");
			fit++;
			sprintf_s(buf1, "%s\\gazou\\%s", CurDir, buf);
			sprintf_s(buf2, "%s\\%s", ptxt[BKUP], buf);//&buf[]:年号部分以降
			CopyFile(buf2, buf1, FALSE);
		}
		flocal.SeekToBegin();
	}

	fall.Abort();
	fremote.Abort();
	flocal.Abort();
	doneFlag = true;*/
	return 0;
}
UINT BackupThread(LPVOID dummy) {

	cancelFlag = false;
	char buf[301];
	total = 0;
	fit = 0;
//	&fn[strlen(fn) - 18];
	for (int i = 0; strlen(fns[i]) >1; i++) {
		sprintf_s(buf, "%s\\%s", ptxt[BKUP], &fns[i][strlen(fns[i]) - 18 - 8]);
		if (!IsFile(buf)) {
			CopyFile(fns[i],buf,FALSE);
			fit++;
		}
		total++;
	}

	doneFlag = true;
	return 0;
}
