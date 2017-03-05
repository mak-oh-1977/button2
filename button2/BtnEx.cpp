// BtnEx.cpp : 実装ファイル
//

#include "stdafx.h"
#include "button2.h"
#include "BtnEx.h"


// CBtnEx

IMPLEMENT_DYNAMIC(CBtnEx, CButton)

CBtnEx::CBtnEx()
{
	m_bm1.LoadBitmap(IDB_BITMAP1);
	m_bm2.LoadBitmap(IDB_BITMAP2);

}

CBtnEx::~CBtnEx()
{
}


BEGIN_MESSAGE_MAP(CBtnEx, CBitmapButton)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
ON_WM_CTLCOLOR_REFLECT()
ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CBtnEx メッセージ ハンドラ




void CBtnEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	m_bDown = true;
//	RedrawWindow();
	CButton::OnLButtonDown(nFlags, point);
}

void CBtnEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	m_bDown = false;
//	RedrawWindow();

	CButton::OnLButtonUp(nFlags, point);
}

BOOL CBtnEx::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CButton::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
}

//void CBtnEx::OnPaint()
//{
///*	CPaintDC dc(this); // device context for painting
//	// TODO: ここにメッセージ ハンドラ コードを追加します。
//	// 描画メッセージで CButton::OnPaint() を呼び出さないでください。
//
//	CDC dcMem;
//	dcMem.CreateCompatibleDC(&dc);
//
//	BITMAP bm;
//	if (m_bDown)
//	{
//		m_bm2.GetObject(sizeof(BITMAP), &bm);
//		dcMem.SelectObject(m_bm2);
//	}
//	else
//	{
//		m_bm1.GetObject(sizeof(BITMAP), &bm);
//		dcMem.SelectObject(m_bm1);
//	}
//	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcMem, 0, 0, SRCCOPY);
//	dcMem.DeleteDC();
//*/
//}

//void CBtnEx::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
//{
//	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
//
//	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
//}
#include "math.h"

