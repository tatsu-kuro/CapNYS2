
#include "stdafx.h"
#include "CapNYS2.h"
#include "CapNYS2Dlg.h"
#include "SetMemo.h"
#include "GetID.h"
#include "GetNewID.h"
#include "afxdialogex.h"
#include <direct.h>
#include "Header.h"
#include "erslib.h"
#include <opencv2\opencv.hpp>
//#pragma comment(lib, "WSock32.lib")
//#pragma comment(lib,"Iphlpapi.lib")

//using namespace cv;
extern bool changeCSIZflag;
void Disp_ken(cv::Mat img, float q0, float q1, float q2, float q3, int sisei);
void Set_rpk_ppk();
bool CheckMPU6050(int comp) {
	char buf[500];
	int i, nc;
	if (ERS_Open(comp, 4096, 4096) == 0) {
		for (i = 0; i<10; i++) {
			Sleep(100);
			if (ERS_CheckRecv(comp) != 0)break;
		}
		if (i>10)return false;
		for (i = 0; i<120; i++) {
			if ((nc = ERS_Getc(comp)) == EOF)break;
			buf[i] = nc;
		}
		buf[i] = '\0';
		if (strstr(buf, "MPU6050")) {
			//			Sleep(500);
			Sleep(100);
			ERS_Close(comp);//All();
			return true;
		}
		Sleep(500);
		ERS_Close(comp);
	}

	return false;
}
/*
bool Checkarcom(int n) {
	int i;
	for (i = 0; i<10; i++) {
		if (ERS_OpenN(n, 4096, 4096) == 0) {
			ERS_Close(n);
//			Sleep(10);//不要だろうが
			return true;
		}
	}
	return false;
}
int GetarcomsDTR_N(int n) {
	int i;
	if (n<1)return 0;
	for (i = n; i>0; i--) {
		if (ERS_OpenN(i, 4095, 4096) == 0) {
			ERS_Close(i);
			break;
		}
	}
	return i;
}
*/
UINT CCapNYS2Dlg::CaptureThread(LPVOID pParam)
{
	((CCapNYS2Dlg*)pParam)->CaptureThread();
	return 0;
}

