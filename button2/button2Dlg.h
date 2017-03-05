
// button2Dlg.h : ヘッダー ファイル
//

#pragma once
#include "afxext.h"
#include "BtnEx.h"
#include "MyBtn.h"


// Cbutton2Dlg ダイアログ
class Cbutton2Dlg : public CDialog
{
// コンストラクション
public:
	Cbutton2Dlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_BUTTON2_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
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
