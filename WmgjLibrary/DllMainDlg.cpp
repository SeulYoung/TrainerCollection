// DllMainDlg.cpp: 实现文件
//

#include "pch.h"
#include "WmgjLibrary.h"
#include "DllMainDlg.h"
#include "afxdialogex.h"


// DllMainDlg 对话框

IMPLEMENT_DYNAMIC(DllMainDlg, CDialogEx)

DllMainDlg::DllMainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLLMAIN_DIALOG, pParent)
{

}

DllMainDlg::~DllMainDlg()
{
}

void DllMainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DllMainDlg, CDialogEx)
	ON_MESSAGE(WM_MY_EVENT_NOTIFY, &DllMainDlg::OnMyEventNotify)
END_MESSAGE_MAP()


// DllMainDlg 消息处理程序


BOOL DllMainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GlobalInfo::getGlobalInfoInstance()->setHWndDllMain(this->GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

LRESULT DllMainDlg::OnMyEventNotify(WPARAM wParam, LPARAM lParam)
{

	return 0;
}
