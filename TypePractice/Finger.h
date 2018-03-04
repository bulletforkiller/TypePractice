#pragma once


// Finger 对话框

class Finger : public CDialog
{
	DECLARE_DYNAMIC(Finger)

public:
	Finger(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Finger();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_FINGER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
