#pragma once

#define WM_MY_EVENT_NOTIFY WM_USER + 1000

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

protected:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnMyEventNotify(WPARAM wParam, LPARAM lParam);
};
