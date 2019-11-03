#pragma once


// DllMainDlg 对话框

class DllMainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DllMainDlg)

public:
	DllMainDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DllMainDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLLMAIN_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
