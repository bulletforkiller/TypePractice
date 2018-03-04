#pragma once
#include "afxwin.h"

enum TypeKind {Eng, Zh_cn};

#define IDTIMER1	1


// DialogTypeIn 对话框

class DialogTypeIn : public CDialog
{
	DECLARE_DYNAMIC(DialogTypeIn)

public:
	enum TypeKind tKind;
// 标准构造函数
	DialogTypeIn(CWnd* pParent = NULL, enum TypeKind kind = Eng);		// 标准构造函数
	virtual ~DialogTypeIn();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_TYPE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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

	// Static框内容
	CString mStatic;
};

// 一些额外的函数
VOID StartType(CWnd* pParent, enum TypeKind kind);

// 线程函数
UINT AFX_CDECL HushUp(LPVOID lpParam);
UINT AFX_CDECL HandleWord(LPVOID lpParam);
