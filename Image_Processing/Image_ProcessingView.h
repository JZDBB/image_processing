
// Image_ProcessingView.h : CImage_ProcessingView 类的接口
//

#pragma once
#include "MyImage_.h"
#include "Image_ProcessingDoc.h"
#include "Image_ProcessingView.h"

class CImage_ProcessingView : public CScrollView
{
protected: // 仅从序列化创建
	CImage_ProcessingView();
	DECLARE_DYNCREATE(CImage_ProcessingView)

// 特性
public:
	CImage_ProcessingDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CImage_ProcessingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
public:
	MyImage_ m_Image;
	CString filename;

	afx_msg void OnDrawline();
	afx_msg void OnFileSaveAs();
	afx_msg void OnShowred();
	afx_msg void OnResolution();
	afx_msg void OnGraychange();
	afx_msg void OnDiff();
	afx_msg void OnDenoiseing();
	afx_msg void OnHistogram();
	afx_msg void OnHistequal();
	afx_msg void OnHistmatch();
	afx_msg void OnMeanfilter();
	afx_msg void OnMidfilter();
	afx_msg void OnAddnoise();
	afx_msg void OnTransformfft();
	afx_msg void OnLowpass();
	afx_msg void OnHighpass();
	afx_msg void OnButterlowpass();
	afx_msg void OnButterhighpass();
	afx_msg void OnGaussianlowpass();
	afx_msg void OnGaussianhighpass();
	afx_msg void OnAddimpulsenoise();
	afx_msg void OnAddguaussiannoise();
	double CImage_ProcessingView::generateGaussianNoise(double mu, double sigma);
};

#ifndef _DEBUG  // Image_ProcessingView.cpp 中的调试版本
inline CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const
   { return reinterpret_cast<CImage_ProcessingDoc*>(m_pDocument); }
#endif

