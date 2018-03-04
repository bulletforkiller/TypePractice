#pragma once
#include "afxwin.h"
#include <atomic>

enum TypeKind {Eng, Zh_cn};

#define IDTIMER1	1
#define WAIT_TIME	30
#define TO_STRING(s) #s


// DialogTypeIn �Ի���

class DialogTypeIn : public CDialog
{
	DECLARE_DYNAMIC(DialogTypeIn)

public:
// ��׼���캯��
	DialogTypeIn(CWnd* pParent = NULL, enum TypeKind kind = Eng);		// ��׼���캯��
	virtual ~DialogTypeIn();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TYPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	enum TypeKind tKind;
	CString szSource;

	// Edit������
	CEdit mEdit;
	
	// Button ����
	CButton mButton;

public:
	bool bWrong;
	std::atomic<int> nTimer;
	int nSpeed;
	DWORD nClock;

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeInput();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// Static������
	CStatic mStatic;
	CStatic mSpeed;
	virtual void OnOK();

	// �̻߳ص�����
	static UINT AFX_CDECL HushUp(LPVOID lpParam);
	static UINT AFX_CDECL HandleWord(LPVOID lpParam);
	static UINT AFX_CDECL HandleTimer(LPVOID lpParam);
};


// �̺߳���
//UINT AFX_CDECL HushUp(LPVOID lpParam);
//UINT AFX_CDECL HandleWord(LPVOID lpParam);
//UINT AFX_CDECL HandleTimer(LPVOID lpParam);