void CCapNYS2Dlg::CaptureThread(void)
{
	bool capdevice = true;
	cv::VideoCapture capture;

	cv::VideoWriter rec;
	int errorcnt = 0,sisei;
	CDC* pDC = GetDC();
	char fn[301], buf[100];// , buf2[100];
	char IDbuf[100];
	cv::Point IDp1, IDp2, IDp3,CTp1, CTp2,CTp3;

	sprintf_s(IDbuf, sizeof(buf), "ID:%08d", IDnum);
	IDp1 = cv::Point(142, CSH - 20);
	IDp2 = cv::Point(0, CSH);
	IDp3 = cv::Point(2, CSH - 3);
	CTp1 = cv::Point(CSW,CSH - 20);
	CTp2 = cv::Point(CSW - 255, CSH);// , CV_RGB(255, 255, 255), -1, CV_AA, 0);
	CTp3 = cv::Point(CSW - 253, CSH - 3);
	m_CaploopEnable = true;
	SetTimer(1, 100, NULL);
	time_t now = time(NULL);
	struct tm tms;
	struct tm* tmp = &tms;
	localtime_s(tmp, &now);
	
	if (strlen(ptxt[SAVE]) == 0) {
		sprintf_s(fn, "%s\\%s\\%08d%i%02i%02i%02i%02i%02i.wmv", CurDir,"gazou", IDnum, tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
	}
	else {
		sprintf_s(fn, "%s\\%08d%i%02i%02i%02i%02i%02i.wmv", ptxt[SAVE], IDnum, tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
	}
	strcpy_s(lastrecfn, fn);

	if (strstr(ptxt[CAME], "9")) {
		capture.open(ptxt[IPAD]);// "http://192.168.3.43:8080/?action=stream");//デバイスのオープン
	}
	else {
		capture.open(Para0(CAME));//デバイスのオープン
	}//デバイスのオープン
	if (!capture.isOpened()) {
		Sleep(100);
		if (strstr(ptxt[CAME], "9")) {
			capture.open(ptxt[IPAD]);// "http://192.168.3.43:8080/?action=stream");//デバイスのオープン
		}
		else {
			capture.open(Para0(CAME));//デバイスのオープン
		}//デバイスのオープン//	MessageBox("camera open err!");// capdevice = false;
	
	}

	if (!capture.isOpened()) {
//		MessageBox("camera open err!");// capdevice = false;
//		Sleep(100);// 
		capdevice = false;
		capture.release();
	//	capture.open(Para0(CAME));
	}
	else {
		capdevice = true;
	}

	pDC->FillSolidRect(Gwinx, Gwiny, Gwinw, Gwinh, RGB(255, 255, 255));
	cv::Mat frame;
	capturetime = 0;
	int start = timeGetTime();
	int recframenum = 0;
	///////////////
	static int winw, winh;
	cv::Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
	HDC whdc = pDC->GetSafeHdc();
	////////////////

	int framecnt = 0;

	if (capdevice == false) {
		ReleaseDC(pDC);
		return;
	}
	rec.open(fn, cv::VideoWriter::fourcc('W', 'M', 'V', '2'), Para0(FPSN), cv::Size(CSW, CSH));


	while (m_CaploopEnable) {

		capturetime = timeGetTime() - start;
		capture >> frame;
		int rows, cols, step;
		uchar *data;
		rows = frame.rows;
		cols = frame.cols;
		if (rows != CSH&&cols != 0) {
			resize(frame, frame, cv::Size(), CSW / cols, CSH / rows);
			rows = frame.rows;
			cols = frame.cols;
		}
		step = frame.step;
		data = frame.data;
		if (strstr(ptxt[INTE], "1")) {//取りあえずこれ。
			for (int y = 0; y < rows - 2; y += 2) {
				for (int x = 0; x < cols; x++) {
					// Blue
					data[(y + 1) * step + x * 3 + 0] = (data[y * step + x * 3 + 0] + data[(y + 2) * step + x * 3 + 0]) / 2;
					//					data[(y+1) * step + x * 3 + 0] = data[y * step + x * 3 + 0];
					// Green
					data[(y + 1) * step + x * 3 + 1] = (data[y * step + x * 3 + 1] + data[(y + 2) * step + x * 3 + 1]) / 2;
					//					data[(y+1) * step + x * 3 + 1] = data[y * step + x * 3 + 1];
					// Red
					data[(y + 1) * step + x * 3 + 2] = (data[y * step + x * 3 + 2] + data[(y + 2) * step + x * 3 + 2]) / 2;
					//					data[(y+1) * step + x * 3 + 2] = data[y * step + x * 3 + 2];
					//Reserved
					//					ColorBuf[(y+1) * cols * 4 + x * 4 + 3] = 0;
				}
			}
		}

//		char buf[64];
		if (strstr(ptxt[WRCA], "1")) {
			localtime_s(tmp, &now);
			now = time(NULL);
			localtime_s(tmp, &now);
			sprintf_s(buf, sizeof(buf), "%i/%02i/%02i %02i:%02i:%02i", tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);
			rectangle(frame, CTp1,CTp2, CV_RGB(255, 255, 255), -1, CV_AA, 0);
			putText(frame, buf,CTp3, cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0), 1, CV_AA);
		}
		if (strstr(ptxt[WRID], "1")) {
			rectangle(frame, IDp1,IDp2, CV_RGB(255, 255, 255), -1, CV_AA, 0);
			putText(frame, IDbuf, IDp3, cv::FONT_HERSHEY_SIMPLEX, 0.7, cv::Scalar(0, 0, 0), 1, CV_AA);
		}
		if (strstr(ptxt[SISE], "1"))sisei = 1;
		else sisei = 2;
		Disp_ken(frame, mnq0, mnq1, mnq2,mnq3, sisei);//mnq are get at arduinothread
	
////////////////////////////////
		if (winw != Gwinw || winh != Gwinh) {//変化したら
			cv::Mat BMat(winw=Gwinw, winh=Gwinh, CV_32FC3);
		}
		BMat = frame;
		BITMAPINFO bitInfo;
		bitInfo.bmiHeader.biBitCount = 24;
		bitInfo.bmiHeader.biWidth = BMat.cols; //the bitmap is a bottom-up DIB and its origin is the lower-left corner.
		bitInfo.bmiHeader.biHeight = -BMat.rows; //If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biCompression = BI_RGB;
		bitInfo.bmiHeader.biClrImportant = 0;
		bitInfo.bmiHeader.biClrUsed = 0;
		bitInfo.bmiHeader.biSizeImage = 0;
		bitInfo.bmiHeader.biXPelsPerMeter = 0;
		bitInfo.bmiHeader.biYPelsPerMeter = 0;
		if (strstr(ptxt[FLSP], "1"))
			pDC->SetStretchBltMode(COLORONCOLOR);//一回設定するとそのままの様
	//BLACKONWHITE	標準設定。低画質だが高速。拡大または等倍だけならこのままで
	//COLORONCOLOR	実用的な画質で高速。縮小が必要な時に使おう
	//	HALFTONE	高画質だが低速。ビューワーなどで使おう
		StretchDIBits(
			whdc,
			Gwinx,Gwiny,
			Gwinw,Gwinh,//matSize.width, matSize.height,
			0, 0,
			BMat.cols, BMat.rows,
			BMat.data,
			&bitInfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);
		if (strstr(ptxt[SENM],"0")){//!Para0(SENM)) {//9分割の区画線を引く
			pDC->MoveTo(Gwinx, Gwiny + Gwinh / 3); pDC->LineTo(Gwinx + Gwinw, Gwiny + Gwinh / 3);
			pDC->MoveTo(Gwinx, Gwiny + 2 * Gwinh / 3); pDC->LineTo(Gwinx + Gwinw, Gwiny + 2 * Gwinh / 3);
			pDC->MoveTo(Gwinx + Gwinw / 3, Gwiny); pDC->LineTo(Gwinx + Gwinw / 3, Gwiny + Gwinh);
			pDC->MoveTo(Gwinx + 2 * Gwinw / 3, Gwiny); pDC->LineTo(Gwinx + 2 * Gwinw / 3, Gwiny + Gwinh);// *24 / 25);
		}
		if (m_CaploopEnable == false)break;
		if (recframenum>15) rec << frame;	//	画像をファイルへ書き込む。頭がリセットされるまでは記録しない。
		recframenum++;
		if (recframenum>30 * 60 * 60) {
				m_CaploopEnable = false;
			break;
		}

	}
	ArduinoM5ThreadF = false;
	m_pCaptureThread = NULL;
	ReleaseDC(pDC);
	if (recframenum>30 * 60 * 60)OnBnClickedStopcap();

}

void RotateX(float *x, float *y, float *z, float rad) {
	float  dy, dz;
	dy = *y * float(cos(rad)) - *z * float(sin(rad));
	dz = *y * float(sin(rad)) + *z * float(cos(rad));
	*y = dy;
	*z = dz;
}

void RotateY(float *x, float *y, float *z, float rad) {
	float dx, dz;// dy, dz;
	dx = *x * float(cos(rad)) + *z * float(sin(rad));
	dz = -*x * float(sin(rad)) + *z * float(cos(rad));
	*x = dx;
	*z = dz;
}

void RotateZ(float *x, float *y, float *z, float rad) {
	float dx, dy;//, dz;
	dx = *x * float(cos(rad)) - *y * float(sin(rad));
	dy = *x * float(sin(rad)) + *y * float(cos(rad));
	*x = dx;
	*y = dy;
}

void RotateQuat(float *x, float *y, float *z,float x0,float y0,float z0, float q0, float q1, float q2, float q3)
{
	float ax, ay, az, norm, mag;

	mag = float(sqrt((q0 * q0) + (q1 * q1) + (q2 * q2) + (q3 * q3)));
	if (mag > FLT_EPSILON) {
		norm = 1 / mag;
		q0 *= norm;
		q1 *= norm;
		q2 *= norm;
		q3 *= norm;
	}

	ax = x0 * (q0 * q0 + q1 * q1 - q2 * q2 - q3 * q3) + y0 * (2 * (q1 * q2 - q0 * q3)) + z0 * (2 * (q1 * q3 + q0 * q2));
	ay = x0 * (2 * (q1 * q2 + q0 * q3)) + y0 * (q0 * q0 - q1 * q1 + q2 * q2 - q3 * q3) + z0 * (2 * (q2 * q3 - q0 * q1));
	az = x0 * (2 * (q1 * q3 - q0 * q2)) + y0 * (2 * (q2 * q3 + q0 * q1)) + z0 * (q0 * q0 - q1 * q1 - q2 * q2 + q3 * q3);
	*x = ax;
	*y = ay;
	*z = az;
}
void MultQuat(float *a0, float *a1, float *a2, float *a3, float q0, float q1, float q2, float q3, float p0, float p1, float p2, float p3)
{
	*a0 = q0 * p0 - q1 * p1 - q2 * p2 - q3 * p3;
	*a1 = q1 * p0 + q0 * p1 - q3 * p2 + q2 * p3;
	*a2 = q2 * p0 + q3 * p1 + q0 * p2 - q1 * p3;
	*a3 = q3 * p0 - q2 * p1 + q1 * p2 + q0 * p3;
}
void QuatXchan(float *q0, float *q1, float *q2, float *q3)
{
	float tx, ty, tz;
	if (Sxyz[0] == '1')tx = *q1;
	else if (Sxyz[0] == '2')tx = *q2;
	else tx = *q3;
	if (Sxyz[1] == '-')tx = -tx;

	if (Sxyz[3] == '1')ty = *q1;
	else if (Sxyz[3] == '2')ty = *q2;
	else ty = *q3;
	if (Sxyz[4] == '-')ty = -ty;

	if (Sxyz[6] == '1')tz = *q1;
	else if (Sxyz[6] == '2')tz = *q2;
	else tz = *q3;
	if (Sxyz[7] == '-')tz = -tz;
	*q1 = tx;
	*q2 = ty;
	*q3 = tz;
}
#define PKKENN 250//実際の点数(117)より多目を設定
float rpk1[PKKENN][2], ppk1[PKKENN][3];
int pk_ken2[PKKENN][3] = {//x1,y1,0, x2,y2,0, x3,y3,1, x4,y4,0  の並びは   MoveTo(x1,y1)  LineTo(x2,y2)  LineTo(x3,y3)  MoveTo(x4,y4) と描画される  
	0,0,0, 15,0,0, 30,0,0, 45,0,0, 60,0,0, 75,0,0, 90,0,0, 105,0,0, 120,0,0, 135,0,0, 150,0,0, 165,0,0,//horizon
	180,0,0, 195,0,0, 210,0,0, 225,0,0, 240,0,0, 255,0,0, 270,0,0, 285,0,0, 300,0,0, 315,0,0, 330,0,0, 345,0,0, 360,0,1,
	0,0,0, 0,15,0, 0,30,0, 0,45,0, 0,60,0, 0,75,0, 0,90,0, 0,105,0, 0,120,0, 0,135,0, 0,150,0, 0,165,0,//vertical
	///		0,0,0, 0,14,1, 0,48,0, 0,60,0, 0,75,0, 0,90,0, 0,105,0, 0,120,0, 0,135,0, 0,150,0, 0,165,0,//vertical bigmouse
	0,180,0, 0,195,0, 0,210,0, 0,225,0, 0,240,0, 0,255,0, 0,270,0, 0,285,0, 0,300,0, 0,315,0, 0,330,0, 0,345,0, 0,360,1,
	0,90,0, 15,90,0, 30,90,0, 45,90,0, 60,90,0, 75,90,0, 90,90,0, 105,90,0, 120,90,0, 135,90,0, 150,90,0, 165,90,0,//coronal
	180,90,0, 195,90,0, 210,90,0, 225,90,0, 240,90,0, 255,90,0, 270,90,0, 285,90,0, 300,90,0, 315,90,0, 330,90,0, 345,90,90, 360,90,1,
	20,-90,0, 20,-105,0, 20,-120,0, 20,-135,0, 20,-150,0, 20,-165,0, 20,-180,1,//hair
	-20,-90,0, -20,-105,0, -20,-120,0, -20,-135,0, -20,-150,0, -20,-165,0, -20,-180,1,//hair
	40,-90,0, 40,-105,0, 40,-140,0, 40,-135,0, 40,-150,0, 40,-165,0, 40,-180,1,//hair
	-40,-90,0, -40,-105,0, -40,-140,0, -40,-135,0, -40,-150,0, -40,-165,0, -40,-180,1,//hair
	23,-9,0, 31,-12,0, 38,-20,0, 40,-31,0, 38,-41,0, 31,-46,0, 23,-45,0, 15,-39,0, 10,-32,0, 8,-23,0, 10,-16,0, 15,-10,0, 23,-9,1,//eye
	-23,-9,0, -31,-12,0, -38,-20,0, -40,-31,0, -38,-41,0, -31,-46,0, -23,-45,0, -15,-39,0, -10,-32,0, -8,-23,0, -10,-16,0, -15,-10,0, -23,-9,1,//eye
	//普通の顔
	22,-26,0, 23,-25,0, 24,-24,1,//eye dots
	-22,-26,0, -23,-25,0, -24,-24,1,//eye dots 
	-19,32,0, -14,31,0, -9,31,0, -4,31,0, 0,30,0, 4,31,0, 9,31,0, 14,31,0, 19,32,1,//mouse
	1000,1000,1000
};
void Set_rpk_ppk() {
	int i,*pk_ken;

	pk_ken = &pk_ken2[0][0];//no smile
	int r = 40;//hankei
			   //	int dx=640,dy=480;

			   // convert draw data to radian
	for (i = 0; pk_ken[3 * i] != 1000; i++) {
		rpk1[i][0] = pk_ken[3 * i + 0] * 3.1415926F / 180;
		rpk1[i][1] = pk_ken[3 * i + 1] * 3.1415926F / 180;
	}

	// move (1,0,0) to each draw point
	for (i = 0; pk_ken[3 * i] != 1000; i++) {
		ppk1[i][0] = 0;
		ppk1[i][1] = 1.0F * r;
		ppk1[i][2] = 0;
	}

	// rotate all draw point based on draw data
	for (i = 0; pk_ken[3 * i] != 1000; i++) {
		RotateX(&ppk1[i][0], &ppk1[i][1], &ppk1[i][2], rpk1[i][0]);
		RotateZ(&ppk1[i][0], &ppk1[i][1], &ppk1[i][2], rpk1[i][1]);
		RotateY(&ppk1[i][0], &ppk1[i][1], &ppk1[i][2], 3.1415926F / 2);
	}

}

void Disp_ken(cv::Mat img, float q0, float q1, float q2, float q3, int sisei)
{
	int i, *pk_ken;
	float ppk[PKKENN][3];

	pk_ken = &pk_ken2[0][0];//no smile
	int x0 = 40 + 2;
	int y0 = 40 + 2;//center
	int r = 40;//hankei

	for (i = 0; pk_ken[3 * i] != 1000; i++) {
		RotateQuat(&ppk[i][0], &ppk[i][1], &ppk[i][2],ppk1[i][0],ppk1[i][1],ppk1[i][2], q0, q1, q2, q3);
	}

	rectangle(img, cv::Point(84, 84), cv::Point(0, 0), CV_RGB(255, 255, 255), -1, CV_AA, 0);
	circle(img, cv::Point(x0, y0), r, CV_RGB(200, 200, 200), -1, 8, 0);
	if (strstr(ptxt[SENM], "0")) {
		if (sisei == 1) {//仰臥位
			rectangle(img, cv::Point(0, 0), cv::Point(13, 9), CV_RGB(0, 0, 0), -1, 8, 0);
			rectangle(img, cv::Point(11, 0), cv::Point(11, 1), CV_RGB(250, 250, 250), 1, 4, 0);
			rectangle(img, cv::Point(2, 1), cv::Point(4, 3), CV_RGB(250, 250, 250), 1, 4, 0);
		}
		else if (sisei == 2) {//座位
			rectangle(img, cv::Point(0, 0), cv::Point(7, 13), CV_RGB(0, 0, 0), -1, 8, 0);
			rectangle(img, cv::Point(6, 11), cv::Point(7, 11), CV_RGB(250, 250, 250), 1, 4, 0);
			rectangle(img, cv::Point(4, 2), cv::Point(6, 4), CV_RGB(250, 250, 250), 1, 4, 0);
		}
	}
	// add offset
//	for (i = 0; pk_ken[3 * i] != 1000; i++) {
//		ppk[i][0] = x0 - ppk[i][0];
//		ppk[i][2] = y0 + ppk[i][2];
//	}
	for (i = 0; pk_ken[3 * i] != 1000; i++) {
		if (pk_ken[3 * i + 2] != 1) {//!=end
			if (ppk[i][1] >= -double(r) / 40.0 || ppk[i + 1][1] >= -double(r) / 40.0) {
				line(img, cv::Point(int(x0-ppk[i][0]), int(y0+ppk[i][2])), cv::Point(int(x0-ppk[i + 1][0]), int(y0+ppk[i + 1][2])), CV_RGB(0, 0, 0), 1.3, CV_AA, 0);
			}
		}
	}
}


UINT CCapNYS2Dlg::PreviewThread(LPVOID pParam)
{
	((CCapNYS2Dlg*)pParam)->PreviewThread();
	return 0;
}

void CCapNYS2Dlg::PreviewThread(void)
{
	cv::VideoCapture capture;
	CDC* pDC = GetDC();
	
	m_PrevloopEnable = true;
//	BITMAP bm;
//	CDC dcMem;
//	float f0=0, f1=0, f2=0, f3=0;
//	dcMem.CreateCompatibleDC(pDC);   // pDCとコンパチブルなデバイスコンテキストを作成
	if (strstr(ptxt[CAME], "9")) {
		capture.open(ptxt[IPAD]);// "http://192.168.3.43:8080/?action=stream");//デバイスのオープン
	}
	else {
		capture.open(Para0(CAME));//デバイスのオープン
	}//デバイスのオープン
	if(!capture.isOpened()) {
		Sleep(100);
		if (strstr(ptxt[CAME], "9")) {
			capture.open(ptxt[IPAD]);// "http://192.168.3.43:8080/?action=stream");//デバイスのオープン
		}
		else {
			capture.open(Para0(CAME));//デバイスのオープン
		}//デバイスのオープン//	MessageBox("camera open err!");// capdevice = false;
		//capture.release();
		//ReleaseDC(pDC);
	//	CapNYSmode = PlayMode;
		//return;
	}
	cv::Mat frame;
	int framenum = 0;
	static int winw, winh;//preview	では必要なさそうだが、タブレットを回したときのため
	///////////////
	cv::Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
	HDC whdc = pDC->GetSafeHdc();
	////////////////

	while (m_PrevloopEnable) {
		capture >> frame;
		if (frame.rows != CSH&&frame.cols != 0) {
			resize(frame, frame, cv::Size(), CSW / frame.cols, CSH / frame.rows);
		}
		framenum++;
		//disp quat
//		rectangle(frame, Point(CSW, CSH - 20), Point(0, CSH), CV_RGB(255, 255, 255), -1, CV_AA, 0);	//
//		sprintf_s(buf, sizeof(buf), "%.2f %.2f %.2f %.2f", mnq0, mnq1, mnq2, mnq3);
//		putText(frame, buf, Point(2, CSH - 3), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 0, 0), 1, CV_AA);
		int sisei;
		if (strstr(ptxt[SISE], "1"))sisei = 1;
		else sisei = 2;
		Disp_ken(frame, mnq0, mnq1, mnq2, mnq3, sisei);//mnq are get at arduinothread
		////////////////////////////////
		if (winw != Gwinw || winh != Gwinh) {//変化したら
			cv::Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
		}
		BMat = frame;
		BITMAPINFO bitInfo;
		bitInfo.bmiHeader.biBitCount = 24;
		bitInfo.bmiHeader.biWidth = BMat.cols; //the bitmap is a bottom-up DIB and its origin is the lower-left corner.
		bitInfo.bmiHeader.biHeight = -BMat.rows; //If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biCompression = BI_RGB;
		bitInfo.bmiHeader.biClrImportant = 0;
		bitInfo.bmiHeader.biClrUsed = 0;
		bitInfo.bmiHeader.biSizeImage = 0;
		bitInfo.bmiHeader.biXPelsPerMeter = 0;
		bitInfo.bmiHeader.biYPelsPerMeter = 0;
		pDC->SetStretchBltMode(HALFTONE);
		StretchDIBits(
			whdc,
			Gwinx, Gwiny,
			winw, winh,
			0, 0,
			BMat.cols, BMat.rows,
			BMat.data,
			&bitInfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);
		if (m_PrevloopEnable == false)break;
		if (strstr(ptxt[SENM], "0")) {//!Para0(SENM)) {//9分割の区画線を引く
			pDC->MoveTo(Gwinx, Gwiny + Gwinh / 3); pDC->LineTo(Gwinx + Gwinw, Gwiny + Gwinh / 3);
			pDC->MoveTo(Gwinx, Gwiny + 2 * Gwinh / 3); pDC->LineTo(Gwinx + Gwinw, Gwiny + 2 * Gwinh / 3);
			pDC->MoveTo(Gwinx + Gwinw / 3, Gwiny); pDC->LineTo(Gwinx + Gwinw / 3, Gwiny + Gwinh);
			pDC->MoveTo(Gwinx + 2 * Gwinw / 3, Gwiny); pDC->LineTo(Gwinx + 2 * Gwinw / 3, Gwiny + Gwinh);// *24 / 25);
		}
	}
//	GetQuartanion(5, &mnq0, &mnq1, &mnq2, &mnq3);
//	ArduinoM5ThreadF = false;
	m_pPreviewThread = NULL;
	Sleep(10);//念のため
	if (KillPreviewCnt == 0) {
		pDC->FillSolidRect(Gwinx, Gwiny, Gwinw, Gwinh, RGB(200, 200, 255));//&dcMem,0,0, bm.bmWidth, bm.bmHeight,SRCCOPY);
		pDC->FillSolidRect(Gwinx - 32, Gwiny, 32, Gwinh, grayRGB);//toref矢印を消す
	}
	ReleaseDC(pDC);
}

UINT CCapNYS2Dlg::PlayThread(LPVOID pParam)
{
	((CCapNYS2Dlg*)pParam)->PlayThread();
	return 0;
}

void CCapNYS2Dlg::PlayThread()
{
	CDC* pDC = GetDC();
	bool atendpos = false;

	SetTimer(1, 100, NULL);

	m_PlayloopEnable = true;
	cv::VideoCapture capture(playingfn);

	cv::Mat frame;
	int frame0;
	DWORD time0, time;
	time0 = time = timeGetTime();

	maxframenum = capture.get(cv::CAP_PROP_FRAME_COUNT);
	frame0 = 0;
	static int winw, winh;
	///////////////
	cv::Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
	HDC whdc = pDC->GetSafeHdc();
	////////////////

	while (m_PlayloopEnable) {
		static bool pausefchange = false;
		capture >> frame;//atendposを-1してみた
		if (frame.empty() || capture.get(cv::CAP_PROP_POS_AVI_RATIO) == 1 || atendpos) {
			if (atendpos) {
				SetFrame = currentframe = trimposa*maxframenum / slidew;
			}
			else {
				SetFrame = currentframe = 0;
			}
			atendpos = false;
			moviepausef=true;
		//	m_PlayloopEnable = false;
		//	break;
		}
		if (moviepausef) {
			capture.set(cv::CAP_PROP_POS_FRAMES, SetFrame);
			frame0 = SetFrame;
			pausefchange = true;
			Sleep(50);
		}
		else {
			if (pausefchange) {
				time0 = timeGetTime();
				pausefchange = false;
			}
		}
		currentframe = capture.get(cv::CAP_PROP_POS_FRAMES);
		if (m_PlayloopEnable == false)break;
		DWORD wait;
		if (!moviepausef) {
			wait = (currentframe - frame0) * 1000 / Para0(FPSN) - (timeGetTime() - time0);
			if (wait>0 && wait<300)Sleep(wait);
		}

		if (currentframe<trimposb*maxframenum/slidew-1) {
			////////////////////////////////
			if (winw != Gwinw || winh != Gwinh) {//変化したら
				cv::Mat BMat(winw = Gwinw, winh = Gwinh, CV_32FC3);
			}
			BMat = frame;
			BITMAPINFO bitInfo;
			bitInfo.bmiHeader.biBitCount = 24;
			bitInfo.bmiHeader.biWidth = BMat.cols; //the bitmap is a bottom-up DIB and its origin is the lower-left corner.
			bitInfo.bmiHeader.biHeight = -BMat.rows; //If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
			bitInfo.bmiHeader.biPlanes = 1;
			bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
			bitInfo.bmiHeader.biCompression = BI_RGB;
			bitInfo.bmiHeader.biClrImportant = 0;
			bitInfo.bmiHeader.biClrUsed = 0;
			bitInfo.bmiHeader.biSizeImage = 0;
			bitInfo.bmiHeader.biXPelsPerMeter = 0;
			bitInfo.bmiHeader.biYPelsPerMeter = 0;
			pDC->SetStretchBltMode(HALFTONE);
			StretchDIBits(
				whdc,
				Gwinx, Gwiny,
				winw, winh,
				0, 0,
				BMat.cols, BMat.rows,
				BMat.data,
				&bitInfo,
				DIB_RGB_COLORS,
				SRCCOPY
			);
			//////////////////////////////////////////////	
/*			m_bmp.GetObject(sizeof(BITMAP), &bm);
			dcMem.SelectObject(&m_bmp);
			pDC->SetStretchBltMode(COLORONCOLOR);//HALFTONE);
			pDC->StretchBlt(Gwinx, Gwiny, Gwinw, Gwinh, &dcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
*/		}
		else {
			atendpos = true;
		}
		if (moviepausef) {
			for (int i = 0; i<30; i++) {
				pDC->FillSolidRect(Gwinx + Gwinw / 2 - 30, Gwiny + Gwinh / 2 - 30 + i, 2 * i, 1, RGB(200, 200, 200));
			}
			for (int i = 0; i<30; i++) {
				pDC->FillSolidRect(Gwinx + Gwinw / 2 - 30, Gwiny + Gwinh / 2 - 0 + i, 2 * (30 - i), 1, RGB(200, 200, 200));
			}
		}
	}
	m_pPlayThread = NULL;
	ReleaseDC(pDC);
//	dcMem.DeleteDC();
	DispOneFrame(playingfn, 0);
	//	KillTimer(1);
}

void PlayFile(CDC *pDC,char playingfn)
{
	cv::VideoCapture capture(playingfn);
	cv::Mat frame;
	int winw, winh;
	cv::Mat BMat(winw=Gwinw, winh=Gwinh, CV_32FC3);
	HDC whdc = pDC->GetSafeHdc();
	////////////////

	while (1) {
		capture >> frame;
		if (frame.empty())break;
		BMat = frame;
		BITMAPINFO bitInfo;
		bitInfo.bmiHeader.biBitCount = 24;
		bitInfo.bmiHeader.biWidth = BMat.cols; //the bitmap is a bottom-up DIB and its origin is the lower-left corner.
		bitInfo.bmiHeader.biHeight = -BMat.rows; //If biHeight is negative, the bitmap is a top-down DIB and its origin is the upper-left corner.
		bitInfo.bmiHeader.biPlanes = 1;
		bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bitInfo.bmiHeader.biCompression = BI_RGB;
		bitInfo.bmiHeader.biClrImportant = 0;
		bitInfo.bmiHeader.biClrUsed = 0;
		bitInfo.bmiHeader.biSizeImage = 0;
		bitInfo.bmiHeader.biXPelsPerMeter = 0;
		bitInfo.bmiHeader.biYPelsPerMeter = 0;
		pDC->SetStretchBltMode(HALFTONE);
		StretchDIBits(
			whdc,
			Gwinx, Gwiny,
			winw, winh,
			0, 0,
			BMat.cols, BMat.rows,
			BMat.data,
			&bitInfo,
			DIB_RGB_COLORS,
			SRCCOPY
		);
	}
}

float getFloat(char *p) {
	char buf[4];
	buf[0] = p[3];
	buf[1] = p[2];
	buf[2] = p[1];
	buf[3] = p[0];
	return *((float*)&buf);
}

UINT iPhoneThread(LPVOID dummy)
{
	WSADATA wsaData;
	SOCKET s;
	SOCKADDR_IN addrin;
	SOCKADDR_IN from;
	int fromlen;
	int i, nRtn;
	u_short port;
	char szBuf[256];
	float f0, f1, f2, f3;
	//	cq0=0.99;cq1=0.00;cq2=0.00;cq3=0.00;//spaceを押した時のcenter quatrnion
	strcpy_s(szBuf, "1108");
	port = atoi(szBuf);

	if (WSAStartup(MAKEWORD(1, 1), &wsaData) != 0) {
		AfxMessageBox("WSAStartup Error");
		return -1;
	}

	s = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		AfxMessageBox("socket失敗");
		WSACleanup();
		return -2;
	}
	memset(&addrin, 0, sizeof(addrin));
	addrin.sin_port = htons(port);
	addrin.sin_family = AF_INET;
	addrin.sin_addr.s_addr = htonl(INADDR_ANY);
	nRtn = bind((SOCKET)s,(const struct sockaddr *) &addrin,(int) sizeof(addrin));
	//nRtn = std::bind(s, (LPSOCKADDR)&addrin, (int)sizeof(addrin));
	if (nRtn == SOCKET_ERROR) {//このエラーが出るが、動きには影響しない様だ？
		closesocket(s);
		WSACleanup();
		return -3;
	}
	iPhoneThreadF = true;

	while (iPhoneThreadF) {
		fromlen = (int)sizeof(from);
		nRtn = recvfrom(s, szBuf, (int)sizeof(szBuf) - 1, 0, (SOCKADDR *)&from, &fromlen);
		if (nRtn == SOCKET_ERROR) {
			AfxMessageBox("recvformエラー");
			closesocket(s);
			WSACleanup();
			return -4;
		}
		szBuf[nRtn] = '\0';

		TRACE("buf:%s", szBuf);

		for (i = 0; i < 50; i++) {
			if (szBuf[i] == 'q'&&szBuf[i + 1] == 'u'&&szBuf[i + 2] == 'a'&&szBuf[i + 3] == 't')break;
		}
		if (i < 50) {//quatの並びがあるなら	//bool checkquat(char *b)
			
			f0 = getFloat(&szBuf[44]);
			f1 = getFloat(&szBuf[48]);
			f2 = getFloat(&szBuf[52]);
			f3 = getFloat(&szBuf[56]);

			//int time = timeGetTime() - rectime;

			if (f0 >= 2)f0 = -4 + f0;
			if (f1 >= 2)f1 = -4 + f1;
			if (f2 >= 2)f2 = -4 + f2;
			if (f3 >= 2)f3 = -4 + f3;
			nq0 = f0;
			nq1 = f1;
			nq2 = f2;
			nq3 = f3;
			MultQuat(&f0, &f1, &f2, &f3, cq0, cq1, cq2, cq3, nq0, nq1, nq2, nq3);

			QuatXchan(&f0, &f1, &f2, &f3);
			mnq0 = f0;
			mnq1 = f1;
			mnq2 = f2;
			mnq3 = f3;
		}
	}
	//以下を実行すると再開が難しい？
	closesocket(s);
	WSACleanup();
	return 0;
}
void M5GyroOffset(int arcom) {
		ERS_Putc(arcom, 0x01);
		ERS_Putc(arcom, 0x80);
		ERS_Putc(arcom, 0x00);
		ERS_Putc(arcom, 0x00);
}

