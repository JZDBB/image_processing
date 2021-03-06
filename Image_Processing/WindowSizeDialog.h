#pragma once


// WindowSizeDialog 对话框

class WindowSizeDialog : public CDialogEx
{
	DECLARE_DYNAMIC(WindowSizeDialog)

public:
	WindowSizeDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WindowSizeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGSIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString str;
	CWnd * pWnd;				
	CDC* pDC;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditsize();
	afx_msg void OnBnClickedOk();
};