void CBtnEx::DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct)
{

	// TODO:  指定された項目を描画するためのコードを追加してください。
/*	CRect rct = lpDrawItemStruct->rcItem;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRgn rgnClip;
	rgnClip.CreateEllipticRgn(rct.left, rct.top, rct.right-1, rct.bottom-1);
	pDC->SelectClipRgn(&rgnClip);

	pDC->FillSolidRect(&rct, ::GetSysColor(COLOR_BTNFACE));

	rct.DeflateRect(1,1);
	
	CPen penWhite(PS_SOLID, 2, (COLORREF)0x00ffffff);
	CPen penBlack(PS_SOLID, 2, (COLORREF)0x00404040);

	if(lpDrawItemStruct->itemState & ODS_SELECTED)  
		pDC->SelectObject(&penBlack);
	else
		pDC->SelectObject(&penWhite);

	pDC->Arc(rct.left, rct.top, rct.right-1, rct.bottom-1, 
			rct.CenterPoint().x + rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y - rct.Height() / 2 /pow(2,0.5),
			rct.CenterPoint().x - rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y + rct.Height() / 2 /pow(2,0.5));
	
	if(lpDrawItemStruct->itemState & ODS_SELECTED)  
		pDC->SelectObject(&penWhite);
	else
		pDC->SelectObject(&penBlack);

	pDC->Arc(rct.left, rct.top, rct.right-1, rct.bottom-1, 
			rct.CenterPoint().x - rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y + rct.Height() / 2 /pow(2,0.5),
			rct.CenterPoint().x + rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y - rct.Height() / 2 /pow(2,0.5));

	CString strWindowText;
	GetWindowText(strWindowText);
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF colorref = pDC->SetTextColor(RGB(255,0,0));
	if(lpDrawItemStruct->itemState & ODS_SELECTED)  
		rct.OffsetRect(1,1);
	pDC->DrawText(strWindowText, &rct, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SetTextColor(colorref);
	pDC->SelectClipRgn(NULL);
	rgnClip.DeleteObject();
/*
	// 好きな色で普通のボタン面を描く
	HBRUSH hBrush = CreateSolidBrush(RGB(153,204,204));// 今回こんな色
	RECT r = lpDrawItemStruct->rcItem;

//	CBrush brush(RGB(255, 255, 255));
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetBkColor(RGB(0,0, 0));
//	pDC->FillRect(&r, &brush);
	CRect rct = lpDrawItemStruct->rcItem;

	CRgn rgnClip;
	rgnClip.CreateEllipticRgn(rct.left, rct.top, rct.right-1, rct.bottom-1);
	pDC->SelectClipRgn(&rgnClip);

	pDC->FillSolidRect(&rct, ::GetSysColor(COLOR_BTNFACE));

	rct.DeflateRect(1,1);
	
	CPen penWhite(PS_SOLID, 2, (COLORREF)0x00ffffff);
	CPen penBlack(PS_SOLID, 2, (COLORREF)0x00404040);

	if(lpDrawItemStruct->itemState & ODS_SELECTED)  
		pDC->SelectObject(&penBlack);
	else
		pDC->SelectObject(&penWhite);

	pDC->Arc(rct.left, rct.top, rct.right-1, rct.bottom-1, 
			rct.CenterPoint().x + rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y - rct.Height() / 2 /pow(2,0.5),
			rct.CenterPoint().x - rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y + rct.Height() / 2 /pow(2,0.5));
	
	if(lpDrawItemStruct->itemState & ODS_SELECTED)  
		pDC->SelectObject(&penWhite);
	else
		pDC->SelectObject(&penBlack);

	pDC->Arc(rct.left, rct.top, rct.right-1, rct.bottom-1, 
			rct.CenterPoint().x - rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y + rct.Height() / 2 /pow(2,0.5),
			rct.CenterPoint().x + rct.Width() / 2 /pow(2,0.5),
			rct.CenterPoint().y - rct.Height() / 2 /pow(2,0.5));

	CString strWindowText;
	GetWindowText(strWindowText);
	int nBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF colorref = pDC->SetTextColor(RGB(255,0,0));
	if(lpDrawItemStruct->itemState & ODS_SELECTED)  
		rct.OffsetRect(1,1);
	pDC->DrawText(strWindowText, &rct, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SetTextColor(colorref);
	pDC->SelectClipRgn(NULL);
	rgnClip.DeleteObject();
	/*
	// TODO:  指定された項目を描画するためのコードを追加してください。
   UINT uStyle = DFCS_BUTTONPUSH;

   // This code only works with buttons.
   ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

   // If drawing selected, add the pushed style to DrawFrameControl.
   if (lpDrawItemStruct->itemState & ODS_SELECTED)
      uStyle |= DFCS_PUSHED;

   // Draw the button frame.
   ::DrawFrameControl(lpDrawItemStruct->hDC, &lpDrawItemStruct->rcItem, 
      DFC_BUTTON, uStyle);

   // Get the button's text.
   CString strText;
   GetWindowText(strText);

   // Draw the button text using the text color red.
   COLORREF crOldColor = ::SetTextColor(lpDrawItemStruct->hDC, RGB(255,0,0));
   ::DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(), 
      &lpDrawItemStruct->rcItem, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
   ::SetTextColor(lpDrawItemStruct->hDC, crOldColor);
*/
   ASSERT_POINTER(pDrawItemStruct, DRAWITEMSTRUCT);
    ASSERT(pDrawItemStruct->CtlType == ODT_BUTTON);

    CDC dc;
    if( dc.Attach(pDrawItemStruct->hDC) ) {
        CRect rect(pDrawItemStruct->rcItem);
        int nState = DFCS_BUTTONPUSH;
        if( (pDrawItemStruct->itemState & ODS_SELECTED) != 0 ) nState |= DFCS_PUSHED;
        if( (pDrawItemStruct->itemState & ODS_DISABLED) != 0 ) nState |= DFCS_INACTIVE;
//        dc.DrawFrameControl(&rect, DFC_BUTTON, nState);

        // (pDrawItemStruct->itemState & ODS_SELECTED) や
        // (pDrawItemStruct->itemState & ODS_DISABLED) や
        // (pDrawItemStruct->itemState & ODS_FOCUS) の状況に応じ
        // たビットマップを選択する例 (ここでは ODS_SELECTED のみ)
        CBitmap& bitmap = ((pDrawItemStruct->itemState & ODS_SELECTED) != 0) ? m_bm2 : m_bm1;

        // dc に対して (CreateCompatibleDC，BitBlt 又は
        // StretchBlt等を使って) pDrawItemStruct->rcItem の真ん
        // 中に其のビットマップを描画する例
        DrawBitmap(dc, bitmap, rect);
        // ついでに...
/*        if( (pDrawItemStruct->itemState & ODS_FOCUS) != 0 ) {
            rect.InflateRect(-5, -5);
            dc.DrawFocusRect(&rect);
        }
*/
        dc.Detach();
    }

   }

