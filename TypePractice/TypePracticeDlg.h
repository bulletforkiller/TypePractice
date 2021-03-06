
// TypePracticeDlg.h: 头文件
//

#pragma once


// CTypePracticeDlg 对话框
class CTypePracticeDlg : public CDialog
{
// 构造
public:
	CTypePracticeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TYPEPRACTICE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonEng();
	afx_msg void OnBnClickedButtonCn();

	// 一些额外的函数
	void StartUp(CWnd* pParent, enum TypeKind kind);

	// Disable Enter to quit
	virtual void OnOK();
};
