
// AoEIIDETrainerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "AoEIIDETrainer.h"
#include "AoEIIDETrainerDlg.h"
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


// CAoEIIDETrainerDlg 对话框



CAoEIIDETrainerDlg::CAoEIIDETrainerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_AOEIIDETRAINER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAoEIIDETrainerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CAoEIIDETrainerDlg::modifyResource()
{
	try
	{
		int resoOffset[] = { OFFSET1, OFFSET2, OFFSET3, OFFSET4, OFFSET5, OFFSET6, OFFSET7, RESO_OFFSET1 };
		MemoryOpt memOpt;
		memOpt.initPara(BASE, resoOffset, sizeof(resoOffset) / sizeof(int));

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

void CAoEIIDETrainerDlg::testCall()
{
	__asm
	{
		push rsp
		push rbx
		push rax
		push rdx
		push rcx
		sub rsp, 0x40
		mov rbx, qword ptr ds : [0x7FF69AC0F668]
		mov rbx, qword ptr ds : [rbx + 0xB8]
		mov rbx, qword ptr ds : [rbx + 0xBBF0]
		mov rbx, qword ptr ds : [rbx + 0xD0]
		mov rbx, qword ptr ds : [rbx + 0x8]
		mov rbx, qword ptr ds : [rbx + 0x168]
		mov rbx, qword ptr ds : [rbx + 0x118]
		mov rbx, qword ptr ds : [rbx + 0x18]
		mov rax, qword ptr ds : [rbx]
		mov dword ptr ss : [rsp + 0x28] , 1
		mov dword ptr ss : [rsp + 0x20] , 0
		mov dword ptr ss : [rsp + 0x38] , 0x42620000
		movss xmm3, dword ptr ss : [rsp + 0x38]
		mov dword ptr ss : [rsp + 0x38] , 0x428F0000
		movss xmm2, dword ptr ss : [rsp + 0x38]
		mov edx, 0x231
		mov rcx, rbx
		call qword ptr ds : [rax + 0x150]
		pop rcx
		pop rdx
		pop rax
		pop rbx
		pop rsp
	}
}

BEGIN_MESSAGE_MAP(CAoEIIDETrainerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


// CAoEIIDETrainerDlg 消息处理程序

BOOL CAoEIIDETrainerDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAoEIIDETrainerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAoEIIDETrainerDlg::OnPaint()
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
HCURSOR CAoEIIDETrainerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAoEIIDETrainerDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
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
			break;
		case VK_NUMPAD5:
			modifyResource();
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
