
// button2.h : PROJECT_NAME �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"		// ���C�� �V���{��


// Cbutton2App:
// ���̃N���X�̎����ɂ��ẮAbutton2.cpp ���Q�Ƃ��Ă��������B
//

class Cbutton2App : public CWinAppEx
{
public:
	Cbutton2App();

// �I�[�o�[���C�h
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern Cbutton2App theApp;