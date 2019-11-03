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
END_MESSAGE_MAP()


// DllMainDlg 消息处理程序
