
// button2Dlg.h : �w�b�_�[ �t�@�C��
//

#pragma once
#include "afxext.h"
#include "BtnEx.h"
#include "MyBtn.h"


// Cbutton2Dlg �_�C�A���O
class Cbutton2Dlg : public CDialog
{
// �R���X�g���N�V����
public:
	Cbutton2Dlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_BUTTON2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CBtnEx m_btn1;
	CBrush m_brDlg;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	CMyBtn m_btn2;
};