UINT ArduinoM5Thread_M5(LPVOID dummy)
{
	static bool initGyro = false;
	int arcom;
	int comErr;
	unsigned char buf[50];
	float f0, f1, f2, f3;
	ArduinoM5ThreadF = true;
	arcom = Para0(COMP);
	sprintf_s(m5text, "%s", "M5StickCPlus_start");

	comErr=ERS_OpenN(arcom, 4096, 4096);
	if (comErr == 0) {//0x8001 0x0000
		if (initGyro == false) {
			M5GyroOffset(arcom);//最初の１回だけoffsetを設定。
			initGyro = true;
		}		
	}
	else {
		return 0;
	}
	ERS_ClearRecv(arcom);
	while (ArduinoM5ThreadF && strstr(ptxt[SENM], "1")) {
		ERS_Recv(arcom, buf, 48);
	
		sprintf_s(m5text, "%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X", buf[0], buf[1], buf[38], buf[39], buf[40], buf[41], buf[42], buf[43], buf[44], buf[45], buf[46], buf[47]);
		if (buf[0] == 1 && buf[1] == 0) {//headerが不正のときは読まない

			f0 = *((float*)&buf[32]);
			f1 = *((float*)&buf[36]);
			f2 = *((float*)&buf[40]);
			f3 = *((float*)&buf[44]);

			if (f0 >= 2)f0 = -4 + f0;
			if (f1 >= 2)f1 = -4 + f1;
			if (f2 >= 2)f2 = -4 + f2;
			if (f3 >= 2)f3 = -4 + f3;
			nq0 = f0;
			nq1 = f1;
			nq2 = f2;
			nq3 = f3;
			MultQuat(&f0, &f1, &f2, &f3, cq0, cq1, cq2, cq3, nq0, nq1, nq2, nq3);
			QuatXchan(&f0, &f1, &f2, &f3);
			mnq0 = f0;
			mnq1 = f1;
			mnq2 = f2;
			mnq3 = f3;
		}
	//	else if (buf[0] == 2) {//m5 button
	//		ERS_Putc(arcom, 0x80);
	//		ERS_Putc(arcom, 0x01);
	//		ERS_Putc(arcom, 0x00);
	//		ERS_Putc(arcom, 0x00);
	//	}
		else {
			int n = 1;
			for (int i = 1; i < 47; i++) {
				if (buf[i] == 1 && buf[(i + 1)] == 0) {
					n = i;
					break;
				}
			}
			ERS_Recv(arcom, buf, n);//頭出し不良ならnByteずらす 9/8
		}
//		sprintf_s(m5text, "%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X", buf[0], buf[1], buf[38], buf[39], buf[40], buf[41], buf[42], buf[43], buf[44], buf[45], buf[46], buf[47]);
//		ERS_ClearRecv(arcom);
		//if (buf[0] == 2) {//m5 button
		//	ERS_Putc(arcom, 0x80);
		//	ERS_Putc(arcom, 0x01);
		//	ERS_Putc(arcom, 0x00);
		//	ERS_Putc(arcom, 0x00);
//			ArduinoThreadf = false;
		//	ERS_Recv(arcom, buf, 5);
		//	ERS_ClearRecv(arcom);
		// 
		//}
		if (GetAsyncKeyState(VK_CONTROL) && GetAsyncKeyState(VK_SHIFT)) {
			//CTRL && Shift キーが押されている 
			M5GyroOffset(arcom);	
		}
		
	}

	if(comErr==0)ERS_Close(arcom);
	// 0 正常終了
	// 1 エラー（ポート番号が範囲外 or ポートがオープンされていない）
	// 2 エラー（何らかの理由によりクローズに失敗した）
	return 0;
}

