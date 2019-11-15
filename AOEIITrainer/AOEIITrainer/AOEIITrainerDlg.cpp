
// AOEIITrainerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AOEIITrainer.h"
#include "AOEIITrainerDlg.h"
#include "afxdialogex.h"
#include "MemoryOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CAOEIITrainerDlg 对话框

CAOEIITrainerDlg::CAOEIITrainerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AOEIITRAINER_DIALOG, pParent)
	, unitHp(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAOEIITrainerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_UnitHp, unitHp);
}

void __stdcall CAOEIITrainerDlg::createUnit(LPVOID unitIdAddr)
{
	int* pUnitId = (int*)unitIdAddr;
	int unitId = *pUnitId;
	__asm
	{
		pushad
		mov ecx, dword ptr ds : [0x7912A0]
		mov ecx, dword ptr ds : [ecx + 0x424]
		mov ecx, dword ptr ds : [ecx + 0x4C]
		mov ecx, dword ptr ds : [ecx + 0x4]
		mov edx, unitId
		push 1
		push 0
		mov eax, dword ptr ds : [ecx]
		push dword ptr ds : [ecx + 0x178]
		push dword ptr ds : [ecx + 0x174]
		push edx
		call dword ptr ds : [eax + 0xAC]
		popad
	}
}

void CAOEIITrainerDlg::modifyResource()
{
	try
	{
		int resoOffset[] = { RESO_OFFSET1, RESO_OFFSET2, RESO_OFFSET3, RESO_OFFSET4 };
		MemoryOpt memOpt;
		memOpt.initPara(RESO_BASE, resoOffset, sizeof(resoOffset) / sizeof(int));

		float reso = 9999;
		resoOffset[0] = FOOD_OFFSET;
		memOpt.writeOffsetMemory(resoOffset, 1, &reso, sizeof(reso));

		resoOffset[0] = WOOD_OFFSET;
		memOpt.writeOffsetMemory(resoOffset, 1, &reso, sizeof(reso));

		resoOffset[0] = STONE_OFFSET;
		memOpt.writeOffsetMemory(resoOffset, 1, &reso, sizeof(reso));

		resoOffset[0] = GOOD_OFFSET;
		memOpt.writeOffsetMemory(resoOffset, 1, &reso, sizeof(reso));
	}
	catch (const std::exception & e)
	{
		CString error;
		error = e.what();
		MessageBox(error);
	}
}

void CAOEIITrainerDlg::modifyPopulation()
{
	try
	{
		int resoOffset[] = { RESO_OFFSET1, RESO_OFFSET2, RESO_OFFSET3, RESO_OFFSET4 };
		MemoryOpt memOpt;
		memOpt.initPara(RESO_BASE, resoOffset, sizeof(resoOffset) / sizeof(int));

		float popu = 0;
		resoOffset[0] = POPULATION_OFFSET;
		memOpt.writeOffsetMemory(resoOffset, 1, &popu, sizeof(popu));
	}
	catch (const std::exception & e)
	{
		CString error;
		error = e.what();
		MessageBox(error);
	}
}

BEGIN_MESSAGE_MAP(CAOEIITrainerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
	ON_BN_CLICKED(IDC_BTN_ModifyHp, &CAOEIITrainerDlg::OnBnClickedModifyHp)
END_MESSAGE_MAP()


// CAOEIITrainerDlg 消息处理程序

BOOL CAOEIITrainerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	RegisterHotKey(GetSafeHwnd(), WM_HOTKEY, NULL, VK_NUMPAD1);
	RegisterHotKey(GetSafeHwnd(), WM_HOTKEY, NULL, VK_NUMPAD2);
	RegisterHotKey(GetSafeHwnd(), WM_HOTKEY, NULL, VK_NUMPAD3);
	RegisterHotKey(GetSafeHwnd(), WM_HOTKEY, NULL, VK_NUMPAD4);
	RegisterHotKey(GetSafeHwnd(), WM_HOTKEY, NULL, VK_NUMPAD5);
	RegisterHotKey(GetSafeHwnd(), WM_HOTKEY, NULL, VK_NUMPAD6);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAOEIITrainerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAOEIITrainerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAOEIITrainerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

__declspec(naked) void testCall()
{
	__asm
	{
		pushad
		mov ecx, dword ptr ds : [0x7912A0]
		mov ecx, dword ptr ds : [ecx + 0x424]
		mov ecx, dword ptr ds : [ecx + 0x4C]
		mov ecx, dword ptr ds : [ecx + 0x4]
		mov edx, dword ptr ds : [PARAM_ADDR]
		push 1
		push 0
		mov eax, dword ptr ds : [ecx]
		push dword ptr ds : [ecx + 0x178]
		push dword ptr ds : [ecx + 0x174]
		push edx
		call dword ptr ds : [eax + 0xAC]
		popad
		ret
	}
}

void CAOEIITrainerDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	CDialogEx::OnHotKey(nHotKeyId, nKey1, nKey2);

	try
	{
		MemoryOpt memOpt;
		memOpt.initPara(PARAM_ADDR, NULL, 0);
		int unitId;
		switch (nKey2)
		{
		case VK_NUMPAD1:
			unitId = HEROC;
			memOpt.writeMemory(&unitId, sizeof(unitId));
			memOpt.runRemoteThread(testCall, NULL, 0);
			break;
		case VK_NUMPAD2:
			unitId = UTKNI;
			memOpt.writeMemory(&unitId, sizeof(unitId));
			memOpt.runRemoteThread(testCall, NULL, 0);
			break;
		case VK_NUMPAD3:
			unitId = UMOSU;
			memOpt.writeMemory(&unitId, sizeof(unitId));
			memOpt.runRemoteThread(testCall, NULL, 0);
			break;
		case VK_NUMPAD4:
			unitId = ULGBW;
			memOpt.writeMemory(&unitId, sizeof(unitId));
			memOpt.runRemoteThread(testCall, NULL, 0);
			//memOpt.runRemoteThread(createUnit, &unitId, sizeof(unitId));
			break;
		case VK_NUMPAD5:
			modifyResource();
			break;
		case VK_NUMPAD6:
			modifyPopulation();
			break;
		}
	}
	catch (const std::exception & e)
	{
		CString error;
		error = e.what();
		MessageBox(error);
	}

}

void CAOEIITrainerDlg::OnBnClickedModifyHp()
{
	UpdateData(TRUE);

	try
	{
		int unitOffset[] = { UNIT_OFFSET1 };
		MemoryOpt memOpt;
		memOpt.initPara(UNIT_BASE, unitOffset, sizeof(unitOffset) / sizeof(int));

		unitOffset[0] = HP_OFFSET;
		memOpt.writeOffsetMemory(unitOffset, 1, &unitHp, sizeof(unitHp));
	}
	catch (const std::exception & e)
	{
		CString error;
		error = e.what();
		MessageBox(error);
	}
}

//void CAOEIITrainerDlg::OnSetFocus(CWnd* pOldWnd)
//{
//	CDialogEx::OnSetFocus(pOldWnd);
//
//	int unitOffset[] = { UNIT_OFFSET1 };
//	try
//	{
//		MemoryOpt memOpt;
//		memOpt.initPara(UNIT_BASE, unitOffset, sizeof(unitOffset) / sizeof(int));
//
//		unitOffset[0] = HP_OFFSET;
//		memOpt.readOffsetMemory(unitOffset, 1, &unitHp, sizeof(unitHp));
//	}
//	catch (const std::exception & e)
//	{
//		CString error;
//		error = e.what();
//		MessageBox(error);
//	}
//
//	UpdateData(FALSE);
//}
