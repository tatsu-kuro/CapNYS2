#include "stdafx.h"
#include "CapNYS2.h"
#include "CapNYS2Dlg.h"
#include "Header.h"

#include <opencv2\opencv.hpp>
//using namespace cv;

static char *ptext[] = {
	"(*)Interlace Filter:",
//	"(*)Video Display size(x,y):",
//	"(*)Video Display size setting(0:manual 1:auto);",
	"(*)Video Capture size(x,y):",
	"(*)Video Capture FPS:",
	"GetNewID Dialog Offset(dx,dy):",
	"COM-PORT:",
	"Sensor Mode 0/off 1/M5Stick 2/Arduino 3/SmartPhone:",
	"Sensor Direction (1-8):",
	"Camera Number:",
	"Sisei 1/supine 2/sit:",
//	"Show CameraNumber, SensorMode, SensorDir (0:hide 1:show):",
//	"Face mode:",
	"(*)write ID on-off:",
	"(*)write date on-off:",
	"ID history:",
	"FontSize, FontType(0/default 1/MSgothic 2/MSminchou 3/Arial 4/Courier 5/Courier New 6/Times New Roman 7/Helvetica):",
	"ListAviColumnSizes:",
	"(*)Antialiasing(set 0 for poor PC) on-off:",
	"BackupFolder:",
	"SaveFolder:",
	"IPcamera_Address:"
};


static char *ptextdef[] = {
	"0",
//	"640,480",
//	"1",
	"640,480",
	"30",
	"0,0",
	"255",
	"0",
	"2",//== 6050をピンが左の縦に置いたとき//1-,3-,2- == 6050をピンが右の縦置き//2-,3-,1+ == 6050 横置き
	"0",
	"1",
//	"1",
//	"0",
	"1",
	"1",
	"00000111,00000222,00000333,00000444,00000555,00000666,00000777,00000888,00000999,00000123",
	"200,1",
	"120,220,100,500,500",
	"1",
	"",
	"",
	""
};
void LoadCon()
{
	int i;
	char buf[500];
	CStdioFile ff;
	if (!ff.Open(CONF_FN, CFile::modeRead | CFile::typeText))
	{
		ff.Open(CONF_FN, CFile::modeCreate | CFile::modeWrite | CFile::modeRead | CFile::typeText);
		for (i = 0; i<PARA; i++) {
			sprintf_s(buf, "%s%s\n", ptext[i], ptextdef[i]);
			ff.WriteString(buf);
			//			strcpy_s(b,buf);
		}
		ff.Abort();
		for (i = 0; i<PARA; i++) {
			strcpy_s(ptxt[i], ptextdef[i]);
		}
		int n = Para0(NEWD);
		int n1 = Para1(NEWD);
		n = n;
		n1 = n1;
	}
	else {
		bool txtf[PARA + 1];
		for (i = 0; i<PARA; i++)txtf[i] = false;
		while (ff.ReadString(buf, 395)) {
			for (i = 0; i<PARA; i++) {
				if (strstr(buf, ptext[i]) && buf[0] == ptext[i][0]) {
					strcpy_s(ptxt[i], &buf[strlen(ptext[i])]);
					ptxt[i][strlen(ptxt[i]) - 1] = 0;
					txtf[i] = true;
				}
			}
		}
		ff.Abort();

		for (i = 0; i<PARA; i++) {
			if (!txtf[i]) {
				strcpy_s(ptxt[i], ptextdef[i]);
			}
		}
	}
	if (strlen(ptxt[SXYZ]) != 1)
	{
		sprintf_s(buf, "LoadCon %s is destroyed.\ndelete the %s and run CapNYS2.exe.", CONF_FN, CONF_FN);
		AfxMessageBox(buf);//"CapNYS.ini is destroyed.\n delete the CapNYS.ini and run CapNYS.exe.");
		exit(0);
	}
	CSW = Para0(CSIZ);
	CSH = Para1(CSIZ);
}

