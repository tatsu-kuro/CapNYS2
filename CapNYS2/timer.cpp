
#include "stdafx.h"
#include "CapNYS2.h"
#include "CapNYS2Dlg.h"
#include "SetMemo.h"

#include <direct.h>
#include "Header.h"

#include <opencv2\opencv.hpp>
//using namespace cv;


void SetHead(int n)
{
	if (!Para0(SENM))GetQuartanion(n, &mnq0, &mnq1, &mnq2, &mnq3);
//	AfxMessageBox("sethead");
}
BOOL CCapNYS2Dlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_LBUTTONUP&&CapNYSmode==PlayMode) {//listboxの中はpretranslateでしか検知できないので
		HCURSOR hCursor = LoadCursor(NULL, IDC_ARROW);     //矢印カーソル
		SetCursor(hCursor);//DC_ARROW
		ldownf = 0;
		CPoint pt = pMsg->pt;
		ScreenToClient(&pt);
		int x = CheckPicPos(CapNYSmode, pt.x, pt.y);
		if (x == 7 && CapNYSmode == PlayMode && PicPosflag == 6) {//videoをドラッグしListref上でUpしたとき
			OnStnClickedArrowore();
		}
		sliderf = false;
		return false;
	}
	else if (pMsg->message == WM_MOUSEMOVE) {
		if (PicPosflag == 6 && CapNYSmode == PlayMode) {
			if (ldownf == 1) {
				HCURSOR hCursor = LoadCursor(NULL, IDC_HAND);     // 砂時計カーソル
				SetCursor(hCursor);//DC_ARROW
			}
			else {
				PicPosflag = -1;
			}
		}
	}
	else if (pMsg->message == WM_KEYDOWN) {
		switch (pMsg->wParam) {
		case VK_F1:
			if (CapNYSmode == CaptMode) {
				OnBnClickedResetrec();
			}else {
				OnClickedRecord();
			}
			return true;
		case VK_F2:
			if (CapNYSmode == CaptMode) {
				OnBnClickedStopcap();
			}
			else if (CapNYSmode == ListMode) {
				OnClickedMemo();
			}
			else if (CapNYSmode == PlayMode) {
				if (m_listref.GetNextItem(-1, LVNI_SELECTED) < 0 && m_listcurrent.GetNextItem(-1, LVNI_SELECTED) < 0)return true;
				OnClickedMemo();
			}
			return true;
//		case VK_F4:
//			if (CapNYSmode == CaptMode) {
//				strcpy_s(ptxt[FLSP], "0");// LowSpecPC mode off
//				OnBnClickedResetrec();
//				return true;
//			}
//			return false;
//		case VK_F5:
//			if (CapNYSmode == CaptMode) {
//				strcpy_s(ptxt[FLSP], "1");// LowSpecPC mode off
//				OnBnClickedResetrec();
//				return true;
//			}
//			return false;
		case VK_RETURN:
			if (CapNYSmode == CaptMode) {
				OnBnClickedStopcap();
			}
			else if (CapNYSmode == PlayMode||CapNYSmode == ListMode){
				OnBnClickedPlaymovie();
			}
			return true;// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
		case VK_SPACE:
		case '0':
			if (CapNYSmode == CaptMode) {
				static int spacetime = 0;
				Resetheadfcnt = 5;
				OnBnClickedResethead();
				if (timeGetTime() - spacetime<300) {//spceのダブルクリック
					::PostMessage(m_resetrec, BM_CLICK, 0, 0);
				}
				spacetime = timeGetTime();
			}
			else if (CapNYSmode == PlayMode) {
				OnBnClickedPlaymovie();
			}
			else if (CapNYSmode == PrevMode) {
				Resetheadfcnt = 5;
				OnBnClickedResethead();
			}
	//		else {
	//			return true;
	//		}
			return true;
		case VK_UP:
			if (CapNYSmode == PlayMode) {
				if (!(::GetKeyState(VK_SHIFT) & 0xF000)) {
					OnBnClickedPlaymovie();
					SetFrame = currentframe + maxframenum / 10;
					if (SetFrame > maxframenum)SetFrame = maxframenum - 5;
					moviepausef = true;
				}
			}
			else if (CapNYSmode == ListMode) {
				int nSelected = m_listavi.GetNextItem(-1, LVNI_SELECTED);
				int sc = m_listavi.GetItemCount();
				if (!(nSelected == sc || sc == 1)) {
					nSelected -= 1;
					m_listavi.SetItemState(nSelected, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
					m_listavi.EnsureVisible(nSelected, false);
				}
			}
			return true;
		case VK_DOWN:
			if (CapNYSmode == PlayMode) {
				if (!(::GetKeyState(VK_SHIFT) & 0xF000)) {
					OnBnClickedPlaymovie();
					SetFrame = currentframe - maxframenum / 10;
					if (SetFrame < 0)SetFrame = 1;
					moviepausef = true;
				}
			}
			else if (CapNYSmode == ListMode) {
				int nSelected = m_listavi.GetNextItem(-1, LVNI_SELECTED);
				int sc = m_listavi.GetItemCount();
				if (!(nSelected == sc || sc == 1)) {
					nSelected += 1;
					m_listavi.SetItemState(nSelected, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
					m_listavi.EnsureVisible(nSelected, false);
				}
			}
			return true;
		case VK_LEFT:

			if (CapNYSmode == PlayMode) {
				if (!(::GetKeyState(VK_SHIFT) & 0xF000)) {
					OnBnClickedPlaymovie();
					SetFrame = currentframe - 1;
					if (SetFrame < 0)SetFrame = 1;
					moviepausef = true;
				}
			}
			return true;
		case VK_RIGHT:
			if (CapNYSmode == PlayMode) {
				if (!(::GetKeyState(VK_SHIFT) & 0xF000)) {
					OnBnClickedPlaymovie();
					SetFrame = currentframe + 1;
					if (SetFrame > maxframenum)SetFrame = maxframenum - 5;
					moviepausef = true;
				}
			}
			return true;
		case VK_DELETE:
//			if (CapNYSmode != CaptMode) {
//				if (CapNYSmode == PlayMode) {
//					if (m_listref.GetNextItem(-1, LVNI_SELECTED) < 0 && m_listcurrent.GetNextItem(-1, LVNI_SELECTED) < 0)return true;
//					if (AfxMessageBox("Erase the playing file. OK?", MB_OKCANCEL) != IDOK) {
//						return true;
//					}
//					OnPopupDelete();
//				}
//				else
			if (CapNYSmode == ListMode) {
				if (m_listavi.GetNextItem(-1, LVNI_SELECTED) < 0)return true;
				if (AfxMessageBox("Erase the selected file. OK?", MB_OKCANCEL) != IDOK) {
					return true;
				}
				OnClickedErasebut();
			}
//			}
			return true;
		case 'J':
		case '1':
		case  VK_NUMPAD1:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(1);
				return true;
			}
			break;
		case 'K':
		case '2':
		case  VK_NUMPAD2:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(2);
				return true;
			}
			break;
		case 'L':
		case '3':
		case  VK_NUMPAD3:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(3);
				return true;
			}
			break;
		case 'U':
		case '4':
		case  VK_NUMPAD4:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(4);
				return true;
			}
			break;
		case 'I':
		case '5':
		case  VK_NUMPAD5:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(5);
				return true;
			}
			break;
		case 'O':
		case '6':
		case  VK_NUMPAD6:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(6);
				return true;
			}
			break;
		case '7':
		case  VK_NUMPAD7:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(7);
				return true;
			}
			break;
		case '8':
		case  VK_NUMPAD8:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(8);
				return true;
			}
			break;
		case '9':
		case  VK_NUMPAD9:
			if (CapNYSmode == CaptMode || CapNYSmode == PrevMode) {
				SetHead(9);
				return true;
			}
			break;
		case VK_ESCAPE:
			return true;
		case VK_BACK:
			if (CapNYSmode == PlayMode) {
				OnBnClickedList();
				m_listavi.SetFocus();
			}
			return true;
		default:break;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