const bool CBtnEx::DrawBitmap(CDC& dc, CBitmap& bitmap, const CRect& rectPosition, DWORD dwRop)
{
    ASSERT(dc.GetSafeHdc() != HDC(0));
    ASSERT(bitmap.GetSafeHandle() != HBITMAP(0));

	dc.SetBkMode(TRANSPARENT);
//	HBRUSHhbr = (HBRUSH)::GetStockObject(NULL_BRUSH);

    CBrush       *pOldBrush = NULL, *pBrush = NULL;
    int          err = 0;
    
    // ストックブラシを選択
    if (!err) if ((pOldBrush = static_cast<CBrush *>
                (dc.SelectStockObject(NULL_BRUSH))) == NULL) err = 1;
    // 現在のブラシを取得
    if (!err) if ((pBrush = dc.GetCurrentBrush()) == NULL) err = 1;
    // 四角形の描画
    CRect rect;
    rect.right = 300;
    rect.bottom = 100;
    if (!err) dc.FillRect(&rect, pBrush);


	
    const CPoint    ptPosition(rectPosition.CenterPoint());
    bool            bRtn = false;
    CDC             dcMemory;
    if( dcMemory.CreateCompatibleDC(&dc) ) {
        CBitmap* const  pBitmap = dcMemory.SelectObject(&bitmap);

		
        BITMAP          bm;
        // rectPosition の真ん中に食み出さないように...
        if( bitmap.GetObject(sizeof(BITMAP), &bm) != 0 ) {
            CSize       size(bm.bmWidth, bm.bmHeight);

//			dc.TransparentBlt(0, 0, size.cx, size.cy, &dcMemory, 0, 0, size.cx, size.cy, RGB(0,0,0));
			Blit(dcMemory, dc, 0, 0, size.cx, size.cy, 0, 0, RGB(0, 0, 0));

/*            // 座標系について考慮しない場合
            CPoint      ptOrg1(0, 0);
            const int   nWidth  = rectPosition.Width();
            if( size.cx > nWidth ) {
                ptOrg1.x += ((size.cx - nWidth ) >> 1);
                size.cx  = nWidth ;
            }
            const int       nHeight = rectPosition.Height();
            if( size.cy > nHeight ) {
                ptOrg1.y += ((size.cy - nHeight) >> 1);
                size.cy  = nHeight;
            }
            const CPoint    ptOrg2(ptPosition.x - (size.cx >> 1), ptPosition.y - (size.cy >> 1));
            bRtn = !!dc.BitBlt(0, 0,
                               size.cx, size.cy,
                               &dcMemory, 0, 0,
                               dwRop);

*/        }

        if( pBitmap != NULL ) dcMemory.SelectObject(pBitmap);
        VERIFY(dcMemory.DeleteDC());
    }
    return bRtn;

}

void CBtnEx::Blit(HDC from,HDC to,int x,int y,int width,int height,int fromx,int fromy,COLORREF tran)
{
    HBITMAP bmono,oldmono,bkuro,oldkuro;
    HDC     mmono,mkuro;


    /*
      描画するビットマップと同じサイズのモノクロビット
    　マップを作成し透明色の部分が白それ以外が黒となるよう
　　  にする。
    */

    mmono=CreateCompatibleDC(from);
    bmono=CreateBitmap(width,height,1,1,NULL);   
    oldmono=(HBITMAP)SelectObject(mmono,bmono);
    SetBkColor(from,tran);
    BitBlt(mmono,0,0,width,height,from,fromx,fromy,SRCCOPY); 
  

    /*
    メモリDCを作成し、元のビットマップと同じ物をコピーする。
    モノクロビットマップにNOT演算したものを
    作ったメモリDCにラスタオペレーションSRCANDでブリットしている。
    */

    mkuro=CreateCompatibleDC(from);
    bkuro=CreateCompatibleBitmap(from,width,height);
    oldkuro=(HBITMAP)SelectObject(mkuro,bkuro);
    BitBlt(mkuro,0,0,width,height,from,fromx,fromy,SRCCOPY);
    
    BitBlt(mkuro,0,0,width,height,mmono,fromx,fromy,0x220326);
      //↑のラスタオペレーションでNOT演算とSRCANDの作業が一度にできる

    /*
    出力先のDCにモノクロビットマップを持つDCを
    ラスタオペレーションSRCANDでブリットし
    もう一つのDCをラスタオペレーションSRCINVERTでブリットする。
    */

    BitBlt(to,x,y,width,height,mmono,fromx,fromy,SRCAND);
    BitBlt(to,x,y,width,height,mkuro,fromx,fromy,SRCINVERT);
    
    SelectObject(mmono,oldmono);
    DeleteObject(bmono);
    DeleteDC(mmono);

    SelectObject(mkuro,oldkuro);
    DeleteObject(bkuro);
    DeleteDC(mkuro);
}


HBRUSH CBtnEx::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  ここで DC の属性を変更してください。

	// TODO:  親のハンドラを呼び出せない場合は NULL 以外のブラシを返します。
	return NULL;
}

BOOL CBtnEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	return TRUE;
//	return CButton::OnEraseBkgnd(pDC);
}
