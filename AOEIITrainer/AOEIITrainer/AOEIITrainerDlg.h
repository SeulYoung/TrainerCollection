
// AOEIITrainerDlg.h: 头文件
//

#pragma once


// CAOEIITrainerDlg 对话框
class CAOEIITrainerDlg : public CDialogEx
{
	// 构造
public:
	CAOEIITrainerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AOEIITRAINER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

protected:
	DWORD getProcId(CString gameProcName);

	// 实现
protected:
	HICON m_hIcon;
	int unitHp;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnBnClickedModifyHp();
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
