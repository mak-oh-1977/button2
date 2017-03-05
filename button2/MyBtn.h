#pragma once


// CMyBtn

class CMyBtn : public CButton
{
	DECLARE_DYNAMIC(CMyBtn)

public:
	CMyBtn();
	virtual ~CMyBtn();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	CBitmap m_bm1;
	CBitmap m_bm2;

	const bool DrawBitmap(CDC& dc, CBitmap& bitmap, const CRect& rectPosition, DWORD dwRop = SRCCOPY);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);

	void Blit(HDC from,HDC to,int x,int y,int width,int height,int fromx,int fromy,COLORREF tran);
};


