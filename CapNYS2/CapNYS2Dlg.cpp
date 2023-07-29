
// CapNYS2Dlg.cpp : 実装ファイル
//video = cv2.VideoCapture("./movie/test.mp4")
#include "stdafx.h"
#include "CapNYS2.h"
#include "CapNYS2Dlg.h"
#include "SetMemo.h"
#include "GetID.h"
#include "GetNewID.h"
#include "Dayretr.h"
#include "Trans.h"
#include "CTrim.h"
#include "CMakeDB.h"
#include "afxdialogex.h"
#include <direct.h>
#define CapNYS2_TOP
#include "Header.h"
#include "setupapi.h"
#include "Ntddser.h"
//#include "erslib.h"


#include "mp3infp_ExportFunc.h"
//#include <ws2tcpip.h>
//#include <iphlpapi.h>
//#define WIN32_LEAN_AND_MEAN
//#pragma comment(lib, "WSock32.lib")
//#pragma comment(lib,"Iphlpapi.lib")
//#include <opencv2\opencv.hpp>
//using namespace cv;
//using namespace std;//これでofstream ifstream が定義されていません　が出なくなる

//using System;
//using System.Threading.Tasks;
//using System.IO;
//using System.Runtime.InteropServices.WindowsRuntime;
//using Windows.Devices.Bluetooth;
//using Windows.Devices.Bluetooth.GenericAttributeProfile;



#ifdef _DEBUG
//#pragma comment(lib,"opencv_core2413d.lib")
//#pragma comment(lib,"opencv_imgproc2413d.lib")
//#pragma comment(lib,"opencv_highgui2413d.lib")
//#pragma comment(lib,"opencv_objdetect2413d.lib")
//#pragma comment(lib,"opencv_contrib2413d.lib")
//#pragma comment(lib,"opencv_features2d2413d.lib")
//#pragma comment(lib,"opencv_flann2413d.lib")
//#pragma comment(lib,"opencv_gpu2413d.lib")
//#pragma comment(lib,"opencv_legacy2413d.lib")
//#pragma comment(lib,"opencv_ts2413d.lib")
//#pragma comment(lib,"opencv_video2413d.lib")
#else
//#pragma comment(lib,"opencv_core2413.lib")
//#pragma comment(lib,"opencv_imgproc2413.lib")
//#pragma comment(lib,"opencv_highgui2413.lib")
//#pragma comment(lib,"opencv_objdetect2413.lib")
//#pragma comment(lib,"opencv_ffmpeg.lib")
//#pragma comment(lib,"opencv_contrib2413.lib")
//#pragma comment(lib,"opencv_features2d2413.lib")
//#pragma comment(lib,"opencv_flann2413.lib")
//#pragma comment(lib,"opencv_gpu2413.lib")
//#pragma comment(lib,"opencv_legacy2413.lib")
//#pragma comment(lib,"opencv_ts2413.lib")
//#pragma comment(lib,"opencv_video2413.lib")
#endif
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
bool changeCSIZflag = false;
int FilesCnt();

#include "setupapi.h"
#include <combaseapi.h>

#pragma comment(lib, "setupapi.lib")

//const GUID GUID_DEVINTERFACE_COMPORT =
//{ 0x86e0d1e0, 0x8089, 0x11d0, 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 };
int EnumCommPort(){//(EnumCommPortFuncDef* func,void* temp){
        HDEVINFO hDevInfo;
        DWORD MemberIndex=0;
        SP_DEVINFO_DATA Data={ sizeof(SP_DEVINFO_DATA) };
        int max=0;
        hDevInfo=SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT,0,0,DIGCF_PRESENT | DIGCF_DEVICEINTERFACE); // デバイス情報セットを取得
        if(hDevInfo==0) //      デバイス情報セットが取得できなかった場合
                return 0;
        Data.cbSize=sizeof(Data);

        while( SetupDiEnumDeviceInfo(hDevInfo,max,&Data)){  // デバイスインターフェイスの取得
                TCHAR* port=0;
                TCHAR* other=0;

                DWORD dataT;
                DWORD size;
                LPTSTR buf;
                TCHAR name[256];
//      COMポート名の取得
                HKEY key=SetupDiOpenDevRegKey(hDevInfo,&Data,DICS_FLAG_GLOBAL,0,DIREG_DEV,KEY_QUERY_VALUE);
                if(key){
                        DWORD type=0;
                        size=sizeof(name);
                        RegQueryValueEx(key,_T("PortName"),NULL,&type,(LPBYTE)name,&size);
                        port=name;
                }
//      デバイスの説明を取得
                size=0;
                buf=NULL;
                while(!SetupDiGetDeviceRegistryProperty(hDevInfo,&Data,SPDRP_DEVICEDESC,&dataT,(PBYTE)buf,size,&size)){
                        if(GetLastError()==ERROR_INSUFFICIENT_BUFFER){
                                if(buf)
                                        LocalFree(buf);
                                buf=(LPTSTR)LocalAlloc(LPTR,size*2);
                        }else
                                break;
                }
  //              func(port,buf,temp);    //      コールバック関数の呼び出し
				AfxMessageBox(buf);
                if(buf)
                        LocalFree(buf);
                ++max;
        }
        SetupDiDestroyDeviceInfoList(hDevInfo); //      デバイス情報セットを解放
        return max;
}
char comStrArray[100][255];
int comList(void)
{
	int count = 0;
	HDEVINFO hDevInfo = SetupDiGetClassDevs(&GUID_DEVINTERFACE_COMPORT, 0, 0, DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);
	if (hDevInfo)
	{
		SP_DEVINFO_DATA data = { sizeof(data) };
		while (SetupDiEnumDeviceInfo(hDevInfo, count++, &data))
		{
			HKEY key = SetupDiOpenDevRegKey(hDevInfo, &data, DICS_FLAG_GLOBAL, 0, DIREG_DEV, KEY_QUERY_VALUE);
			if (key)
			{
				TCHAR name[256];
				DWORD size = sizeof(name);
				RegQueryValueEx(key, TEXT("PortName"), NULL, NULL, (LPBYTE)name, &size);
				//_tprintf(TEXT("%s"), name);
//				AfxMessageBox(name);
				comArray[count - 1] = atoi(&name[3]);
//				AfxMessageBox(name);

				if (SetupDiGetDeviceRegistryProperty(hDevInfo, &data, SPDRP_DEVICEDESC, NULL, (LPBYTE)name, sizeof(name), NULL)) {
					//comStrArray[count-1] = to_string(comArray[count-1]) + name;
					sprintf_s(comStrArray[count - 1], "COM%d( %s)", comArray[count - 1], name);
				}
				else {
					sprintf_s(comStrArray[count - 1], "COM%d( %s)", comArray[count - 1], "?");
				}

		/*		if (SetupDiGetDeviceRegistryProperty(hDevInfo, &data, SPDRP_HARDWAREID, NULL, (LPBYTE)name, sizeof(name), NULL))
					_tprintf(TEXT(", %s\n"), name);
				else
					_tprintf(TEXT("\n"));*/
//
//				AfxMessageBox(TEXT(comStrArray[count-1]));
			}
		}
		comArray[count - 1] = 0;
		SetupDiDestroyDeviceInfoList(hDevInfo);
	}

	int tmp;
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			if (comArray[j] < comArray[j + 1]) {
				tmp = comArray[j];
				comArray[j] = comArray[j + 1];
				comArray[j + 1] = tmp;
			}
		}
	}

	return count;
}

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCapNYS2Dlg ダイアログ



CCapNYS2Dlg::CCapNYS2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CAPNYS2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCapNYS2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CURPLAY, m_curplay);
	DDX_Control(pDX, IDC_CURRENTID, m_currentid);
	DDX_Control(pDX, IDC_CUTMOVIE, m_cutmovie);
	DDX_Control(pDX, IDC_MOVIEPT, m_moviept);
	DDX_Control(pDX, IDC_RESETHEAD, m_resethead);
	DDX_Control(pDX, IDC_RESETREC, m_resetrec);
	//  DDX_Control(pDX, IDC_STARTCAP, m_startcap);
	DDX_Control(pDX, IDC_STOPCAP, m_stopcap);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_LISTAVI, m_listavi);
	DDX_Control(pDX, IDC_LISTCURRENT, m_listcurrent);
	DDX_Control(pDX, IDC_LISTREF, m_listref);
	DDX_Control(pDX, IDC_TIMETRIM, m_timetrim);
	DDX_Control(pDX, IDC_RECORD, m_record);
	DDX_Control(pDX, IDC_TOTALNUM, m_totalnum);
	DDX_Control(pDX, IDC_ERASEBUT, m_erasebut);
	DDX_Control(pDX, IDC_MEMO, m_memo);
	DDX_Control(pDX, IDC_CHANID, m_chanid);
	DDX_Control(pDX, IDC_SETID, m_setid);
	DDX_Control(pDX, IDC_SAVE, m_save);
	DDX_Control(pDX, IDC_BACKUP, m_backup);
	DDX_Control(pDX, IDC_BACKUPFOLDER, m_backupfolder);
	DDX_Control(pDX, IDC_MENU, m_menu);
	DDX_Control(pDX, IDC_SENSORMODE, m_sensormode);
}

BEGIN_MESSAGE_MAP(CCapNYS2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_STOPCAP, &CCapNYS2Dlg::OnBnClickedStopcap)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RESETREC, &CCapNYS2Dlg::OnBnClickedResetrec)
	ON_BN_CLICKED(IDC_RESETHEAD, &CCapNYS2Dlg::OnBnClickedResethead)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDCANCEL, &CCapNYS2Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_LIST, &CCapNYS2Dlg::OnBnClickedList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LISTAVI, &CCapNYS2Dlg::OnColumnclickListavi)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LISTAVI, &CCapNYS2Dlg::OnItemchangingListavi)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTAVI, &CCapNYS2Dlg::OnDblclkListavi)
	ON_NOTIFY(NM_RCLICK, IDC_LISTAVI, &CCapNYS2Dlg::OnRclickListavi)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LISTCURRENT, &CCapNYS2Dlg::OnItemchangingListcurrent)
	ON_NOTIFY(NM_RCLICK, IDC_LISTCURRENT, &CCapNYS2Dlg::OnRclickListcurrent)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTCURRENT, &CCapNYS2Dlg::OnDblclkListcurrent)
	ON_NOTIFY(LVN_ITEMCHANGING, IDC_LISTREF, &CCapNYS2Dlg::OnItemchangingListref)
	ON_NOTIFY(NM_RCLICK, IDC_LISTREF, &CCapNYS2Dlg::OnRclickListref)
	ON_NOTIFY(NM_DBLCLK, IDC_LISTREF, &CCapNYS2Dlg::OnDblclkListref)
	ON_BN_CLICKED(IDC_CURPLAY, &CCapNYS2Dlg::OnBnClickedCurplay)
	ON_BN_CLICKED(IDC_CUTMOVIE, &CCapNYS2Dlg::OnBnClickedCutmovie)
	ON_COMMAND(ID_POPUP_CHANGEID2, &CCapNYS2Dlg::OnPopupChangeid2)
	ON_COMMAND(ID_POPUP_CHANGEID3, &CCapNYS2Dlg::OnPopupChangeid3)
	ON_COMMAND(ID_POPUP_COPY, &CCapNYS2Dlg::OnPopupCopy)
	ON_COMMAND(ID_POPUP_COPY2, &CCapNYS2Dlg::OnPopupCopy2)
	ON_COMMAND(ID_POPUP_COPY3, &CCapNYS2Dlg::OnPopupCopy3)
	ON_COMMAND(ID_POPUP_DELETE, &CCapNYS2Dlg::OnPopupDelete)
	ON_COMMAND(ID_POPUP_DELETE2, &CCapNYS2Dlg::OnPopupDelete2)
	ON_COMMAND(ID_POPUP_DELETE3, &CCapNYS2Dlg::OnPopupDelete3)
	ON_COMMAND(ID_POPUP_EDITMEMO, &CCapNYS2Dlg::OnPopupEditmemo)
	ON_COMMAND(ID_POPUP_EDITMEMO2, &CCapNYS2Dlg::OnPopupEditmemo2)
	ON_COMMAND(ID_POPUP_EDITMEMO3, &CCapNYS2Dlg::OnPopupEditmemo3)
	ON_BN_CLICKED(IDC_RECORD, &CCapNYS2Dlg::OnClickedRecord)
//	ON_STN_CLICKED(IDC_NEXTCOM, &CCapNYS2Dlg::OnStnClickedNextcom)
	ON_COMMAND(ID_BKUP, &CCapNYS2Dlg::OnBkup)
	ON_COMMAND(ID_SETBKF, &CCapNYS2Dlg::OnSetbkf)
	ON_BN_CLICKED(IDC_ERASEBUT, &CCapNYS2Dlg::OnClickedErasebut)
	ON_COMMAND(ID_POPUP_CHANID9, &CCapNYS2Dlg::OnPopupChanid9)
	ON_BN_CLICKED(IDC_MEMO, &CCapNYS2Dlg::OnClickedMemo)
	ON_BN_CLICKED(IDC_CHANID, &CCapNYS2Dlg::OnClickedChanid)
	ON_BN_CLICKED(IDC_SETID, &CCapNYS2Dlg::OnClickedSetid)
	ON_BN_CLICKED(IDC_SAVE, &CCapNYS2Dlg::OnClickedSave)
	ON_BN_CLICKED(IDC_BACKUP, &CCapNYS2Dlg::OnClickedBackup)
	ON_BN_CLICKED(IDC_BACKUPFOLDER, &CCapNYS2Dlg::OnClickedBackupfolder)
	ON_BN_CLICKED(IDC_MENU, &CCapNYS2Dlg::OnClickedMenu)
//	ON_COMMAND(ID_POPUP_DEINTER, &CCapNYS2Dlg::OnPopupDeinter)
	ON_COMMAND(ID_POPUP_HELP, &CCapNYS2Dlg::OnPopupHelp)
//	ON_COMMAND(ID_POPUP_DEINTEROFF, &CCapNYS2Dlg::OnPopupDeinteroff)
//	ON_COMMAND(ID_POPUP_GYRO6050, &CCapNYS2Dlg::OnPopupArduino)
	ON_COMMAND(ID_POPUP_GYROOFF, &CCapNYS2Dlg::OnPopupManual)
	ON_COMMAND(ID_POPUP_DIRECTION1, &CCapNYS2Dlg::OnPopupDirection1)
	ON_COMMAND(ID_POPUP_DIRECTION2, &CCapNYS2Dlg::OnPopupDirection2)
	ON_COMMAND(ID_POPUP_DIRECTION3, &CCapNYS2Dlg::OnPopupDirection3)
	ON_COMMAND(ID_POPUP_DIRECTION4, &CCapNYS2Dlg::OnPopupDirection4)
	ON_COMMAND(ID_POPUP_DIRECTION5, &CCapNYS2Dlg::OnPopupDirection5)
	ON_COMMAND(ID_POPUP_DIRECTION6, &CCapNYS2Dlg::OnPopupDirection6)
	ON_COMMAND(ID_POPUP_DIRECTION7, &CCapNYS2Dlg::OnPopupDirection7)
	ON_COMMAND(ID_POPUP_DIRECTION8, &CCapNYS2Dlg::OnPopupDirection8)
	ON_COMMAND(ID_POPUP_CAMERA1, &CCapNYS2Dlg::OnPopupCamera1)
	ON_COMMAND(ID_POPUP_CAMERA2, &CCapNYS2Dlg::OnPopupCamera2)
	ON_COMMAND(ID_POPUP_CAMERA3, &CCapNYS2Dlg::OnPopupCamera3)
	ON_COMMAND(ID_POPUP_CAMERA4, &CCapNYS2Dlg::OnPopupCamera4)
	ON_COMMAND(ID_POPUP_CAMERA5, &CCapNYS2Dlg::OnPopupCamera5)
	ON_COMMAND(ID_SETSAVEF, &CCapNYS2Dlg::OnSetsavef)
	ON_COMMAND(ID_TOUROKU, &CCapNYS2Dlg::OnTouroku)
	ON_COMMAND(ID_GYROSMART, &CCapNYS2Dlg::OnPopupiPhone)

//ON_COMMAND(ID_POPUP_M5, &CCapNYS2Dlg::OnPopupM5)
//ON_BN_CLICKED(IDC_CHANCOM, &CCapNYS2Dlg::OnClickedChancom)
ON_COMMAND(ID_MPU_COM1, &CCapNYS2Dlg::OnMpuCom1)
ON_COMMAND(ID_MPU_COM2, &CCapNYS2Dlg::OnMpuCom2)
ON_COMMAND(ID_MPU_COM3, &CCapNYS2Dlg::OnMpuCom3)
ON_COMMAND(ID_MPU_COM4, &CCapNYS2Dlg::OnMpuCom4)
ON_COMMAND(ID_MPU_COM5, &CCapNYS2Dlg::OnMpuCom5)
ON_COMMAND(ID_MPU_COM6, &CCapNYS2Dlg::OnMpuCom6)
ON_COMMAND(ID_MPU_COM7, &CCapNYS2Dlg::OnMpuCom7)
ON_COMMAND(ID_MPU_COM8, &CCapNYS2Dlg::OnMpuCom8)
ON_COMMAND(ID_MPU_COM9, &CCapNYS2Dlg::OnMpuCom9)
ON_COMMAND(ID_M5_COM1, &CCapNYS2Dlg::OnM5Com1)
ON_COMMAND(ID_M5_COM2, &CCapNYS2Dlg::OnM5Com2)
ON_COMMAND(ID_M5_COM3, &CCapNYS2Dlg::OnM5Com3)
ON_COMMAND(ID_M5_COM4, &CCapNYS2Dlg::OnM5Com4)
ON_COMMAND(ID_M5_COM5, &CCapNYS2Dlg::OnM5Com5)
ON_COMMAND(ID_M5_COM6, &CCapNYS2Dlg::OnM5Com6)
ON_COMMAND(ID_M5_COM7, &CCapNYS2Dlg::OnM5Com7)
ON_COMMAND(ID_M5_COM8, &CCapNYS2Dlg::OnM5Com8)
ON_COMMAND(ID_M5_COM9, &CCapNYS2Dlg::OnM5Com9)
ON_COMMAND(ID_POPUP_IPCAMERA, &CCapNYS2Dlg::OnPopupIpcamera)
ON_COMMAND(ID_IPCAMERA, &CCapNYS2Dlg::OnIpcamera)
END_MESSAGE_MAP()

HMODULE m_hMp3infpDll;
LPMP3INFP_GETVER m_mp3infp_GetVer;
LPMP3INFP_LOAD m_mp3infp_Load;
LPMP3INFP_VIEWPROP m_mp3infp_ViewProp;
LPMP3INFP_GETTYPE m_mp3infp_GetType;
LPMP3INFP_GETVALUE m_mp3infp_GetValue;
LPMP3INFP_MP3_GETTAGTYPE m_mp3infp_mp3_GetTagType;
LPMP3INFP_SETCONF m_mp3infp_SetConf;
LPMP3INFP_SETVALUE m_mp3infp_SetValue;
LPMP3INFP_SAVE m_mp3infp_Save;
LPMP3INFP_MP3_MAKEID3V1 m_mp3infp_mp3_MakeId3v1;
LPMP3INFP_MP3_DELID3V1 m_mp3infp_mp3_DelId3v1;
LPMP3INFP_MP3_MAKEID3V2 m_mp3infp_mp3_MakeId3v2;
LPMP3INFP_MP3_DELID3V2 m_mp3infp_mp3_DelId3v2;
LPMP3INFP_MP3_MAKERMP m_mp3infp_mp3_MakeRMP;
LPMP3INFP_MP3_DELRMP m_mp3infp_mp3_DelRMP;
LPMP3INFP_MP3_MAKEAPETAG m_mp3infp_mp3_MakeApeTag;
LPMP3INFP_MP3_DELAPETAG m_mp3infp_mp3_DelApeTag;

