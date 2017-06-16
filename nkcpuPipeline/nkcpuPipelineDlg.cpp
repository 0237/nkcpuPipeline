
// nkcpuPipelineDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "nkcpuPipeline.h"
#include "nkcpuPipelineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CnkcpuPipelineDlg �Ի���



CnkcpuPipelineDlg::CnkcpuPipelineDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NKCPUPIPELINE_DIALOG, pParent)
	, m_PC(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CnkcpuPipelineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Reg[0]);
	DDX_Text(pDX, IDC_EDIT2, m_Reg[1]);
	DDX_Text(pDX, IDC_EDIT3, m_Reg[2]);
	DDX_Text(pDX, IDC_EDIT4, m_Reg[3]);
	DDX_Text(pDX, IDC_EDIT5, m_Reg[4]);
	DDX_Text(pDX, IDC_EDIT6, m_Reg[5]);
	DDX_Text(pDX, IDC_EDIT7, m_Reg[6]);
	DDX_Text(pDX, IDC_EDIT8, m_Reg[7]);
	DDX_Text(pDX, IDC_EDIT9, m_Reg[8]);
	DDX_Text(pDX, IDC_EDIT10, m_Reg[9]);
	DDX_Text(pDX, IDC_EDIT11, m_Reg[10]);
	DDX_Text(pDX, IDC_EDIT12, m_Reg[11]);
	DDX_Text(pDX, IDC_EDIT13, m_Reg[12]);
	DDX_Text(pDX, IDC_EDIT14, m_Reg[13]);
	DDX_Text(pDX, IDC_EDIT15, m_Reg[14]);
	DDX_Text(pDX, IDC_EDIT16, m_Reg[15]);
	DDX_Text(pDX, IDC_EDIT17, m_Reg[16]);
	DDX_Text(pDX, IDC_EDIT18, m_Reg[17]);
	DDX_Text(pDX, IDC_EDIT19, m_Reg[18]);
	DDX_Text(pDX, IDC_EDIT20, m_Reg[19]);
	DDX_Text(pDX, IDC_EDIT21, m_Reg[20]);
	DDX_Text(pDX, IDC_EDIT22, m_Reg[21]);
	DDX_Text(pDX, IDC_EDIT23, m_Reg[22]);
	DDX_Text(pDX, IDC_EDIT24, m_Reg[23]);
	DDX_Text(pDX, IDC_EDIT25, m_Reg[24]);
	DDX_Text(pDX, IDC_EDIT26, m_Reg[25]);
	DDX_Text(pDX, IDC_EDIT27, m_Reg[26]);
	DDX_Text(pDX, IDC_EDIT28, m_Reg[27]);
	DDX_Text(pDX, IDC_EDIT29, m_Reg[28]);
	DDX_Text(pDX, IDC_EDIT30, m_Reg[29]);
	DDX_Text(pDX, IDC_EDIT31, m_Reg[30]);
	DDX_Text(pDX, IDC_EDIT32, m_Reg[31]);
	DDX_Text(pDX, IDC_EDIT33, m_PC);
	DDX_Control(pDX, IDC_LIST5, m_pipeline);
	DDX_Control(pDX, IDC_LIST6, m_program);
	DDX_Control(pDX, IDC_LIST7, m_datamem);
	DDX_Control(pDX, IDC_EDIT34, m_edit);
}

BEGIN_MESSAGE_MAP(CnkcpuPipelineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CnkcpuPipelineDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CnkcpuPipelineDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CnkcpuPipelineDlg::OnBnClickedButton1)
//	ON_NOTIFY(NM_CLICK, IDC_LIST7, &CnkcpuPipelineDlg::OnNMClickList7)
ON_NOTIFY(NM_DBLCLK, IDC_LIST7, &CnkcpuPipelineDlg::OnNMDblclkList7)
ON_EN_KILLFOCUS(IDC_EDIT34, &CnkcpuPipelineDlg::OnEnKillfocusEdit34)
END_MESSAGE_MAP()


// CnkcpuPipelineDlg ��Ϣ�������

BOOL CnkcpuPipelineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	// ��ʾ�����д���
	//FILE *stream;
	//AllocConsole();
	//freopen_s(&stream, "CON", "r", stdin);
	//freopen_s(&stream, "CON", "w", stdout);
	//freopen_s(&stream, "CON", "w", stderr);

	CRect piprect,prorect,dmrect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_pipeline.GetClientRect(&piprect);
	m_program.GetClientRect(&prorect);
	m_datamem.GetClientRect(&dmrect);

	// Ϊ�б���ͼ�ؼ����ȫ��ѡ�к�դ����   
	m_pipeline.SetExtendedStyle(m_pipeline.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_program.SetExtendedStyle(m_program.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_datamem.SetExtendedStyle(m_datamem.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// Ϊ�б���ͼ�ؼ������   
	m_pipeline.InsertColumn(0, _T("ʱ��"), LVCFMT_CENTER, 60, 0);
	m_pipeline.InsertColumn(1, _T("IF"), LVCFMT_CENTER, (piprect.Width()-85) / 5, 1);
	m_pipeline.InsertColumn(2, _T("ID"), LVCFMT_CENTER, (piprect.Width() - 85) / 5, 2);
	m_pipeline.InsertColumn(3, _T("EX"), LVCFMT_CENTER, (piprect.Width() - 85) / 5, 3);
	m_pipeline.InsertColumn(4, _T("MEM"), LVCFMT_CENTER, (piprect.Width() - 85) / 5, 4);
	m_pipeline.InsertColumn(5, _T("WB"), LVCFMT_CENTER, (piprect.Width() - 85) / 5, 5);

	m_program.InsertColumn(0, _T("��ַ"), LVCFMT_CENTER, 50, 0);
	m_program.InsertColumn(1, _T("32 λ������"), LVCFMT_CENTER, 350, 1);
	m_program.InsertColumn(2, _T("�����"), LVCFMT_LEFT, prorect.Width() - 400, 2);

	m_datamem.InsertColumn(0, _T("��ַ"), LVCFMT_CENTER, 50, 0);
	m_datamem.InsertColumn(1, _T("16 λ��������"), LVCFMT_CENTER, 200, 1);
	m_datamem.InsertColumn(2, _T("ʮ������"), LVCFMT_LEFT, dmrect.Width() - 250, 2);

	ifstream fin;
	fin.open("sort1.asm", ios_base::in);
	if (!fin) {
		MessageBox(_T("������������"), _T("����"), MB_ICONERROR);
	}
	ifstream imin;
	imin.open("mcode1.txt", ios_base::in);
	if (!imin) {
		MessageBox(_T("����ָ��洢����"), _T("����"), MB_ICONERROR);
	}
	ifstream dmin;
	dmin.open("mdata.txt", ios_base::in);
	if (!dmin) {
		MessageBox(_T("�������ݴ洢����"), _T("����"), MB_ICONERROR);
	}
	char buffer[256];
	char imbuff[256];
	char dmbuff[256];
	char* tokenPtr;
	char* pNext;
	int add = 0;
	int seg = 0;
	//��������������Ӧ�Ļ���������ݴ洢
	while (!fin.eof()) {
		fin.getline(buffer, 256);
		if (buffer[0] != 0) {
			tokenPtr = strtok_s(buffer, "#", &pNext);
			if (tokenPtr[0] != 0) {
				char* pchd = strstr(tokenPtr, ".data");
				char* pcht = strstr(tokenPtr, ".text");
				if (pchd != NULL) {
					seg = 1;
					add = 0;
					continue;
				}
				if (pcht != NULL) {
					seg = 2;
					add = 0;
					continue;
				}
				if (seg == 1) {
					pchd = strstr(tokenPtr, ":");
					if (pchd != NULL) {
						tokenPtr = strtok_s(tokenPtr, ":", &pNext);
						CString str1;
						str1.Format(_T("%d"), add*2);//��ַ
						m_datamem.InsertItem(add, (LPCTSTR)str1);
						tokenPtr = strtok_s(NULL, " .word,", &pNext);
						while (tokenPtr != NULL) {
							dmin.getline(dmbuff, 256);
							CString str2(dmbuff);
							m_datamem.SetItemText(add, 1, (LPCTSTR)str2);
							CString str3(tokenPtr);
							m_datamem.SetItemText(add, 2, (LPCTSTR)str3);
							add++;//�к�
							CString str1;
							str1.Format(_T("%d"), add*2);
							m_datamem.InsertItem(add, (LPCTSTR)str1);
							tokenPtr = strtok_s(NULL, " .word,", &pNext);
						}
						CString str2("00000000 00000000");
						m_datamem.SetItemText(add, 1, (LPCTSTR)str2);
						CString str3("0");
						m_datamem.SetItemText(add, 2, (LPCTSTR)str3);
					}
				}
				else if (seg == 2) {
					CString str1;
					str1.Format(_T("%d"), add * 4);//��ַ
					m_program.InsertItem(add, (LPCTSTR)str1);
					imin.getline(imbuff, 256);
					CString str2(imbuff);
					m_program.SetItemText(add, 1, (LPCTSTR)str2);
					CString str3(tokenPtr);
					m_program.SetItemText(add, 2, (LPCTSTR)str3);
					add++;//�к�
				}
			}
		}
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CnkcpuPipelineDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CnkcpuPipelineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CnkcpuPipelineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CnkcpuPipelineDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

// �ַ���ת������
CString num2bin(int num) {
	char* bin = new char[17];
	for (int i = 15, j = 0; i >= 0; i--)
	{
		if (i == 7) { j = 1;bin[8] = ' '; }
		if (num & (1 << i))
			bin[15 - i + j] = '1';
		else
			bin[15 - i + j] = '0';
	}
	bin[17] = '\0';
	CString a(bin);
	return a;
}

int bin2num(CString bin) {
	char *e;
	char szStr[256] = { 0 };
	size_t s;
	wcstombs_s(&s, szStr, (size_t)256, bin, (size_t)256);
	const char * p = szStr;
	int i = strtol(p, &e, 2);
	return i;
}

// ģ�����֮���������
// IF/ID
class ifData {
public:
	CString PC;
	CString IR;
	ifData& operator=(ifData x) {
		this->PC = x.PC;
		this->IR = x.IR;
		return *this;
	}
};
ifData ifbefore, ifafter;

// ID/EX
class idData {
public:
	CString PC;
	CString IR;
	int A;
	int B;
	int C;
	int Imm;
	idData& operator=(idData x) {
		this->PC = x.PC;
		this->IR = x.IR;
		this->A = x.A;
		this->B = x.B;
		this->C = x.C;
		this->Imm = x.Imm;
		return *this;
	}
};
idData idbefore, idafter;

// EX/MEM
class exData {
public:
	CString PC;
	CString IR;
	int C;
	int Imm;
	int ALUOutput;
	exData& operator=(exData x) {
		this->PC = x.PC;
		this->IR = x.IR;
		this->ALUOutput = x.ALUOutput;
		this->C = x.C;
		this->Imm = x.Imm;
		return *this;
	}
};
exData exbefore, exafter;

// MEM/WB
class memData {
public:
	CString PC;
	CString IR;
	int Imm;
	int LMD;
	int ALUOutput;
	memData& operator=(memData x) {
		this->PC = x.PC;
		this->IR = x.IR;
		this->ALUOutput = x.ALUOutput;
		this->LMD = x.LMD;
		this->Imm = x.Imm;
		return *this;
	}
};
memData membefore, memafter;

//class wbData {
//public:
//	int PC;
//	int state;
//	wbData& operator=(wbData x) {
//		this->PC = x.PC;
//		this->state = x.state;
//		return *this;
//	}
//};

// ģ�� IF ID EX MEM WB ����ԭ��
CString CnkcpuPipelineDlg::IF() {
	if (ifbefore.IR == "11111111111111111111111111111111") {
		ifafter.IR = ifbefore.IR;
		return _T("NOP");
	}
	else {
		UpdateData(TRUE);
		CString strPC;
		strPC.Format(_T("%d"), m_PC);
		ifafter.PC = strPC;
		m_program.EnsureVisible(m_PC / 4, FALSE);// ������ѡ����
		m_program.SetItemState(m_PC / 4, LVIS_SELECTED, LVIS_SELECTED);// ����ѡ���У���ʵδ�۽�ʱΪ��ɫ
		CString code = m_program.GetItemText(m_PC / 4, 1);
		ifafter.IR = code.Left(8) + code.Mid(9, 8) + code.Mid(18, 8) + code.Right(8);

		if ((idbefore.IR.Left(6) == "100011"
			&& ifbefore.IR.Left(6) == "101011"
			&& (idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(6, 5) || idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(11, 5) || idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(16, 5))) ||
			(idbefore.IR.Left(6) == "100011"
				&& (ifbefore.IR.Left(6) == "000000" || ifbefore.IR.Left(6) == "100011")//|| ifbefore.IR.Left(6) == "101011"
				&& (idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(6, 5) || idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(11, 5))) ||// || idafter.IR.Mid(16, 5) == ifbefore.IR.Mid(16, 5)
				(idbefore.IR.Left(6) == "100011"
					&& (ifbefore.IR.Left(6) == "001000" || ifbefore.IR.Left(6) == "000110")
					&& idbefore.IR.Mid(16, 5) == ifbefore.IR.Mid(6, 5))) {
			//MessageBox(_T("��"), _T("����"), MB_ICONINFORMATION);
			ifafter = ifbefore;
			idafter.IR = _T("000000") + idafter.IR.Mid(6, 20) + _T("000000");
		}
		else if (ifbefore.IR.Left(6) == "000010" || (ifbefore.IR.Left(6) == "000110"&&idafter.A <= 0)) {
			m_PC = idafter.Imm;
			ifafter.IR = _T("000000") + ifafter.IR.Mid(6, 20) + _T("000000");
		}
		else {
			m_PC += 4;
		}
		UpdateData(FALSE);
		return strPC;
	}
}

CString CnkcpuPipelineDlg::ID() {
	if (time < 1)return _T("");
	else if (ifbefore.IR.Left(6) == "000000"&&ifbefore.IR.Right(6) == "000000"|| ifbefore.IR == "11111111111111111111111111111111") {
		idafter.IR = ifbefore.IR;
		return _T("NOP");
	}
	else {
		idafter.PC = ifbefore.PC;
		idafter.IR = ifbefore.IR;
		idafter.A = m_Reg[bin2num(ifbefore.IR.Mid(6, 5))];
		idafter.B = m_Reg[bin2num(ifbefore.IR.Mid(11, 5))];
		idafter.C = m_Reg[bin2num(ifbefore.IR.Mid(16, 5))];
		idafter.Imm = bin2num(ifbefore.IR.Right(16));
		if ((memafter.IR.Left(6) == "000000"|| memafter.IR.Left(6) == "100011")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (memafter.IR.Mid(16, 5) == idafter.IR.Mid(6, 5))) {
			if (memafter.IR.Left(6) == "000000")idafter.A = memafter.ALUOutput;
			if (memafter.IR.Left(6) == "100011")idafter.A = memafter.LMD;
		}
		if ((memafter.IR.Left(6) == "000000" || memafter.IR.Left(6) == "100011")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(16, 5) == idafter.IR.Mid(11, 5))) {
			if (memafter.IR.Left(6) == "000000")idafter.B = memafter.ALUOutput;
			if (memafter.IR.Left(6) == "100011")idafter.B = memafter.LMD;
		}
		if ((memafter.IR.Left(6) == "000000" || memafter.IR.Left(6) == "100011")
			&& (idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(16, 5) == idafter.IR.Mid(16, 5))) {
			if (memafter.IR.Left(6) == "000000")idafter.C = memafter.ALUOutput;
			if (memafter.IR.Left(6) == "100011")idafter.C = memafter.LMD;
		}

		if ((memafter.IR.Left(6) == "001000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (memafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
			idafter.A = memafter.ALUOutput;
		}
		if ((memafter.IR.Left(6) == "001000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
			idafter.B = memafter.ALUOutput;
		}
		if ((memafter.IR.Left(6) == "001000")
			&& (idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
			idafter.C = memafter.ALUOutput;
		}

		if ((memafter.IR.Left(6) == "001111" || memafter.IR.Left(6) == "100000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (memafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
			idafter.A = memafter.Imm;
		}
		if ((memafter.IR.Left(6) == "001111" || memafter.IR.Left(6) == "100000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
			idafter.B = memafter.Imm;
		}
		if ((memafter.IR.Left(6) == "001111" || memafter.IR.Left(6) == "100000")
			&& (idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
			idafter.C = memafter.Imm;
		}

		/*if (memafter.IR.Left(6) == "100011"
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (memafter.IR.Mid(16, 5) == idafter.IR.Mid(6, 5))) {
			idafter.A = memafter.ALUOutput;
		}
		if (memafter.IR.Left(6) == "100011"
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(16, 5) == idafter.IR.Mid(11, 5))) {
			idafter.B = memafter.ALUOutput;
		}
		if (memafter.IR.Left(6) == "100011"
			&& (idafter.IR.Left(6) == "101011")
			&& (memafter.IR.Mid(16, 5) == idafter.IR.Mid(16, 5))) {
			idafter.C = memafter.C;
		}*/

		if (exafter.IR.Left(6) == "000000"
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (exafter.IR.Mid(16, 5) == idafter.IR.Mid(6, 5))) {
			idafter.A = exafter.ALUOutput;
		}
		if (exafter.IR.Left(6) == "000000"
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (exafter.IR.Mid(16, 5) == idafter.IR.Mid(11, 5))) {
			idafter.B = exafter.ALUOutput;
		}
		if (exafter.IR.Left(6) == "000000"
			&& (idafter.IR.Left(6) == "101011")
			&& (exafter.IR.Mid(16, 5) == idafter.IR.Mid(16, 5))) {
			idafter.C = exafter.ALUOutput;
		}

		if ((exafter.IR.Left(6) == "001000")////////////////////////
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (exafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
			idafter.A = exafter.ALUOutput;
		}
		if ((exafter.IR.Left(6) == "001000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (exafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
			idafter.B = exafter.ALUOutput;
		}
		if ((exafter.IR.Left(6) == "001000")
			&& (idafter.IR.Left(6) == "101011")
			&& (exafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
			idafter.C = exafter.ALUOutput;
		}

		if ((exafter.IR.Left(6) == "001111" || exafter.IR.Left(6) == "100000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011" || idafter.IR.Left(6) == "001000" || idafter.IR.Left(6) == "000110")
			&& (exafter.IR.Mid(11, 5) == idafter.IR.Mid(6, 5))) {
			idafter.A = exafter.Imm;
		}
		if ((exafter.IR.Left(6) == "001111" || exafter.IR.Left(6) == "100000")
			&& (idafter.IR.Left(6) == "000000" || idafter.IR.Left(6) == "100011" || idafter.IR.Left(6) == "101011")
			&& (exafter.IR.Mid(11, 5) == idafter.IR.Mid(11, 5))) {
			idafter.B = exafter.Imm;
		}
		if ((exafter.IR.Left(6) == "001111" || exafter.IR.Left(6) == "100000")
			&& (idafter.IR.Left(6) == "101011")
			&& (exafter.IR.Mid(11, 5) == idafter.IR.Mid(16, 5))) {
			idafter.C = exafter.Imm;
		}

		return ifbefore.PC;
	}
}

CString CnkcpuPipelineDlg::EX() {
	if (time < 2)return _T("");
	else if (idbefore.IR.Left(6) == "000000"&&idbefore.IR.Right(6) == "000000"|| idbefore.IR == "11111111111111111111111111111111") {
		exafter.IR = idbefore.IR;
		return _T("NOP");
	}
	else {
		exafter.PC = idbefore.PC;
		exafter.IR = idbefore.IR;
		exafter.C = idbefore.C;
		exafter.Imm = idbefore.Imm;
		if ((idbefore.IR.Left(6) == "000000"&&idbefore.IR.Right(6) == "100000") ||
			idbefore.IR.Left(6) == "100011" ||
			idbefore.IR.Left(6) == "101011") {
			exafter.ALUOutput = idbefore.A + idbefore.B;
		}
		else if (idbefore.IR.Left(6) == "000000"&&idbefore.IR.Right(6) == "101010") {
			exafter.ALUOutput = idbefore.A < idbefore.B ? 1 : 0;
		}
		else if (idbefore.IR.Left(6) == "001000") {
			exafter.ALUOutput = idbefore.A + idbefore.Imm;
		}			
		return idbefore.PC;
	}
}

CString CnkcpuPipelineDlg::MEM() {
	if (time < 3)return _T("");
	else if (exbefore.IR.Left(6) == "000000"&&exbefore.IR.Right(6) == "000000"|| exbefore.IR == "11111111111111111111111111111111") {
		memafter.IR = exbefore.IR;
		return _T("NOP");
	}
	else {
		memafter.PC = exbefore.PC;
		memafter.IR = exbefore.IR;
		memafter.ALUOutput = exbefore.ALUOutput;
		memafter.Imm = exbefore.Imm;
		if (exbefore.IR.Left(6) == "100011") {
			m_datamem.EnsureVisible(exbefore.ALUOutput, FALSE);// ������ѡ����
			m_datamem.SetItemState(exbefore.ALUOutput, LVIS_SELECTED, LVIS_SELECTED);// ����ѡ���У���ʵδ�۽�ʱΪ��ɫ
			CString numb = m_datamem.GetItemText(exbefore.ALUOutput, 2);
			memafter.LMD = _ttoi(numb);
		}
		else if (exbefore.IR.Left(6) == "101011") {
			CString n;
			n.Format(_T("%d"), exbefore.C);
			m_datamem.EnsureVisible(exbefore.ALUOutput, FALSE);// ������ѡ����
			m_datamem.SetItemState(exbefore.ALUOutput, LVIS_SELECTED, LVIS_SELECTED);// ����ѡ���У���ʵδ�۽�ʱΪ��ɫ
			m_datamem.SetItemText(exbefore.ALUOutput, 1, num2bin(exbefore.C));
			m_datamem.SetItemText(exbefore.ALUOutput, 2, n);
		}
		return exbefore.PC;
	}
}

CString CnkcpuPipelineDlg::WB() {
	if (time < 4)return _T("");
	else if (membefore.IR == "11111111111111111111111111111111") { 
		endState = END;
		return _T("NOP");
	}
	else if (membefore.IR.Left(6) == "000000"&&membefore.IR.Right(6) == "000000") {
		return _T("NOP");
	}
	else {
		if (membefore.IR.Left(6) == "000000") {
			m_Reg[bin2num(membefore.IR.Mid(16, 5))] = membefore.ALUOutput;
		}
		else if (membefore.IR.Left(6) == "001000") {
			int a = bin2num(membefore.IR.Mid(11, 5));
			m_Reg[a] = membefore.ALUOutput;
		}
		else if (membefore.IR.Left(6) == "100011") {
			m_Reg[bin2num(membefore.IR.Mid(16, 5))] = membefore.LMD;
		}
		else if (membefore.IR.Left(6) == "001111" || membefore.IR.Left(6) == "100000") {
			m_Reg[bin2num(membefore.IR.Mid(11, 5))] = membefore.Imm;
		}
		UpdateData(FALSE);
		return membefore.PC;
	}
}

// ʹ�ð�ť����ʱ�����ڣ���һ����һ��ʱ������
void CnkcpuPipelineDlg::OnBnClickedButton2()
{
	// TODO: 
	/*MessageBox(_T("�����Զ�����ʾ��Ϣ"), _T("���Ǳ���"), MB_ICONERROR);
	m_PC += 4;
	m_Reg[10] = m_Reg[1]+1;
	UpdateData(FALSE);*/

	if (endState != END) {
		CString t;
		t.Format(_T("%d"), time);
		m_pipeline.InsertItem(0, _T("t") + t);
		m_pipeline.SetItemText(0, 5, WB());//ͬһ��ʱ�����ڣ��Ĵ�����д���
		m_pipeline.SetItemText(0, 4, MEM());//����lwָ���д���
		m_pipeline.SetItemText(0, 3, EX());
		m_pipeline.SetItemText(0, 2, ID());//����ð�ս������ID/EX
		m_pipeline.SetItemText(0, 1, IF());
		//m_pipeline.SetItemText(0, 2, ID());
		//m_pipeline.SetItemText(0, 3, EX());
		//m_pipeline.SetItemText(0, 4, MEM());
		//m_pipeline.SetItemText(0, 5, WB());
		m_pipeline.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);// ����ѡ���У���ʵδ�۽�ʱΪ��ɫ

		ifbefore = ifafter;
		idbefore = idafter;
		exbefore = exafter;
		membefore = memafter;
		time++;
	}
	else {
		MessageBox(_T("����ִ����ϣ�"), _T("��ʾ"), MB_ICONINFORMATION);
	}
}

void CnkcpuPipelineDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//m_datamem.SetItemText(10, 1, _T("hello"));
	//m_datamem.SetItemText(10, 2, _T("world"));
	//CString a = m_program.GetItemText(2, 1);
	//if(a.Left(6)=="100011")MessageBox(_T("��Ҫ�㣡"), _T("��ʾ"), MB_ICONINFORMATION);
	//else MessageBox(_T("��"), _T("����"), MB_ICONINFORMATION);
	//cout << "hello world!" << endl;;
	//CString a = m_datamem.GetItemText(0, 1);
	////m_datamem.SetItemText(19, 2, a.Left(8)+a.Right(8));
	//m_PC = bin2num(a.Left(8) + a.Right(8));
	////m_program.EnsureVisible(20, FALSE);// ������ѡ����
	////m_program.SetItemState(20, LVIS_SELECTED, LVIS_SELECTED);// ����ѡ���У���ʵδ�۽�ʱΪ��ɫ
	////m_datamem.SetItemState(8, LVIS_SELECTED, LVIS_SELECTED);
	////m_program.SetItemState(8, LVIS_SELECTED, LVIS_SELECTED);
	////m_program.SetFocus();
	////m_PC += 4;
	//m_Reg[1] = 1;
	//UpdateData(FALSE);

	while (endState != END) {
		OnBnClickedButton2();
		//Sleep(6000);
	}
	MessageBox(_T("����ִ����ϣ�"), _T("��ʾ"), MB_ICONINFORMATION);
}


// ������ʵ��listCtrl�Ŀɱ༭
void CnkcpuPipelineDlg::OnNMDblclkList7(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//���ѡ�е���  
	//m_Col = pNMListView->iSubItem;//���ѡ����  
	m_Col = 2;//����ǿ��ָ��Ϊ������

	if (pNMListView->iSubItem != 0) //���ѡ���������;  
	{
		m_datamem.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//��������RECT��  
		m_edit.SetParent(&m_datamem);//ת������Ϊ�б���е�����  
		m_edit.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;  
		m_edit.SetWindowText(m_datamem.GetItemText(m_Row, m_Col));//���������е�ֵ����Edit�ؼ��У�  
		m_edit.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���  
		m_edit.SetFocus();//����Edit����  
		m_edit.ShowCaret();//��ʾ���  
		m_edit.SetSel(-1);//������ƶ������  
	}

	*pResult = 0;
}


void CnkcpuPipelineDlg::OnEnKillfocusEdit34()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString tem;
	m_edit.GetWindowText(tem);    //�õ��û�������µ�����  
	m_datamem.SetItemText(m_Row, m_Col, tem);   //���ñ༭���������
	m_datamem.SetItemText(m_Row, m_Col-1, num2bin(_ttoi(tem)));   //���ñ༭��������ݶ�Ӧ�Ķ�����
	m_edit.ShowWindow(SW_HIDE);                //Ӧ�ر༭��  
}
