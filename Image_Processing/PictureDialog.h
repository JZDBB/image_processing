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
	CRect rect;
	bool move_flag, up_flag, flag;
	int rect_width;
	int rect_height;
	int xscale;
	int yscale;

	CPoint m_startPoint, m_endPoint;
	CImage m_Image;

	//Rect ROIrect;
	//Mat m_tmpGray;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