bool setmp3infp(char *fn, char *strTitle)//, char *strArtist)
{
#ifdef _WIN64
//	AfxMessageBox("64");
	m_hMp3infpDll = LoadLibrary("mp3infp64.dll");

#else
//	AfxMessageBox("32");
	m_hMp3infpDll = LoadLibrary("mp3infp86.dll");
#endif
	if (m_hMp3infpDll == NULL)
	{
		AfxMessageBox("mp3infpをロードできませんでした");
		return false;
	}

	m_mp3infp_GetVer = (LPMP3INFP_GETVER)GetProcAddress(m_hMp3infpDll, "mp3infp_GetVer");
	// バージョンチェック
	if (m_mp3infp_GetVer && (m_mp3infp_GetVer() < 0x0243))
	{
		AfxMessageBox("mp3infp v2.43以上が必要です");
		FreeLibrary(m_hMp3infpDll);
		return false;
	}

	m_mp3infp_Load = (LPMP3INFP_LOAD)GetProcAddress(m_hMp3infpDll, "mp3infp_Load");
	m_mp3infp_ViewProp = (LPMP3INFP_VIEWPROP)GetProcAddress(m_hMp3infpDll, "mp3infp_ViewProp");
	m_mp3infp_GetType = (LPMP3INFP_GETTYPE)GetProcAddress(m_hMp3infpDll, "mp3infp_GetType");
	m_mp3infp_GetValue = (LPMP3INFP_GETVALUE)GetProcAddress(m_hMp3infpDll, "mp3infp_GetValue");
	m_mp3infp_mp3_GetTagType = (LPMP3INFP_MP3_GETTAGTYPE)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_GetTagType");
	m_mp3infp_SetConf = (LPMP3INFP_SETCONF)GetProcAddress(m_hMp3infpDll, "mp3infp_SetConf");
	m_mp3infp_SetValue = (LPMP3INFP_SETVALUE)GetProcAddress(m_hMp3infpDll, "mp3infp_SetValue");
	m_mp3infp_Save = (LPMP3INFP_SAVE)GetProcAddress(m_hMp3infpDll, "mp3infp_Save");
	m_mp3infp_mp3_MakeId3v1 = (LPMP3INFP_MP3_MAKEID3V1)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeId3v1");
	m_mp3infp_mp3_DelId3v1 = (LPMP3INFP_MP3_DELID3V1)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelId3v1");
	m_mp3infp_mp3_MakeId3v2 = (LPMP3INFP_MP3_MAKEID3V2)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeId3v2");
	m_mp3infp_mp3_DelId3v2 = (LPMP3INFP_MP3_DELID3V2)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelId3v2");
	m_mp3infp_mp3_MakeRMP = (LPMP3INFP_MP3_MAKERMP)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeRMP");
	m_mp3infp_mp3_DelRMP = (LPMP3INFP_MP3_DELRMP)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelRMP");
	m_mp3infp_mp3_MakeApeTag = (LPMP3INFP_MP3_MAKEAPETAG)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeApeTag");
	m_mp3infp_mp3_DelApeTag = (LPMP3INFP_MP3_DELAPETAG)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelApeTag");
	//DLLのロード
	if (m_mp3infp_Load(NULL, fn) != ERROR_SUCCESS)
	{
		AfxMessageBox("ロード失敗");
		FreeLibrary(m_hMp3infpDll);
		return false;
	}

//	DWORD dwTagType;
	DWORD dwType = m_mp3infp_GetType();
	switch (dwType) {

	case MP3INFP_FILE_AVI:
		m_mp3infp_SetValue("ISBJ", "");
		m_mp3infp_SetValue("INAM", (LPCTSTR)strTitle);
//		m_mp3infp_SetValue("IART", (LPCTSTR)strArtist);
		break;
	case MP3INFP_FILE_VQF:
	case MP3INFP_FILE_WMA:
	case MP3INFP_FILE_OGG:
	case MP3INFP_FILE_APE:
	case MP3INFP_FILE_MP4:
		m_mp3infp_SetValue("INAM", (LPCTSTR)strTitle);
//		m_mp3infp_SetValue("IART", (LPCTSTR)strArtist);
		break;
	case MP3INFP_FILE_UNKNOWN:
	default:
		break;
	}
	// Save
	DWORD dwRet = m_mp3infp_Save((LPCTSTR)fn);
	if (dwRet != ERROR_SUCCESS)
	{
		CString strMes;
		strMes.Format("Fail code=%08x", dwRet);
		AfxMessageBox(strMes);
		FreeLibrary(m_hMp3infpDll);
		return false;
	}
	FreeLibrary(m_hMp3infpDll);
	return true;
}
//void CMp3infp_sample2Dlg::OnButtonLoad() 
//void GetNameArtist(char *fn, char *strTitle, char *strArtist)
void GetNameArtist(CString cs, char *strTitle)

{
	char fn[301]; 
	strcpy_s(fn, 301,cs);
	strcpy_s(strTitle,301, "");
//	strcpy_s(strArtist, 301, "");

#ifdef _WIN64
	//	AfxMessageBox("64");
	m_hMp3infpDll = LoadLibrary("mp3infp64.dll");

#else
	//	AfxMessageBox("32");
	m_hMp3infpDll = LoadLibrary("mp3infp86.dll");
#endif
//	m_hMp3infpDll = LoadLibrary("mp3infp.dll");
	if (m_hMp3infpDll == NULL)
	{
		AfxMessageBox("mp3infpをロードできませんでした");
		return;// false;
	}

	m_mp3infp_GetVer = (LPMP3INFP_GETVER)GetProcAddress(m_hMp3infpDll, "mp3infp_GetVer");
	// バージョンチェック
	if (m_mp3infp_GetVer && (m_mp3infp_GetVer() < 0x0243))
	{
		AfxMessageBox("mp3infp v2.43以上が必要です");
		FreeLibrary(m_hMp3infpDll);
		return;// false;
	}

	m_mp3infp_Load = (LPMP3INFP_LOAD)GetProcAddress(m_hMp3infpDll, "mp3infp_Load");
	m_mp3infp_ViewProp = (LPMP3INFP_VIEWPROP)GetProcAddress(m_hMp3infpDll, "mp3infp_ViewProp");
	m_mp3infp_GetType = (LPMP3INFP_GETTYPE)GetProcAddress(m_hMp3infpDll, "mp3infp_GetType");
	m_mp3infp_GetValue = (LPMP3INFP_GETVALUE)GetProcAddress(m_hMp3infpDll, "mp3infp_GetValue");
	m_mp3infp_mp3_GetTagType = (LPMP3INFP_MP3_GETTAGTYPE)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_GetTagType");
	m_mp3infp_SetConf = (LPMP3INFP_SETCONF)GetProcAddress(m_hMp3infpDll, "mp3infp_SetConf");
	m_mp3infp_SetValue = (LPMP3INFP_SETVALUE)GetProcAddress(m_hMp3infpDll, "mp3infp_SetValue");
	m_mp3infp_Save = (LPMP3INFP_SAVE)GetProcAddress(m_hMp3infpDll, "mp3infp_Save");
	m_mp3infp_mp3_MakeId3v1 = (LPMP3INFP_MP3_MAKEID3V1)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeId3v1");
	m_mp3infp_mp3_DelId3v1 = (LPMP3INFP_MP3_DELID3V1)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelId3v1");
	m_mp3infp_mp3_MakeId3v2 = (LPMP3INFP_MP3_MAKEID3V2)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeId3v2");
	m_mp3infp_mp3_DelId3v2 = (LPMP3INFP_MP3_DELID3V2)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelId3v2");
	m_mp3infp_mp3_MakeRMP = (LPMP3INFP_MP3_MAKERMP)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeRMP");
	m_mp3infp_mp3_DelRMP = (LPMP3INFP_MP3_DELRMP)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelRMP");
	m_mp3infp_mp3_MakeApeTag = (LPMP3INFP_MP3_MAKEAPETAG)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_MakeApeTag");
	m_mp3infp_mp3_DelApeTag = (LPMP3INFP_MP3_DELAPETAG)GetProcAddress(m_hMp3infpDll, "mp3infp_mp3_DelApeTag");
	//DLLのロード
	if (m_mp3infp_Load(NULL, fn) != ERROR_SUCCESS)
	{
		AfxMessageBox("ロード失敗");
		FreeLibrary(m_hMp3infpDll);
		return;// false;
	}

	// Load
	DWORD dwRet = m_mp3infp_Load(NULL, (LPCTSTR)fn);
	if (dwRet != ERROR_SUCCESS)
	{
		CString strMes;
		strMes.Format("Fail code=%08x", dwRet);
		AfxMessageBox(strMes);
		return;
	}
	char *value;
//	DWORD dwTagType;
	DWORD dwType = m_mp3infp_GetType();
	switch (dwType) {


	case MP3INFP_FILE_AVI:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle, 301, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;
	case MP3INFP_FILE_WMA:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle, 301, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;
	case MP3INFP_FILE_MP4:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle, 301, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;
	case MP3INFP_FILE_OGG:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle, 301, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;
	case MP3INFP_FILE_WAV:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle,300, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;
	case MP3INFP_FILE_VQF:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle, 301, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;
	case MP3INFP_FILE_APE:
		m_mp3infp_GetValue("INAM", &value);
		strcpy_s(strTitle, 301, value);
	//	m_mp3infp_GetValue("IART", &value);
	//	strcpy_s(strArtist, 301, value);
		break;

	case MP3INFP_FILE_UNKNOWN:
	default:
		break;
	}
	FreeLibrary(m_hMp3infpDll);
}
int GetDeviceN() {
	int i;
	for (i = 0; i < 10; i++) {
		cv::VideoCapture capture(i);//デバイスのオープン
		if (!capture.isOpened()) {
			capture.release();
			return i;
		}
		capture.release();
		Sleep(200);
	}
	return i;
}

// CCapNYS2Dlg メッセージ ハンドラー
int getfsize(char *Path)//fullpathで飛んでくる
{
	CFileFind Finder;
	int size;
	BOOL bWorking = Finder.FindFile(Path, 0);
	if (bWorking) {
		Finder.FindNextFile();//))break;
		CString Getpath = Finder.GetFilePath();
		CString Getname = Finder.GetFileName();
		size = Finder.GetLength();
		Finder.Close();
		return size;
	}
	Finder.Close();
	return 0;
}

float filesec(char *fn) {//ビデオファイルの長さ(秒）を返す
	
	float l1, l2;
	char buf[301];
	if (strlen(ptxt[SAVE]) == 0) {
		sprintf_s(buf, "%s\\%s\\%s", CurDir, "gazou",fn);
	}
	else {
		sprintf_s(buf, "%s\\%s", ptxt[SAVE],fn);
	}
	cv::VideoCapture ocvfile(buf);// *fn.GetString);//デバイスのオープン
	l1 = ocvfile.get(cv::CAP_PROP_FRAME_COUNT);
	l2 = ocvfile.get(cv::CAP_PROP_FPS);
#ifdef _DEBUG
	sprintf_s(buf, "%s:%.0f/%.0f", fn, l1 / l2);// timeGetTime() - st);
	AfxMessageBox(buf);
#endif	
	return l1 / l2;// ocvfilelength;
}

float fullfilesec(char *fn) {//フルパスのビデオファイルの長さ(秒）を返す
//	char buf[301];
	float l1, l2;
	cv::VideoCapture ocvfile(fn);// *fn.GetString);//デバイスのオープン
	l1 = ocvfile.get(cv::CAP_PROP_FRAME_COUNT);
	l2 = ocvfile.get(cv::CAP_PROP_FPS);
	//	sprintf_s(buf, "%s:%f/%f:", fn, l1, l2);// ocvfilelength);
	//	AfxMessageBox(buf);
	return l1 / l2;// ocvfilelength;
}

void SetlistaviSize_bit(CListCtrl* all)
{//sizeが0ならkB単位で書き込む
	int i, sc, len;
	char size[51], temp[301];
	sc = all->GetItemCount();
	for (i = 0; i<sc; i++) {
		all->GetItemText(i, 2, size, 50);
		if (strlen(size) == 1 && strstr(size, "0")) {//strstr(temp,ids)){
			all->GetItemText(i, 4, temp, 300);
			len = getfsize(temp);
			wsprintf(size, "%d", len / 1000);
			all->SetItemText(i, 2, size);//
		}
	}
}

void SetlistaviSize0(CListCtrl* all)
{//sizeが0ならkB単位で書き込む
	int i, sc;
	char size[51], temp[301];
	sc = all->GetItemCount();
	int st= timeGetTime();
	for (i = 0; i<sc; i++) {
		all->GetItemText(i, 2, size, 50);
		if (strlen(size) == 1 && strstr(size, "0")) {//strstr(temp,ids)){
			all->GetItemText(i, 4, temp, 300);
			//len = getfsize(temp);
			//wsprintf(size, "%d", len / 1000);
			float len = fullfilesec(temp);
			if (len == 0)len = 1.0;
			if (len >= 60)
				sprintf_s(size, "%dm%02ds", int(len) / 60, int(len) % 60);
			else sprintf_s(size, " %02ds", int(len)); // filiesec(temp));
			//sprintf_s(size, "%.0fm%02ds", len / 60, int(len)% 60);// fullfilesec(temp));
			all->SetItemText(i, 2, size);//
//			AfxMessageBox(temp);
		}
	}
//	sprintf_s(temp,"%d",timeGetTime() - st);
	//AfxMessageBox(temp);
}

/*void LoadComList()
{
	int ai=0;
	char buf[500];
	CStdioFile ff;
	char path[] = "\"comlist.exe > comlist.txt\"";
	system(path);
	if (!ff.Open("comlist.txt", CFile::modeRead | CFile::typeText))
	{
		AfxMessageBox("no comlist.txt!");
	}
	else {
		while (ff.ReadString(buf, 395)) {
			if (buf[0] == 'C' && buf[1] == 'O' && strstr(buf, "(")) {
				for (int i = 0; i < 10; i++) {
					if (buf[i] == '(') {
						buf[i] = 0;
						comArray[ai++] = atoi(&buf[3]);
						break;
					}
					if (i==9)comArray[ai++] = 0;//不正な文字列のとき
				}
			}
		}
		comArray[ai++] = 0;
		ff.Abort();
	}
//	sprintf_s(buf, "%d,%d,%d,%d,%d,%d,%d", comArray[0], comArray[1], comArray[2], comArray[3], comArray[4], comArray[5], comArray[6]);
//	AfxMessageBox(buf);
}*/

BOOL CCapNYS2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	SetWindowText(Vertxt);

	int senm = 0;
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定
	
	GetCurrentDirectory(300, CurDir);
	cameran = GetDeviceN();

	comList();

	if (Para0(SENM) == 1 || Para0(SENM) == 2) {
		int i;
		for (i = 0; comArray[i]!=0; i++) {
			if (Para0(COMP) == comArray[i])break;
		}
		if (comArray[i] == 0) {//ptxt[COMP]が存在しないときは、comArray[0]を設定。
			sprintf_s(ptxt[COMP], "%d", comArray[0]);
		}
	}
	ShowWindow(SW_MAXIMIZE);
	grayRGB = GetSysColor(COLOR_BTNFACE);
	CRect rect;
	m_ok.ShowWindow(SW_HIDE);
	GetClientRect(&rect);
	SetCtrlPos(rect.right, rect.bottom);

	bmp_button_record.LoadBitmapA(IDB_BM_RECORD);
	m_record.SetBitmap(bmp_button_record);
	bmp_button_newid.LoadBitmapA(IDB_BM_NEWID);
	m_setid.SetBitmap(bmp_button_newid);
	bmp_button_alllist.LoadBitmapA(IDB_BM_ALLLIST);
	m_list.SetBitmap(bmp_button_alllist);
	bmp_button_resetrec.LoadBitmapA(IDB_BM_RESETREC);
	m_resetrec.SetBitmap(bmp_button_resetrec);
	bmp_button_gomi.LoadBitmapA(IDB_BM_GOMI);
	m_erasebut.SetBitmap(bmp_button_gomi);
	bmp_button_memo.LoadBitmapA(IDB_BM_MEMO);
	m_memo.SetBitmap(bmp_button_memo);
	bmp_button_menu.LoadBitmapA(IDB_BM_MENU);
	m_menu.SetBitmap(bmp_button_menu);

	bmp_button_changeid.LoadBitmapA(IDB_BM_CHANID);
	m_chanid.SetBitmap(bmp_button_changeid);
	if (strstr(ptxt[SENM], "0"))
	{
		bmp_button_head.LoadBitmapA(IDB_SISEI);
	}
	else {
		bmp_button_head.LoadBitmapA(IDB_BM_HEAD);
	}
	m_resethead.SetBitmap(bmp_button_head);
	bmp_button_exit.LoadBitmapA(IDB_BM_EXIT);
	m_cancel.SetBitmap(bmp_button_exit);
	bmp_button_stop.LoadBitmapA(IDB_BM_STOP);
	m_stopcap.SetBitmap(bmp_button_stop);
	//	bmp_button_start.LoadBitmapA(IDB_BM_START);
	//	m_startcap.SetBitmap(bmp_button_start);
	bmp_button_curplay.LoadBitmapA(IDB_BM_CURPLAY);
	m_curplay.SetBitmap(bmp_button_curplay);
	bmp_button_trim.LoadBitmapA(IDB_BM_TRIM);
	m_cutmovie.SetBitmap(bmp_button_trim);
	bmp_button_save.LoadBitmapA(IDB_BM_SAVE);
	m_save.SetBitmap(bmp_button_save);
	bmp_button_backup.LoadBitmapA(IDB_BM_BACKUP);
	m_backup.SetBitmap(bmp_button_backup);
	bmp_button_backupfolder.LoadBitmapA(IDB_BM_BACKUPFOLDER);
	m_backupfolder.SetBitmap(bmp_button_backupfolder);
	_mkdir("gazou");
	IDnum = 0;
	if (Para1(FONT) > 0) {
		//char *font[10] = { "nonfont","Arial","Courier","Courier New","Times New Roman","Helvetica" };
		if (Para1(FONT) == 1)m_font.CreatePointFont(Para0(FONT), _T("ＭＳ ゴシック"));
		else if (Para1(FONT) == 2)m_font.CreatePointFont(Para0(FONT), _T("ＭＳ 明朝"));
		else if (Para1(FONT) == 3)m_font.CreatePointFont(Para0(FONT), _T("Arial"));
		else if (Para1(FONT) == 4)m_font.CreatePointFont(Para0(FONT), _T("Courier"));
		else if (Para1(FONT) == 5)m_font.CreatePointFont(Para0(FONT), _T("Courier New"));
		else if (Para1(FONT) == 6)m_font.CreatePointFont(Para0(FONT), _T("Times New Roman"));
		else if (Para1(FONT) == 7)m_font.CreatePointFont(Para0(FONT), _T("Helvetica"));
		m_listavi.SetFont(&m_font);
		m_listref.SetFont(&m_font);
		m_listcurrent.SetFont(&m_font);
	}
	int c1, c2, c3, c4, c5;
	sscanf_s(ptxt[COLS], "%d,%d,%d,%d,%d", &c1, &c2, &c3, &c4, &c5);
	m_listavi.InsertColumn(0, "ID", LVCFMT_LEFT, c1);//IDの記録日時を表示、180は表示時に再設定
	m_listavi.InsertColumn(1, English ? "Date" : "撮影日時", LVCFMT_LEFT, c2);
	m_listavi.InsertColumn(2, English ? "Length" : "時間", LVCFMT_RIGHT, c3);
	//	if (strstr(ptxt[LENG], "1"))m_listavi.InsertColumn(2, English ? "Length" : "時間", LVCFMT_RIGHT, c3);
	//	else m_listavi.InsertColumn(2, English ? "Length" : "サイズ", LVCFMT_RIGHT, c3);
	m_listavi.InsertColumn(3, English ? "memo" : "メモ情報", LVCFMT_LEFT, c4);
	m_listavi.InsertColumn(4, English ? "full path" : "ファイルパス", LVCFMT_LEFT, c5);
	m_listavi.SetExtendedStyle(m_listavi.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT);
	m_listcurrent.InsertColumn(0, "ID", LVCFMT_LEFT, Columnwidth);//IDの記録日時を表示、180は表示時に再設定
	m_listcurrent.InsertColumn(1, "", LVS_NOCOLUMNHEADER, 0);//full path
	m_listcurrent.SetExtendedStyle(m_listcurrent.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT);
	m_listref.InsertColumn(0, English ? "references" : "参照眼振", LVCFMT_LEFT, Columnwidth);//メモを表示、widthは表示時に再設定
	m_listref.InsertColumn(1, "", LVS_NOCOLUMNHEADER, 0);//full path
	m_listref.SetExtendedStyle(m_listref.GetExtendedStyle() | LVS_EX_SUBITEMIMAGES | LVS_EX_FULLROWSELECT);
