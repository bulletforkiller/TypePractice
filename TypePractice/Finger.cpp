// Finger.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TypePractice.h"
#include "Finger.h"
#include "afxdialogex.h"


// Finger �Ի���

IMPLEMENT_DYNAMIC(Finger, CDialog)

Finger::Finger(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_FINGER, pParent)
{

}

Finger::~Finger()
{
	m_pParentWnd->ShowWindow(SW_NORMAL);
}

void Finger::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Finger, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Finger ��Ϣ�������


void Finger::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()

	CRect rect;
	GetClientRect(&rect);
	CDC dcBmp;

	dcBmp.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);
	
	BITMAP m_bitmap;
	bmpBackground.GetBitmap(&m_bitmap);

	CBitmap *pbmpOld = dcBmp.SelectObject(&bmpBackground);

	dc.SetStretchBltMode(COLORONCOLOR);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
}