#ifdef _DEBUG
void CCapNYS2Dlg::Save_sen4()
{
	CStdioFile ff;
	char buf[300];
	int i;
	ff.Open("sensor_data.txt", CFile::modeCreate |
		CFile::modeWrite | CFile::modeRead | CFile::typeText);
	for (i = 0; i < 5000; i++) {//writeini
		sprintf_s(buf, 299, "%05d - %09.8f, %09.8f, %09.8f, %09.8f\n", i, SenD4[i][0], SenD4[i][1], SenD4[i][2], SenD4[i][3]);
		ff.WriteString(buf);
	}
	ff.Abort();
}
#endif

void CCapNYS2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) {//100msecごと
		static int cnt = 0;
		cnt++;
		static bool m5 = false;
		if (CapNYSmode == PlayMode) {//play
			static bool trimf = false;
			DispSlider();
			if(cnt%5==0)DispTimeTrim();

			if (KillPlayCnt>0) {
				if (!m_pPlayThread) {
					KillPlayCnt--;//=false;
					if (KillPlayCnt == 0) {
						int tm;
						if (strstr(ptxt[SENM], "1")) {
							AfxBeginThread(ArduinoM5Thread_M5, &tm);
						}
						else if (strstr(ptxt[SENM], "2")) {
							AfxBeginThread(ArduinoM5Thread, &tm);
						}
						else {
							AfxBeginThread(iPhoneThread, &tm);
						}
						m_pCaptureThread = AfxBeginThread(CaptureThread, this);
						Resetheadfcnt = 5;
						SetButtons(CapNYSmode = CaptMode);
					}
				}
			}


		}
		else if (CapNYSmode == CaptMode) {//capture
			if ((GetKeyState(VK_SHIFT) & 0x8000) && m5textFlag == false) {
				m5textFlag = true;
			}
			if (m5textFlag == true) {
				SetWindowTextA(m5text);
			}
			
			if (cnt % 2 == 0)DispTimeTrim();
			if (Resetheadfcnt > 0) {
				cq0 = nq0; cq3 = -nq3;
				Resetheadfcnt--;
			}
			if (KillRecordCnt>0) {//capture
				if (!m_pCaptureThread) {
					KillRecordCnt--;//=false;
					if (KillRecordCnt == 0) {
						int tm;
						if (IsFile(lastrecfn))f2gomi(lastrecfn);

						if (strstr(ptxt[SENM], "1")) {
							AfxBeginThread(ArduinoM5Thread_M5, &tm);
						}
						else if (strstr(ptxt[SENM], "2")) {
							AfxBeginThread(ArduinoM5Thread, &tm);
						}
						else {
							AfxBeginThread(iPhoneThread, &tm);
						}
					
						m_pCaptureThread = AfxBeginThread(CaptureThread, this);
						Resetheadfcnt = 5;
					}
				}
			}

		}
		else if (CapNYSmode == PrevMode) {//preview
			if (Resetheadfcnt>0) {
				if (!(nq0 == 0.01F&&nq1 == 0.0F&&nq2 == 0.0F&&nq3 == 0.0F)) {
					cq0 = nq0; cq3 = -nq3;
				}
				Resetheadfcnt--;
			}
			if (KillPreviewCnt>0) {
				if (!m_pPreviewThread) {
					KillPreviewCnt--;//=false;
					if (KillPreviewCnt == 0) {

						m_pCaptureThread = AfxBeginThread(CaptureThread, this);
						Resetheadfcnt = 5;
						SetButtons(CapNYSmode = CaptMode);	
					}
				}
			}

		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