/*	m_tooltip.Create(this);
	m_tooltip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 512);
//	m_tooltip.AddTool(&m_showhideb,"ボタン枠は表示されていませんが、この場所のクリックで\n左上のボタン群の表示、非表示の切り替えです");
	m_tooltip.AddTool(&m_memo, "ファイル一覧で選択されているファイルのメモを設定します");
	m_tooltip.AddTool(&m_chanid, "ファイル一覧で選択されているファイルのIDを変更します");
	m_tooltip.AddTool(&m_list, "保存されている全ファイルの一覧表示モードに移行します");
	m_tooltip.AddTool(&m_setid, "枠上部に現行IDを表示しています\n現行IDを設定変更します");// \n全一覧表示の場合は現行ID一覧表示に移行します");
	m_tooltip.AddTool(&m_cutmovie, "下方の再生バーの左右黄色三角マークに挟まれた範囲を保存します\n左右黄色三角マークはマウスドラッグで動かせます");
	m_tooltip.AddTool(&m_curplay, "参照ファイル、現行IDファイル一覧および眼振映像画面に移行します");
	m_tooltip.AddTool(&m_resetrec, "録画をリセットし、頭位アニメーションの向きを正面にします（F1キーと同等です）");
//	m_tooltip.AddTool(&m_sensor, "ジャイロセンサーの向きを設定します");
//	m_tooltip.AddTool(&m_camnum, "カメラデバイスを変更します");
//	m_tooltip.AddTool(&m_nextcom, "ジャイロセンサーのポートを探します\nセンサーが動かないときにお試しください");
//	m_tooltip.AddTool(&m_sensoronoff, "ジャイロセンサーモードのON・OFFです\nOFFモードでは、頭位をキーボード・マウスで入力できます");
	m_tooltip.AddTool(&m_resethead, "頭位アニメーションを正面に設定します\nセンサーが水平なら仰臥位モード、垂直なら座位モードマークを頭位アニメ左上に表示します");
//	m_tooltip.AddTool(&m_arrow, "再生中の映像を参照ファイルに設定します\n右の映像を左参照ファイル枠にドラッグ・ドロップしても設定できます");
//	m_tooltip.AddTool(&m_deinter, "deInterlaseのON/OFF\nデジ蔵などのキャプチャーデバイスの場合は、ONにするとジャギーが取れます");
	m_tooltip.AddTool(&m_erasebut, "再生中の映像を削除します");
//	m_tooltip.AddTool(&m_smile, "顔アニメーションの笑顔と普通の顔の切り替えです");
//	m_tooltip.AddTool(&m_cpuspec, "眼振映像の滑らか表示機能をON・OFFします\n低スペックパソコンでもOFFにすると使えるかもしれません\n保存映像には影響しません");
	m_tooltip.AddTool(&m_listavi, "ファイルをダブルクリックすると再生します\nファイルの右クリックでポップアップメニューがでます");
*/
//	SetButtons(CapNYSmode = PrevMode);
	if (SetLists() == -1) {//capnys2list.txt	
		if (FilesCnt() > 0) {
			CMakeDB dlg;
			dlg.m_setumei = English ? "no CapNYS2list.txt(video files) then make it." : "CapNYS2list.txt(video files)がありませんので、作ります。";
			if (dlg.DoModal() == IDOK) {
			}
			SetLists();
		}
	}
	maxframenum = 1000;//取りあえず
	m_CaploopEnable = false;
	m_PlayloopEnable = false;
	m_PrevloopEnable = false;
	ArduinoM5ThreadF = false;

	m_pCaptureThread = NULL;
	m_pPlayThread = NULL;
//	m_pTrimThread = NULL;
	KillRecordCnt = 0;
	KillPlayCnt = 0;
	KillPreviewCnt = 0;
	strcpy_s(playingfn, 100, "");
	strcpy_s(lastrecfn, 100, "");
	strcpy_s(trimingfn, 100, "");
	strcpy_s(listaviselected, 100, "");

	DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
	Set_rpk_ppk();


	Preview();// _init();
	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CCapNYS2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。



void CCapNYS2Dlg::DispOneNum(CStatic *ms, int num, int src)
{
	int x, x0 = 0, y0 = 47, dx = 11, dy = 20;
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC = ms->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	if (src == SRCAND)pDC->FillSolidRect(0, 0, 33, 33, grayRGB);//(255,255,255));//grayRGB);
	else pDC->FillSolidRect(0, 0, 33, 33, RGB(255, 255, 255));//grayRGB);
	x = num*dx + x0;
	pDC->BitBlt(11, 8, dx, dy, &MemDC, x, y0, src);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void CCapNYS2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		CRect rect;
		int senm = 0;
		GetClientRect(&rect);
		SetCtrlPos(rect.right, rect.bottom);

		SetButtons(CapNYSmode);
		//if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {//capture
			if (CapNYSmode == PrevMode) {
				DispNum_sub(&m_currentid, -1);//なにも書かない
			}
			else {
				DispNum_sub(&m_currentid, IDnum);
			}
			sscanf_s(ptxt[SENM], "%d", &senm);
			DispNum_Sensor(&m_sensormode, senm);
			if (Para0(SENM)==1 || Para0(SENM)==2) {	
				int num;
//				DispIroiro(&m_nextcom, 0, 0, 621, 0, 82, 30, 3, SRCCOPY);
				sscanf_s(ptxt[COMP], "%d", &num);
//				DispNum3(&m_nextcom, 46, 1, num);
//				DispNum_sub(&m_nextcom, num);
			}
		
		if (CapNYSmode == PlayMode) {//play
			DispNum_sub(&m_currentid, IDnum);
			DispSlider();
			if (!m_PlayloopEnable) {
				DispOneFrame(playingfn, 0);
			}
		}
//		else if (CapNYSmode == PrevMode) {//preview
//			DispNum_sub(&m_currentid, IDnum);		
//		}
		else if (CapNYSmode == ListMode) {
			DispNum_sub(&m_currentid, IDnum);
		}
		int n = m_listavi.GetItemCount();
		if (n>-1&&n<1000000)DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CCapNYS2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCapNYS2Dlg::SetCtrlPos(int w, int h)
{
	Winw = w;
	Winh = h;
	int ww = Para0(CSIZ);//640
	int wh = Para1(CSIZ);// 480;
	int y = 5;
	if (w<850)w = 850;
	if (h<400)h = 400;
	int dx = 90, butw = 85, buth = 85;
//	strcpy_s(ptxt[CSIZ], "640,480");
//	int para0 = 
//	int para1 = Para1(CSIZ);
	
//	if (strstr(ptxt[DAUT], "1")) {
		Gwinh = h - 165;//-(h-Para1(CSIZ))/4;
		if (Gwinh>wh) {
			Gwinh = wh + (Gwinh - wh) / 3;
		}
		Gwinh = Gwinh - Gwinh % 12;
		Gwinw = w - Columnwidth * 2 - 72;//-(w-800)/4;
		if (Gwinw>ww) {
			Gwinw = ww + (Gwinw - ww) / 3;
		}
		Gwinw = Gwinw - (Gwinw % 12);
		if (Gwinh >= Gwinw*wh / ww) {
			Gwinh = Gwinw*wh / ww;
		}
		else {
			Gwinw = Gwinh*ww / wh;
		}
//		sprintf_s(ptxt[DSIZ], "%d,%d", Gwinw, Gwinh);
//	}
//	else {
//		Gwinw = Para0(DSIZ);
//		Gwinh = Para1(DSIZ);
//	}
	//Gwinw = 640;
	//Gwinh = 480;

	Gwinx = slidex = (w - Gwinw) / 2;;
	Gwiny = (h - Gwinh - buth) / 2 + buth;
	slidey = (h - Gwinh - buth) / 2 + buth + Gwinh + 3;
	slidew = Gwinw;//-39;
	slideh = 29;
	//0:del 1:setid 2:toref矢印 3:memo 4:changeid 5:curplay 6:video 7:listref 8:listcurrent 9:listavi 
	//15:sensor 16:camnum 17:sen_onof 18:nextcom
	PicPos[6][0] = Gwinx; PicPos[6][1] = Gwiny; PicPos[6][2] = Gwinw; PicPos[6][3] = Gwinh;
//	m_startcap.MoveWindow(w / 2 - butw / 2, y, butw, buth, 1);
	m_stopcap.MoveWindow(w / 2 - butw / 2, y, butw, buth, 1);

	m_cutmovie.MoveWindow(slidex + Gwinw - butw, y, butw, buth, 1);


	m_list.MoveWindow(w / 2 - butw / 2 + dx, y, butw, buth, 1);
	m_erasebut.MoveWindow(w - 2 * dx - 1, y, butw, buth, 1);

	m_cancel.MoveWindow(w - dx - 1, y + 20, butw, buth - 20, 1);
	m_totalnum.MoveWindow(w - dx - 1, y, butw, 20, 1);
	m_resethead.MoveWindow(slidex + Gwinw - butw, y, butw, buth, 1);

	m_resetrec.MoveWindow(slidex, y, butw, buth, 1);

	m_record.MoveWindow(w / 2 - butw / 2,y, butw, buth, 1);
	m_setid.MoveWindow(PicPos[1][0] = w / 2 - butw / 2-dx, PicPos[1][1] = y+20, PicPos[1][2] = butw, PicPos[1][3] = buth-20, 1);
	PicPos[2][0] = 0;
	PicPos[2][1] = 0;
	PicPos[2][2] = 0;
	PicPos[2][3] = 0;
	m_menu.MoveWindow(6, y+20, butw, buth-20, 1);
	m_sensormode.MoveWindow(6, y, butw, 20, 1);

	m_memo.MoveWindow(PicPos[3][0] = 6 + 1 * dx, PicPos[3][1] = y, PicPos[3][2] = butw, PicPos[3][3] = buth, 1);
	m_chanid.MoveWindow(PicPos[4][0] = 6 + 2 * dx, PicPos[4][1] = y, PicPos[4][2] = butw, PicPos[4][3] = buth, 1);
	m_save.MoveWindow(6 + 3 * dx,  y,  butw, buth, 1);
	m_backup.MoveWindow(6 +15+ 4 * dx,  y, butw,  buth, 1);
	m_backupfolder.MoveWindow(6 +15+ 5 * dx, y, butw, buth, 1);
	m_curplay.MoveWindow(PicPos[5][0] = w / 2 - butw / 2 + dx, PicPos[5][1] = y, PicPos[5][2] = butw, PicPos[5][3] = buth, 1);

	m_currentid.MoveWindow(w / 2 - butw / 2 - dx, y, butw, 20, 1);

	m_listref.MoveWindow(PicPos[7][0] = 5, PicPos[7][1] = 95, PicPos[7][2] = Columnwidth + 4, PicPos[7][3] = h - 100, 1);
	m_listcurrent.MoveWindow(PicPos[8][0] = w - Columnwidth - 9, PicPos[8][1] = 95, PicPos[8][2] = Columnwidth + 4, PicPos[8][3] = h - 100, 1);
	m_listavi.MoveWindow(PicPos[9][0] = 5, PicPos[9][1] = 95, PicPos[9][2] = w - 10, PicPos[9][3] = h - 100, 1);
	m_timetrim.MoveWindow(slidex, Gwiny - 25, Gwinw, 30);

	m_moviept.MoveWindow(slidex - 10, slidey, slidew + 12, 29);

}
void SetEN(char *path, char *fullpath)
{
	int i;
	if (strlen(fullpath) == 0)strcpy_s(path, 50, "");
	for (i = strlen(fullpath); i>0; i--) {
		if (fullpath[i] == '\\')break;
	}
	strcpy_s(path, 50, &fullpath[i + 1]);
}
int Setfn2iddate(char *fn, char *iddate)
{
	int id, y, m, d, h, M, s;
	char buf[51];
	if (strlen(fn)<5 || strstr(fn, "\\"))return -1;//適当なチェック
	sscanf_s(fn, "%08d%04d%02d%02d%02d%02d%02d%s", &id, &y, &M, &d, &h, &m, &s, buf, 50);
	sprintf_s(iddate, 200, "%08d %04d-%02d-%02d %02d:%02d", id, y, M, d, h, m);
	return id;
}

void CCapNYS2Dlg::SetButtons(int mode)
{
	int swm[8][31] = {
		0,1,0,0,0, 0,1,1,1,0, 0,0,1,1,1, 0,1,0,0,1, 1,1,0,0,0, 0,1,1,0,1,1,//capture
		1,0,0,0,0, 1,1,0,1,0, 1,1,0,0,0, 0,0,0,0,1, 1,0,0,0,0, 0,1,0,1,0,1,//preview
		1,0,0,1,1, 1,1,0,0,0, 1,1,0,0,0, 0,0,0,0,1, 1,1,1,1,0, 0,0,0,1,0,1,//play
		0,0,0,0,0, 1,1,0,0,1, 1,0,0,0,0, 0,0,0,1,0, 0,0,0,1,1, 1,0,0,1,1,0,//disp
	};

	m_setid.ShowWindow(swm[mode][0] ? SW_SHOW : SW_HIDE);
	m_currentid.ShowWindow(swm[mode][0] ? SW_SHOW : SW_HIDE);
	m_stopcap.ShowWindow(swm[mode][1] ? SW_SHOW : SW_HIDE);
//	m_startcap.ShowWindow(swm[mode][2] ? SW_SHOW : SW_HIDE);
	char buf[301], buf1[301];
	int id;
	if (strlen(playingfn)>10 && strstr(playingfn, "gazou")) {
		SetEN(buf, playingfn);
		id = Setfn2iddate(buf, buf1);
	}
	else id = 0;
	m_cutmovie.ShowWindow((id == IDnum) && swm[mode][3] ? SW_SHOW : SW_HIDE);
	m_cancel.ShowWindow(swm[mode][6] ? SW_SHOW : SW_HIDE);
	m_resetrec.ShowWindow(swm[mode][7] ? SW_SHOW : SW_HIDE);
	m_resethead.ShowWindow(swm[mode][8] ? SW_SHOW : SW_HIDE);
	m_curplay.ShowWindow(swm[mode][9] ? SW_SHOW : SW_HIDE);//

	m_list.ShowWindow(swm[mode][11] ? SW_SHOW : SW_HIDE);
	m_listavi.ShowWindow(swm[mode][18] ? SW_SHOW : SW_HIDE);
	m_listref.ShowWindow(swm[mode][19] ? SW_SHOW : SW_HIDE);

	m_listcurrent.ShowWindow(swm[mode][20] ? SW_SHOW : SW_HIDE);
	m_timetrim.ShowWindow(swm[mode][21] ? SW_SHOW : SW_HIDE);
	m_moviept.ShowWindow(swm[mode][22] ? SW_SHOW : SW_HIDE);
	m_memo.ShowWindow(swm[mode][23] ? SW_SHOW : SW_HIDE);
	m_erasebut.ShowWindow(swm[mode][24] ? SW_SHOW : SW_HIDE);

	m_chanid.ShowWindow(swm[mode][25] ? SW_SHOW : SW_HIDE);
	char *s = ptxt[SENM];
//	m_nextcom.ShowWindow((strstr(s, "1") || strstr(s, "2")) && swm[mode][26] ? SW_SHOW : SW_HIDE);
//	m_chancom.ShowWindow((strstr(s, "1") || strstr(s, "2")) && swm[mode][26] ? SW_SHOW : SW_HIDE);
	m_record.ShowWindow(swm[mode][29] ? SW_HIDE : SW_SHOW);
	m_save.ShowWindow(swm[mode][30] ? SW_HIDE : SW_SHOW);
	m_backup.ShowWindow(swm[mode][30] ? SW_HIDE : SW_SHOW);
	m_backupfolder.ShowWindow(swm[mode][30] ? SW_HIDE : SW_SHOW);
	if (strstr(ptxt[SENM], "0"))
	{
		bmp_button_head.LoadBitmapA(IDB_SISEI);
	}
	else {
		bmp_button_head.LoadBitmapA(IDB_BM_HEAD);
	}
	m_resethead.SetBitmap(bmp_button_head);

}

void FolderTree2lists(CString inPath, CListCtrl *list, CListCtrl *ref)
{
	//ファイルの検索
	CFileFind Finder;
	char sizeb[301], fname[301], iddate[301],title[130];
	CString Path = inPath + _T("\\*.*");
	BOOL bWorking = Finder.FindFile(Path, 0);
	int insn;
	while (bWorking) {
		bWorking = Finder.FindNextFile();//))break;
		CString Getpath = Finder.GetFilePath();
		CString Getname = Finder.GetFileName();
//		if (strstr(ptxt[LENG], "0")) {
//			size = Finder.GetLength();
//			wsprintf(sizeb, "%d", size / 1000);// フォルダのみ　再帰的にフォルダアイテムを作成
//		}
		if (!(GetFileAttributes(Getpath)&FILE_ATTRIBUTE_DIRECTORY)) {
			if (strlen(Getname)==26&&(strstr(Getname, ".avi") || strstr(Getname, ".wmv"))) {
				insn = list->InsertItem(0, NULL, 1);
				strcpy_s(fname, 300, Getname);
				Setfn2iddate(fname, iddate);
				list->SetItemText(insn, 1, &iddate[9]);
				iddate[8] = '\0';
				list->SetItemText(insn, 0, iddate);
//				if (strstr(ptxt[LENG], "1")) {
				float len = filesec(fname);
				if (len == 0)len = 1;
				if (len >= 60)
					sprintf_s(sizeb, "%dm%02ds", int(len) / 60, int(len) % 60);
				else sprintf_s(sizeb, " %02ds", int(len));
	//			}
				list->SetItemText(insn, 2, sizeb);
				//char buf1[300], buf2[300];
				GetNameArtist(Getpath, title);//titlename memo
				list->SetItemText(insn, 3, title);
				list->SetItemText(insn, 4, Getpath);
				foundn++;
				if (Getname[strlen(Getname)-26]=='9'){
				// if (strstr(kensaku, "refer")) {
					insn = ref->InsertItem(0, NULL, 1);
					ref->SetItemText(insn, 0, title);
					ref->SetItemText(insn, 1, Getpath);
				}
			}
		}
		else {
			if (Getname != _T(".") && Getname != _T("..")) {
				FolderTree2lists(Getpath, list, ref);// フォルダの場合は自分自身を呼び直す。
			}
		}
	}
	Finder.Close();
}

int FilesCnt()
{
	CFileFind Finder;
	int cnt=0;
	char dir[301];
	if (strlen(ptxt[SAVE]) == 0) {
		wsprintf(dir, "%s\\%s", CurDir, "gazou");
	}
	else {
		wsprintf(dir, "%s", ptxt[SAVE]);
	}
	CString path = dir;
	CString Path = path + _T("\\*.*");
	BOOL bWorking = Finder.FindFile(Path, 0);

	while (bWorking) {
		bWorking = Finder.FindNextFile();//))break;
		CString Getpath = Finder.GetFilePath();
		CString Getname = Finder.GetFileName();
		if (!(GetFileAttributes(Getpath)&FILE_ATTRIBUTE_DIRECTORY)) {
			if (strstr(Getname, ".avi") || strstr(Getname, ".wmv")) {
				cnt++;
				break;
			}
		}
	}
	Finder.Close();
	return cnt;
}


int CCapNYS2Dlg::SetLists()
{
	char *p1, *p2, *p3,*p4,buf[500];
	CStdioFile fr;
	int sc,insn,cnt=0;
	for (sc = m_listavi.GetItemCount() - 1; sc >= 0; sc--)m_listavi.DeleteItem(sc);
	for (sc = m_listref.GetItemCount() - 1; sc >= 0; sc--)m_listref.DeleteItem(sc);
	
	if(!fr.Open(LIST_FN, CFile::modeRead | CFile::typeText)){
	//	MessageBox("memo_text open err");
		return -1;
	}
	while (fr.ReadString(buf, 500)) {
		cnt++;
		if (strstr(buf, "<nys>")) {
			p1 = strstr(buf, "<nys>");
			*p1 = 0;
			p1 = p1 + 5;
			p2 = strstr(p1, "<nys>");
			*p2 = 0;
			p2 = p2 + 5;
			p3 = strstr(p2, "<nys>");
			*p3 = 0;
			p3 = p3 + 5;
			p4 = strstr(p3, "<nys>");
			*p4 = 0;
			p4 = p4 + 5;
			*strstr(p4, "\n") = 0;
			insn = m_listavi.InsertItem(0, NULL, 1);
			m_listavi.SetItemText(insn, 0, buf);
			m_listavi.SetItemText(insn, 1, p1);
			m_listavi.SetItemText(insn, 2, p2);
			m_listavi.SetItemText(insn, 3, p3);
			m_listavi.SetItemText(insn, 4, p4);
			if (buf[0] == '9') {
				insn = m_listref.InsertItem(0, NULL, 1);
				m_listref.SetItemText(insn, 1, p4);//
				m_listref.SetItemText(insn, 0, p3);// ref->SetItemText(insn, 1, Getpath);
			}
		}
	}
	fr.Abort();
	UpdateData(true);
	return cnt;
}
int CCapNYS2Dlg::NewLists()
{
	int sc;
	CString path;
	char dir[301];
	if (strlen(ptxt[SAVE]) == 0) {
		wsprintf(dir, "%s\\%s", CurDir, "gazou");
	}
	else {
		wsprintf(dir, "%s", ptxt[SAVE]);
	}
	path = dir;
	for (sc = m_listavi.GetItemCount() - 1; sc >= 0; sc--)m_listavi.DeleteItem(sc);
	for (sc = m_listref.GetItemCount() - 1; sc >= 0; sc--)m_listref.DeleteItem(sc);
	foundn = 0;
	FolderTree2lists(path,&m_listavi, &m_listref);// "allavi");
	return 0;
}

int CCapNYS2Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;
	LoadCon();
	int n;
	CapNYSmode = PrevMode;//preview
	sscanf_s(ptxt[SXYZ], "%d", &n);
	GetSXYZ(Sxyz, n);
	return 0;
}

