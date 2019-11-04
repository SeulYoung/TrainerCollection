
// WmgjTrainerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "WmgjTrainer.h"
#include "WmgjTrainerDlg.h"
#include "afxdialogex.h"
#include <TlHelp32.h>

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


// CWmgjTrainerDlg 对话框



CWmgjTrainerDlg::CWmgjTrainerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WMGJTRAINER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWmgjTrainerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_GameProcInfo, gameProcInfo);
}

BEGIN_MESSAGE_MAP(CWmgjTrainerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_RunTrainer, &CWmgjTrainerDlg::OnBnClickedBtnRunTrainer)
	ON_BN_CLICKED(IDC_BTN_ExitTrainer, &CWmgjTrainerDlg::OnBnClickedBtnExitTrainer)
	ON_MESSAGE(MSG_ICON_NOTIFY, &CWmgjTrainerDlg::OnMsgIconNotify)
END_MESSAGE_MAP()


CString CWmgjTrainerDlg::getAppPath()
{
	WCHAR path[MAX_PATH];
	GetModuleFileName(NULL, path, MAX_PATH);
	CString temp = path;
	return temp.Left(temp.ReverseFind('\\') + 1);
}

void CWmgjTrainerDlg::getProcessIdList(CString name, std::vector<DWORD>& procIdList)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	bool result = Process32First(hSnapShot, &pe32);
	while (result)
	{
		CString procName = pe32.szExeFile;
		//procName.MakeLower();
		if (name == procName)
			procIdList.push_back(pe32.th32ProcessID);
		result = Process32Next(hSnapShot, &pe32);
	}
	CloseHandle(hSnapShot);
}