void SaveCon(CListCtrl *list)//SetCurrentDirectory後にここに来る
{
	CStdioFile ff;
	char buf[300];
	int i;
//	if (Para0(CSIZ) == 0) {
//		strcpy_s(ptxt[CSIZ], "640,480");
//	}
	sprintf_s(ptxt[COLS], "%d,%d,%d,%d,%d", list->GetColumnWidth(0), list->GetColumnWidth(1), list->GetColumnWidth(2), list->GetColumnWidth(3), list->GetColumnWidth(4));
//	SetCurrentDirectory(CurDir);
	ff.Open(CONF_FN, CFile::modeCreate |
		CFile::modeWrite | CFile::modeRead | CFile::typeText);
	for (i = 0; i<PARA; i++) {//writeini
		sprintf_s(buf, "%s%s\n", ptext[i], ptxt[i]);
		ff.WriteString(buf);
	}
	ff.Abort();
	if (strlen(ptxt[SXYZ]) != 1)
	{
		sprintf_s(buf, "SaveCon %s is destroyed.\ndelete the %s and run CapNYS2.exe.", CONF_FN, CONF_FN);
		AfxMessageBox(buf);//"CapNYS.ini is destroyed.\n delete the CapNYS.ini and run CapNYS.exe.");
	}
}
int Para0(int para)
{
	char *p;
	int i, j;
	if (p = strstr(ptxt[para], ",")) {
		if (strstr(p + 1, ",")) {//,が2個あったら戻る
			return -1;
		}
		else {//,が1個のとき
			sscanf_s(ptxt[para], "%d,%d", &i, &j);
			return i;
		}
	}
	else {//,がないとき
		sscanf_s(ptxt[para], "%d", &i);
		return i;
	}
}
int Para1(int para)
{
	char *p;
	int i, j;
	if (p = strstr(ptxt[para], ",")) {
		if (strstr(p + 1, ",")) {//,が2個あったら戻る
			return -1;
		}
		else {//,が1個のとき
			sscanf_s(ptxt[para], "%d,%d", &i, &j);
			return j;
		}
	}
	else {//,がないとき
		return -1;
	}
}
void f2gomi(char *gomi)//void f2gomi(HWND hwnd,char *gomi)
{
	char	buf[513];
	if (!IsFile(gomi)) {
		sprintf_s(buf, "%s can't be found.", gomi);
		AfxMessageBox(buf);
		return;
	}
	SHFILEOPSTRUCT	fo;
	fo.hwnd = NULL;//hwnd;
	fo.wFunc = FO_DELETE;
	strcpy_s(buf, 512, gomi);
	buf[strlen(buf) + 1] = 0;
	fo.pFrom = buf;
	fo.pTo = 0;
	fo.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION | FOF_NOERRORUI;
	if (SHFileOperation(&fo)) {
		sprintf_s(buf, "%s can't be deleted.", gomi);
		AfxMessageBox(buf);
	}
}

void GetSXYZ(char *sxyz, int s)
{
	//Sensor 普通の設置 
	if (s == 1) {
		strcpy_s(sxyz, 10, "1+,3-,2+");
	}
	else if (s == 2) {
		strcpy_s(sxyz, 10, "2+,3-,1-");
	}
	else if (s == 3) {
		strcpy_s(sxyz, 10, "2-,3-,1+");
	}
	else if (s == 4) {
		strcpy_s(sxyz, 10, "1-,3-,2-");
		//Sensor 裏返し設置したとき
	}
	else if (s == 5) {
		strcpy_s(sxyz, 10, "1-,3+,2+");
	}
	else if (s == 6) {
		strcpy_s(sxyz, 10, "2-,3+,1-");
	}
	else if (s == 7) {
		strcpy_s(sxyz, 10, "2+,3+,1+");
	}
	else {// if(params[SENS]==7){
		strcpy_s(sxyz, 10, "1+,3+,2-");
	}
}
int GetSXYZn(char *sxyz)
{
	//Sensor 普通の設置 
	if (strstr(sxyz, "1+,3-,2+"))return 1;
	if (strstr(sxyz, "2+,3-,1-"))return 2;
	if (strstr(sxyz, "2-,3-,1+"))return 3;
	if (strstr(sxyz, "1-,3-,2-"))return 4;
	//Sensor 裏返し設置したとき
	if (strstr(sxyz, "1-,3+,2+"))return 5;
	if (strstr(sxyz, "2-,3+,1-"))return 6;
	if (strstr(sxyz, "2+,3+,1+"))return 7;
	if (strstr(sxyz, "1+,3+,2-"))return 8;
	return 0;
}