//オリジナルをシンプルにできたが、動作がどうか？暫く使用してみる。
UINT ArduinoM5Thread(LPVOID dummy)
{
	int comErr;
	int arcom;
	unsigned char teapotPacket[15];
	unsigned char buf[50];

	float f0, f1, f2, f3;

	ArduinoM5ThreadF = true;
	arcom = Para0(COMP);
	
	comErr=ERS_OpenN(arcom, 4096, 4096);
	if (comErr != 0) {
		return 0;
	}
	Sleep(10);//おかないと	ERS_Putc(arcom, 'r');　をうけつけないようだ
	ERS_Putc(arcom, 'r');
	while (ERS_CheckRecv(arcom) == 0) {
		Sleep(10);
		ERS_Putc(arcom, 'r');
	}

	sprintf_s(m5text, "%s", "MPU6050_start");
	ERS_ClearRecv(arcom);

	while (ArduinoM5ThreadF && strstr(ptxt[SENM], "2")) {
		
		ERS_Recv(arcom, buf, 14);
		sprintf_s(m5text, "%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X,%02X", buf[0], buf[1], buf[2], buf[3], buf[4], buf[5], buf[6], buf[7], buf[8], buf[9], buf[10], buf[11]);
		if (buf[0] == 0x24 && buf[1] == 2) {
			for (int i = 0; i < 12; i++) {
				teapotPacket[i] = buf[i];
			}
			f0 = ((teapotPacket[2] << 8) | teapotPacket[3]) / 16384.0f;
			f1 = ((teapotPacket[4] << 8) | teapotPacket[5]) / 16384.0f;
			f2 = ((teapotPacket[6] << 8) | teapotPacket[7]) / 16384.0f;
			f3 = ((teapotPacket[8] << 8) | teapotPacket[9]) / 16384.0f;
			if (f0 >= 2)f0 = -4 + f0;
			if (f1 >= 2)f1 = -4 + f1;
			if (f2 >= 2)f2 = -4 + f2;
			if (f3 >= 2)f3 = -4 + f3;
			nq0 = f0;
			nq1 = f1;
			nq2 = f2;
			nq3 = f3;
			MultQuat(&f0, &f1, &f2, &f3, cq0, cq1, cq2, cq3, nq0, nq1, nq2, nq3);
			QuatXchan(&f0, &f1, &f2, &f3);

			mnq0 = f0;
			mnq1 = f1;
			mnq2 = f2;
			mnq3 = f3;
		}
		else {
			int n = 1;
			for (int i = 1; i < 13; i++) {
				if (buf[i] == 1 && buf[(i + 1)] == 0) {
					n = i;
					break;
				}
			}
			ERS_Recv(arcom, buf, n);//頭出し不良ならnByteずらす
		}
	}
	if(comErr==0)ERS_Close(arcom);
	return 0;
}


