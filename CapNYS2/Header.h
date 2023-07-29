#pragma once

#define INTE 0
//#define DSIZ 1
//#define DAUT 1
#define CSIZ 1
#define FPSN 2
#define NEWD 3//getnewid dialog
#define COMP 4
#define SENM 5
#define SXYZ 6
#define CAME 7
#define SISE 8
//#define FACE 11
#define WRID 9
#define WRCA 10
#define HIST 11
#define FONT 12
#define COLS 13//ListAvi 5Colomn's size
#define FLSP 14
#define BKUP 15
#define SAVE 16
#define IPAD 17
#define PARA 18
#define CaptMode 0
#define PrevMode 1
#define PlayMode 2
#define ListMode 3
#define CONF_FN "CapNYS2config.ini"
#define LIST_FN "CapNYS2list.txt"
#define CV_AA 16
#include <opencv2\opencv.hpp>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <iphlpapi.h>

//#include "erslib.h"

//#include <ws2tcpip.h>

//#include <opencv2/core.hpp>    // coreモジュールのヘッダーをインクルード
//#include <opencv2/highgui.hpp> // highguiモジュールのヘッダーをインクルード
#include <iostream>
#include <fstream>
#include "mmsystem.h"
#include <sys/stat.h> 
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "WSock32.lib")
#pragma comment(lib,"Iphlpapi.lib")
//#pragma comment(lib, "wsock32.lib")
//#pragma comment(lib, "ws2_32.lib")

//using namespace cv;
using namespace std;//これでofstream ifstream が定義されていません　が出なくなる

#ifdef CapNYS2_TOP
int CSW, CSH;
int cameran = 0;
int foundn;
bool sensor_error;
char Sxyz[10];
int Resetheadfcnt = 0;
int params[22];
int Columnwidth = 200;//reference current lists　の幅
int qq0, qq1, qq2, qq3;//,qqsisei;
float cq0 = 0.99F, cq1 = 0.0F, cq2 = 0.0F, cq3 = 0.0F;//spaceを押した時のcenter quatrnion 
float nq0 = 0.01F, nq1 = 0.0F, nq2 = 0.0F, nq3 = 0.0F;//現在のquaternion
float mnq0 = 0.01F, mnq1 = 0.0F, mnq2 = 0.0F, mnq3 = 0.0F;//受け渡し用のquaternion
bool ArduinoM5ThreadF;
bool iPhoneThreadF;
char m5text[100];
bool m5stickF;
int comArray[255];
DWORD grayRGB;
char CurDir[301];
char ptxt[22][200];
int Gwinw, Gwinh;//映像Windowの横縦幅
int Gwinx, Gwiny;//映像Windowの左上
int slidex, slidey, sliderf;
int slidew;
int slideh;
int Winw, Winh;//Windowの横縦幅
int PicPos[20][4];
int PicPosflag; bool m5 = false;
bool Manualmode;
int CurIDcnt;
//int chanid;
char chanfn1[301], chanfn2[301];
bool origerasef;
int ldownf;
bool m5textFlag = false;

#else
extern bool m5stickF;
extern char m5text[100];
extern int comArray[255];
extern int cameran;
extern int CSW, CSH;

extern int foundn;
extern bool sensor_error;
extern char Sxyz[10];
extern int Resetheadfcnt;
extern int params[22];
extern int Columnwidth;
extern int qq0, qq1, qq2, qq3, qqsisei;
extern float cq0, cq1, cq2, cq3;//spaceを押した時のcenter quatrnion 
extern float nq0, nq1, nq2, nq3;//現在のquaternion
extern float mnq0, mnq1, mnq2, mnq3;//受け渡し用のquaternion
extern bool ArduinoM5ThreadF;
extern bool iPhoneThreadF;

extern DWORD grayRGB;
extern char CurDir[301];
extern char ptxt[22][200];
extern int Gwinw, Gwinh;//映像Windowの横縦幅
extern int Gwinx, Gwiny;//映像Windowの左上
extern int slidex, slidey, sliderf;
extern int slidew;//sliderの幅
extern int slideh;//sliderの縦幅
extern int Winw, Winh;//Windowの横縦幅
extern int PicPos[20][4];
extern int PicPosflag;
extern bool Manualmode;
extern int CurIDcnt;

extern char chanfn1[301], chanfn2[301];
extern bool origerasef;
extern int ldownf;
extern bool m5textFlag;
#endif

bool IsFile(char *fn);
//bool Checkarcom(int n);
//int GetarcomsDTR_N(int n);
UINT ArduinoM5Thread(LPVOID dummy);
UINT ArduinoM5Thread_M5(LPVOID dummy);
UINT iPhoneThread(LPVOID dummy);
void SetEN(char *s1, char *s2);
int Setfn2iddate(char *fn, char *iddate);
void Waku(CDC *pDC, int x, int y, int x1, int y1);
void Addfn2listavi(CListCtrl *list, char *fn,char* memo);
void FolderTree2lists(CString inPath, CListCtrl *list, CListCtrl *ref);
void Setlistavi2listcur(CListCtrl* all, CListCtrl* cur, int id);
void f2gomi(char *gomi);
bool checkavifn(char *fn);
void LoadCon();
void SaveCon(CListCtrl* list);
int Para0(int para);
int Para1(int para);
int checkslider(int x, int y);
int CheckPicPos(int mode, int x, int y);
void GetQuartanion(int f, float *q0, float *q1, float *q2, float *q3);
void GetSXYZ(char *sxyz, int s);
int GetSXYZn(char *sxyz);
int GetIDcnt(CListCtrl* all, int id);
void Delete1item(CListCtrl *avi, CListCtrl *cur, CListCtrl *ref, char *fn);
void SetlistaviSize0(CListCtrl* all);
void Set_rpk_ppk();
void SetHead(int n);

