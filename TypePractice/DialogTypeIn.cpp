// DialogTypeIn.cpp : 实现文件
//

#include "stdafx.h"
#include "TypePractice.h"
#include "DialogTypeIn.h"
#include "afxdialogex.h"


// DialogTypeIn 对话框

IMPLEMENT_DYNAMIC(DialogTypeIn, CDialog)

DialogTypeIn::DialogTypeIn(CWnd* pParent /*=NULL*/ , enum TypeKind kind)
	: CDialog(IDD_DIALOG_TYPE, pParent), tKind(kind), nSpeed(0), nTimer(0), bWrong(FALSE)
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
	DDX_Control(pDX, IDC_FROM, mStatic);
	DDX_Control(pDX, IDC_SPEED, mSpeed);
}


BEGIN_MESSAGE_MAP(DialogTypeIn, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &DialogTypeIn::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_INPUT, &DialogTypeIn::OnEnChangeInput)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// DialogTypeIn 消息处理程序


void DialogTypeIn::OnBnClickedButton1()
{
	CWinThread* thread;

	mEdit.SetFocus();
	thread =  AfxBeginThread(HushUp, (LPVOID)this);
}

void DialogTypeIn::OnEnChangeInput()
{
	CWinThread* thread = AfxBeginThread(HandleWord, (LPVOID)this);
}

void DialogTypeIn::OnTimer(UINT_PTR nIDEvent)
{
	CWinThread* thread = AfxBeginThread(HandleTimer, (LPVOID)this);
}

void DialogTypeIn::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

UINT AFX_CDECL DialogTypeIn::HushUp(LPVOID lpParam)
{
	CTypePracticeApp* pApp;
	SIZE_T nStringNum;
	DialogTypeIn* dtWnd;
	TCHAR szBuffer[4] = { 0 };

	pApp = (CTypePracticeApp*)AfxGetApp();
	dtWnd = (DialogTypeIn*)lpParam;

	// 清空之前的记录
	dtWnd->nSpeed = 0;

	nStringNum = pApp->root["Value"][dtWnd->tKind].size();
	srand((unsigned int)time(NULL));
	dtWnd->szSource = pApp->root["Value"][dtWnd->tKind][(int)(rand() % nStringNum)].asCString();
	dtWnd->mStatic.SetWindowText(dtWnd->szSource);
	
	dtWnd->SetTimer(IDTIMER1, 1000, NULL);
	dtWnd->nTimer = WAIT_TIME;
	swprintf_s(szBuffer, TEXT("%d"), WAIT_TIME);
	dtWnd->mButton.SetWindowText(szBuffer);
	
	dtWnd->mButton.EnableWindow(FALSE);
	dtWnd->mEdit.SetReadOnly(FALSE);
	dtWnd->nClock = GetTickCount();

	return 0;
}

UINT AFX_CDECL DialogTypeIn::HandleWord(LPVOID lpParam)
{
	int nLength;
	DialogTypeIn* dtWnd = (DialogTypeIn*)lpParam;
	CString mInput;
	DWORD nTimeStamp;

	dtWnd->mEdit.GetWindowText(mInput);
	nLength = mInput.GetLength();
	nTimeStamp = GetTickCount();

	if (dtWnd->szSource.Find(mInput) == 0) {
		dtWnd->mEdit.SetLimitText(0);
		dtWnd->nSpeed = (int)(nLength * 60 / ((nTimeStamp - dtWnd->nClock) / 1000.0));
		return 0;
	}
	else {
		for (int i = 0; i < nLength; i++) {
			if (dtWnd->szSource[i] != mInput[i]) {
				dtWnd->mEdit.SetLimitText(i + 1);
				dtWnd->nSpeed = (int)(i * 60 / ((nTimeStamp - dtWnd->nClock) / 1000.0));
				break;
			}
		}

		return -1;
	}
	
}

UINT AFX_CDECL DialogTypeIn::HandleTimer(LPVOID lpParam)
{
	DialogTypeIn* dtWnd = (DialogTypeIn*)lpParam;
	int nTimer;
	TCHAR szBuffer[16] = { 0 };
	SIZE_T nLength = 0;

	if (--dtWnd->nTimer) {
		nTimer = dtWnd->nTimer;
		swprintf_s(szBuffer, TEXT("%d"), nTimer);
		dtWnd->mButton.SetWindowTextW(szBuffer);
		swprintf_s(szBuffer, TEXT("%d"), dtWnd->nSpeed);
		dtWnd->mSpeed.SetWindowText(szBuffer);
	}
	else {
		dtWnd->KillTimer(IDTIMER1);
		dtWnd->mButton.SetWindowText(TEXT("开始"));
		dtWnd->mButton.EnableWindow(TRUE);
		dtWnd->mButton.SetFocus();

		nLength = dtWnd->mEdit.GetWindowTextLengthW();
		dtWnd->nSpeed = nLength * 60 / WAIT_TIME;

		dtWnd->mEdit.SetWindowText(TEXT(""));
		dtWnd->mEdit.SetReadOnly(TRUE);
		dtWnd->mStatic.SetWindowText(TEXT(""));
		dtWnd->mSpeed.SetWindowText(TEXT(""));
		
		swprintf_s(szBuffer, TEXT("%d"), dtWnd->nSpeed);
		dtWnd->MessageBox(szBuffer);
	}

	return 0;
}

