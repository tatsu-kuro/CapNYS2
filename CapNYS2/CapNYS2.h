
// CapNYS2.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��
#define Vertxt "CapNYS V6.4 - 2023/7/27"
#define English true

// CCapNYS2App:
// ���̃N���X�̎����ɂ��ẮACapNYS2.cpp ���Q�Ƃ��Ă��������B
//


class CCapNYS2App : public CWinApp
{
public:
	CCapNYS2App();

// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CCapNYS2App theApp;