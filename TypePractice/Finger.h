#pragma once


// Finger �Ի���

class Finger : public CDialog
{
	DECLARE_DYNAMIC(Finger)

public:
	Finger(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Finger();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FINGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
