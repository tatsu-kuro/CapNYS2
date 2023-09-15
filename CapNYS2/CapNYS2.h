
// CapNYS2.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル
#define Vertxt "CapNYS V6.4 - 2023/9/15"
#define English true

// CCapNYS2App:
// このクラスの実装については、CapNYS2.cpp を参照してください。
//


class CCapNYS2App : public CWinApp
{
public:
	CCapNYS2App();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CCapNYS2App theApp;
