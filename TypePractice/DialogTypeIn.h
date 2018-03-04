#pragma once
#include "afxwin.h"

enum TypeKind {Eng, Zh_cn};

#define IDTIMER1	1


// DialogTypeIn �Ի���

class DialogTypeIn : public CDialog
{
	DECLARE_DYNAMIC(DialogTypeIn)

public:
	enum TypeKind tKind;
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
	CString szSource;
	CEdit mEdit;
	afx_msg void OnBnClickedButton1();
	CButton mButton;

private:
	bool bWrong;
public:
	afx_msg void OnEnChangeInput();

	// Static������
	CString mStatic;
};

// һЩ����ĺ���
VOID StartType(CWnd* pParent, enum TypeKind kind);

// �̺߳���
UINT AFX_CDECL HushUp(LPVOID lpParam);
UINT AFX_CDECL HandleWord(LPVOID lpParam);