void CCapNYS2Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	bool trimingf = false;//トリム中に終了の時

	m_PlayloopEnable = false;

	m_CaploopEnable = false;
	Sleep(200);
	if (CapNYSmode == CaptMode) {
		if (IsFile(lastrecfn))f2gomi(lastrecfn);
	}
	SetCurrentDirectory(CurDir);
	SaveCon(&m_listavi);
	SaveList();
	ArduinoM5ThreadF = false;
#ifdef _DEBUG
	Save_sen4();
#endif
}
bool IsFile(char *fn)
{
	struct stat st;
	if (stat(fn, &st) != 0)return false;
	return true;
}

void CCapNYS2Dlg::SaveList(void)//SetCurrentDirectory後にここに来る
{
	CStdioFile fout;
//	char memo[301],path[301],buf[500];
	char b0[10],b1[20], b2[20], b3[130],b4[301],buf[500];
	int i,sc;	
	if(!fout.Open(LIST_FN,CFile::modeCreate|
				CFile::modeWrite|CFile::modeRead|CFile::typeText)){
		MessageBox("list_text open err");
		return;
	}
	sc=m_listavi.GetItemCount();
	if (sc == 0) {
		fout.Abort();
		return;
	}
	for(i=sc-1;i>=0;i--){
		m_listavi.GetItemText(i,0,b0,300);
		m_listavi.GetItemText(i,1,b1,300);
		m_listavi.GetItemText(i,2,b2,300);
		m_listavi.GetItemText(i,3,b3,300);
		m_listavi.GetItemText(i,4,b4,300);
	//	MessageBox(b3);
		sprintf_s(buf, "%s<nys>%s<nys>%s<nys>%s<nys>%s\n", b0, b1, b2, b3, b4);
		fout.WriteString(buf);
	}
	fout.Abort();
}
/*
void SetMemo(CListCtrl *list,int n1,char *memo,int n2,char *path)
{
	int sc,i;
	char fn[301],temp[301];
	sc=list->GetItemCount();
	if(sc==0)return;
	for(i=0;i<sc;i++){
		list->GetItemText(i,n2,temp,300);
		SetEN(fn,temp);
		if(strstr(path,fn)){
			list->SetItemText(i,n1,memo);
			return;
		}
	}
}*/
/*if(dlg.DoModal()==IDOK){
		char *p1,*p2,*p3;//,fn[MAX_PATH];
		int mlen;
		CStdioFile fr;
		//sprintf(fn,"%s\\s8Tunes_temp.txt",curdir);
		fr.Open(temppath,CFile::modeRead|CFile::typeText);

		while(fr.ReadString(buf,995)){
			p1=strstr(buf,"<s8t>");
			*p1=0;
			p1=p1+5;
			p2=strstr(p1,"<s8t>");
			*p2=0;
			p2=p2+5;
			p3=strstr(p2,"<s8t>");
			*p3=0;
			p3=p3+5;
			sscanf(p3,"%d",&mlen);
			AddSongFile(buf,p1,p2,mlen);
		}
		fr.Abort();
	}
void CCapNYS2Dlg::LoadMemo(void)//oninitから呼ばれるときはSetCurrentDirectoryしたも同然だが
{
	CStdioFile fin;
	char *p,memo[501],path[501],buf[501];
	SetCurrentDirectory(CurDir);
	if(!fin.Open(MEMO_FN,CFile::modeRead|CFile::typeText))
	{
		//MessageBox("memo_text open err");
		return;
	}
	while(fin.ReadString(buf,500)){
		p=strstr(buf," ");
		strcpy_s(memo,p+1);
		*strstr(memo,"\n")='\0';
		*p='\0';
		strcpy_s(path,buf);
		SetMemo(&m_listref,0,memo,1,path);
		SetMemo(&m_listavi,3,memo,4,path);
	}
	fin.Abort();
}*/
void PushfnPtxt(char *fn)
{
	char buf[100];
	char *p;
	if (strstr(fn, "00000000"))return;
	if (p=strstr(ptxt[HIST], fn)) {//fnを先頭に移動する
		strcpy_s(p,100,(p + strlen(fn)+1));
	}
	sprintf_s(buf, "%s,%s", fn, ptxt[HIST]);
	buf[8 * 10 + 9] = '\0';
	strcpy_s(ptxt[HIST], buf);
}
void Setlistavi2listcur(CListCtrl* all, CListCtrl* cur, int id)
{
	int i, sc, insn, idcnt = 0;
	char ids[15], temp[301];

	sprintf_s(ids, "ID : %08d", id);
	cur->DeleteColumn(0);
	cur->InsertColumn(0, ids, LVCFMT_LEFT, Columnwidth);//IDの記録日時を表示、180は表示時に再設定

	sprintf_s(ids, "%08d", id);
	for (sc = cur->GetItemCount() - 1; sc >= 0; sc--)cur->DeleteItem(sc);
	sc = all->GetItemCount();
	for (i = 0; i<sc; i++) {
		all->GetItemText(i, 0, temp, 300);
		if (strstr(temp, ids)) {
			idcnt++;
			insn = cur->InsertItem(0, NULL, 1);
			all->GetItemText(i, 4, temp, 300);
			cur->SetItemText(insn, 1, temp);//
			all->GetItemText(i, 1, temp, 300);//
			cur->SetItemText(insn, 0, temp);
		}
	}
	CurIDcnt = idcnt;
}
/*
void CCapNYS2Dlg::Preview(void)
{
	CGetNewID dlg;
	char path[30];
	dlg.m_IDnum = 0;
	dlg.m_record_setid = 0;
	if (!m_PrevloopEnable) {
		//	run arduinothread
		int tm;
		if (strstr(ptxt[SENM], "1")) {
			AfxBeginThread(ArduinoM5Thread_M5, &tm);
		}
		else if (strstr(ptxt[SENM], "2")) {
			AfxBeginThread(ArduinoM5Thread, &tm);
		}
		else if (strstr(ptxt[SENM], "3")) {
				AfxBeginThread(iPhoneThread, &tm);
		}
		//	Run previewthread
		m_pPreviewThread = AfxBeginThread(PreviewThread, this);
	}
	Resetheadfcnt = 5;
	dlg.m_record_setid = 0;
	//DispNum3(&m_nextcom, 46, 8, Para0(COMP));
	SetButtons(CapNYSmode = PrevMode);
	SetHead(5);
//	DispNum3(&m_nextcom, 46, 8, Para0(COMP));
//	DispNum3(&m_nextcom, 46, 8, Para0(COMP));

//	OnClickedChancom();
//	DispNum3(&m_nextcom, 46, 8, 0);
//	AfxMessageBox(ptxt[COMP]);

	if (dlg.DoModal() == IDOK) {
		SetTimer(1, 100, NULL);
		IDnum = dlg.m_IDnum;
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		m_PrevloopEnable = false;
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		KillPreviewCnt =5;
		CurIDcnt = GetIDcnt(&m_listavi, IDnum);
		//CaptureThreadは、完全に？ほかのthreadが消えていないと立ち上がらない？
		//PlayThreadはそうでもなさそう。
		//timerで、m_pPreviewThreadが消えたあと3回カウントさせると、下３行が働く？
		//			int tm;
			//		AfxBeginThread(ArduinoThread, &tm);
				///	m_pCaptureThread = AfxBeginThread(CaptureThread, this);
		sprintf_s(path, "%08d", IDnum);
		PushfnPtxt(path);
	}
}
void CCapNYS2Dlg::Preview_init(void)
{
	int senm = 0;
	CGetNewID dlg;
	char path[30];
	dlg.m_IDnum = 0;
	dlg.m_record_setid = 0;

	if (!m_PrevloopEnable) {
		//	run arduinothread
		int tm;
		if (strstr(ptxt[SENM], "1")) {
			AfxBeginThread(ArduinoM5Thread_M5, &tm);
		}
		else if (strstr(ptxt[SENM], "2")) {
			AfxBeginThread(ArduinoM5Thread, &tm);
		}
		else if (strstr(ptxt[SENM], "3")) {
			AfxBeginThread(iPhoneThread, &tm);
		}
		//	Run previewthread
		m_pPreviewThread = AfxBeginThread(PreviewThread, this);
	}


	Resetheadfcnt = 5;
	dlg.m_record_setid = 0;
	//	DispNum3(&m_nextcom, 46, 8, Para0(COMP));
	SetButtons(CapNYSmode = PrevMode);
	SetHead(5);
	SetTimer(1, 100, NULL);
	sscanf_s(ptxt[SENM], "%d", &senm);
	DispNum_Sensor(&m_sensormode,senm);
	//	DispNum3(&m_nextcom, 46, 8, Para0(COMP));

	//	OnClickedChancom();
	//	DispNum3(&m_nextcom, 46, 8, 0);
	//	AfxMessageBox(ptxt[COMP]);
}*/

void CCapNYS2Dlg::Preview(void)
{
	CGetNewID dlg;
	char path[30];
	dlg.m_IDnum = 0;
	dlg.m_record_setid = 0;
	SetButtons(CapNYSmode = PrevMode);
	if (!m_PrevloopEnable) {
		//	run arduinothread
		int tm;
		if (strstr(ptxt[SENM], "1")) {
			AfxBeginThread(ArduinoM5Thread_M5, &tm);
		}
		else if (strstr(ptxt[SENM], "2")) {
			AfxBeginThread(ArduinoM5Thread, &tm);
		}
		else if (strstr(ptxt[SENM], "3")) {
			AfxBeginThread(iPhoneThread, &tm);
		}
		//	Run previewthread
		m_pPreviewThread = AfxBeginThread(PreviewThread, this);
	}
	else {
		//		Resetheadfcnt = 5;
		dlg.m_record_setid = 0;
		//		SetButtons(CapNYSmode = PrevMode);
		//		SetHead(5);
	}
	if (dlg.DoModal() == IDOK) {
		SetTimer(1, 100, NULL);
		IDnum = dlg.m_IDnum;
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		m_PrevloopEnable = false;
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		KillPreviewCnt = 5;
		CurIDcnt = GetIDcnt(&m_listavi, IDnum);
		//CaptureThreadは、完全に？ほかのthreadが消えていないと立ち上がらない？
		//PlayThreadはそうでもなさそう。
		//timerで、m_pPreviewThreadが消えたあと3回カウントさせると、下３行が働く？
		//			int tm;
		//			AfxBeginThread(ArduinoThread, &tm);
		//			m_pCaptureThread = AfxBeginThread(CaptureThread, this);
		sprintf_s(path, "%08d", IDnum);
		PushfnPtxt(path);
	}
	else {
		m_PrevloopEnable = false;
		IDnum = dlg.m_IDnum;
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		m_PrevloopEnable = false;
		DispNum_sub(&m_currentid, IDnum);
		SetButtons(CapNYSmode = PlayMode);
	}
}

void CCapNYS2Dlg::Preview_init(void)
{
	CGetNewID dlg;
	char path[30];
	dlg.m_IDnum = 0;
	dlg.m_record_setid = 0;

	if (!m_PrevloopEnable) {
		//	run arduinothread
		int tm;
		if (strstr(ptxt[SENM], "1")) {
			AfxBeginThread(ArduinoM5Thread_M5, &tm);
		}
		else if (strstr(ptxt[SENM], "2")) {
			AfxBeginThread(ArduinoM5Thread, &tm);
		}
		else if (strstr(ptxt[SENM], "3")) {
			AfxBeginThread(iPhoneThread, &tm);
		}
		//	Run previewthread
		m_pPreviewThread = AfxBeginThread(PreviewThread, this);
	}
	Resetheadfcnt = 5;
	dlg.m_record_setid = 0;
	//	DispNum3(&m_nextcom, 46, 8, Para0(COMP));
	SetButtons(CapNYSmode = PrevMode);
	SetHead(5);
	//	SetTimer(1, 100, NULL);
		//	DispNum3(&m_nextcom, 46, 8, Para0(COMP));

		//	OnClickedChancom();
		//	DispNum3(&m_nextcom, 46, 8, 0);
		//	AfxMessageBox(ptxt[COMP]);
	return;
	if (dlg.DoModal() == IDOK) {
		SetTimer(1, 100, NULL);
		IDnum = dlg.m_IDnum;
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		m_PrevloopEnable = false;
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		KillPreviewCnt = 5;
		CurIDcnt = GetIDcnt(&m_listavi, IDnum);
		//CaptureThreadは、完全に？ほかのthreadが消えていないと立ち上がらない？
		//PlayThreadはそうでもなさそう。
		//timerで、m_pPreviewThreadが消えたあと3回カウントさせると、下３行が働く？
		//			AfxBeginThread(ArduinoThread, &tm);
		m_pCaptureThread = AfxBeginThread(CaptureThread, this);
		sprintf_s(path, "%08d", IDnum);
		PushfnPtxt(path);
	}
	else {
		//m_PrevloopEnable = false;
		IDnum = dlg.m_IDnum;
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		m_PrevloopEnable = false;
		DispNum_sub(&m_currentid, IDnum);
		SetButtons(CapNYSmode = PlayMode);
	}

}



int GetIDcnt(CListCtrl* all, int id)
{
	int i, sc, cnt = 0;
	char ids[15], temp[301];
	sprintf_s(ids, "%08d", id);
	sc = all->GetItemCount();
	for (i = 0; i<sc; i++) {
		all->GetItemText(i, 0, temp, 300);
		if (strstr(temp, ids)) {
			cnt++;
		}
	}
	return cnt;
}
void Waku(CDC *pDC, int x, int y, int x1, int y1)
{
	pDC->FillSolidRect(x, y, x1, 1, RGB(0, 0, 0));
	pDC->FillSolidRect(x, y, 1, y1, RGB(0, 0, 0));
	pDC->FillSolidRect(x + x1, y, 1, y1, RGB(0, 0, 0));
	pDC->FillSolidRect(x, y + y1, x1 + 1, 1, RGB(0, 0, 0));
}

void CCapNYS2Dlg::DispNum_sub(CStatic *id, int idn)
{
	int i, x, x0 = 0, y0 = 47, dx = 11, dy = 20;
	bool zerof = false;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC = id->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	pDC->FillSolidRect(0, 0, 84, 20, RGB(255, 255, 255));
	if (idn > -1) {
		if (idn > 99999999)idn = 0;
		sprintf_s(buf, "%08d", idn);//8桁未満は上のけたを０で埋める
		for (i = 0; i < 8; i++) {//
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
			pDC->BitBlt(2 + i * (dx - 1), 1, dx, dy, &MemDC, x, y0, SRCAND);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
		//	Waku(pDC, 0, 0, 84, 20);
		}
	}
	Waku(pDC, 0, 0, 84, 20);
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}
void CCapNYS2Dlg::DispNum_Sensor(CStatic *id, int mode)
{
	
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC = id->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	pDC->FillSolidRect(0, 0, 84, 20, RGB(255, 255, 255));
	
		
			
	pDC->BitBlt(1, 2, 80, 16, &MemDC, 620,2+mode*16 , SRCAND);
	
	Waku(pDC, 0, 0, 84, 20);
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void CCapNYS2Dlg::DispOneFrame(char* fn, int fnumber)
{
	CDC* pDC = GetDC();
	BITMAP bm;
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);   // pDCとコンパチブルなデバイスコンテキストを作成

	cv::VideoCapture capture(fn);

	cv::Mat frame;
	maxframenum = capture.get(cv::CAP_PROP_FRAME_COUNT);
	if (fnumber >= maxframenum - 1)fnumber = maxframenum - 1;
	capture.set(cv::CAP_PROP_POS_FRAMES, fnumber);
	capture >> frame;
	CBitmap m_bmp;
	int rows, cols, step;
	uchar *data;
	rows = frame.rows;
	cols = frame.cols;
	step = frame.step;
	data = frame.data;
	char* ColorBuf = (char*)calloc(rows * rows * 4, sizeof(RGBQUAD));

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			// Blue
			ColorBuf[y * cols * 4 + x * 4 + 0] = data[y * step + x * 3 + 0];
			// Green
			ColorBuf[y * cols * 4 + x * 4 + 1] = data[y * step + x * 3 + 1];
			// Red
			ColorBuf[y * cols * 4 + x * 4 + 2] = data[y * step + x * 3 + 2];
			//Reserved
			ColorBuf[y * cols * 4 + x * 4 + 3] = 0;
		}
	}
	m_bmp.CreateBitmap(frame.cols, frame.rows, 1, 32, ColorBuf);
	free(ColorBuf);
	m_bmp.GetObject(sizeof(BITMAP), &bm);
	dcMem.SelectObject(&m_bmp);
	pDC->SetStretchBltMode(HALFTONE);
	pDC->StretchBlt(Gwinx, Gwiny, Gwinw, Gwinh, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	for (int i = 0; i<30; i++) {
		pDC->FillSolidRect(Gwinx + Gwinw / 2 - 30, Gwiny + Gwinh / 2 - 30 + i, 2 * i, 1, RGB(200, 200, 200));
	}
	for (int i = 0; i<30; i++) {
		pDC->FillSolidRect(Gwinx + Gwinw / 2 - 30, Gwiny + Gwinh / 2 - 0 + i, 2 * (30 - i), 1, RGB(200, 200, 200));
	}
	
	ReleaseDC(pDC);
	dcMem.DeleteDC();
}

