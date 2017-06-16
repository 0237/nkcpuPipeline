
// nkcpuPipelineDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <fstream>
#include "afxwin.h"
#include <iostream>

using namespace std;

// 定义状态
#define BUSY 0
#define FREE 1
#define JUMP 2
#define LOAD 3
#define STORE 4
#define BACK 5
#define END 6

// 模拟各段的存储器
class ifData;
class idData;
class exData;
class memData;
//class wbData;

// CnkcpuPipelineDlg 对话框
class CnkcpuPipelineDlg : public CDialogEx
{
// 构造
public:
	CnkcpuPipelineDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NKCPUPIPELINE_DIALOG };
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

	BOOL CnkcpuPipelineDlg::PreTranslateMessage(MSG* pMsg)
	{
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
		if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) return TRUE;
		else
			return CDialog::PreTranslateMessage(pMsg);
	}
public:
	afx_msg void OnEnChangeEdit1();
	// 32个寄存器
	UINT m_Reg[32];
	// PC计数
	UINT m_PC;
	// 指令流水线
	CListCtrl m_pipeline;
	// 代码列表：地址、机器码、汇编码
	CListCtrl m_program;
	// 数据存储
	CListCtrl m_datamem;

	CString IF();
	CString ID();
	CString EX();
	CString MEM();
	CString WB() ;

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
//	afx_msg void OnNMClickList7(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList7(NMHDR *pNMHDR, LRESULT *pResult);
	// 隐藏的文本框
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit34();
	int m_Row;//获得选中的行  
	int m_Col;//获得选中的列
	int time;//时钟周期


	// 各种状态标记
	//int regState[32];//暂时用不到
	//int jmpState;
	int endState;
};
