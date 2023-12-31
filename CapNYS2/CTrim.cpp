// CTrim.cpp : 実装ファイル
//

#include "stdafx.h"
#include "CapNYS2.h"
#include "CTrim.h"
#include "afxdialogex.h"
#include "Header.h"
//#include <opencv2\opencv.hpp>
//using namespace cv;
UINT CTrimThread(LPVOID pParam);
UINT ChanIDThread(LPVOID dummy);
bool loopEnable;
int framenum;
int maxframenum;
char trimfn2[301];
char trimfn1[301];
int posa;
int posb;
int newid;
// CTrim ダイアログ

IMPLEMENT_DYNAMIC(CTrim, CDialogEx)

CTrim::CTrim(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TRIM, pParent)
	, m_resttime(_T(""))
{
	m_posa = 0;
	m_posb = 0;
	m_newid = 0;
}

CTrim::~CTrim()
{
}

void CTrim::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELETEF, m_delf);
	DDX_Text(pDX, IDC_RESTTIME, m_resttime);
}


BEGIN_MESSAGE_MAP(CTrim, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_DELETEF, &CTrim::OnBnClickedDeletef)
END_MESSAGE_MAP()


// CTrim メッセージ ハンドラー


BOOL CTrim::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ここに初期化を追加してください
	m_delf.SetCheck(0);
	strcpy_s(trimfn1, m_trimfn1);
	strcpy_s(trimfn2, m_trimfn2);
	posa = m_posa;
	posb = m_posb;
	newid = m_newid;
	loopEnable = false;

	if (posa == posb)  {
		int tm;
		AfxBeginThread(ChanIDThread, &tm);
		m_delf.ShowWindow(SW_HIDE);
		SetTimer(1, 100, NULL);
	}
	else {
		if(English)m_delf.SetWindowTextA("Keep the original file.");
		else m_delf.SetWindowTextA("元のファイルを残す時はチェック");
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


void CTrim::OnOK()
{	
	if (loopEnable)return;
	UpdateData(true);
	if (m_delf.GetCheck() == 0)checkON = false;
	else checkON = true;
	if (posa != posb) {
		int tm;
		AfxBeginThread(CTrimThread, &tm);
		SetTimer(1, 100, NULL);
	}
//	CDialogEx::OnOK();
}
UINT CTrimThread(LPVOID dummy)
{

	cv::VideoWriter rec(trimfn2, cv::VideoWriter::fourcc('W','M','V','2'), Para0(FPSN), cv::Size(CSW, CSH));

	cv::VideoCapture capture(trimfn1);//デバイスのオープン
	cv::Mat frame;
	loopEnable = true;
	framenum = 0;

	maxframenum = capture.get(cv::CAP_PROP_FRAME_COUNT);
	capture.set(cv::CAP_PROP_POS_FRAMES, posa*maxframenum / slidew);

	Sleep(100);//いるか？
	for (int i = 0; loopEnable && (i < (posb - posa)*maxframenum / slidew); i++) {
		framenum++;
		capture >> frame;
		rec << frame;	//	画像をファイルへ書き込む
	}
	loopEnable = false;
	return 0;
}

UINT ChanIDThread(LPVOID dummy)//char *fn,char *final,int id)
{
	char buf[50];

	cv::VideoWriter rec(trimfn2, cv::VideoWriter::fourcc('W', 'M', 'V', '2'), Para0(FPSN), cv::Size(Para0(CSIZ), Para1(CSIZ)));//trim ではないが、そのままとしている
	cv::VideoCapture capture(trimfn1);//デバイスのオープン
	loopEnable = true;
	framenum = 0;
	maxframenum = capture.get(cv::CAP_PROP_FRAME_COUNT);

	cv::Mat frame;
	for (;;) {
		if (!loopEnable)break;
		capture >> frame;
		if (frame.empty())break;
		framenum++;
		if (strstr(ptxt[WRID], "1")) {
			sprintf_s(buf, sizeof(buf), "ID:%08d", newid);
			rectangle(frame, cv::Point(142, Para1(CSIZ) - 20), cv::Point(0, Para1(CSIZ)), CV_RGB(255, 255, 255), -1, CV_AA, 0);
			putText(frame, buf, cv::Point(2, Para1(CSIZ) - 3), cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0), 1, CV_AA);
		}
		rec << frame;	//	画像をファイルへ書き込む
	}
	loopEnable = false;
	return 0;
}

void CTrim::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。
	if (nIDEvent == 1) {//100msecごと
		char buf[100];
		if (posb != posa) {
			sprintf_s(buf, "frames : %04d/%04d", framenum, (posb-posa)*maxframenum/Gwinw);
			m_resttime = buf;
			if (!loopEnable) {
				CDialogEx::OnOK();//OnOK();
			}
		}
		else {
			sprintf_s(buf, "frames : %04d/%04d",framenum,maxframenum);
			m_resttime = buf;
			if (!loopEnable) {
				CDialogEx::OnOK();//OnOK();
			}
		}
		UpdateData(false);
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CTrim::OnBnClickedDeletef()
{
	UpdateData(false);// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CTrim::OnCancel()
{
	// TODO: ここに特定なコードを追加するか、もしくは基底クラスを呼び出してください。
	loopEnable = false;
	CDialogEx::OnCancel();
}
