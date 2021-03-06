
// TypePractice.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "json\json.h"		//通过jsoncpp实现对json的支持


// CTypePracticeApp:
// 有关此类的实现，请参阅 TypePractice.cpp
//

class CTypePracticeApp : public CWinApp
{
public:
	CTypePracticeApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()

public:
	Json::Value root;
};

extern CTypePracticeApp theApp;