void CCapNYS2Dlg::Dispfname(char *fn)
{
	int i, x, x0 = 0, y0 = 46, dx = 11, dy = 22;
	char buf[301], fname[301];
	CDC MemDC;
	CDC *pDC = m_timetrim.GetDC();
	CBitmap *pOldBmp, m_bmp;
	SetEN(buf, fn);
//	MessageBox(buf);
	Setfn2iddate(buf, fname);
//	MessageBox(fname);
	m_bmp.LoadBitmap(IDB_NUMBER);
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	for (i = 0; i<strlen(fname); i++) {
		if (fname[i] >= '0'&&fname[i] <= '9') {
			x = (fname[i] - '0')*dx + x0;
		}
		else if (fname[i] == '.') {
			x = 10 * dx + x0;
		}
		else if (fname[i] == ':') {
			x = 11 * dx + x0;
		}
		else if (fname[i] == '-') {
			x = 12 * dx + x0;
		}
		else x = 14 * dx + x0;
		pDC->BitBlt(Gwinw - 275 + i*(dx), 0, dx, dy, &MemDC, x, y0, SRCCOPY);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	}
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

void drawmaru(CDC* pDC, int cx, int cy)
{
	CPen pen_red(PS_SOLID, 1, RGB(255, 0, 0));
	CBrush br_red(RGB(255, 0, 0));
	CPen* oldpen = pDC->SelectObject(&pen_red);
	CBrush* oldbr = pDC->SelectObject(&br_red);
	CRect rect;
	rect.top = cy - 10;
	rect.left = cx - 10;
	rect.bottom = cy + 10;
	rect.right = cx + 10;
	pDC->Ellipse(&rect);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbr);
	return;
}
int CheckSelected(CListCtrl *cur, CListCtrl *ref) {
//	int sc,i;
	if (cur->GetNextItem(-1, LVNI_SELECTED) != 0)return 1;
	if (ref->GetNextItem(-1, LVNI_SELECTED) != 0)return 1;
	return 0;
}

void Delete1item(CListCtrl *avi, CListCtrl *cur, CListCtrl *ref, char *fn)
{
	int i, sc;
	char tfn[301];

	sc = avi->GetItemCount();
	if (sc == 0)return;
	for (i = 0; i<sc; i++) {
		avi->GetItemText(i, 4, tfn, 300);
		if (strstr(tfn, fn)) {
			avi->DeleteItem(i);
			foundn--;
			break;
		}
	}
	sc = cur->GetItemCount();
	if (sc == 0)return;
	for (i = 0; i<sc; i++) {
		cur->GetItemText(i, 1, tfn, 300);
		if (strstr(tfn, fn)) {
			cur->DeleteItem(i);
			return;
		}
	}

	if (fn[strlen(fn)-26]=='9'){//strstr(fn, "990000002")) {//reference folder
		sc = ref->GetItemCount();
		if (sc == 0)return;
		for (i = 0; i<sc; i++) {
			ref->GetItemText(i, 1, tfn, 300);
			if (strstr(tfn, fn)) {
				ref->DeleteItem(i);
				return;
			}
		}
	}
}
void Addfn2listavi(CListCtrl *list, char *fn,char *memo)
{
	int insn;
	char path[50], iddate[201];//,sizeb[10];
	insn = list->InsertItem(0, NULL, 1);
	SetEN(path, fn);
	Setfn2iddate(path, iddate);
	list->SetItemText(insn, 1, &iddate[9]);
	iddate[8] = '\0';
	list->SetItemText(insn, 0, iddate);
	list->SetItemText(insn, 2, "0");//一覧表示の時にゼロのitemを探して、正しいサイズを書き込む
	list->SetItemText(insn, 3, memo);
	list->SetItemText(insn, 4, fn);
}
void CCapNYS2Dlg::OnBnClickedStopcap()
{
	m_CaploopEnable = false;

	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	strcpy_s(playingfn, 300, lastrecfn);
	Addfn2listavi(&m_listavi, playingfn,"");
	foundn++;
	Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);

	DispOneFrame(playingfn, 0);
	SetButtons(CapNYSmode = PlayMode);
	Sleep(300);
	CDC* pDC = GetDC();
	pDC->FillSolidRect(Gwinx + Gwinw / 2 - 10, Gwiny - 25, 20, 20, grayRGB);//赤丸を消す
	ReleaseDC(pDC);
	DispSlider(2);
	int sc = m_listcurrent.GetItemCount();
	m_listcurrent.SetItemState(sc - 1, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
	m_listcurrent.EnsureVisible(sc - 1, false);
}

void drawmaru(CDC* pDC, DWORD co, int cx, int cy, int r)
{
	CPen pen(PS_SOLID, 1, co);
	CBrush pen_br(co);
	CPen* oldpen = pDC->SelectObject(&pen);
	CBrush* oldbr = pDC->SelectObject(&pen_br);
	CRect rect;
	rect.top = cy - r;
	rect.left = cx - r;
	rect.bottom = cy + r;
	rect.right = cx + r;
	pDC->Ellipse(&rect);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbr);
	return;
}

void CCapNYS2Dlg::DispTimeTrim(void)
{
	int i, ct, x, x0 = 0, y0 = 46, dx = 11, dy = 22;
	char buf[100];
	CDC MemDC;
	CDC *pDC = m_timetrim.GetDC();
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	if (CapNYSmode == CaptMode) {//capture
		ct = capturetime / 1000;
		if (ct % 2) {
			drawmaru(pDC, RGB(255, 0, 0), Gwinw / 2 + 32, 7+97 - Gwiny, 7);
		}
		else {
			drawmaru(pDC, RGB(240, 240, 240), Gwinw / 2 + 32, 7+97 - Gwiny, 7);
		}
		sprintf_s(buf, "%02d:%02d", ct / 60, ct % 60);
		for (i = 0; i<strlen(buf); i++) {
			if (buf[i] >= '0'&&buf[i] <= '9') {
				x = (buf[i] - '0')*dx + x0;
			}
			else if (buf[i] == '.') {
				x = 10 * dx + x0;
			}
			else if (buf[i] == ':') {
				x = 11 * dx + x0;
			}
			else x = 14 * dx + x0;
			pDC->BitBlt(i*(dx), 0, dx, dy, &MemDC, x, y0, SRCCOPY);
		}
	}
	else if (CapNYSmode == PlayMode) {//m_PlayloopEnable){
		sprintf_s(buf, "%02d:%02d/%02d:%02d", currentframe / Para0(FPSN) / 60, (currentframe / Para0(FPSN)) % 60,
			(maxframenum / Para0(FPSN) / 60) % 100, (maxframenum / Para0(FPSN)) % 60);
		
//		if (strlen(buf) > 11)return;
		for (i = 0; i<strlen(buf); i++) {
			if (buf[i] >= '0'&&buf[i] <= '9') {
				x = (buf[i] - '0')*dx + x0;
			}
			else if (buf[i] == '.') {
				x = 10 * dx + x0;
			}
			else if (buf[i] == ':') {
				x = 11 * dx + x0;
			}
			else if (buf[i] == '-') {
				x = 12 * dx + x0;
			}
			else if (buf[i] == '/') {
				x = 13 * dx + x0;
			}
			else x = 14 * dx + x0;
			pDC->BitBlt(i*(dx), 0, dx, dy, &MemDC, x, y0, SRCCOPY);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
		}
	}
	else {
		pDC->FillSolidRect(0, 0, Gwinw, dy, grayRGB);
	}
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}


#define hisiRGB RGB(250,250,250)
#define sankakuRGB RGB(250,250,0)
#define haniRGB RGB(120,120,120)
#define wakuRGB RGB(180,180,180) //grayRGB
#define sumiRGB RGB(0,0,0)//縦じま

void Hisigata(CDC *pDC, int x, int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(hisiRGB);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];
	po[0].x = x - 9;
	po[0].y = y + 11;
	po[1].x = x;
	po[1].y = y + 2;
	po[2].x = x + 9;
	po[2].y = y + 11;
	po[3].x = x;
	po[3].y = y + 20;
	pDC->SetPolyFillMode(WINDING);
	pDC->Polygon(po, 4);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}
void SankakuL(CDC *pDC, int x, int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(sankakuRGB);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];

	po[0].x = x;
	po[0].y = y;
	po[1].x = x + 11;
	po[1].y = y + 12 - 1;
	po[2].x = x;
	po[2].y = y + 24 - 2;
	pDC->SetPolyFillMode(WINDING);
	pDC->Polygon(po, 3);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}
void SankakuR(CDC *pDC, int x, int y)
{
	CBrush BR, *oldB; // oldB は、使う必要はありません。(選択前の、古いブラシのポインタを保存します。)
	BR.CreateSolidBrush(sankakuRGB);// RGB(0,255,255) ); // BR を水色のブラシとする
	oldB = pDC->SelectObject(&BR); // ブラシ BR を選択します。(以後の塗りつぶしには BR が使用されます。)
	POINT po[5];
	po[0].x = x - 11;
	po[0].y = y + 12 - 1;
	po[1].x = x;
	po[1].y = y;
	po[2].x = x;
	po[2].y = y + 24 - 2;
	pDC->SetPolyFillMode(WINDING);
	pDC->Polygon(po, 3);
	pDC->SelectObject(oldB); // ブラシを元に戻します。
}

void CCapNYS2Dlg::DispSlider(int f)//0:消去 1:デフォルト 2:初期設定
{//全体を右に10ずらす
//	slideh=29;
	if(trimposa<0||//trimposb>slidew||
		trimposa>trimposb||currentframe<0||maxframenum<=0){
		if(f==1)return;
	}
	if(	trimposb>slidew)trimposb=slidew;
	CDC *pDC=m_moviept.GetDC();
	CDC	MemDC;
	CBitmap bmpMem;
	MemDC.CreateCompatibleDC(pDC);
	bmpMem.CreateCompatibleBitmap(pDC,slidew+100,slideh+100);
	CBitmap* pOldBmp=MemDC.SelectObject(&bmpMem);
	int wab=trimposb-trimposa;//,dy=27;
	MemDC.FillSolidRect(0,0,slidew+20,slideh,grayRGB);
	if(f==2){//初期設定表示
		MemDC.FillSolidRect(10,0,slidew+1,slideh,wakuRGB);//(234,232,216));//塗りつぶし
		MemDC.FillSolidRect(10,0,wab+1,slideh,haniRGB);
		SankakuL(&MemDC,10,3);
		SankakuR(&MemDC,10+slidew,3);
		Hisigata(&MemDC,10,3);
	}else if(f==1){//1:default  0：slideを消すだけ
	//枠内塗りつぶし
		MemDC.FillSolidRect(10,0,slidew+1,slideh,wakuRGB);//(234,232,216));//塗りつぶし
	//範囲(a-b)
		MemDC.FillSolidRect(10+trimposa,0,wab+1,slideh,haniRGB);
		SankakuL(&MemDC,10+trimposa,3);
		SankakuR(&MemDC,10+trimposb,3);
	//菱形
		Hisigata(&MemDC,10+slidew*currentframe/maxframenum,3);//int(double(WI)*(pos/avilen))+tx0(),Y0+1);
	}
	//ちらつき防止：temporaryCDCに描いたsliderを実際のsliderにコピー
	pDC->BitBlt(0,0,slidew+20,slideh,&MemDC,0,0,SRCCOPY);
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}
//0:capture 1:preview 2:play 3:disp
//0:del 1:setid 2:toref矢印 3:memo 4:changeid 5:curplay 6:video 7:listref 8:listcurrent 9:listavi 
//15:sensor 16:camnum 17:sen_onof 18:nextcom

int CheckPicPos(int mode, int x, int y)
{
	int i, r = -1;
	if (mode == CaptMode || mode == PrevMode||mode==ListMode)return -1;
	for (i = 0; i<9; i++) {
		if (x >= PicPos[i][0] && y >= PicPos[i][1] && x<PicPos[i][0] + PicPos[i][2] && y<PicPos[i][1] + PicPos[i][3]) {
			r = i;
		}
	}
	if (mode == PlayMode) {//slider上なら（GWINの下1/5も含めて)
		if (checkslider(x, y) >=  0)r = -1;
	}
	return r;
}
//0:capture 1:preview 2:play 3:disp
//0:del 1:setid 2:toref矢印 3:memo 4:changeid 5:curplay 6:video 7:listref 8:listcurrent 9:listavi 
//15:sensor 16:camnum 17:sen_onof 18:nextcom

int checkslider(int x, int y)
{
	if (y >= slidey - Gwinh/10 && y<slidey + slideh + 30) {
		if (x >= slidex - 15 && x <= slidex + 15 + slidew) {
			if (x<slidex)return 0;
			else if (x>slidex + slidew)return slidew;
			else return x - slidex;
		}
	}
	else if (x>Gwinx && x<Gwinx + Gwinw && y>Gwiny && y<Gwiny + Gwinh) {
		return -2;
	}
	return -1;
}

bool checkavifn(char *fn)
{
	if (strlen(fn)<20)return false;
	if (strlen(fn)>300)return false;
	if (!(strstr(fn, ".avi") || strstr(fn, ".wmv")))return false;
	return true;
}
void GetQuartanion(int f, float *q0, float *q1, float *q2, float *q3)
{
	if (f == 7) {//左上
		*q0 = .9F;
		*q1 = -.4F;
		*q2 = -.04F;
		*q3 = -0.280F;
	}
	else if (f == 8) {//上向きの表示
		*q0 = .9F;
		*q1 = -.4F;
		*q2 = 0.0F;
		*q3 = 0.0F;
	}
	else if (f == 9) {//右上
		*q0 = .9F;
		*q1 = -.4F;
		*q2 = .04F;
		*q3 = .280F;
	}
	else if (f == 4) {//左
		*q0 = .9F;
		*q1 = .0F;
		*q2 = .0F;
		*q3 = -.40F;
	}
	else if (f == 5) {//正面
		*q0 = .99F;
		*q1 = .0F;
		*q2 = .0F;
		*q3 = .0F;
	}
	else if (f == 6) {//右
		*q0 = .9F;
		*q1 = .0F;
		*q2 = .0F;
		*q3 = .40F;
	}
	else if (f == 1) {//左下
		*q0 = .9F;
		*q1 = .4F;
		*q2 = -.04F;
		*q3 = -.360F;
	}
	else if (f == 2) {//下
		*q0 = .9F;
		*q1 = .4F;
		*q2 = .0F;
		*q3 = .0F;
	}
	else {//3 右下
		*q0 = .9F;
		*q1 = .4F;
		*q2 = .04F;
		*q3 = .360F;
	}
}

void CCapNYS2Dlg::OnBnClickedPlaymovie()
{
	if (CapNYSmode == PlayMode) {
		if (m_pPlayThread) {//!=NULL){
			if (!moviepausef) {//SetFrame<0){
				if (currentframe>maxframenum - 2)SetFrame = 0;
				else SetFrame = currentframe;
				moviepausef = true;
			}
			else {
				moviepausef = false;//SetFrame=-1;
			}
		}
		else {
			if (strlen(playingfn)<3 || !IsFile(playingfn))return;
			sliderf = 0;
			currentframe = 0;
			DispSlider();
			moviepausef = false;
			m_pPlayThread = AfxBeginThread(PlayThread, this);
			Dispfname(playingfn);
		}
	}
	else if (CapNYSmode == ListMode) {
		if (!checkavifn(listaviselected))return;
		SetButtons(CapNYSmode = PlayMode);
		strcpy_s(playingfn, 300, listaviselected);
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		DispSlider();
		moviepausef = false;
		m_pPlayThread = AfxBeginThread(PlayThread, this);
		Dispfname(playingfn);
	}
}

void CCapNYS2Dlg::OnStnClickedArrowore()//矢印俺
{
	char refer[301];
	char memo[200];
	if (CapNYSmode == PlayMode && checkavifn(playingfn)) {
		strcpy_s(refer, 300, playingfn);
	}
	else {
		return;
	}
	if (refer[strlen(refer) - 18] != '2')return;//123456782071......
	refer[strlen(refer) - 26] = '9';
	refer[strlen(refer) - 25] = '9';
	refer[strlen(refer) - 24] = '0';
	refer[strlen(refer) - 23] = '0';
	refer[strlen(refer) - 22] = '0';
	refer[strlen(refer) - 21] = '0';
	refer[strlen(refer) - 20] = '0';
	refer[strlen(refer) - 19] = '0';
	if (IsFile(refer))return;
	CopyFile(playingfn, refer, FALSE);//上書き

	int insn;
	insn = m_listref.InsertItem(m_listref.GetItemCount(), NULL, 1);//add to the tail
	m_listref.SetItemText(insn, 1, refer);
	SetEN(memo, playingfn);
	memo[16] = '\0';
	m_listref.SetItemText(insn, 0, memo);

	Addfn2listavi(&m_listavi, refer, memo);
	DispNum_sub(&m_totalnum, m_listavi.GetItemCount());

//	strcpy_s(buf, 300, dlg.m_memotxt);
//	m_listref.SetItemText(i, 0, buf);
//	AfxMessageBox(refer);
	setmp3infp(refer, memo);// , "");//tag情報(title)に書き込む。
}

int CCapNYS2Dlg::setNGpos(CPoint pos)
{
	int x = pos.x, y = pos.y;
	int x0, y0, x1, y1, x2, y2, x3, y3;
	x0 = Gwinx;
	x1 = Gwinx + Gwinw / 3;
	x2 = Gwinx + 2 * Gwinw / 3;
	x3 = Gwinx + Gwinw;
	y0 = Gwiny;
	y1 = Gwiny + Gwinh / 3;
	y2 = Gwiny + 2 * Gwinh / 3;
	y3 = Gwiny + Gwinh;
	if (x>x0&&x <= x1) {
		if (y>y0&&y <= y1)return 7;
		if (y>y1&&y <= y2)return 4;
		if (y>y2&&y <= y3)return 1;
	}
	else if (x>x1&&x <= x2) {
		if (y>y0&&y <= y1)return 8;
		if (y>y1&&y <= y2)return 5;
		if (y>y2&&y <= y3)return 2;
	}
	else if (x>x2&&x <= x3) {
		if (y>y0&&y <= y1)return 9;
		if (y>y1&&y <= y2)return 6;
		if (y>y2&&y <= y3)return 3;
	}
	return 5;
}
void CCapNYS2Dlg::OnBnClickedResetrec()
{
	ArduinoM5ThreadF = false;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}

void CCapNYS2Dlg::OnBnClickedResethead()
{
	if (strstr(ptxt[SENM], "0")){
		if (strstr(ptxt[SISE], "1"))strcpy_s(ptxt[SISE], "2");
		else strcpy_s(ptxt[SISE], "1");
	}
	else {
		Resetheadfcnt = 5;
		cq0 = nq0; cq3 = -nq3;
	}
	//AfxMessageBox("resethead");
}
void CCapNYS2Dlg::OnMouseMove(UINT nFlags, CPoint point)
{

	if (CapNYSmode == PlayMode) {
		int x = checkslider(point.x, point.y);
		if (sliderf) {
			if (x >= 0) {
				if (x*maxframenum / slidew >= maxframenum)SetFrame = maxframenum - 1;//かたまりそう？
				else SetFrame = x*maxframenum / slidew;
			}
			else {
				sliderf = 0;
			}
		}
		if (sliderf == 1) {
			if (x + sankakuzure<trimposb - 20)trimposa = x + sankakuzure;
			else trimposa = trimposb - 20;
			if (trimposa<0)trimposa = 0;
		}
		else if (sliderf == 3) {
			if (x + sankakuzure>trimposa + 20)trimposb = x + sankakuzure;
			else trimposb = trimposa + 20;
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CCapNYS2Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	InvalidateRect(false);
	// TODO: ここにメッセージ ハンドラー コードを追加します。
}

void CCapNYS2Dlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int x = checkslider(point.x, point.y);
	if (CapNYSmode == PlayMode) {
		if (x >= 0) {
			OnBnClickedPlaymovie();
		}
	}
	CDialogEx::OnLButtonDblClk(nFlags, point);
}
//0:capture 1:preview 2:play 3:disp
//0:del 1:setid 2:toref矢印 3:memo 4:changeid 5:curplay 6:video 7:listref 8:listcurrent 9:listavi 
//15:sensor 16:camnum 17:sen_onof 18:nextcom
//bool changingDownf;
void CCapNYS2Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	ldownf = 1;
	PicPosflag = CheckPicPos(CapNYSmode, point.x, point.y);
	if (PicPosflag == 6) {
		if (ldownf == 1) {
			HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);     // handカーソル
			SetCursor(hCursor);//DC_ARROW
		}
		else {
			PicPosflag = -1;
		}
	}
	if (CapNYSmode == PlayMode) {//pretranslateでslider以外の処理は済んでいる

		int x = checkslider(point.x, point.y);
		if (x >= 0) {
			if (!m_pPlayThread) {
				m_pPlayThread = AfxBeginThread(PlayThread, this);
				sliderf = 0;
			}
			if (x>trimposa - 14 && x<trimposa + 14) {
				sankakuzure = trimposa - x;
				sliderf = 1;
			}
			else if (x>trimposb - 14 && x<trimposb + 14) {
				sankakuzure = trimposb - x;
				sliderf = 3;
			}
			else {
				sliderf = 2;
			}
			SetFrame = x*maxframenum / slidew;
			moviepausef = true;
		}
	}