bool CWmgjTrainerDlg::injectModle(HANDLE hProcess, CString dllName, bool isInject)
{
	bool ret = true;
	LPVOID remoteParam = NULL;
	HANDLE hThread = NULL;
	try
	{
		remoteParam = VirtualAllocEx(hProcess, NULL, dllName.GetLength() + 1, MEM_COMMIT, PAGE_READWRITE);
		if (remoteParam == NULL)
			throw text_exception("原程分配地址空间失败");

		DWORD bytes;
		if (!WriteProcessMemory(hProcess, remoteParam, dllName.GetBuffer(0), dllName.GetLength(), &bytes))
			throw text_exception("远程进程写入数据失败");

		HMODULE hMod = GetModuleHandleA("Kernel32.dll");
		if (hMod == NULL)
			throw text_exception("获取Kernel32.dll句柄失败");

		if (isInject)
		{
			PTHREAD_START_ROUTINE remoteFunc = (PTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryA");
			if (remoteFunc == NULL)
				throw text_exception("获取LoadLibrary地址失败");

			hThread = CreateRemoteThread(hProcess, NULL, 0, remoteFunc, remoteParam, 0, NULL);
			if (hThread == NULL)
				throw text_exception("远程线程创建失败");
			WaitForSingleObject(hThread, INFINITE);
		}
		else
		{
			PTHREAD_START_ROUTINE remoteFunc = (PTHREAD_START_ROUTINE)GetProcAddress(hMod, "GetModuleHandleA");
			if (remoteFunc == NULL)
				throw text_exception("获取GetModuleHandle地址失败");

			hThread = CreateRemoteThread(hProcess, NULL, 0, remoteFunc, remoteParam, 0, NULL);
			if (hThread == NULL)
				throw text_exception("远程线程创建失败");
			WaitForSingleObject(hThread, INFINITE);

			DWORD code;
			GetExitCodeThread(hThread, &code);
			if (code == 0)
				throw text_exception("获取辅助模块句柄失败");

			CloseHandle(hThread);
			hThread = NULL;

			remoteFunc = (PTHREAD_START_ROUTINE)GetProcAddress(hMod, "FreeLibraryA");
			if (remoteFunc == NULL)
				throw text_exception("获取FreeLibrary地址失败");

			hThread = CreateRemoteThread(hProcess, NULL, 0, remoteFunc, (LPVOID)code, 0, NULL);
			if (hThread == NULL)
				throw text_exception("远程线程创建失败");
			WaitForSingleObject(hThread, INFINITE);

			code;
			GetExitCodeThread(hThread, &code);
		}
	}
	catch (const std::exception & e)
	{
		CString error;
		error = e.what();
		MessageBox(error);

		ret = false;
	}
	if (remoteParam != NULL)
		VirtualFreeEx(hProcess, remoteParam, 0, MEM_RELEASE);
	if (hThread != NULL)
		CloseHandle(hThread);

	return ret;
}

void CWmgjTrainerDlg::getTrainerWndList(std::vector<TrainerWndInfo>& trainerWndInfoList)
{
	HWND hWnd = ::FindWindow(NULL, GW_HWNDFIRST);
	while (hWnd != NULL)
	{
		WCHAR text[256];
		::GetWindowText(hWnd, text, sizeof(text) / 2);
		CString temp = text;
		int pos = temp.Find(_T(" - Trainer"));
		if (pos > 0)
		{
			DWORD procId;
			GetWindowThreadProcessId(hWnd, &procId);
			trainerWndInfoList.push_back(TrainerWndInfo{ procId, hWnd, temp.Left(pos) });
		}
		hWnd = ::GetNextWindow(hWnd, GW_HWNDNEXT);
	}
}


// CWmgjTrainerDlg 消息处理程序

BOOL CWmgjTrainerDlg::OnInitDialog()
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
	gameProcInfo.InsertColumn(0, _T("进程ID"), LVCFMT_LEFT, 60);
	gameProcInfo.InsertColumn(1, _T("进程名称"), LVCFMT_LEFT, 150);
	gameProcInfo.InsertColumn(2, _T("角色名称"), LVCFMT_LEFT, 150);
	gameProcInfo.SetExtendedStyle(gameProcInfo.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	SetTimer(1, 1000, NULL);
	trayIcon.InitTrayIcon(this);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWmgjTrainerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWmgjTrainerDlg::OnPaint()
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
HCURSOR CWmgjTrainerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWmgjTrainerDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

void CWmgjTrainerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	std::vector<DWORD> procIdList;
	getProcessIdList(GAME_PROC_NAME, procIdList);

	// 从列表删除被关闭的进程
	for (size_t i = 0; i < (size_t)gameProcInfo.GetItemCount(); i++)
	{
		bool isFind = false;
		TrainerWndInfo* info = (TrainerWndInfo*)gameProcInfo.GetItemData(i);
		for (size_t j = 0; j < procIdList.size(); j++)
			if (info->procId == procIdList[j])
			{
				isFind = true;
				break;
			}

		if (!isFind)
			gameProcInfo.DeleteItem(i);
	}

	// 添加对应的进程到列表
	for (size_t i = 0; i < procIdList.size(); i++)
	{
		bool isFind = false;
		for (size_t j = 0; j < (size_t)gameProcInfo.GetItemCount(); j++)
		{
			TrainerWndInfo* info = (TrainerWndInfo*)gameProcInfo.GetItemData(j);
			if (procIdList[i] == info->procId)
			{
				isFind = true;
				break;
			}
		}
		if (!isFind)
		{
			int count = gameProcInfo.GetItemCount();
			CString str;
			str.Format(_T("%d"), procIdList[i]);
			gameProcInfo.InsertItem(count, str);
			gameProcInfo.SetItemText(count, 1, GAME_PROC_NAME);
			gameProcInfo.SetItemData(count, (DWORD)new TrainerWndInfo{ procIdList[i], NULL, _T("") });
		}
	}

	// 获取辅助窗口和更新角色名
	std::vector<TrainerWndInfo> trainerWndInfoList;
	getTrainerWndList(trainerWndInfoList);
	for (size_t i = 0; i < (size_t)gameProcInfo.GetItemCount(); i++)
	{
		int index = -1;
		TrainerWndInfo* info = (TrainerWndInfo*)gameProcInfo.GetItemData(i);
		for (size_t j = 0; j < trainerWndInfoList.size(); j++)
			if (info->procId == trainerWndInfoList[j].procId)
			{
				index = j;
				break;
			}

		if (index >= 0)
		{
			*info = trainerWndInfoList[index];
			gameProcInfo.SetItemText(i, 2, info->roleName);
		}
		else
		{
			info->hWnd = NULL;
			info->roleName = _T("");
			gameProcInfo.SetItemText(i, 2, info->roleName);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CWmgjTrainerDlg::OnBnClickedBtnRunTrainer()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = gameProcInfo.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		MessageBox(_T("请选择一个进程"));
		return;
	}
	int index = gameProcInfo.GetNextSelectedItem(pos);

	TrainerWndInfo* info = (TrainerWndInfo*)gameProcInfo.GetItemData(index);
	if (info->hWnd != NULL)
	{
		MessageBox(_T("该进程已运行了辅助"));
		return;
	}

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, info->procId);
	bool ret = injectModle(hProcess, getAppPath() + GAME_DLL_NAME, true);
}


void CWmgjTrainerDlg::OnBnClickedBtnExitTrainer()
{
	// TODO: 在此添加控件通知处理程序代码
	POSITION pos = gameProcInfo.GetFirstSelectedItemPosition();
	if (pos == NULL)
		MessageBox(_T("请选择一个进程"));
	int index = gameProcInfo.GetNextSelectedItem(pos);

	TrainerWndInfo* info = (TrainerWndInfo*)gameProcInfo.GetItemData(index);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, info->procId);
	bool ret = injectModle(hProcess, GAME_DLL_NAME, false);
}


afx_msg LRESULT CWmgjTrainerDlg::OnMsgIconNotify(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDOWN)
		ShowWindow(IsWindowVisible() ? SW_HIDE : SW_SHOW);

	return 0;
}
