// MyBtn.cpp : �����t�@�C��
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



// CMyBtn ���b�Z�[�W �n���h��



void CMyBtn::DrawItem(LPDRAWITEMSTRUCT pDrawItemStruct)
{

	// TODO:  �w�肳�ꂽ���ڂ�`�悷�邽�߂̃R�[�h��ǉ����Ă��������B
   ASSERT_POINTER(pDrawItemStruct, DRAWITEMSTRUCT);
    ASSERT(pDrawItemStruct->CtlType == ODT_BUTTON);

    CDC dc;
    if( dc.Attach(pDrawItemStruct->hDC) ) {
        CRect rect(pDrawItemStruct->rcItem);
        int nState = DFCS_BUTTONPUSH;
        if( (pDrawItemStruct->itemState & ODS_SELECTED) != 0 ) nState |= DFCS_PUSHED;
        if( (pDrawItemStruct->itemState & ODS_DISABLED) != 0 ) nState |= DFCS_INACTIVE;
//        dc.DrawFrameControl(&rect, DFC_BUTTON, nState);

        // (pDrawItemStruct->itemState & ODS_SELECTED) ��
        // (pDrawItemStruct->itemState & ODS_DISABLED) ��
        // (pDrawItemStruct->itemState & ODS_FOCUS) �̏󋵂ɉ���
        // ���r�b�g�}�b�v��I������� (�����ł� ODS_SELECTED �̂�)
        CBitmap& bitmap = ((pDrawItemStruct->itemState & ODS_SELECTED) != 0) ? m_bm2 : m_bm1;

        // dc �ɑ΂��� (CreateCompatibleDC�CBitBlt ����
        // StretchBlt�����g����) pDrawItemStruct->rcItem �̐^��
        // ���ɑ��̃r�b�g�}�b�v��`�悷���
        DrawBitmap(dc, bitmap, rect);
        // ���ł�...
/*        if( (pDrawItemStruct->itemState & ODS_FOCUS) != 0 ) {
            rect.InflateRect(-5, -5);
            dc.DrawFocusRect(&rect);
        }
*/
		CFont* pFont;
		CFont font;

		// �t�H���g���쐬����
		font.CreateFont(
			30,                   // �t�H���g�̍���(�傫��)�B
			0,                    // �t�H���g�̕��B���ʂO�B
			0,                    // �p�x�B�O�łn�j�B
			0,                    // �������p�x�B������O�B
			FW_HEAVY,             // �����̑����B
			FALSE,                // �t�H���g���C�^���b�N�Ȃ�TRUE���w��B
			FALSE,                // �����������Ȃ�TRUE�B
			FALSE,                // ���������������Ȃ�TRUE�B
			SHIFTJIS_CHARSET,     // �t�H���g�̕����Z�b�g�B���̂܂܂łn�j�B
			OUT_DEFAULT_PRECIS,   // �o�͐��x�̐ݒ�B���̂܂܂łn�j�B
			CLIP_DEFAULT_PRECIS,  // �N���b�s���O���x�B���̂܂܂łn�j�B
			DRAFT_QUALITY,        // �t�H���g�̏o�͕i���B���̂܂܂łn�j�B
			DEFAULT_PITCH,        // �t�H���g�̃s�b�`�ƃt�@�~�����w��B���̂܂܂łn�j�B
			_T("���C���I")			// �t�H���g�̃^�C�v�t�F�C�X���̎w��B����͌����܂�܁B
			);
		pFont = dc.SelectObject(&font);        // �t�H���g��ݒ�B



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
    
    // �X�g�b�N�u���V��I��
    if (!err) if ((pOldBrush = static_cast<CBrush *>
                (dc.SelectStockObject(NULL_BRUSH))) == NULL) err = 1;
    // ���݂̃u���V���擾
    if (!err) if ((pBrush = dc.GetCurrentBrush()) == NULL) err = 1;
    // �l�p�`�̕`��
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
        // rectPosition �̐^�񒆂ɐH�ݏo���Ȃ��悤��...
        if( bitmap.GetObject(sizeof(BITMAP), &bm) != 0 ) {
            CSize       size(bm.bmWidth, bm.bmHeight);

//			dc.TransparentBlt(0, 0, size.cx, size.cy, &dcMemory, 0, 0, size.cx, size.cy, RGB(0,0,0));
			Blit(dcMemory, dc, 0, 0, size.cx, size.cy, 0, 0, RGB(0, 0, 0));

/*            // ���W�n�ɂ��čl�����Ȃ��ꍇ
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
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	return NULL;
	
}

HBRUSH CMyBtn::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  ������ DC �̑�����ύX���Ă��������B

	// TODO:  �e�̃n���h�����Ăяo���Ȃ��ꍇ�� NULL �ȊO�̃u���V��Ԃ��܂��B
	return NULL;
}

void CMyBtn::Blit(HDC from,HDC to,int x,int y,int width,int height,int fromx,int fromy,COLORREF tran)
{
    HBITMAP bmono,oldmono,bkuro,oldkuro;
    HDC     mmono,mkuro;


    /*
      �`�悷��r�b�g�}�b�v�Ɠ����T�C�Y�̃��m�N���r�b�g
    �@�}�b�v���쐬�������F�̕�����������ȊO�����ƂȂ�悤
�@�@  �ɂ���B
    */

    mmono=CreateCompatibleDC(from);
    bmono=CreateBitmap(width,height,1,1,NULL);   
    oldmono=(HBITMAP)SelectObject(mmono,bmono);
    SetBkColor(from,tran);
    BitBlt(mmono,0,0,width,height,from,fromx,fromy,SRCCOPY); 
  

    /*
    ������DC���쐬���A���̃r�b�g�}�b�v�Ɠ��������R�s�[����B
    ���m�N���r�b�g�}�b�v��NOT���Z�������̂�
    �����������DC�Ƀ��X�^�I�y���[�V����SRCAND�Ńu���b�g���Ă���B
    */

    mkuro=CreateCompatibleDC(from);
    bkuro=CreateCompatibleBitmap(from,width,height);
    oldkuro=(HBITMAP)SelectObject(mkuro,bkuro);
    BitBlt(mkuro,0,0,width,height,from,fromx,fromy,SRCCOPY);
    
    BitBlt(mkuro,0,0,width,height,mmono,fromx,fromy,0x220326);
      //���̃��X�^�I�y���[�V������NOT���Z��SRCAND�̍�Ƃ���x�ɂł���

    /*
    �o�͐��DC�Ƀ��m�N���r�b�g�}�b�v������DC��
    ���X�^�I�y���[�V����SRCAND�Ńu���b�g��
    �������DC�����X�^�I�y���[�V����SRCINVERT�Ńu���b�g����B
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

