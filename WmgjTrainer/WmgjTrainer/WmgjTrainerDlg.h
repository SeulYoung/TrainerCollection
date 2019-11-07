
// WmgjTrainerDlg.h: 头文件
//

#pragma once

#include "TrayIcon.h"

typedef struct
{
	DWORD procId;
	HWND hWnd;
	CString roleName;
}TrainerWndInfo;

// CWmgjTrainerDlg 对话框
class CWmgjTrainerDlg : public CDialogEx
{
	// 构造
public:
	CWmgjTrainerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WMGJTRAINER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 自定义函数
public:
	CString getAppPath();
	void getProcessIdList(CString name, std::vector<DWORD>& procIdList);
	bool injectModle(HANDLE hProcess, CString dllName, bool isInject);
	void getTrainerWndList(std::vector<TrainerWndInfo>& trainerWndInfoList);

	// 实现
protected:
	HICON m_hIcon;
	CListCtrl gameProcInfo;
	TrayIcon trayIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedBtnRunTrainer();
	afx_msg void OnBnClickedBtnExitTrainer();
	afx_msg LRESULT OnMsgIconNotify(WPARAM wParam, LPARAM lParam);
};

class text_exception : public std::exception
{
private:
	char* text_;

public:
	text_exception(const char* text)
	{
		size_t length = strlen(text) + 1;
		text_ = new char[length];
		strcpy_s(text_, length, text);
	}
	text_exception(const text_exception& e)
	{
		size_t length = strlen(e.text_) + 1;
		text_ = new char[length];
		strcpy_s(text_, length, e.text_);
	}
	~text_exception()
	{
		delete[] text_;
	}

	const char* what() const noexcept { return text_; }
};
