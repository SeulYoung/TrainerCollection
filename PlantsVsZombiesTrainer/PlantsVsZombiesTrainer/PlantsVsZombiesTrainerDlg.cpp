
// PlantsVsZombiesTrainerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "PlantsVsZombiesTrainer.h"
#include "PlantsVsZombiesTrainerDlg.h"
#include "afxdialogex.h"

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


// CPlantsVsZombiesTrainerDlg 对话框



CPlantsVsZombiesTrainerDlg::CPlantsVsZombiesTrainerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PLANTSVSZOMBIESTRAINER_DIALOG, pParent)
	, x(0)
	, y(0)
	, plantId(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlantsVsZombiesTrainerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_XCoordinate, x);
	DDX_Text(pDX, IDC_EDT_YCoordinate, y);
	DDX_Text(pDX, IDC_EDT_PlantId, plantId);
}

bool CPlantsVsZombiesTrainerDlg::enableDebugPriv()
{
	HANDLE hToken;
	LUID debugNameValue;
	TOKEN_PRIVILEGES tkp;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
		return false;
	if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &debugNameValue))
	{
		CloseHandle(hToken);
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = debugNameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL))
	{
		CloseHandle(hToken);
		return false;
	}

	return true;
}

DWORD CPlantsVsZombiesTrainerDlg::findProcessIdByWinTitle(CString title)
{
	HWND hWnd = ::FindWindow(NULL, title.GetBuffer());
	if (!hWnd)
	{
		MessageBox(_T("未找到游戏窗口"));
		return NULL;
	}
	DWORD winPid = NULL;
	GetWindowThreadProcessId(hWnd, &winPid);
	return winPid;
}

DWORD __stdcall CPlantsVsZombiesTrainerDlg::createPlant(LPVOID threadPara)
{
	PlantParameter* plantPara = (PlantParameter*)threadPara;
	UINT x = plantPara->x;
	UINT y = plantPara->y;
	UINT plantId = plantPara->plantId;

	__asm
	{
		pushad
		mov eax, x
		push - 1
		push plantId
		push y
		mov ebx, dword ptr ds : [0x007794F8]
		mov ebx, dword ptr ds : [ebx + 0x868]
		push ebx
		mov edx, 0x00422610
		call edx
		popad
	}
	return 0;
}


BEGIN_MESSAGE_MAP(CPlantsVsZombiesTrainerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_Plant, &CPlantsVsZombiesTrainerDlg::OnBnClickedBtnPlant)
END_MESSAGE_MAP()


// CPlantsVsZombiesTrainerDlg 消息处理程序

BOOL CPlantsVsZombiesTrainerDlg::OnInitDialog()
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CPlantsVsZombiesTrainerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPlantsVsZombiesTrainerDlg::OnPaint()
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
HCURSOR CPlantsVsZombiesTrainerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPlantsVsZombiesTrainerDlg::OnBnClickedBtnPlant()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	PVOID threadAddr = NULL;
	PVOID plantParAddress = NULL;
	try
	{
		DWORD winPid = findProcessIdByWinTitle(_T("Plants vs. Zombies 1.2.0.1073 RELEASE"));
		hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, winPid);
		if (hProcess == NULL)
			throw "打开游戏进程失败";

		threadAddr = VirtualAllocEx(hProcess, NULL, 4096, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (threadAddr == NULL)
			throw "分配线程运行内存失败";

		DWORD writeSize;
		if (!WriteProcessMemory(hProcess, threadAddr, createPlant, 4096, &writeSize))
			throw "线程写入内存失败";

		PlantParameter plantPara = { (UINT)x - 1, (UINT)y - 1, (UINT)plantId };
		plantParAddress = VirtualAllocEx(hProcess, NULL, sizeof(plantPara), MEM_COMMIT, PAGE_READWRITE);
		if (plantParAddress == NULL)
			throw "分配数据内存失败";

		if (!WriteProcessMemory(hProcess, plantParAddress, &plantPara, sizeof(plantPara), &writeSize))
			throw "数据写入内存失败";

		hThread = CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)threadAddr, plantParAddress, NULL, NULL);
		if (hThread == NULL)
			throw "创建线程失败";

		DWORD waitResult = WaitForSingleObject(hThread, INFINITE);
		if (waitResult == WAIT_TIMEOUT)
			throw "线程执行等待超时";
	}
	catch (const char* e)
	{
		CString error;
		error = e;
		MessageBox(error);
	}

	if (plantParAddress != NULL)
		VirtualFreeEx(hProcess, plantParAddress, 0, MEM_RELEASE);
	if (threadAddr != NULL)
		VirtualFreeEx(hProcess, threadAddr, 0, MEM_RELEASE);

	if (hThread != NULL)
		CloseHandle(hThread);
	if (hProcess != NULL)
		CloseHandle(hProcess);
}
