
// PlantsVsZombiesTrainerDlg.h: 头文件
//

#pragma once

typedef struct
{
	UINT x;
	UINT y;
	UINT plantId;
}PlantParameter;

// CPlantsVsZombiesTrainerDlg 对话框
class CPlantsVsZombiesTrainerDlg : public CDialogEx
{
	// 构造
public:
	CPlantsVsZombiesTrainerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PLANTSVSZOMBIESTRAINER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	bool enableDebugPriv();
	DWORD findProcessIdByWinTitle(CString title);
	static DWORD __stdcall createPlant(LPVOID threadPara);

	// 实现
protected:
	HICON m_hIcon;
	int x;
	int y;
	int plantId;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnPlant();
};
