#pragma once
#include"resource.h"
#include"Image_ProcessingView.h"
// paintHistDialog 对话框

class paintHistDialog : public CDialogEx
{
	DECLARE_DYNAMIC(paintHistDialog)

	
public:
	paintHistDialog(CImage_ProcessingView* pParent);   // 标准构造函数
	virtual ~paintHistDialog();

	enum { IDD = IDD_DIALOGHIST };

	// 对话框数据
//#ifdef AFX_DESIGN_TIME
//	enum { IDD = IDD_DIALOGHIST };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	CWnd * pWnd;					//
	CDC* pDC;						//
	CImage_ProcessingView* pv;		//
	virtual BOOL OnInitDialog();	//初始化
	afx_msg void OnPaint();			//画图


};