//	else if (CapNYSmode == CaptMode) {
//		m_down_x =m_move_x= point.x;
//	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CCapNYS2Dlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (CapNYSmode == PlayMode) {
		int x = CheckPicPos(CapNYSmode, point.x, point.y);
		if (x == 6) {
			CMenu    *popupMenuP = NULL;
			CMenu    cMenu;
			int      err = 0;
			// メニューをロード
			if (!err) if (!cMenu.LoadMenu(English ? IDR_MENU7E : IDR_MENU7)) err = 1;
			// サブメニューを取得
			if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
			// メニューをポップアップ
			if (!err)
			{
				ClientToScreen(&point);
				if (!popupMenuP->TrackPopupMenu(
					TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
			}
			// メニューを破棄
			cMenu.DestroyMenu();
		}
	}
	CDialogEx::OnRButtonDown(nFlags, point);
}
void CCapNYS2Dlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	sliderf = 0;
	CDialogEx::OnRButtonUp(nFlags, point);
}
void CCapNYS2Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	int x;
	if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
//		if(point.x-m_down_x<2 && point.x-m_down_x>-2){
			if (!Para0(SENM)) {
				int n = setNGpos(point);
				GetQuartanion(n, &mnq0, &mnq1, &mnq2, &mnq3);
			}
//撮影範囲を動かす操作で正面を向いてしまうことがない様に、ここは削除した。正面を向かせるときは顔マークを
			else {
//				if (!(nq0 == 0.01F&&nq1 == 0.0F&&nq2 == 0.0F&&nq3 == 0.0F)) {//センサーがまだ起動していないときは書き直さない！！！！！！！！！！！！！！！！！！！！！！
	//			cq0 = nq0; cq1 = -nq1; cq2 = -nq2; cq3 = -nq3;
				cq0 = nq0; cq3 = -nq3;
				//				}
	//			float fq = nq1*nq1 + nq2*nq2;

		//		if (fq<0.2F || fq>0.87F)strcpy_s(ptxt[SISE], "1");// sisei = 1;//version 5.7
			//	else strcpy_s(ptxt[SISE], "2");// sisei = 2;//version 5.7


//				if (fq<0.2F || fq>0.87F)sisei = 1;//version 5.7
//				else sisei = 2;//version 5.7
			}
	//	}
	
		CDialogEx::OnLButtonUp(nFlags, point);
		return;
	}//録画モードは終了
	if (sliderf == 2) {
		x = checkslider(point.x, point.y);
		if (x >= 0) {
			SetFrame = x*maxframenum / slidew;
		}
		sliderf = 0;
	}
	else if (sliderf == 1 || sliderf == 3) {
		sliderf = 0;
	}//slider処理は終了
	else {
		x = CheckPicPos(CapNYSmode, point.x, point.y);
		if (x == 6 && PicPosflag == 6) {//playmovie
			OnBnClickedPlaymovie();
		}
	}
	//x==7 ListCtrl上でのButtonUpDownは検知できないので、pretranslateでチェック
	PicPosflag = -1;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CCapNYS2Dlg::OnBnClickedCancel()
{
	m_CaploopEnable = false;
	m_PlayloopEnable = false;
	m_PrevloopEnable = false;
	Sleep(300);
	CDialogEx::OnCancel();
}


void CCapNYS2Dlg::OnBnClickedList()
{
	m_PlayloopEnable = false;
	m_PrevloopEnable = false;
	Sleep(300);//timer でerase
	KillTimer(1);
	CDC* pDC = GetDC();
	pDC->FillSolidRect(Gwinx, Gwiny, Gwinw, Gwinh, RGB(255, 255, 255));
	ReleaseDC(pDC);
	SetButtons(CapNYSmode = ListMode);
	//直前に録画した
	SetlistaviSize0(&m_listavi);
//	if (strstr(ptxt[LENG], "1"))SetlistaviSize0(&m_listavi);
//	else SetlistaviSize_bit(&m_listavi);
	DispNum_sub(&m_currentid, IDnum);
}


void CCapNYS2Dlg::OnItemchangingListcurrent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (CapNYSmode == CaptMode) {
		*pResult = 0;
		return;
	}
	if ((pNMLV->uChanged & LVIF_STATE) &&
		(pNMLV->uNewState & LVIS_SELECTED))
	{
		if (CapNYSmode == CaptMode)return;
		char path[301];
		m_listcurrent.GetItemText(pNMLV->iItem, 1, path, 300);
		strcpy_s(playingfn, 300, path);
		if (m_PlayloopEnable)m_PlayloopEnable = false;
		m_PrevloopEnable = false;
		trimposb = slidew;
		trimposa = 0;
		currentframe = 0;
		KillTimer(1);
		DispSlider(2);
		SetButtons(CapNYSmode = PlayMode);
		DispOneFrame(playingfn, 0);
		DispTimeTrim();
		Dispfname(playingfn);
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	*pResult = 0;
}

void CCapNYS2Dlg::OnItemchangingListref(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if (CapNYSmode == CaptMode) {
		*pResult = 0;
		return;
	}
	if ((pNMLV->uChanged & LVIF_STATE) &&
		(pNMLV->uNewState & LVIS_SELECTED))
	{
		char path[301];
		m_listref.GetItemText(pNMLV->iItem, 1, path, 300);
		strcpy_s(playingfn, 300, path);
		if (m_PlayloopEnable)m_PlayloopEnable = false;
		m_PrevloopEnable = false;
		trimposb = slidew;
		trimposa = 0;
		currentframe = 0;
		KillTimer(1);
		DispSlider(2);
		SetButtons(CapNYSmode = PlayMode);
		DispOneFrame(playingfn, 0);
		DispTimeTrim();
		Dispfname(playingfn);
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	*pResult = 0;
}

void CCapNYS2Dlg::OnItemchangingListavi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	if ((pNMLV->uChanged & LVIF_STATE) &&
		(pNMLV->uNewState & LVIS_SELECTED))
	{
		char path[301];
		m_listavi.GetItemText(pNMLV->iItem, 4, path, 300);
		strcpy_s(listaviselected, 300, path);
		if (m_PlayloopEnable)m_PlayloopEnable = false;
		trimposb = slidew;
		trimposa = 0;
		currentframe = 0;
	}
	*pResult = 0;
}

void CCapNYS2Dlg::OnDblclkListavi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	char fn[301];

	if (IsFile(listaviselected)) {

		SetEN(fn, listaviselected);
		fn[8] = '\0';
		sscanf_s(fn, "%d", &IDnum);
//		MessageBox(fn);
		if (fn[0]=='9' && fn[1]=='9' && fn[2]=='0') {
//			MessageBox("onaji");
			OnBnClickedPlaymovie();
		}
		else {
			//			MessageBox("tigau");
			//		}
			Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);

			strcpy_s(playingfn, 300, listaviselected);
			sliderf = 0;
			trimposa = 0;
			trimposb = slidew;
			currentframe = 0;
			DispSlider();
			moviepausef = false;
			m_pPlayThread = AfxBeginThread(PlayThread, this);
			SetButtons(CapNYSmode = PlayMode);
			Dispfname(playingfn);
		}
	}
	*pResult = 0;
}


void CCapNYS2Dlg::OnDblclkListcurrent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem<0) {
		*pResult = 0;
		return;
	}
	if (IsFile(playingfn) && CapNYSmode == PlayMode) {
		m_PlayloopEnable = false;
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		DispSlider();
		moviepausef = false;
		m_pPlayThread = AfxBeginThread(PlayThread, this);
		Dispfname(playingfn);
	}
	*pResult = 0;
}


void CCapNYS2Dlg::OnDblclkListref(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem<0) {
		*pResult = 0;
		return;
	}
	if (IsFile(playingfn) && CapNYSmode == PlayMode) {
		m_PlayloopEnable = false;
		sliderf = 0;
		trimposa = 0;
		trimposb = slidew;
		currentframe = 0;
		DispSlider();
		moviepausef = false;
		m_pPlayThread = AfxBeginThread(PlayThread, this);
		Dispfname(playingfn);
	}

	*pResult = 0;
}

void CCapNYS2Dlg::OnRclickListavi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem<0) {
		*pResult = 0;
		return;
	}
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CPoint pt;
	GetCursorPos(&pt);
	CMenu    *popupMenuP = NULL;
	CMenu    cMenu;
	int      err = 0;
	if (!err) if (!cMenu.LoadMenu(English ? IDR_MENU3E : IDR_MENU3)) err = 1;
	if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
	if (!err)
	{
		if (!popupMenuP->TrackPopupMenu(TPM_LEFTBUTTON, pt.x, pt.y, this)) err = 1;
	}
	// メニューを破棄
	cMenu.DestroyMenu();
	*pResult = 0;
}
void CCapNYS2Dlg::OnRclickListcurrent(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (CapNYSmode == CaptMode) {
		*pResult = 0;
		return;
	}
	if (pNMItemActivate->iItem<0) {
		*pResult = 0;
		return;
	}
	CPoint pt;
	GetCursorPos(&pt);
	CMenu    *popupMenuP = NULL;
	CMenu    cMenu;
	int      err = 0;
	if (!err) if (!cMenu.LoadMenu(English ? IDR_MENU2E : IDR_MENU2)) err = 1;
	if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
	if (!err)
	{
		if (!popupMenuP->TrackPopupMenu(TPM_LEFTBUTTON, pt.x, pt.y, this)) err = 1;
	}
	// メニューを破棄
	cMenu.DestroyMenu();
	*pResult = 0;
}

void CCapNYS2Dlg::OnRclickListref(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (CapNYSmode == CaptMode) {
		*pResult = 0;
		return;
	}
	if (pNMItemActivate->iItem<0) {
		*pResult = 0;
		return;
	}
	CPoint pt;
	GetCursorPos(&pt);
	CMenu    *popupMenuP = NULL;
	CMenu    cMenu;
	int      err = 0;
	if (!err) if (!cMenu.LoadMenu(English ? IDR_MENU1E:IDR_MENU1)) err = 1;
	if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
	if (!err)
	{
		MENUITEMINFO mii = { sizeof(mii) };
		mii.fMask = MIIM_STRING;
			
		mii.dwTypeData = GetCurrentMemo();
		//GetCurrentMemo(&mii.dwTypeData);
		popupMenuP->SetMenuItemInfoA(0, &mii, TRUE);

		if (!popupMenuP->TrackPopupMenu(TPM_LEFTBUTTON, pt.x, pt.y, this)) err = 1;
	}
	// メニューを破棄
	cMenu.DestroyMenu();
	//	MessageBox(playingfn);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	*pResult = 0;
}

void dispbackup(CDC *pDC, int f1, int t1, char *ymd, int type)
{
	char buf[200];
	int x = Gwinw / 3, y = 30;
	x = 6 + 15 + 5 * 90;
	y = 5;
	if (type == 0) {//跡形もなく消す
		pDC->FillSolidRect(x - 1, y - 1, 172, 60, grayRGB);
	}
	else {
		pDC->FillSolidRect(x - 1, y - 1, 172, 60, grayRGB);
		sprintf_s(buf, "backup : %04d / %04d", f1, t1);
		pDC->TextOutA(x + 12, y + 26, buf);
		sprintf_s(buf, "%s????????", ymd);
		buf[8] = 0;
		pDC->TextOutA(x + 12, y + 6, buf);
	}
}
void CCapNYS2Dlg::OnBnClickedCurplay()
{
	SetButtons(CapNYSmode = PlayMode);
	Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
	CDC *pDC = GetDC();
	dispbackup(pDC, 0, 0, "", 0);// 0, 0, 0);//backupの表示を消す
	ReleaseDC(pDC);
}


void CCapNYS2Dlg::OnBnClickedCutmovie()
{
	CTrim dlg;
	if (trimposa == 0 && trimposb == slidew) {
		MessageBox("same length, no change !");
		return;
	}
	if (trimposa == trimposb)return;
	if (!strstr(playingfn, ".wmv"))return;//.wmv でなければ、今のところtrim不能

	m_PlayloopEnable = false;
	SetTrimName(trimingfn, playingfn, trimposa);
	strcpy_s(dlg.m_trimfn1, playingfn);
	strcpy_s(dlg.m_trimfn2, trimingfn);
	dlg.m_posa = trimposa;
	dlg.m_posb = trimposb;
	if (dlg.DoModal() == IDOK) {
		Addfn2listavi(&m_listavi, trimingfn, "");
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		Sleep(300);
		if (dlg.checkON == false) {//erase original
			Delete1item(&m_listavi, &m_listcurrent, &m_listref, playingfn);
			f2gomi(playingfn);
			strcpy_s(playingfn, trimingfn);
			trimposa = 0;
			trimposb = slidew;
			currentframe = 0;
			DispSlider(2);
			DispOneFrame(playingfn, 0);
			Dispfname(playingfn);
		}
	}
	else {
		Sleep(300);
		if (IsFile(trimingfn))CFile::Remove(trimingfn);
	}
	DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
}
void SetEN(char *path, char *fullpath, int mode)//1:path 2:2017\path 0:.....\2017￥ CapENT
{//CapNYS  0:....gazou￥ 1:0123456782017...  2:2017....
	int i;
	if (strlen(fullpath) == 0) {
		strcpy_s(path, 50, "");
		return;
	}
	for (i = strlen(fullpath); i>0; i--) {
		if (fullpath[i] == '\\')break;
	}
	if (mode == 0) {//.....gazou￥ まで
		strcpy_s(path,300, fullpath);
		path[i+1] = '\0';
		return;
	}
	strcpy_s(path, 50, &fullpath[i + 1]);
	if (mode == 1)return;//1234567820170603121212.jpg
	strcpy_s(path, 50, &fullpath[strlen(fullpath)-18]);
	if (mode == 2)return;//2017....jpg
}

void CCapNYS2Dlg::SetTrimName(char* tfn, char* pfn, int n)
{//21xx年というwmvのこともあるのでyear部分は年号フォルダからモラル
	int i, id, y, mo, d, h, m, s, damy, ns;
	char b[301];
	//CTime ct;
	CTimeSpan cts(0, 0, 0, 1);//1second
	SetEN(b, pfn, 2);
	b[4] = '\0';
	sscanf_s(b, "%d", &y);
	SetEN(b, pfn, 1);
	sscanf_s(b, "%08d%04d%02d%02d%02d%02d%02d.wmv", &id, &damy, &mo, &d, &h, &m, &s);
	CTime ct(y, mo, d, h, m, s);
	ns = n*maxframenum / slidew / Para0(FPSN);//currentframe/Para0(FPSN);
	if (ns == 0)ns = 1;
	for (i = 0; i<ns; i++)ct += cts;//1secを加える
	SetEN(b, pfn, 0);
	while (1) {
		sprintf_s(tfn, 300, "%s%08d%04d%02d%02d%02d%02d%02d.wmv", b, id,y = ct.GetYear(), mo = ct.GetMonth(), d = ct.GetDay(), h = ct.GetHour(), m = ct.GetMinute(), s = ct.GetSecond());
		if (!IsFile(tfn))break;
		ct += cts;
	}
}

void CCapNYS2Dlg::OnPopupEditmemo()//listref
{
	OnClickedMemo();
}

void CCapNYS2Dlg::OnPopupEditmemo2()
{
	OnClickedMemo();
}

void CCapNYS2Dlg::OnPopupEditmemo3()
{
	OnClickedMemo();
}

void CCapNYS2Dlg::OnPopupChangeid2()
{
	int i, j, sc, tempid;
	char fn[301],newfn[301], num[101];
	CGetID dlg;	
	if (IsFile(playingfn)){// && playingfn[strlen(playingfn) - 26] != '9') {//9???????参照ファイルの場合は変更不可		
	//	mode2chanf = true;
		SetEN(fn, playingfn);
		fn[8] = '\0';
		sscanf_s(fn, "%d", &i);
		dlg.m_IDnum = i;
		if (dlg.DoModal() == IDOK) {
			tempid = dlg.m_IDnum;
			if (i == tempid)return;
			sc = m_listavi.GetItemCount();
			for (i = 0; i<sc; i++) {
				m_listavi.GetItemText(i, 4, fn, 300);
				if (strstr(fn, playingfn)) {
					sprintf_s(num, "%08d", tempid);//IDnum);
					strcpy_s(newfn, fn);
					CTrim dlg1;
					for (j = 0; j<8; j++) {
						newfn[strlen(newfn) - 26 + j] = num[j];
					}
					strcpy_s(dlg1.m_trimfn1, fn);
					strcpy_s(dlg1.m_trimfn2, newfn);
					dlg1.m_newid = tempid;
					dlg1.m_posa = 0;
					dlg1.m_posb = 0;
					if (dlg1.DoModal() == IDOK) {
						m_listavi.SetItemText(i, 0, num);//IDを変更する。
						strcpy_s(playingfn, newfn);
						m_listavi.SetItemText(i, 4, playingfn);
						if (IsFile(fn))CFile::Remove(fn);
						Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);

						trimposa = 0;
						trimposb = slidew;
						currentframe = 0;
						DispSlider(2);
						DispOneFrame(playingfn, 0);
						Dispfname(playingfn);
					}
					else {
						if (IsFile(newfn))CFile::Remove(newfn);
					}
					break;
				}
			}
		}
		DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
	}
}

void CCapNYS2Dlg::OnPopupChangeid3()
{
	OnClickedChanid();
}


void CCapNYS2Dlg::OnPopupDelete()
{
	if (IsFile(playingfn)) {
		m_PlayloopEnable = false;
		Delete1item(&m_listavi, &m_listcurrent, &m_listref, playingfn);
		f2gomi(playingfn);
		if (strstr(listaviselected, playingfn)) {
			SetButtons(CapNYSmode = ListMode);
			DispSlider(0);
		}
		strcpy_s(playingfn, 300, "");
		CDC *pDC = GetDC();
		pDC->FillSolidRect(Gwinx, Gwiny, Gwinw, Gwinh, RGB(200, 200, 255));
		pDC->FillSolidRect(Gwinx - 32, Gwiny, 32, Gwinh, grayRGB);//toref矢印を消す
		ReleaseDC(pDC);
		SetButtons(CapNYSmode = PrevMode);
		DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
	}
	else {
		Delete1item(&m_listavi, &m_listcurrent, &m_listref, playingfn);
	}
}

void CCapNYS2Dlg::OnPopupDelete2()
{
	OnPopupDelete();
}
/*
void CCapNYS2Dlg::OnPopupDelete3()
{
	if (IsFile(listaviselected)) {
		m_PlayloopEnable = false;
		Delete1item(&m_listavi, &m_listcurrent, &m_listref, listaviselected);
		f2gomi(listaviselected);
		strcpy_s(listaviselected, 300, "");
		DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
	}
	else {
		Delete1item(&m_listavi, &m_listcurrent, &m_listref, listaviselected);
	}
	MessageBox("delete3");
}*/

