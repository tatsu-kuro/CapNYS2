// CMakeDB.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "CMakeDB.h"
#include "afxdialogex.h"
#include "mp3infp_ExportFunc.h"
#include "Header.h"
void GetNameArtist(CString cs, char *strTitle);
int Setfn2iddate(char *fn, char *iddate);
float filesec(char *fn);
// CMakeDB ダイアログ
int fcnt;
IMPLEMENT_DYNAMIC(CMakeDB, CDialogEx)

CMakeDB::CMakeDB(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAKEDB, pParent)
	, m_filesnum(_T(""))
	, m_setumei(_T(""))
{

}

CMakeDB::~CMakeDB()
{
}

void CMakeDB::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FILESNUM, m_filesnum);
	DDX_Text(pDX, IDC_SETUMEI, m_setumei);
}


BEGIN_MESSAGE_MAP(CMakeDB, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CMakeDB::OnBnClickedOk)
END_MESSAGE_MAP()

// CMakeDB メッセージ ハンドラー
void FolderTree(CString inPath, CStdioFile *fw)
{
	CFileFind Finder;
	char sizeb[301], path[300], fname[301], iddate[301], title[130], id[20], date[20], buf[500];
	CString Path = inPath + _T("\\*.*");
	BOOL bWorking = Finder.FindFile(Path, 0);
	//	int insn, size;
	while (bWorking) {
		bWorking = Finder.FindNextFile();//))break;
		CString Getpath = Finder.GetFilePath();
		CString Getname = Finder.GetFileName();
		if (!(GetFileAttributes(Getpath)&FILE_ATTRIBUTE_DIRECTORY)) {
			if (strlen(Getname) == 26 && (strstr(Getname, ".avi") || strstr(Getname, ".wmv"))) {
				fcnt++;
				//insn = list->InsertItem(0, NULL, 1);
				strcpy_s(fname, 300, Getname);
				Setfn2iddate(fname, iddate);
				strcpy_s(date, &iddate[9]);
				iddate[8] = '\0';
				strcpy_s(id, iddate);
				float len = filesec(fname);
				if (len == 0)len = 1;
				if (len >= 60)
					sprintf_s(sizeb, "%dm%02ds", int(len) / 60, int(len) % 60);
				else sprintf_s(sizeb, " %02ds", int(len));
				GetNameArtist(Getpath, title);//titlename memo
				//AfxMessageBox(title);
				strcpy_s(path, Getpath);
				sprintf_s(buf, "%s<nys>%s<nys>%s<nys>%s<nys>%s\n", id, date, sizeb, title, path);
				fw->WriteString(buf);
				//sprintf_s(buf, "%s : %04d", &buf[strlen(buf) - 29], fcnt);
				//m_filesnum = buf;
			}
		}
		else {
			if (Getname != _T(".") && Getname != _T("..")) {
				FolderTree(Getpath, fw);// フォルダの場合は自分自身を呼び直す。
			}
		}
	}
	if (fcnt > 0) {
		fcnt = 0 - fcnt;
	}
	Finder.Close();
}
UINT MakeListThread(LPVOID dummy) {
	CStdioFile fw;
	CString path;
	char dir[301];
	//	SetTimer(1, 200, NULL);
	fcnt = 0;
	if (!fw.Open(LIST_FN, CFile::modeCreate |
		CFile::modeWrite | CFile::modeRead | CFile::typeText)) {
		AfxMessageBox("list_text open err");
		return false;
	}
	if (strlen(ptxt[SAVE]) == 0) {
		wsprintf(dir, "%s\\%s", CurDir, "gazou");
	}
	else {
		wsprintf(dir, "%s", ptxt[SAVE]);
	}
	path = dir;
	FolderTree(path, &fw);
	fw.Abort();
	return true;
}
BOOL CMakeDB::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	initf = true;
//	SetTimer(1, 200, NULL);
//	int tm;
//	AfxBeginThread(MakeListThread, &tm);
	return TRUE;  // return TRUE unless you set the focus to a control
			  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CMakeDB::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {//100msecごと
		char buf[100];

		if (fcnt <= 0) {
			sprintf_s(buf, "done : %04d", -fcnt);
		}
		else {
			sprintf_s(buf, "---> : %04d", fcnt);
		}
		m_filesnum = buf;
		UpdateData(false);
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMakeDB::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if (initf) {
		SetTimer(1, 200, NULL);
		int tm;
		AfxBeginThread(MakeListThread, &tm);
		initf = false;
		return;
	}
	//KillTimer(1);
	CDialogEx::OnOK();
}

