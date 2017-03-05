// MyBtn.cpp : 実装ファイル
//

#include "stdafx.h"
#include "button2.h"
#include "MyBtn.h"

#pragma comment(lib, "msimg32")

// CMyBtn

IMPLEMENT_DYNAMIC(CMyBtn, CButton)

CMyBtn::CMyBtn()
{
	m_bm1.LoadBitmap(IDB_BTN);
	m_bm2.LoadBitmap(IDB_BTNON);

}

CMyBtn::~CMyBtn()
{
}


BEGIN_MESSAGE_MAP(CMyBtn, CButton)
	ON_WM_ERASEBKGND()
//	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyBtn メッセージ ハンドラ



void CMyBtn::DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct)
{

	// TODO:  指定された項目を描画するためのコードを追加してください。
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
		CFont* pFont;
		CFont font;

		// フォントを作成する
		font.CreateFont(
			30,                   // フォントの高さ(大きさ)。
			0,                    // フォントの幅。普通０。
			0,                    // 角度。０でＯＫ。
			0,                    // 同じく角度。これも０。
			FW_HEAVY,             // 文字の太さ。
			FALSE,                // フォントがイタリックならTRUEを指定。
			FALSE,                // 下線を引くならTRUE。
			FALSE,                // 取り消し線を引くならTRUE。
			SHIFTJIS_CHARSET,     // フォントの文字セット。このままでＯＫ。
			OUT_DEFAULT_PRECIS,   // 出力精度の設定。このままでＯＫ。
			CLIP_DEFAULT_PRECIS,  // クリッピング精度。このままでＯＫ。
			DRAFT_QUALITY,        // フォントの出力品質。このままでＯＫ。
			DEFAULT_PITCH,        // フォントのピッチとファミリを指定。このままでＯＫ。
			_T("メイリオ")			// フォントのタイプフェイス名の指定。これは見たまんま。
			);
		pFont = dc.SelectObject(&font);        // フォントを設定。



		CString s;
		GetWindowText(s);	
        dc.SetBkMode(TRANSPARENT);
        dc.SetTextColor(RGB(120, 120, 120));
        dc.TextOutW(11, 11, s);
        dc.SetTextColor(RGB(255, 255, 255));
        dc.TextOutW(10, 10, s);
        dc.Detach();
    }

}

const bool CMyBtn::DrawBitmap(CDC& dc, CBitmap& bitmap, const CRect& rectPosition, DWORD dwRop)
{
    ASSERT(dc.GetSafeHdc() != HDC(0));
    ASSERT(bitmap.GetSafeHandle() != HBITMAP(0));

//	dc.SetBkMode(TRANSPARENT);
//	HBRUSH hbr = (HBRUSH)::GetStockObject(NULL_BRUSH);

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

BOOL CMyBtn::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	return NULL;
	
}

HBRUSH CMyBtn::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  ここで DC の属性を変更してください。

	// TODO:  親のハンドラを呼び出せない場合は NULL 以外のブラシを返します。
	return NULL;
}

void CMyBtn::Blit(HDC from,HDC to,int x,int y,int width,int height,int fromx,int fromy,COLORREF tran)
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

