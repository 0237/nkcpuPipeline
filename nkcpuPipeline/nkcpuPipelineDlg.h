
// nkcpuPipelineDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <fstream>
#include "afxwin.h"
#include <iostream>

using namespace std;

// ����״̬
#define BUSY 0
#define FREE 1
#define JUMP 2
#define LOAD 3
#define STORE 4
#define BACK 5
#define END 6

// ģ����εĴ洢��
class ifData;
class idData;
class exData;
class memData;
//class wbData;

// CnkcpuPipelineDlg �Ի���
class CnkcpuPipelineDlg : public CDialogEx
{
// ����
public:
	CnkcpuPipelineDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NKCPUPIPELINE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	// 32���Ĵ���
	UINT m_Reg[32];
	// PC����
	UINT m_PC;
	// ָ����ˮ��
	CListCtrl m_pipeline;
	// �����б���ַ�������롢�����
	CListCtrl m_program;
	// ���ݴ洢
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
	// ���ص��ı���
	CEdit m_edit;
	afx_msg void OnEnKillfocusEdit34();
	int m_Row;//���ѡ�е���  
	int m_Col;//���ѡ�е���
	int time;//ʱ������


	// ����״̬���
	//int regState[32];//��ʱ�ò���
	//int jmpState;
	int endState;
};
