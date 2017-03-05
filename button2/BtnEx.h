#pragma once


// CBtnEx

class CBtnEx : public CButton
{
	DECLARE_DYNAMIC(CBtnEx)

public:
	CBtnEx();
	virtual ~CBtnEx();

protected:
	DECLARE_MESSAGE_MAP()
public:

	BOOL m_bDown;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CBitmap m_bm1;
	CBitmap m_bm2;
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
//	afx_msg void OnPaint();
//	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	const bool DrawBitmap(CDC& dc, CBitmap& bitmap, const CRect& rectPosition, DWORD dwRop = SRCCOPY);
	void Blit(HDC from,HDC to,int x,int y,int width,int height,int fromx,int fromy,COLORREF tran);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


