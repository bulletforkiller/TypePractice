// DialogTypeIn.cpp : 实现文件
//

#include "stdafx.h"
#include "TypePractice.h"
#include "DialogTypeIn.h"
#include "afxdialogex.h"


// DialogTypeIn 对话框

IMPLEMENT_DYNAMIC(DialogTypeIn, CDialog)

DialogTypeIn::DialogTypeIn(CWnd* pParent /*=NULL*/ , enum TypeKind kind)
	: CDialog(IDD_DIALOG_TYPE, pParent), tKind(kind)
	, szSource(_T(""))
{
	
}

DialogTypeIn::~DialogTypeIn()
{
	m_pParentWnd->ShowWindow(SW_NORMAL);
}

void DialogTypeIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FROM, szSource);
	DDX_Control(pDX, IDC_INPUT, mEdit);
	DDX_Control(pDX, IDC_BUTTON1, mButton);
}


BEGIN_MESSAGE_MAP(DialogTypeIn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogTypeIn::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_INPUT, &DialogTypeIn::OnEnChangeInput)
END_MESSAGE_MAP()


// DialogTypeIn 消息处理程序






VOID StartType(CWnd* pParent, enum TypeKind kind)
{
	int nLength = GetSystemMetrics(SM_CXSCREEN);
	int nWidth = GetSystemMetrics(SM_CYSCREEN);

	DialogTypeIn * dtWnd = new DialogTypeIn(pParent, kind);

	INT_PTR nResponse = dtWnd->DoModal();

	delete dtWnd;
}


void DialogTypeIn::OnBnClickedButton1()
{
	CTypePracticeApp* pApp;
	SIZE_T nStringNum;
	CWinThread* thread;

	pApp = (CTypePracticeApp*)AfxGetApp();
	nStringNum = pApp->Value[tKind].size();
	srand(_getpid());
	mStatic = pApp->Value[tKind][(int)(rand() % nStringNum)].asCString();
	szSource = mStatic;
	UpdateData(FALSE);
	
	mEdit.SetFocus();
	thread =  AfxBeginThread(HushUp, (LPVOID)this);
}

UINT AFX_CDECL HushUp(LPVOID lpParam)
{
	DialogTypeIn* dtWnd = (DialogTypeIn*)lpParam;
	TCHAR szBuffer[8] = { 0 };
	UINT uSecond = 60;
	SYSTEMTIME st;
	LARGE_INTEGER liUTC;
	FILETIME ftLocal, ftUTC;
	

	st.wYear = 2001;
	st.wMonth = 1;
	st.wDayOfWeek = 0;
	st.wDay = 1;
	st.wHour = 1;
	st.wMinute = 1;
	st.wSecond = 1;
	st.wMilliseconds = 0;

	SystemTimeToFileTime(&st, &ftLocal);
	LocalFileTimeToFileTime(&ftLocal, &ftUTC);
	liUTC.LowPart = ftUTC.dwLowDateTime;
	liUTC.HighPart = ftUTC.dwHighDateTime;

	HANDLE hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	if (!hTimer)
		return -1;

	if (!SetWaitableTimer(hTimer, &liUTC, 1000, NULL, NULL, NULL))
		return -1;

	dtWnd->mButton.EnableWindow(FALSE);
	dtWnd->mEdit.SetReadOnly(FALSE);

	while (uSecond) {
		WaitForSingleObject(hTimer, INFINITE);
		swprintf_s(szBuffer, TEXT("%u"), uSecond--);
		dtWnd->mButton.SetWindowTextW(szBuffer);
	}

	dtWnd->mButton.EnableWindow(TRUE);
	dtWnd->mButton.SetWindowText(TEXT("开始"));
	dtWnd->mEdit.SetWindowText(TEXT(""));
	dtWnd->mEdit.SetReadOnly(TRUE);
	

	CancelWaitableTimer(hTimer);
	CloseHandle(hTimer);

	return 0;
}


void DialogTypeIn::OnEnChangeInput()
{
	CWinThread* thread = AfxBeginThread(HandleWord, (LPVOID)this);
}

UINT AFX_CDECL HandleWord(LPVOID lpParam)
{
	int nLength;
	DialogTypeIn* dtWnd = (DialogTypeIn*)lpParam;
	CString mInput;

	dtWnd->mEdit.GetWindowText(mInput);

	if (dtWnd->szSource.Find(mInput) == 0) {
		dtWnd->mEdit.SetLimitText(0);
		return 0;
	}
	else {
		nLength = dtWnd->mEdit.GetWindowTextLengthW();
		for (int i = 0; i < nLength; i++) {
			if (dtWnd->szSource[i] != mInput[i])
				dtWnd->mEdit.SetLimitText(i + 1);
		}

		return -1;
	}
	
}