void CCapNYS2Dlg::OnPopupCopy()
{
	char fn[301], path[301];
	strcpy_s(path, playingfn);
	SetEN(fn, playingfn);
	CString SetFPath;
	if (strstr(fn, ".wmv") || strstr(fn, ".WMV")) {
		CFileDialog myDLG(FALSE, "wmv", fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.wmv)|*.wmv||", NULL);
		if (myDLG.DoModal() == IDOK) {
			SetFPath = myDLG.GetPathName();
			CopyFile(path, SetFPath, FALSE);
		}
	}
	else {
		CFileDialog myDLG(FALSE, "avi", fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.avi)|*.avi||", NULL);
		if (myDLG.DoModal() == IDOK) {
			SetFPath = myDLG.GetPathName();
			CopyFile(path, SetFPath, FALSE);
		}
	}
}

void CCapNYS2Dlg::OnPopupCopy2()
{
	char fn[301], path[301];
	strcpy_s(path, playingfn);
	SetEN(fn, playingfn);
	CString SetFPath;
	if (strstr(fn, ".wmv") || strstr(fn, ".WMV")) {
		CFileDialog myDLG(FALSE, "wmv", fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.wmv)|*.wmv||", NULL);
		if (myDLG.DoModal() == IDOK) {
			SetFPath = myDLG.GetPathName();
			CopyFile(path, SetFPath, FALSE);
		}
	}
	else {
		CFileDialog myDLG(FALSE, "avi", fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.avi)|*.avi||", NULL);
		if (myDLG.DoModal() == IDOK) {
			SetFPath = myDLG.GetPathName();
			CopyFile(path, SetFPath, FALSE);
		}
	}
}

void CCapNYS2Dlg::OnPopupCopy3()
{
	char fn[301], path[301];
	strcpy_s(path, listaviselected);
	SetEN(fn, listaviselected);
	CString SetFPath;
	if (strstr(fn, ".wmv") || strstr(fn, ".WMV")) {
		CFileDialog myDLG(FALSE, "wmv", fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.wmv)|*.wmv||", NULL);
		if (myDLG.DoModal() == IDOK) {
			SetFPath = myDLG.GetPathName();
			CopyFile(path, SetFPath, FALSE);
		}
	}
	else {
		CFileDialog myDLG(FALSE, "avi", fn,
			OFN_OVERWRITEPROMPT,
			"movie(*.avi)|*.avi||", NULL);
		if (myDLG.DoModal() == IDOK) {
			SetFPath = myDLG.GetPathName();
			CopyFile(path, SetFPath, FALSE);
		}
	}
}

void CCapNYS2Dlg::OnClickedRecord()
{
	if (GetKeyState(VK_SHIFT) & 0x8000) {
		changeCSIZflag = true;
	}
	else {
		changeCSIZflag = false;
	}
	m_PlayloopEnable = false;
	//	m_PrevloopEnable = false;
	//	iPhoneThreadF = false;

	Preview();// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
int CALLBACK CCapNYS2Dlg::MyCompareProc1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CCapNYS2Dlg* pMyDlg = (CCapNYS2Dlg*)lParamSort;
	LPARAM nSubItem = pMyDlg->m_iSubItem;
	CString    strItem1 = pMyDlg->m_listavi.GetItemText(lParam1, nSubItem);
	CString    strItem2 = pMyDlg->m_listavi.GetItemText(lParam2, nSubItem);
	return strcmp(strItem1, strItem2);
}
int CALLBACK CCapNYS2Dlg::MyCompareProc2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CCapNYS2Dlg* pMyDlg = (CCapNYS2Dlg*)lParamSort;
	LPARAM nSubItem = pMyDlg->m_iSubItem;
	CString    strItem1 = pMyDlg->m_listavi.GetItemText(lParam1, nSubItem);
	CString    strItem2 = pMyDlg->m_listavi.GetItemText(lParam2, nSubItem);
	return strcmp(strItem2, strItem1);
}

int CALLBACK CCapNYS2Dlg::MyCompareProcInt1(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CCapNYS2Dlg* pMyDlg = (CCapNYS2Dlg*)lParamSort;
	LPARAM nSubItem = pMyDlg->m_iSubItem;
	CString    strItem1 = pMyDlg->m_listavi.GetItemText(lParam1, nSubItem);
	CString    strItem2 = pMyDlg->m_listavi.GetItemText(lParam2, nSubItem);

	int i1 = _ttoi(strItem1);
	int i2 = _ttoi(strItem2);
	return i1 - i2;
}
int CALLBACK CCapNYS2Dlg::MyCompareProcInt2(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	CCapNYS2Dlg* pMyDlg = (CCapNYS2Dlg*)lParamSort;
	LPARAM nSubItem = pMyDlg->m_iSubItem;
	CString    strItem1 = pMyDlg->m_listavi.GetItemText(lParam1, nSubItem);
	CString    strItem2 = pMyDlg->m_listavi.GetItemText(lParam2, nSubItem);
	int i1 = _ttoi(strItem1);
	int i2 = _ttoi(strItem2);

	return i2 - i1;
}


void CCapNYS2Dlg::OnColumnclickListavi(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	int i, sc;
	static int sortf[15] = { 0,0,0,0,0,0,0,0,0,0,0 };
	m_iSubItem = pNMLV->iSubItem;

	if (sortf[m_iSubItem] == 1)sortf[m_iSubItem] = 0;
	else sortf[m_iSubItem] = 1;

	if (sortf[m_iSubItem] == 0) {
		//if (m_iSubItem == 2)m_listavi.SortItems(MyCompareProcInt1, (LPARAM)this);
		//else
		m_listavi.SortItems(MyCompareProc1, (LPARAM)this);
	}else {
	//	if (m_iSubItem == 2)m_listavi.SortItems(MyCompareProcInt2, (LPARAM)this);
		//else
		m_listavi.SortItems(MyCompareProc2, (LPARAM)this);
	}
	sc = m_listavi.GetItemCount();
	for (i = 0; i < sc; i++)
		m_listavi.SetItemData(i, (DWORD)i);
	*pResult = 0;
}

void CCapNYS2Dlg::DispIroiro(CStatic* cs, int x0, int y0, int x, int y, int dx,int dy,int mode,int src)
{
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);
	pDC = cs->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	//余白を白で塗り潰す
	if (mode == 1)pDC->FillSolidRect(x0, y0, dx, 70, RGB(255, 255, 255));
	if (mode == 2)pDC->FillSolidRect(x0, y0 - 10, dx, 80, RGB(255, 255, 255));
	if (mode == 3)pDC->FillSolidRect(x0, y0, dx, 82, RGB(255, 255, 255));
	pDC->BitBlt(x0, y0, dx, dy, &MemDC, x, y, src);//(i*dx,0,dx,dy,MemDC,x,0);//,mode);
	cs->ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}

/*void CCapNYS2Dlg::DispNum3(CStatic* id, int x0, int y0, int com)
{
	int i, x, nx0 = 0, ny0 = 47, dx = 11, dy = 20;
	char buf[100];
	CDC MemDC, *pDC;
	CBitmap *pOldBmp, m_bmp;
	m_bmp.LoadBitmap(IDB_NUMBER);

	pDC = id->GetDC();
	MemDC.CreateCompatibleDC(pDC);
	pOldBmp = MemDC.SelectObject(&m_bmp);
	sprintf_s(buf, "%03d", com);
	if (com == 0) {
		pDC->FillSolidRect(x0, y0, 33, 20, RGB(255, 255, 255));
	}
	else if (com == 255) {
		pDC->BitBlt(x0, y0, 33, 20, &MemDC, 707, 8,SRCCOPY);
	}
	else {
		for (i = 0; i < 3; i++) {
			x = (buf[i] - '0')*dx + nx0;
			pDC->BitBlt(x0 + i*(dx - 1), y0, dx, dy, &MemDC, x, ny0, SRCCOPY);
		}
	}
	ReleaseDC(pDC);
	MemDC.SelectObject(pOldBmp);
	DeleteDC(MemDC);
}*/

bool strstr_match(char *str1, char *str2)
{
	while (*str2) {
		if (*str1 != *str2)return false;
		str1++;
		str2++;
	}
	return true;
}

void CCapNYS2Dlg::OnBkup()
{
	CDayretr dlg;
	Trans dlg1;
	int i = 0, j = 0;
	int total = 0, fit = 0;
	char ymd[30],fn[MAX_PATH];
	if (strlen(ptxt[BKUP]) < 5) {
		MessageBox(English ? "Set the BackUp folder!":"バックアップフォルダーが未設定です");
		return;
	}
	if (dlg.DoModal() == IDOK) {
		sprintf_s(ymd, "%d", dlg.ymd);
		if (strlen(ymd) < 4) {
			MessageBox(English ? "within on year!":"年単位のバックアップが限度です");
			return;
		}
		strcpy_s(dlg1.title, "<BackUp> from local to remote");
		strcpy_s(dlg1.ymd, ymd);
		int sc = m_listavi.GetItemCount();
		if (sc == 0)return;
		for (i = 0; i < sc; i++) {
			m_listavi.GetItemText(i, 4, fn, 300);
			if (strstr_match(&fn[strlen(fn) - 18], ymd)) {
				strcpy_s(dlg1.ymdfns[fit], fn);
				strcpy_s(dlg1.ymdfns[fit + 1], "");
				fit++;
			}
			if (fit > 999)break;
		}

		if (dlg1.DoModal() == IDOK) {
		}
	}
}

void CCapNYS2Dlg::OnSetbkf()
{
	char cdr[MAX_PATH], buf[MAX_PATH];
	LPMALLOC pma;
	BROWSEINFO bif;
	LPITEMIDLIST iil;
	sprintf_s(buf, "Folder for Backup : %s", ptxt[BKUP]);
	if (::SHGetMalloc(&pma) == NOERROR)//Shell の標準のアロケータを取得
	{
		GetCurrentDirectory(sizeof(cdr), cdr);
		memset(&bif, 0x00, sizeof(bif));
		bif.hwndOwner = m_hWnd;//GetSafeHwnd();
		bif.pidlRoot = NULL;
		bif.pszDisplayName = cdr;
		bif.lpszTitle = buf;//"Backupフォルダ"
		bif.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
		bif.lpfn = NULL;
		bif.lParam = 0;
		if ((iil = SHBrowseForFolder(&bif)))
		{
			if (::SHGetPathFromIDList(iil, ptxt[BKUP]))//SaveFolder))
			{//bufに選択されたパスが入っています。
				TRACE("buf=%s\n", ptxt[BKUP]);//SaveFolder);
			}
			//iilを解放します。
			pma->Free(iil);
			//			m_videofold = ptxt[FOL2]r;

			UpdateData(false);
		}
		pma->Release();
	}	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
char *CCapNYS2Dlg::GetCurrentMemo() {
	int sc = 0;
	char fn[301], buf[305],buf2[301];// , path[301];
	strcpy_s(buf,300,"MEMO;");
	sc = m_listref.GetItemCount();
	if (sc == 0)return(buf);
	for (int i = 0; i < sc; i++) {
		m_listref.GetItemText(i, 1, fn, 300);
		if (strstr(fn, playingfn)) {
		//	SetEN(path, playingfn);//listaviselected);
		//	sprintf_s(buf, "memo of %s", path);
			//dlg.m_memohead = buf;
			m_listref.GetItemText(i, 0, buf2, 300);
			sprintf_s(buf, "MEMO:%s", buf2);
			break;
			//dlg.m_memotxt = buf;
			//return(buf);
		}
	}
	return(buf);
}

void CCapNYS2Dlg::OnClickedMemo()
{
	CSetMemo dlg;
	int i, sc;
	char fn[301], buf[301], path[50];
	if (CapNYSmode == PlayMode&& IsFile(playingfn)&&playingfn[strlen(playingfn) - 26] == '9') {
		
		sc = m_listref.GetItemCount();
		if (sc == 0)return;
		for (i = 0; i < sc; i++) {
			m_listref.GetItemText(i, 1, fn, 300);
			if (strstr(fn, playingfn)) {
				SetEN(path, playingfn);//listaviselected);
				sprintf_s(buf, "memo of %s", path);
				dlg.m_memohead = buf;
				m_listref.GetItemText(i, 0, buf, 300);
				dlg.m_memotxt = buf;
				if (dlg.DoModal() == IDOK) {
					if (strlen(dlg.m_memotxt) > 80) {
						MessageBox("too many characters ! <80");
						return;
					}
					strcpy_s(buf, 300, dlg.m_memotxt);
					m_listref.SetItemText(i, 0, buf);
//					AfxMessageBox(fn);
					setmp3infp(fn, buf);// , "");//tag情報(title)に書き込む。
					break;
				}
			}
		}
	
		sc = m_listavi.GetItemCount();
		if (sc == 0)return;
		for (i = 0; i < sc; i++) {
			m_listavi.GetItemText(i, 4, fn, 300);
			if (strstr(fn, playingfn)) {
				m_listavi.SetItemText(i, 3, buf);//ref->DeleteItem(i);
				break;
			}
		}
	}
	else if (CapNYSmode == ListMode) {
		if (IsFile(listaviselected)) {
			sc = m_listavi.GetItemCount();
			if (sc == 0)return;
			for (i = 0; i < sc; i++) {
				m_listavi.GetItemText(i, 4, fn, 300);
				if (strstr(fn, listaviselected)) {
					//MessageBox("kokodesuyo");
					SetEN(path, listaviselected);
					sprintf_s(buf, "memo of %s", path);
					dlg.m_memohead = buf;
					m_listavi.GetItemText(i, 3, buf, 300);
					dlg.m_memotxt = buf;
					if (dlg.DoModal() == IDOK) {
						strcpy_s(buf, 300, dlg.m_memotxt);
						m_listavi.SetItemText(i, 3, buf);//ref->DeleteItem(i);
						setmp3infp(fn, buf);// , "");//tag情報(title)に書き込む。
	//					char buf1[300], buf2[300];
	//					GetNameArtist(fn, buf1, buf2);
	//					AfxMessageBox(buf1);
					}
					break;
				}
			}
			sc = m_listref.GetItemCount();
			if (sc == 0)return;
			for (i = 0; i < sc; i++) {
				m_listref.GetItemText(i, 1, fn, 300);
				if (strstr(fn, listaviselected)) {
					m_listref.SetItemText(i, 0, buf);
					break;
				}
			}
		}
	}
}

void CCapNYS2Dlg::OnPopupDelete3() {
	OnClickedErasebut();
}

void CCapNYS2Dlg::OnClickedErasebut()
{
	if (IsFile(listaviselected)) {
		int nSelected = m_listavi.GetNextItem(-1, LVNI_SELECTED);

		m_PlayloopEnable = false;
		Delete1item(&m_listavi, &m_listcurrent, &m_listref, listaviselected);
		f2gomi(listaviselected);
		strcpy_s(listaviselected, 300, "");

		int sc = m_listavi.GetItemCount();
		if (nSelected == sc) {//最後なら
			nSelected -= 1;
		}
		if (sc != 0) {//0以外の時は選択させる
			m_listavi.SetItemState(nSelected, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
			m_listavi.SetFocus();
		}
	}
	DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
}


void CCapNYS2Dlg::OnPopupChanid9()
{
	OnStnClickedArrowore();
}


void CCapNYS2Dlg::OnClickedChanid()
{
	int i, j, sc, tempid;
	char fn[301],newfn[301], num[101];
	CGetID dlg;
	if (IsFile(listaviselected)&&listaviselected[strlen(listaviselected)-26]!='9') {//9???????参照ファイルの場合は変更不可
		SetEN(fn, listaviselected);
		fn[8] = '\0';
		sscanf_s(fn, "%d", &i);
		dlg.m_IDnum = i;//元のID
		if (dlg.DoModal() == IDOK) {
			tempid = dlg.m_IDnum;//変更したはずのID
			if (i == tempid)return;
			sc = m_listavi.GetItemCount();
			for (i = 0; i<sc; i++) {
				m_listavi.GetItemText(i, 4, fn, 300);
				if (strstr(fn, listaviselected)) {//元のファイル
					sprintf_s(num, "%08d", tempid);
					strcpy_s(newfn, fn);
					CTrim dlg1;
					for (j = 0; j<8; j++) {
						newfn[strlen(newfn) - 26 + j] = num[j];
					}
					strcpy_s(dlg1.m_trimfn1, fn);
					strcpy_s(dlg1.m_trimfn2, newfn);
					dlg1.m_newid = tempid;
					dlg1.m_posa = 0;
					dlg1.m_posb = 0;
					if (dlg1.DoModal() == IDOK) {
						m_listavi.SetItemText(i, 0, num);//IDを変更する。
						strcpy_s(listaviselected, newfn);
						m_listavi.SetItemText(i, 4, listaviselected);
						if (IsFile(fn))CFile::Remove(fn);
					}
					else {
						if (IsFile(newfn))CFile::Remove(newfn);
					}
						break;
				}
			}
		}
		DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
	}
	else {
		MessageBox(English ? "unselected? or reference file can't be changed!!" : "ファイルが選択されてないか、参照映像ファイルは変更できません");
	}
}


void CCapNYS2Dlg::OnClickedSetid()
{
	CGetNewID dlg;
	char path[30];
	dlg.m_IDnum = 0;
	dlg.m_record_setid = 1;
	if (dlg.DoModal() == IDOK) {
		IDnum = dlg.m_IDnum;
		Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
		m_PrevloopEnable = false;
		DispNum_sub(&m_currentid, IDnum);
		sprintf_s(path, "%08d", IDnum);
		PushfnPtxt(path);
		if (CapNYSmode == ListMode) {
			SetButtons(CapNYSmode = PlayMode);
		}
//		return true;
	}
	//	return false;	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCapNYS2Dlg::OnClickedSave()
{
	if (IsFile(listaviselected)) {
		OnPopupCopy3();
	}
	else {
		MessageBox(English ? "unselected!" : "ファイルが選択されてません");
	}// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCapNYS2Dlg::OnClickedBackup()
{
	OnBkup();
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}


void CCapNYS2Dlg::OnClickedBackupfolder()
{
	OnSetbkf();
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
}
void setComStr(char *buf) {//いい加減に作ったが動いた、いずれチェック！！
	char tbuf[10];
	int i, j;
	sprintf_s(tbuf, "%s(", buf);//COM1( COM13

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 5; j++) {
			if (comStrArray[i][j]!=tbuf[j]) {
				break;
			}
		}
		if (j == 5) {
			strcpy_s(buf, 250,comStrArray[i]);
			return;
		}
	}
}
void CCapNYS2Dlg::OnClickedMenu()
{
	CMenu   *popupMenuP = NULL;
	CMenu	*popMenuP = NULL;
	CMenu   cMenu;
	int     err = 0;
	POINT point;
//	if (CapNYSmode == PlayMode)	MessageBox("play");
//	if (CapNYSmode == CaptMode)	MessageBox("Capt");
//	if (CapNYSmode == PrevMode)	MessageBox("Prev");
	//画面全体でのマウスカーソルの位置を取得
	GetCursorPos(&point);
	if (!err) {
		if (CapNYSmode == PrevMode ) {
			if (!cMenu.LoadMenu(English ? IDR_MENU7E : IDR_MENU7)) err = 1;
		}
		else if (CapNYSmode == CaptMode) {
			if (!cMenu.LoadMenu(English ? IDR_MENU8E : IDR_MENU8)) err = 1;
		}
		else if (CapNYSmode == PlayMode) {
			if (!cMenu.LoadMenu(English ? IDR_MENU7E : IDR_MENU7)) err = 1;
		}
		else if (CapNYSmode == ListMode) {
			if (!cMenu.LoadMenu(English ? IDR_MENU5E : IDR_MENU5)) err = 1;
		}
	}
	if (!err) if ((popupMenuP = cMenu.GetSubMenu(0)) == NULL) err = 1;
	if (!err) {
		ClientToScreen(&point);
		if (CapNYSmode == CaptMode) {
			if (strstr(ptxt[SENM], "0")) {
				popupMenuP->CheckMenuItem(0, MF_BYPOSITION | MF_CHECKED);
			}
			else if (strstr(ptxt[SENM], "1")) {
				popupMenuP->CheckMenuItem(1, MF_BYPOSITION | MF_CHECKED);
			}
			else if (strstr(ptxt[SENM], "2")) {
				popupMenuP->CheckMenuItem(2, MF_BYPOSITION | MF_CHECKED);
			}
			else {
				popupMenuP->CheckMenuItem(3, MF_BYPOSITION | MF_CHECKED);
			}
			popMenuP = popupMenuP->GetSubMenu(4);
			if (!strstr(ptxt[SENM], "0")) {
				if (strstr(ptxt[SXYZ], "1"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION1, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "2"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION2, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "3"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION3, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "4"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION4, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "5"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION5, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "6"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION6, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "7"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION7, MF_CHECKED);
				if (strstr(ptxt[SXYZ], "8"))popMenuP->CheckMenuItem(ID_POPUP_DIRECTION8, MF_CHECKED);
			}
			else {
				popupMenuP->EnableMenuItem(4, MF_BYPOSITION | MF_DISABLED);
			}
			
			MENUITEMINFO mii = { sizeof(mii) };
			mii.fMask = MIIM_STRING;
			comList();
			
			char buf[255];
			int num,checkN;
			sscanf_s(ptxt[COMP], "%d", &num);
			for (int i = 0; i < 9; i++) {
				if (comArray[i] == num)checkN = i;
			}

			popMenuP = popupMenuP->GetSubMenu(1);
			int i,j;
			for (i = 0; comArray[i] != 0; i++) {
				sprintf_s(buf, "COM%d", comArray[i]);
				setComStr(buf);//いい加減に作ったが動いた
				mii.dwTypeData = buf;
				popMenuP->SetMenuItemInfoA(i, &mii, TRUE);
			//	popMenuP->CheckMenuItem(3 , MFS_CHECKED);
			}
			for (j = i; j < 10; j++) {
				popMenuP->RemoveMenu(i, MF_BYPOSITION);
			}
			if (checkN == 0)popMenuP->CheckMenuItem(ID_M5_COM1, MF_CHECKED);
			if (checkN == 1)popMenuP->CheckMenuItem(ID_M5_COM2, MF_CHECKED);
			if (checkN == 2)popMenuP->CheckMenuItem(ID_M5_COM3, MF_CHECKED);
			if (checkN == 3)popMenuP->CheckMenuItem(ID_M5_COM4, MF_CHECKED);
			if (checkN == 4)popMenuP->CheckMenuItem(ID_M5_COM5, MF_CHECKED);
			if (checkN == 5)popMenuP->CheckMenuItem(ID_M5_COM6, MF_CHECKED);
			if (checkN == 6)popMenuP->CheckMenuItem(ID_M5_COM7, MF_CHECKED);
			if (checkN == 7)popMenuP->CheckMenuItem(ID_M5_COM8, MF_CHECKED);
			if (checkN == 8)popMenuP->CheckMenuItem(ID_M5_COM9, MF_CHECKED);

			popMenuP = popupMenuP->GetSubMenu(2);
			for (i = 0; comArray[i] != 0; i++) {
				sprintf_s(buf, "COM%d", comArray[i]);
				setComStr(buf);//いい加減に作ったが動いた
				mii.dwTypeData = buf;
				popMenuP->SetMenuItemInfoA(i, &mii, TRUE);
			}
			for (j = i; j < 10; j++) {
				popMenuP->RemoveMenu(i, MF_BYPOSITION);
			}
			if (checkN == 0)popMenuP->CheckMenuItem(ID_MPU_COM1, MF_CHECKED);
			if (checkN == 1)popMenuP->CheckMenuItem(ID_MPU_COM2, MF_CHECKED);
			if (checkN == 2)popMenuP->CheckMenuItem(ID_MPU_COM3, MF_CHECKED);
			if (checkN == 3)popMenuP->CheckMenuItem(ID_MPU_COM4, MF_CHECKED);
			if (checkN == 4)popMenuP->CheckMenuItem(ID_MPU_COM5, MF_CHECKED);
			if (checkN == 5)popMenuP->CheckMenuItem(ID_MPU_COM6, MF_CHECKED);
			if (checkN == 6)popMenuP->CheckMenuItem(ID_MPU_COM7, MF_CHECKED);
			if (checkN == 7)popMenuP->CheckMenuItem(ID_MPU_COM8, MF_CHECKED);
			if (checkN == 8)popMenuP->CheckMenuItem(ID_MPU_COM9, MF_CHECKED);

			popMenuP = popupMenuP->GetSubMenu(6);
			
			for (int i = 4; i > cameran-1; i--) {
				popMenuP->RemoveMenu(i, MF_BYPOSITION);
			}
			if (Para0(CAME) == 0)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA1, MF_CHECKED);
			if (Para0(CAME) == 1)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA2, MF_CHECKED);
			if (Para0(CAME) == 2)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA3, MF_CHECKED);
			if (Para0(CAME) == 3)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA4, MF_CHECKED);
			if (Para0(CAME) == 4)popupMenuP->CheckMenuItem(ID_POPUP_CAMERA5, MF_CHECKED);
			if (Para0(CAME) == 9)popupMenuP->CheckMenuItem(ID_POPUP_IPCAMERA, MF_CHECKED);
			if (!strstr(ptxt[IPAD],"http"))popupMenuP->EnableMenuItem(ID_POPUP_IPCAMERA, MF_DISABLED);
		}
		if (!popupMenuP->TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this)) err = 1;
	}
	cMenu.DestroyMenu();// TODO: ここにコントロール通知ハンドラー コードを追加します。
}

