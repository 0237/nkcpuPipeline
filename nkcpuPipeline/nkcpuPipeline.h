
// nkcpuPipeline.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CnkcpuPipelineApp: 
// �йش����ʵ�֣������ nkcpuPipeline.cpp
//

class CnkcpuPipelineApp : public CWinApp
{
public:
	CnkcpuPipelineApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CnkcpuPipelineApp theApp;