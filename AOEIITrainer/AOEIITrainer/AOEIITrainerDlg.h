
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

public:
	static DWORD __stdcall createUnit(LPVOID unitId);
	void modifyResource();
	void modifyPopulation();

	// 实现
protected:
	HICON m_hIcon;
	float unitHp;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnBnClickedModifyHp();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