//オリジナルをコピーしたものだが、多少動作が不安定。
/*UINT ArduinoM5Thread(LPVOID dummy)
{
	int ch;
	int comErr;
	int arcom;
	static int interval;
	unsigned char teapotPacket[15];
	float f0, f1, f2, f3;
	static int serialCount = 0, aligned = 0;
	ArduinoM5ThreadF = true;
	arcom = Para0(COMP);

	comErr = ERS_OpenN(arcom, 4096, 4096);
	//	sprintf_s(m5text, "port:%d", ch);
	ERS_Putc(arcom,'r');

	while (ArduinoM5ThreadF && strstr(ptxt[SENM], "2")) {
		//		cnt++;
		//		if(cnt++%1000==0)
		//上でどうか。それともデータが来てないときはスレッドを再起動するか。
		ch = ERS_Getc(arcom);
		if (ch == '$') {
			serialCount = 0;  // this will help with alignment
		}
		if (aligned < 4) {
			// make sure we are properly aligned on a 14-byte packet
			if (serialCount == 0) {
				if (ch == '$') aligned++; else aligned = 0;
			}
			else if (serialCount == 1) {
				if (ch == 2) aligned++; else aligned = 0;
			}
			else if (serialCount == 12) {
				if (ch == '\r') aligned++; else aligned = 0;
			}
			else if (serialCount == 13) {
				if (ch == '\n') aligned++; else aligned = 0;
			}
			//println(ch + " " + aligned + " " + serialCount);
			serialCount++;
			if (serialCount == 14) serialCount = 0;
		}
		else {
			if (serialCount > 0 || ch == '$') {
				teapotPacket[serialCount++] = (char)ch;
				if (serialCount == 14) {
					serialCount = 0; // restart packet byte position
					f0 = ((teapotPacket[2] << 8) | teapotPacket[3]) / 16384.0f;
					f1 = ((teapotPacket[4] << 8) | teapotPacket[5]) / 16384.0f;
					f2 = ((teapotPacket[6] << 8) | teapotPacket[7]) / 16384.0f;
					f3 = ((teapotPacket[8] << 8) | teapotPacket[9]) / 16384.0f;
					if (f0 >= 2)f0 = -4 + f0;
					if (f1 >= 2)f1 = -4 + f1;
					if (f2 >= 2)f2 = -4 + f2;
					if (f3 >= 2)f3 = -4 + f3;
					nq0 = f0;
					nq1 = f1;
					nq2 = f2;
					nq3 = f3;
					MultQuat(&f0, &f1, &f2, &f3, cq0, cq1, cq2, cq3, nq0, nq1, nq2, nq3);
					QuatXchan(&f0, &f1, &f2, &f3);

					mnq0 = f0;
					mnq1 = f1;
					mnq2 = f2;
					mnq3 = f3;
					ERS_ClearRecv(arcom);
				}
			}
		}
	}
	if (comErr == 0)ERS_Close(arcom);
	return 0;
}*/


