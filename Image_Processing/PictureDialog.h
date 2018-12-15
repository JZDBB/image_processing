#pragma once


// PictureDialog 对话框

class PictureDialog : public CDialogEx
{
	DECLARE_DYNAMIC(PictureDialog)

public:
	PictureDialog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~PictureDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGPIC };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnClickedPic();
	afx_msg void OnBnClickedButton1();
};
