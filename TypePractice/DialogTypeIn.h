#pragma once
#include "afxwin.h"
#include <atomic>

enum TypeKind {Eng, Zh_cn};

#define IDTIMER1	1
#define WAIT_TIME	30
#define TO_STRING(s) #s


// DialogTypeIn 对话框

class DialogTypeIn : public CDialog
{
	DECLARE_DYNAMIC(DialogTypeIn)

public:
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
	enum TypeKind tKind;
	CString szSource;

	// Edit框内容
	CEdit mEdit;
	
	// Button 内容
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

	// Static框内容
	CStatic mStatic;
	CStatic mSpeed;
	virtual void OnOK();

	// 线程回调函数
	static UINT AFX_CDECL HushUp(LPVOID lpParam);
	static UINT AFX_CDECL HandleWord(LPVOID lpParam);
	static UINT AFX_CDECL HandleTimer(LPVOID lpParam);
};


// 线程函数
//UINT AFX_CDECL HushUp(LPVOID lpParam);
//UINT AFX_CDECL HandleWord(LPVOID lpParam);
//UINT AFX_CDECL HandleTimer(LPVOID lpParam);