void CCapNYS2Dlg::OnPopupHelp()
{
	CFileFind find;
	char fn[301];
	sprintf_s(fn, "%s\\CapNYS2_Help\\capnys.html", CurDir);

	if (find.FindFile(fn)) {
		::ShellExecute(NULL, "open", fn, NULL, NULL, SW_SHOWNORMAL);
	}
	else {
		MessageBox("no help-file.");
	}
}


void CCapNYS2Dlg::OnPopupDirection1()
{
	int num = 1;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection2()
{
	int num = 2;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection3()
{
	int num = 3;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection4()
{
	int num = 4;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection5()
{
	int num = 5;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection6()
{
	int num = 6;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection7()
{
	int num = 7;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupDirection8()
{
	int num = 8;
	GetSXYZ(Sxyz, num);
	sprintf_s(ptxt[SXYZ], "%d", num);
}


void CCapNYS2Dlg::OnPopupCamera1()
{
	sprintf_s(ptxt[CAME], "%d", 0);
	if (CapNYSmode == PlayMode)return;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapNYS2Dlg::OnPopupCamera2()
{
	sprintf_s(ptxt[CAME], "%d", 1);
	if (CapNYSmode == PlayMode)return;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapNYS2Dlg::OnPopupCamera3()
{
	sprintf_s(ptxt[CAME], "%d", 2);
	if (CapNYSmode == PlayMode)return;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapNYS2Dlg::OnPopupCamera4()
{
	sprintf_s(ptxt[CAME], "%d", 3);
	if (CapNYSmode == PlayMode)return;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}


void CCapNYS2Dlg::OnPopupCamera5()
{
	sprintf_s(ptxt[CAME], "%d", 4);
	if (CapNYSmode == PlayMode)return;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}
void CCapNYS2Dlg::OnPopupIpcamera()
{
	sprintf_s(ptxt[CAME], "%d", 9);// TODO: ここにコマンド ハンドラー コードを追加します。
	if (CapNYSmode == PlayMode)return;
	m_CaploopEnable = false;
	sliderf = 0;
	trimposa = 0;
	trimposb = slidew;
	currentframe = 0;
	KillRecordCnt = 3;
}

void CCapNYS2Dlg::OnIpcamera()
{
	CSetMemo dlg;
	//	dlg.SetWindowTextA("ipadress");
	//	dlg.SetWindowTextA("");
	dlg.m_memohead = English ? "Set the address of the IP_Camera.  http://x.x.x.x" : "IPカメラのアドレスを設定してください。   http://x.x.x.x";
	dlg.m_memotxt = ptxt[IPAD];
	if (dlg.DoModal() == IDOK) {
		if (strlen(dlg.m_memotxt) < 15 || !strstr(dlg.m_memotxt, "http")) {
			MessageBox("	Invalid string !");
			strcpy_s(ptxt[IPAD], "");
		}
		else {
			strcpy_s(ptxt[IPAD], dlg.m_memotxt);
		}
	//	strcpy_s(ptxt[CAME], "9");
	//	sliderf = 0;
	//	trimposa = 0;
	//	trimposb = slidew;
	//	currentframe = 0;
	//	KillRecordCnt = 3;
	}
}

void CCapNYS2Dlg::OnSetsavef()
{
	{
		char cdr[MAX_PATH], buf[MAX_PATH],oldSAVE[301];
		LPMALLOC pma;
		BROWSEINFO bif;
		LPITEMIDLIST iil;
		strcpy_s(oldSAVE, ptxt[SAVE]);
		sprintf_s(buf, "Folder for Saving : %s", ptxt[SAVE]);
		if (::SHGetMalloc(&pma) == NOERROR)//Shell の標準のアロケータを取得
		{
			GetCurrentDirectory(sizeof(cdr), cdr);
			memset(&bif, 0x00, sizeof(bif));
			bif.hwndOwner = m_hWnd;//GetSafeHwnd();
			bif.pidlRoot = NULL;
			bif.pszDisplayName = cdr;
			bif.lpszTitle = buf;//"Backupフォルダ"
			bif.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
			bif.lpfn = NULL;
			bif.lParam = 0;
			if ((iil = SHBrowseForFolder(&bif)))
			{
				if (::SHGetPathFromIDList(iil, ptxt[SAVE]))//SaveFolder))
				{//bufに選択されたパスが入っています。
					TRACE("buf=%s\n", ptxt[SAVE]);//SaveFolder);
				}
				//iilを解放します。
				pma->Free(iil);
				//			m_videofold = ptxt[FOL2]r;
				if (FilesCnt() > 0) {
					CMakeDB dlg;
					dlg.m_setumei = English ? "Making CapNYS2list.txt(video files)" : "CapNYS2list.txt(video files) に Video を登録します。";
					if (dlg.DoModal() == IDOK) {
						SetLists();
					}
					else {//cancelのときはlictboxはそのままだから、
						//新たに作られたCapNYS2list.txtも終了時に元に戻る
						strcpy_s(ptxt[SAVE], oldSAVE);
						//SetLists();
					}
				}
				else {//fileが無いときはListを消去
					int sc;
					for (sc = m_listavi.GetItemCount() - 1; sc >= 0; sc--)m_listavi.DeleteItem(sc);
					for (sc = m_listref.GetItemCount() - 1; sc >= 0; sc--)m_listref.DeleteItem(sc);
				}

				m_PrevloopEnable = false;
				Setlistavi2listcur(&m_listavi, &m_listcurrent, IDnum);
				m_PrevloopEnable = false;
				DispNum_sub(&m_currentid, IDnum);
				DispNum_sub(&m_totalnum, m_listavi.GetItemCount());
				strcpy_s(playingfn, "");
			}
			pma->Release();
		}	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	}
}


void CCapNYS2Dlg::OnTouroku()
{
	CMakeDB dlg;
	dlg.m_setumei = English ? "Making CapNYS2list.txt(video files)" : "CapNYS2list.txt に Video を登録します。";
	if (dlg.DoModal() == IDOK) {
		SetLists();
	}
	else {//cancelのときはlictboxはそのままだから、
		//新たに作られたCapNYS2list.txtも終了時に元に戻る
	//	strcpy_s(ptxt[SAVE], oldSAVE);
		//SetLists();
	}
}
void CCapNYS2Dlg::DispIP()
{
	PMIB_IPADDRTABLE pIPAddrTable;
	DWORD dwSize = 0;
	DWORD dwRetVal;
	char adr[30], buf[300];
	pIPAddrTable = (MIB_IPADDRTABLE *)malloc(sizeof(MIB_IPADDRTABLE));
	if (pIPAddrTable) {
		// dwSizeには以下の呼び出し後に必要なサイズが入る
		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) ==
			ERROR_INSUFFICIENT_BUFFER) {
			free(pIPAddrTable);
			// dwSizeの値を使い、必要な領域をmallocする。
			pIPAddrTable = (MIB_IPADDRTABLE *)malloc(dwSize);
		}

		if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR) {
			// エラー処理
		}
		//　これ以降では取得した値を使用できる。
		//printf("\tNum Entries: %ld\n", pIPAddrTable->dwNumEntries);
//		sprintf_s(buf,"Num Entries: %ld", pIPAddrTable->dwNumEntries);
//		AfxMessageBox(buf);
//		for (int i = 0; i < pIPAddrTable->dwNumEntries; i++) {
			//printf("\n\tInterface Index[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwIndex);
			//sprintf_s(buf, "Index[%d]:%x", i, pIPAddrTable->table[i].dwAddr);// .dwIndex);
//		struct sockaddr_in sa;
		//char str[INET_ADDRSTRLEN];
		strcpy_s(buf, "Set GyrOSC as follows.\n\n");
		for (int i = 0; i < pIPAddrTable->dwNumEntries; i++) {
			inet_ntop(AF_INET, &(pIPAddrTable->table[i].dwAddr), adr, INET_ADDRSTRLEN);
			if (!strstr(adr, "127")) {
				strcat_s(buf, "IP adress : ");
				strcat_s(buf, adr);
				strcat_s(buf, "\n");
			}
		}
		//	inet_ntop(AF_INET, &(pIPAddrTable->table[1].dwAddr), ad2, INET_ADDRSTRLEN);
			//AfxMessageBox(buf);
		//	strcat_s(buf, "IPアドレス：");
		//	strcat_s(buf, adr);
		//	strcat_s(buf, "\nIPアドレス：");
		//	strcat_s(buf, ad2);
		strcat_s(buf, "\nPort number : 1108");
		MessageBox(buf);
	}
}

void CCapNYS2Dlg::OnPopupiPhone()
{
	if (strstr(ptxt[SENM], "3")) {
		return;
	}

	DispNum_Sensor(&m_sensormode, 3);
	ArduinoM5ThreadF = false;
	iPhoneThreadF = false;
	Sleep(500);
	sprintf_s(ptxt[SENM], "3");
	SetButtons(CapNYSmode = CaptMode);
	DispIP();
	int tm;
	AfxBeginThread(iPhoneThread, &tm);
	SetButtons(CapNYSmode = CaptMode);
}

void CCapNYS2Dlg::OnPopupManual()
{
	if (strstr(ptxt[SENM], "0")) {
		return;
	}
	sprintf_s(ptxt[SENM], "0");

	DispNum_Sensor(&m_sensormode, 0);
	iPhoneThreadF = false;
	ArduinoM5ThreadF = false;
	SetButtons(CapNYSmode = CaptMode);
}

//void CCapNYS2Dlg::OnPopupArduino()
//{
//	if (strstr(ptxt[SENM], "2")) {
//		return;
//	}
//	comList();
//	DispNum_Sensor(&m_sensormode, 2);
//	iPhoneThreadF = false;
//	ArduinoM5ThreadF = false;
//	Sleep(500);
//	sprintf_s(ptxt[SENM], "2");
//
//	int tm;
//	AfxBeginThread(ArduinoM5Thread, &tm);
//	SetButtons(CapNYSmode = CaptMode);
//}

//void CCapNYS2Dlg::OnPopupM5()
//{
//	if (strstr(ptxt[SENM], "1")) {
//		return;
//	}
//	comList();
//	DispNum_Sensor(&m_sensormode, 1);
//	iPhoneThreadF = false;
//	ArduinoM5ThreadF = false;
//	Sleep(500);
//	sprintf_s(ptxt[SENM], "1");
//
//	int tm;
//	AfxBeginThread(ArduinoM5Thread_M5, &tm);
//	SetButtons(CapNYSmode = CaptMode);
//}
/*
void CCapNYS2Dlg::OnClickedChancom()
{
	return;
	int i;
	ArduinoM5ThreadF = false;
	int comOld = 0;
	sscanf_s(ptxt[COMP], "%d", &comOld);
	Sleep(300);
//	comList();
//	char buf[300];
//	sprintf_s(buf, "%d,%d,%d,%d,%d,%d,%d", comArray[0], comArray[1], comArray[2], comArray[3], comArray[4], comArray[5], comArray[6]);
//	AfxMessageBox(buf);
	DispNum_sub(&m_nextcom, 9);

	for (i = 0; comArray[i] != 0; i++) {
		if (comArray[i] == comOld) {
			i++;
			break;
		}
	}
	if (comArray[i] == 0)i = 0;

	sprintf_s(ptxt[COMP], "%d", comArray[i]);

	DispNum_sub(&m_nextcom, Para0(COMP));
	int tm;
	if (strstr(ptxt[SENM], "2")) {
		AfxBeginThread(ArduinoM5Thread, &tm);
	}
	else {
		AfxBeginThread(ArduinoM5Thread_M5, &tm);
	}
}*/

void CCapNYS2Dlg::SetMpuComNum(int num) {
	DispNum_Sensor(&m_sensormode, 2);
	iPhoneThreadF = false;
	ArduinoM5ThreadF = false;
	Sleep(500);
	sprintf_s(ptxt[SENM], "2");
	sprintf_s(ptxt[COMP], "%d", comArray[num]);
//	AfxMessageBox(ptxt[COMP]);
	int tm;
	AfxBeginThread(ArduinoM5Thread, &tm);
	SetButtons(CapNYSmode = CaptMode);
}
void CCapNYS2Dlg::SetM5ComNum(int num) {

	DispNum_Sensor(&m_sensormode, 1);
	iPhoneThreadF = false;
	ArduinoM5ThreadF = false;
	Sleep(500);
	sprintf_s(ptxt[SENM], "1");
	sprintf_s(ptxt[COMP], "%d", comArray[num]);
	int tm;
	AfxBeginThread(ArduinoM5Thread_M5, &tm);
	SetButtons(CapNYSmode = CaptMode);
}
void CCapNYS2Dlg::OnMpuCom1()
{
	SetMpuComNum(0);
}


void CCapNYS2Dlg::OnMpuCom2()
{
	SetMpuComNum(1);
}


void CCapNYS2Dlg::OnMpuCom3()
{
	SetMpuComNum(2);
}


void CCapNYS2Dlg::OnMpuCom4()
{
	SetMpuComNum(3);
}


void CCapNYS2Dlg::OnMpuCom5()
{
	SetMpuComNum(4);
}


void CCapNYS2Dlg::OnMpuCom6()
{
	SetMpuComNum(5);
}


void CCapNYS2Dlg::OnMpuCom7()
{
	SetMpuComNum(6);
}


void CCapNYS2Dlg::OnMpuCom8()
{
	SetMpuComNum(7);
}


void CCapNYS2Dlg::OnMpuCom9()
{
	SetMpuComNum(8);
}


void CCapNYS2Dlg::OnM5Com1()
{
	SetM5ComNum(0);
}


void CCapNYS2Dlg::OnM5Com2()
{
	SetM5ComNum(1);
}


void CCapNYS2Dlg::OnM5Com3()
{
	SetM5ComNum(2);
}


void CCapNYS2Dlg::OnM5Com4()
{
	SetM5ComNum(3);
}


void CCapNYS2Dlg::OnM5Com5()
{
	SetM5ComNum(4);
}


void CCapNYS2Dlg::OnM5Com6()
{
	SetM5ComNum(5);
}


void CCapNYS2Dlg::OnM5Com7()
{
	SetM5ComNum(6);
}


void CCapNYS2Dlg::OnM5Com8()
{
	SetM5ComNum(7);
}


void CCapNYS2Dlg::OnM5Com9()
{
	SetM5ComNum(8);
}

