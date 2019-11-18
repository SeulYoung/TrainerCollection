
// AoEIIDETrainerDlg.h: 头文件
//

#pragma once


// CAoEIIDETrainerDlg 对话框
class CAoEIIDETrainerDlg : public CDialogEx
{
	// 构造
public:
	CAoEIIDETrainerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AOEIIDETRAINER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	DECLARE_MESSAGE_MAP()

public:
	void modifyResource();
	void testCall();

	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
};
