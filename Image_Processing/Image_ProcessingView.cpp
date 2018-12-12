
// Image_ProcessingView.cpp : CImage_ProcessingView 类的实现
//
#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Image_Processing.h"
#endif
#include <vector>
#include <algorithm>
#include <limits>
#include <iostream>
#include <cmath>
#include "math.h"
#include "FFT_transform.hpp"
#include "complex_mat.hpp"
#include "Image_ProcessingDoc.h"
#include "paintHistDialog.h"
#include "Image_ProcessingView.h"
using namespace std;

#define  E 2.718281828;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImage_ProcessingView

IMPLEMENT_DYNCREATE(CImage_ProcessingView, CScrollView)

BEGIN_MESSAGE_MAP(CImage_ProcessingView, CScrollView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImage_ProcessingView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FILE_OPEN, &CImage_ProcessingView::OnFileOpen)
	ON_COMMAND(IDM_DRAWLINE, &CImage_ProcessingView::OnDrawline)
	ON_COMMAND(ID_FILE_SAVE_AS, &CImage_ProcessingView::OnFileSaveAs)
	ON_COMMAND(IDM_SHOWRED, &CImage_ProcessingView::OnShowred)
//	ON_COMMAND(ID_VIEW_TOOLBAR, &CImage_ProcessingView::OnViewToolbar)
	ON_COMMAND(ID_RESOLUTION, &CImage_ProcessingView::OnResolution)
	ON_COMMAND(ID_GRAYCHANGE, &CImage_ProcessingView::OnGraychange)
	ON_COMMAND(ID_DIFF, &CImage_ProcessingView::OnDiff)
	ON_COMMAND(ID_DENOISEING, &CImage_ProcessingView::OnDenoiseing)
	ON_COMMAND(ID_HISTOGRAM, &CImage_ProcessingView::OnHistogram)
	ON_COMMAND(ID_HISTEQUAL, &CImage_ProcessingView::OnHistequal)
	ON_COMMAND(ID_HISTMATCH, &CImage_ProcessingView::OnHistmatch)
	ON_COMMAND(ID_MEANFILTER, &CImage_ProcessingView::OnMeanfilter)
	ON_COMMAND(ID_MIDFILTER, &CImage_ProcessingView::OnMidfilter)
	ON_COMMAND(ID_ADDNOISE, &CImage_ProcessingView::OnAddnoise)
	ON_COMMAND(ID_TRANSFORMFFT, &CImage_ProcessingView::OnTransformfft)
	ON_COMMAND(ID_TRANSFORMIFFT, &CImage_ProcessingView::OnTransformifft)
	ON_COMMAND(ID_LOWPASS, &CImage_ProcessingView::OnLowpass)
	ON_COMMAND(ID_HIGHPASS, &CImage_ProcessingView::OnHighpass)
	ON_COMMAND(ID_BUTTERLOWPASS, &CImage_ProcessingView::OnButterlowpass)
	ON_COMMAND(ID_BUTTERHIGHPASS, &CImage_ProcessingView::OnButterhighpass)
	ON_COMMAND(ID_GAUSSIANLOWPASS, &CImage_ProcessingView::OnGaussianlowpass)
	ON_COMMAND(ID_GAUSSIANHIGHPASS, &CImage_ProcessingView::OnGaussianhighpass)
	ON_COMMAND(ID_ADDIMPULSENOISE, &CImage_ProcessingView::OnAddimpulsenoise)
	ON_COMMAND(ID_ADDGUAUSSIANNOISE, &CImage_ProcessingView::OnAddguaussiannoise)
	ON_COMMAND(ID_ADAPTEDMIDFILTER, &CImage_ProcessingView::OnAdaptedmidfilter)
	ON_COMMAND(ID_SHOWRGB, &CImage_ProcessingView::OnShowrgb)
	ON_COMMAND(ID_SHOWHSI, &CImage_ProcessingView::OnShowhsi)
	ON_COMMAND(ID_EQUALRGB, &CImage_ProcessingView::OnEqualrgb)
	ON_COMMAND(ID_EQUALI, &CImage_ProcessingView::OnEquali)
END_MESSAGE_MAP()

// CImage_ProcessingView 构造/析构

CImage_ProcessingView::CImage_ProcessingView()
{
	// TODO: 在此处添加构造代码

}


CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView 绘制

void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	if (!m_Image.IsNull())
	{

		if (m_Image.flag == 2)//显示操作后的对比
		{
			m_Image.Draw(pDC->m_hDC, 0, 0);
			image2.Draw(pDC->m_hDC, m_Image.GetWidth(), 0);
		}

		else if (m_Image.flag == 1)//对比原图
		{
			m_Image.Draw(pDC->m_hDC, 0, 0);
			m_Imagesrc.Draw(pDC->m_hDC, m_Image.GetWidth(), 0);
		}

		else if (m_Image.flag == 0)//只显示原图
		{
			m_Image.Draw(pDC->m_hDC, 0, 0);
		}
		else if (m_Image.flag == 3)//对比原图
		{
			m_Image_r.Draw(pDC->m_hDC, 0, 0);
			m_Image_g.Draw(pDC->m_hDC, m_Image_r.GetWidth(), 0);
			m_Image_b.Draw(pDC->m_hDC, m_Image_r.GetWidth() + m_Image_g.GetWidth(), 0);
		}
		else if (m_Image.flag == 4)//对比原图
		{
			m_Image_h.Draw(pDC->m_hDC, 0, 0);
			m_Image_s.Draw(pDC->m_hDC, m_Image_h.GetWidth(), 0);
			m_Image_i.Draw(pDC->m_hDC, m_Image_h.GetWidth() + m_Image_i.GetWidth(), 0);
		}
	}
	return;
	
	//CImage_ProcessingDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	//// TODO: 在此处为本机数据添加绘制代码
	//if (!m_Image.IsNull())
	//{
	//	m_Image.Draw(pDC->m_hDC,0,0); 
	//}
	//return;
}

void CImage_ProcessingView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 计算此视图的合计大小
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView 打印


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CImage_ProcessingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImage_ProcessingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImage_ProcessingView 诊断

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView 消息处理程序


void CImage_ProcessingView::OnFileOpen()
{
	// TODO: 在此添加命令处理程序代码
	CFileDialog dlg(TRUE);    //为打开文件创建一个变量
	if(IDOK == dlg.DoModal())    //调用函数打开一个对话框，并判断是否打开成功
	{
		if(!m_Image.IsNull()) m_Image.Destroy();//判断是否已经有图片，有的话进行清除
		filename = dlg.GetPathName();
		m_Image.Load(filename);//获得图片的地址，并且加载图片

		//获得图片的大小，并按其大小设置滚动条的初始窗口大小等参数
		CSize sizeTotal;
		int w=m_Image.GetWidth();
		int h=m_Image.GetHeight();
		sizeTotal.cx =w;
		sizeTotal.cy =h;
		SetScrollSizes(MM_TEXT, sizeTotal);

		//Window_Image_w=m_Image.GetWidth();//获得图片的初始大小，为放大缩小功能做准备
		//Window_Image_h=m_Image.GetHeight();//
		m_Image.flag = 0;
		Invalidate(1); //强制调用ONDRAW函数
	}
}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) return;
	
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();

	for (int k=0;k<w;k++)
	{
		m_Image.m_pBits[0][10][k]=0;//B
		m_Image.m_pBits[1][10][k]=0;//G
		m_Image.m_pBits[2][10][k]=0;//R

	}

	Invalidate(1); //强制调用ONDRAW函数

}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) {
		MessageBox(_T("你还没有打开一个要保存的图像文件！"));
		return;
	}
	CString strFilter;
	//strFilter ="位图文件|*.bmp|JPEG 图像文件|*.jpg|GIF 图像文件|*.gif|PNG 图像文件|*.png||";   //
	strFilter ="所有文件|*.*||";   //

	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if ( IDOK != dlg.DoModal()) 
		return;
	// 如果用户没有指定文件扩展名，则为其添加一个
	CString strFileName;
	//CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  获得文件名
	//if(dlg.m_ofn.nFileExtension == 0)     //获得文件扩展名
	//{
	//	switch (dlg.m_ofn.nFilterIndex)
	//	{
	//	case 1:
	//		strExtension = "bmp"; break;
	//	case 2:
	//		strExtension = "jpg"; break;
	//	case 3:
	//		strExtension = "gif"; break;
	//	case 4:
	//		strExtension = "png"; break;
	//	default:
	//		break;
	//	}
	//	strFileName = strFileName + _T(".") + strExtension;
	//	//strFileName="C:\\Users\\Lenovo\\Desktop\\QSanguosha-Qingming\\abc.bmp";
	//}
	// 图像保存
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("保存图像文件失败！"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: 在此添加命令处理程序代码
	if(m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w=m_Image.GetWidth();//获得图像的宽度
	int h=m_Image.GetHeight();//获得图像的高度
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image.m_pBits[1][j][k]=0;//G
		}
	}

	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::OnResolution()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度

	int bits = m_Image.GetBPP();
	int C = 3;
	//if (bits == 8) C = 1;
	int inter = 5;

	for (int c = 0; c < C; c++)
	{
		for (int j = 0; j < h; j++)
		{
			for (int k = 0; k < w; k++)
			{
				m_Image.m_pBits[c][j][k] = m_Image.m_pBits[c][j / inter * inter][k / inter * inter];
			}
		}
	}
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::OnGraychange()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度

	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	// change image to gray
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			int ave = 0.1140 *m_Image.m_pBits[0][j][k] + 0.5870 *m_Image.m_pBits[1][j][k] + 0.2989 *m_Image.m_pBits[2][j][k];
			m_Image.m_pBits[0][j][k] = ave;
			m_Image.m_pBits[1][j][k] = ave;
			m_Image.m_pBits[2][j][k] = ave;
		}
	}
	// wait minute 

	int K = 2; //灰度分辨率等级
	// change Gray
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int step = 256 / (K);
			int value = (step << 1) - 1;
			m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / step) * value;
			m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / step) * value;
			m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / step) * value;
		}
	}
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::OnDiff()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	MyImage_ m_Image2;
	CFileDialog dlg(TRUE);//同样是打开一个新的对话框，存储别的输入图片
	if (IDOK == dlg.DoModal())
	{
		if (!m_Image2.IsNull())
			m_Image2.Destroy();
		m_Image2.Load(dlg.GetPathName());
		if (m_Image2.IsNull())
			return;
		int w0 = m_Image2.GetWidth();
		int h0 = m_Image2.GetHeight();
		if (w0 != w || h0 != h) {
			return;
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				m_Image.m_pBits[0][i][j] = m_Image.m_pBits[0][i][j] - m_Image2.m_pBits[0][i][j];
				m_Image.m_pBits[1][i][j] = m_Image.m_pBits[1][i][j] - m_Image2.m_pBits[1][i][j];
				m_Image.m_pBits[2][i][j] = m_Image.m_pBits[2][i][j] - m_Image2.m_pBits[2][i][j];
			}
		}
		Invalidate(1);
	}

}

void CImage_ProcessingView::OnDenoiseing()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	MyImage_ m_Image2;
	CFileDialog dlg(TRUE);//同样是打开一个新的对话框，存储别的输入图片
	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;//允许选择多个文件

	dlg.m_ofn.nMaxFile = 20 * 101;//最多可以打开20个文件，每个文件名的字符数<=100

	const DWORD numberOfFileNames = 32;//最多允许32个文件
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;
	TCHAR* filenamesBuffer = new TCHAR[bufferSize];
	// Initialize beginning and end of buffer.
	filenamesBuffer[0] = NULL;//必须的
	filenamesBuffer[bufferSize - 1] = NULL;

	// Attach buffer to OPENFILENAME member.
	dlg.m_ofn.lpstrFile = filenamesBuffer;
	dlg.m_ofn.nMaxFile = bufferSize;

	CStringArray strArrFilePaths;
	if (dlg.DoModal() == IDOK)
	{
		int k = 0;
		POSITION pos = dlg.GetStartPosition();//获取第一个文件名的位置
		while (pos != NULL) //GetNextPathName()返回当前pos的文件名，并将下一个文件名的位置保存到pos中
		{//连续叠加多幅图片
			if (!m_Image2.IsNull())
				m_Image2.Destroy();
			m_Image2.Load(dlg.GetNextPathName(pos));
			if (m_Image2.IsNull())
				return;
			int w0 = m_Image2.GetWidth();
			int h0 = m_Image2.GetHeight();
			if (w0 != w || h0 != h) {
				return;
			}
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					m_Image.m_pBits[0][i][j] = (m_Image.m_pBits[0][i][j] / (k + 2))*(k + 1) + m_Image2.m_pBits[0][i][j] / (k + 2);
					m_Image.m_pBits[1][i][j] = (m_Image.m_pBits[1][i][j] / (k + 2))*(k + 1) + m_Image2.m_pBits[1][i][j] / (k + 2);
					m_Image.m_pBits[2][i][j] = (m_Image.m_pBits[2][i][j] / (k + 2))*(k + 1) + m_Image2.m_pBits[2][i][j] / (k + 2);
				}
			}
			k++;
		}	
		Invalidate(1);
	}
}


void CImage_ProcessingView::OnHistogram()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度

	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	if (bits == 24 || bits == 32)
	{
		// change image to gray
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	m_Image.calcHistogram();

	paintHistDialog dlg(this);//用一个CImage_ProcessingView的指针取初始化dlg
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistequal()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	if (bits == 24 || bits == 32)
	{
		// change image to gray
		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	m_Image.calcHistogram();
	/*m_Image.histEqual();*/

	float s[256] = { 0 };//均衡
	int hist_equal[256] = { 0 };//均衡后

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			s[i] += 255 * m_Image.hist[j];
		}
		hist_equal[i] = floor(s[i]);
	}

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = m_Image.m_pBits[0][i][j];
			int new_value = hist_equal[value];
			m_Image.m_pBits[0][i][j] = new_value;
			m_Image.m_pBits[1][i][j] = new_value;
			m_Image.m_pBits[2][i][j] = new_value;
		}
	}

	m_Image.calcHistogram();

	paintHistDialog dlg(this);//用一个CImage_ProcessingView的指针取初始化dlg
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistmatch()
{
	// TODO: 在此添加命令处理程序代码
	MyImage_ m_Image_Match;
	CFileDialog dlg(TRUE);//同样是打开一个新的对话框，存储别的输入图片
	if (IDOK == dlg.DoModal())
	{
		if (!m_Image_Match.IsNull())
			m_Image_Match.Destroy();
		m_Image_Match.Load(dlg.GetPathName());
		if (m_Image_Match.IsNull())
			return;

		int w = m_Image_Match.GetWidth();//获得图像的宽度
		int h = m_Image_Match.GetHeight();//获得图像的高度
		int arr[256] = { 0 };
		int G[256] = { 0 };
		int bits = m_Image_Match.GetBPP();
		if (bits == 24 || bits == 32)
		{
			// change image to gray
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					int ave = 0.1140 *m_Image_Match.m_pBits[0][i][j] + 0.5870 *m_Image_Match.m_pBits[1][i][j] + 0.2989 *m_Image_Match.m_pBits[2][i][j];
					m_Image_Match.m_pBits[0][i][j] = ave;
					m_Image_Match.m_pBits[1][i][j] = ave;
					m_Image_Match.m_pBits[2][i][j] = ave;
				}
			}
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				BYTE value = m_Image_Match.m_pBits[0][i][j];
				arr[value] ++;
			}
		}
		
		if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
		int w0 = w;
		int h0 = h;
		w = m_Image.GetWidth();//获得图像的宽度
		h = m_Image.GetHeight();//获得图像的高度
		for (int i = 0; i < 256; i++)
		{
			for (int j = 0; j <= i; j++)
			{
				G[i] += float(arr[j]) / w0 / h0 * w * h;
			}
		}
		bits = m_Image.GetBPP();
		int hierarchical = 2;
		int n[256] = { 0 };
		int nMap[256] = { 0 };
		if (bits == 24 || bits == 32)
		{
			// change image to gray
			for (int i = 0; i < h; i++)
			{
				for (int j = 0; j < w; j++)
				{
					int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
					m_Image.m_pBits[0][i][j] = ave;
					m_Image.m_pBits[1][i][j] = ave;
					m_Image.m_pBits[2][i][j] = ave;
				}
			}
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				BYTE value = m_Image.m_pBits[0][i][j];
				n[value] ++;
			}
		}
		int count_g = 0;
		int count_n = 0;
		int sum = 0;
		while (true)
		{
			if (count_n == 256) break;
			
			if (sum < G[count_g]) {
				//count_n++;
				sum += n[count_n++];
				continue;
			}
			else {
				nMap[count_n] = count_g;
				count_g++;
			}
			if (count_g == 255) {
				nMap[255] = 255;
				break;
			}
		}
		int k = nMap[255];
		for (int i = 255; i >= 0; i--)
		{
			if (nMap[i] == 0) nMap[i] = k;
			else k = nMap[i];
		}

		for (int i = 0; i < h; i++)
		{
			for (int j = 0; j < w; j++)
			{
				int value = m_Image.m_pBits[0][i][j];
				m_Image.m_pBits[0][i][j] = nMap[value];
				m_Image.m_pBits[1][i][j] = nMap[value];
				m_Image.m_pBits[2][i][j] = nMap[value];
			}
		}
		m_Image.calcHistogram();

		paintHistDialog dlg1(this);//用一个CImage_ProcessingView的指针取初始化dlg
		dlg1.DoModal();

		Invalidate(1);
	}
}


void CImage_ProcessingView::OnMeanfilter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	MyImage_ m_Image2;
	m_Image2.Load(filename);

	for (int i = 1; i < h - 1; i++)
	{
		for (int j = 1; j < w - 1; j++)
		{
			m_Image.m_pBits[0][i][j] = m_Image2.m_pBits[0][i - 1][j - 1] / 9 + m_Image2.m_pBits[0][i][j - 1] / 9 + m_Image2.m_pBits[0][i + 1][j - 1] / 9 + m_Image2.m_pBits[0][i - 1][j] / 9 + m_Image2.m_pBits[0][i][j] / 9 + m_Image2.m_pBits[0][i + 1][j] / 9 + m_Image2.m_pBits[0][i - 1][j + 1] / 9 + m_Image2.m_pBits[0][i][j + 1] / 9 + m_Image2.m_pBits[0][i + 1][j + 1] / 9;
			m_Image.m_pBits[1][i][j] = m_Image2.m_pBits[1][i - 1][j - 1] / 9 + m_Image2.m_pBits[1][i][j - 1] / 9 + m_Image2.m_pBits[1][i + 1][j - 1] / 9 + m_Image2.m_pBits[1][i - 1][j] / 9 + m_Image2.m_pBits[1][i][j] / 9 + m_Image2.m_pBits[1][i + 1][j] / 9 + m_Image2.m_pBits[1][i - 1][j + 1] / 9 + m_Image2.m_pBits[1][i][j + 1] / 9 + m_Image2.m_pBits[1][i + 1][j + 1] / 9;
			m_Image.m_pBits[2][i][j] = m_Image2.m_pBits[2][i - 1][j - 1] / 9 + m_Image2.m_pBits[2][i][j - 1] / 9 + m_Image2.m_pBits[2][i + 1][j - 1] / 9 + m_Image2.m_pBits[2][i - 1][j] / 9 + m_Image2.m_pBits[2][i][j] / 9 + m_Image2.m_pBits[2][i + 1][j] / 9 + m_Image2.m_pBits[2][i - 1][j + 1] / 9 + m_Image2.m_pBits[2][i][j + 1] / 9 + m_Image2.m_pBits[2][i + 1][j + 1] / 9;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnMidfilter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误

	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	MyImage_ m_Image2;
	m_Image2.Load(filename);
	
	for (int i = 1; i < h - 1; i++)
	{
		for (int j = 1; j < w - 1; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				int arr[9] = {m_Image2.m_pBits[k][i - 1][j - 1], m_Image2.m_pBits[k][i][j - 1], m_Image2.m_pBits[k][i + 1][j - 1], m_Image2.m_pBits[k][i - 1][j], m_Image2.m_pBits[k][i][j], m_Image2.m_pBits[k][i + 1][j], m_Image2.m_pBits[k][i - 1][j + 1], m_Image2.m_pBits[k][i][j + 1], m_Image2.m_pBits[k][i + 1][j + 1]};
				sort(arr, arr + 9);
				m_Image.m_pBits[k][i][j] = arr[4];
			}
		}
	}
	Invalidate(1);
}



void CImage_ProcessingView::OnAddnoise()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) //判断图像是否为空，如果对空图像进行操作会出现未知的错误
	{
		OnFileOpen();
		//_T("请先打开一幅图像！"));
		return;
	}
	UpdateData();//获得编辑框用户输入的数据

	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();

	float p_a = 0.15;//获取噪声点的概率,p_a(黑),p_b（白）
	float p_b = 0.08;


	float P_Sum = p_a + p_b;
	float xishu = 1 / P_Sum;
	float p_a_1 = p_a*xishu;
	for (int i = 0; i <w; i++)
		for (int j = 0; j <h; j++)
		{
			if (rand() / 32767.0<P_Sum)//指定概率rand()产生随机的介于1-32767的数
			{
				if (rand() / 32767.0<p_a_1)
				{
					m_Image.m_pBits[0][j][i] = 1;         //该像素点显示为黑色
					m_Image.m_pBits[1][j][i] = 1;
					m_Image.m_pBits[2][j][i] = 1;

				}
				else
				{
					m_Image.m_pBits[0][j][i] = 255;         //该像素点显示为白色
					m_Image.m_pBits[1][j][i] = 255;
					m_Image.m_pBits[2][j][i] = 255;
				}

			}
		}
	Invalidate(1);
}


void CImage_ProcessingView::OnTransformfft()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32){
		for (int i = 0; i < h; i++){
			for (int j = 0; j < w; j++){
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	m_Image.flag = 1;
	Invalidate(1);
}

void CImage_ProcessingView::OnTransformifft()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F_ifft(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F_ifft.y, w, h);
	ifft2<float>(F_ifft.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F_ifft.y[i][j]);
			m_Image.m_pBits[0][i][j] = value;
			m_Image.m_pBits[1][i][j] = value;
			m_Image.m_pBits[2][i][j] = value;
		}
	}
	
	Invalidate(1);
}

void CImage_ProcessingView::OnLowpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float center_x, center_y;
	center_x = float(w) / 2;
	center_y = float(h) / 2;
	float D0 = 100;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float dis = pow(i - center_y, 2) + pow(j - center_x, 2);
			if ( dis > pow(D0, 2))
			{
				F.y[i][j] = 0;
			}
		}
	}
	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	fft_shift<float>(F.y, w, h);
	ifft2<float>(F.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F.y[i][j]);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Imagesrc.m_pBits[0][i][j] = value;
			m_Imagesrc.m_pBits[1][i][j] = value;
			m_Imagesrc.m_pBits[2][i][j] = value;
		}
	}

	m_Image.flag = 1;
	Invalidate(1);
}


void CImage_ProcessingView::OnHighpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float center_x, center_y;
	center_x = float(w) / 2;
	center_y = float(h) / 2;
	float D0 = 80;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float dis = pow(i - center_y, 2) + pow(j - center_x, 2);
			if (dis < pow(D0, 2))
			{
				F.y[i][j] = 0;
			}
		}
	}
	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	fft_shift<float>(F.y, w, h);
	ifft2<float>(F.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F.y[i][j]);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Imagesrc.m_pBits[0][i][j] = value;
			m_Imagesrc.m_pBits[1][i][j] = value;
			m_Imagesrc.m_pBits[2][i][j] = value;
		}
	}

	m_Image.flag = 1;
	Invalidate(1);
}


void CImage_ProcessingView::OnButterlowpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float center_x, center_y;
	center_x = float(w) / 2;
	center_y = float(h) / 2;
	float D0 = 1000;
	int order = 5;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float dis = pow(i - center_y, 2) + pow(j - center_x, 2);
			float H = 1 / (1 + pow(dis / D0, 2 * order));
			F.y[i][j] = F.y[i][j] * H;
		}
	}
	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	fft_shift<float>(F.y, w, h);
	ifft2<float>(F.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F.y[i][j]);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Imagesrc.m_pBits[0][i][j] = value;
			m_Imagesrc.m_pBits[1][i][j] = value;
			m_Imagesrc.m_pBits[2][i][j] = value;
		}
	}

	m_Image.flag = 1;
	Invalidate(1);
}


void CImage_ProcessingView::OnButterhighpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float center_x, center_y;
	center_x = float(w) / 2;
	center_y = float(h) / 2;
	float D0 = 1000;
	int order = 5;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float dis = pow(i - center_y, 2) + pow(j - center_x, 2);
			float H = 1 / (1 + pow(D0 / dis, 2 * order));
			F.y[i][j] = F.y[i][j] * H;
		}
	}
	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	fft_shift<float>(F.y, w, h);
	ifft2<float>(F.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F.y[i][j]);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Imagesrc.m_pBits[0][i][j] = value;
			m_Imagesrc.m_pBits[1][i][j] = value;
			m_Imagesrc.m_pBits[2][i][j] = value;
		}
	}

	m_Image.flag = 1;
	Invalidate(1);
}


void CImage_ProcessingView::OnGaussianlowpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float center_x, center_y;
	center_x = float(w) / 2;
	center_y = float(h) / 2;
	float D0 = 1000;
	int order = 5;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float dis = pow(i - center_y, 2) + pow(j - center_x, 2);
			float m = -pow(dis, 2) / (2 * pow(D0, 2));
			float e = E;
			float H = pow(e, m);
			F.y[i][j] = F.y[i][j] * H;
		}
	}
	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	fft_shift<float>(F.y, w, h);
	ifft2<float>(F.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F.y[i][j]);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Imagesrc.m_pBits[0][i][j] = value;
			m_Imagesrc.m_pBits[1][i][j] = value;
			m_Imagesrc.m_pBits[2][i][j] = value;
		}
	}

	m_Image.flag = 1;
	Invalidate(1);
}


void CImage_ProcessingView::OnGaussianhighpass()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获取高度和宽度
	int h = m_Image.GetHeight();
	if (!m_Imagesrc.IsNull()) m_Imagesrc.Destroy();
	m_Imagesrc.Load(filename);
	int bits = m_Image.GetBPP();
	if (w & w - 1 != 0 || h & h - 1 != 0) return;
	if (bits == 24 || bits == 32) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				int ave = 0.1140 *m_Image.m_pBits[0][i][j] + 0.5870 *m_Image.m_pBits[1][i][j] + 0.2989 *m_Image.m_pBits[2][i][j];
				m_Image.m_pBits[0][i][j] = ave;
				m_Image.m_pBits[1][i][j] = ave;
				m_Image.m_pBits[2][i][j] = ave;
			}
		}
	}
	complex_mat<float> F(w, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			F.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
			//F_ifft.y[i][j] = complex<float>(m_Image.m_pBits[0][i][j], 0);
		}
	}
	fft2<float>(F.y, w, h);//现在的F.y就是fft后的结果
	fft_shift<float>(F.y, w, h);

	float center_x, center_y;
	center_x = float(w) / 2;
	center_y = float(h) / 2;
	float D0 = 1000;
	int order = 5;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float dis = pow(i - center_y, 2) + pow(j - center_x, 2);
			float m = -pow(dis, 2) / (2 * pow(D0, 2));
			float e = E;
			float H = 1 - pow(e, m);
			F.y[i][j] = F.y[i][j] * H;
		}
	}
	float max = log(1 + abs(F.y[0][0]));
	float min = log(1 + abs(F.y[0][0]));
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			if (value > max) max = value;
			if (value < min) min = value;
		}
	}
	float inner = 0;
	inner = (max - min) / 255;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			float value = log(1 + abs(F.y[i][j]));
			value = float((value + min) / inner);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Image.m_pBits[0][i][j] = int(value);
			m_Image.m_pBits[1][i][j] = int(value);
			m_Image.m_pBits[2][i][j] = int(value);
		}
	}
	fft_shift<float>(F.y, w, h);
	ifft2<float>(F.y, w, h);

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int value = abs(F.y[i][j]);
			if (value > 255) value = 255;
			if (value < 0) value = 0;
			m_Imagesrc.m_pBits[0][i][j] = value;
			m_Imagesrc.m_pBits[1][i][j] = value;
			m_Imagesrc.m_pBits[2][i][j] = value;
		}
	}

	m_Image.flag = 1;
	Invalidate(1);
}

//生成高斯噪声
double CImage_ProcessingView::generateGaussianNoise(double mu, double sigma)
{
	//定义小值  
	const double epsilon = 0.00000001;
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flag为假构造高斯随机变量X  
	if (!flag)
		return z1 * sigma + mu;
	double u1, u2;
	//构造随机变量  
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flag为真构造高斯随机变量
	z0 = sqrt(-2.0*log(u1))*cos(2 * PI*u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * PI*u2);
	return z0 * sigma + mu;
	return mu;
}

void CImage_ProcessingView::OnAddimpulsenoise()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获得第一幅图像的宽度
	int h = m_Image.GetHeight();//获得第一幅图像的高度
	int n = 0.2*h*w;//盐噪声概率0.1
	for (int k = 0; k < n; k++)
	{
		//随机取值行列  
		int i = rand() % w;
		int j = rand() % h;
		m_Image.m_pBits[0][j][i] = 255;
		m_Image.m_pBits[1][j][i] = 255;
		m_Image.m_pBits[2][j][i] = 255;
	}
	int d = 0.2*h*w;
	for (int k = 0; k < d; k++)
	{
		//随机取值行列  
		int i = rand() % w;
		int j = rand() % h;
		m_Image.m_pBits[0][j][i] = 0;
		m_Image.m_pBits[1][j][i] = 0;
		m_Image.m_pBits[2][j][i] = 0;
	}

	Invalidate(1);
}


void CImage_ProcessingView::OnAddguaussiannoise()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获得第一幅图像的宽度
	int h = m_Image.GetHeight();//获得第一幅图像的高度
	int mean = 0;
	int var = 30;
	for (int j = 0; j < h; j++)
	{
		for (int i = 0; i < w; i++)
		{
			int val0 = m_Image.m_pBits[0][j][i] + generateGaussianNoise(mean, var);
			int val1 = m_Image.m_pBits[1][j][i] + generateGaussianNoise(mean, var);
			int val2 = m_Image.m_pBits[2][j][i] + generateGaussianNoise(mean, var);

			if (val0 < 0)
				val0 = 0;
			if (val0 > 255)
				val0 = 255;
			if (val1 < 0)
				val1 = 0;
			if (val1 > 255)
				val1 = 255;
			if (val2 < 0)
				val2 = 0;
			if (val2 > 255)
				val2 = 255;
			m_Image.m_pBits[0][j][i] = val0;
			m_Image.m_pBits[1][j][i] = val1;
			m_Image.m_pBits[2][j][i] = val2;
		}
	}
	Invalidate(1);
}


void CImage_ProcessingView::OnAdaptedmidfilter()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获得第一幅图像的宽度
	int h = m_Image.GetHeight();//获得第一幅图像的高度
	m_Imagesrc.Load(filename);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++)
		{
			m_Imagesrc.m_pBits[0][i][j] = m_Image.m_pBits[0][i][j];
			m_Imagesrc.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Imagesrc.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	int W_size = 11;//还需手动输入
	int size = 5;//初始窗口大小
	int min, max, med, A1, A2, B1, B2;
	int p[1024];
	int* arr = p;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			while(true)
			{
				for (int m = -size/2; m <= size / 2; m++)
				{
					for (int n = -size / 2; n <= size / 2; n++)
					{
						int value;
						if (i + m < 0) value = 0;
						else if (j + n < 0) value = 0;
						else if (i + m > h - 1) value = 0;
						else if (j + n > w - 1) value = 0;
						else value = m_Image.m_pBits[0][i + m][j + n];
						*arr = value;
						arr++;
					}
				}
				
				int nums = pow(size, 2);
				arr -= nums;
				sort(arr, arr + nums);
				med = arr[nums / 2 + 1];
				min = arr[0];
				max = arr[nums - 1];
				A1 = med - min;
				A2 = med - max;
				if (A1 > 0 && A2 < 0) {
					B1 = m_Image.m_pBits[0][i][j] - min;
					B2 = m_Image.m_pBits[0][i][j] - max;
					if (B1 > 0 && B2 < 0) {
						m_Imagesrc.m_pBits[0][i][j] = m_Image.m_pBits[0][i][j];
						m_Imagesrc.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
						m_Imagesrc.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
						break;
					}
					else {
						m_Imagesrc.m_pBits[0][i][j] = med;
						m_Imagesrc.m_pBits[1][i][j] = med;
						m_Imagesrc.m_pBits[2][i][j] = med;
						break;
					}
				}
				else {
					size += 2;
					if (size > W_size) {
						m_Imagesrc.m_pBits[0][i][j] = med;
						m_Imagesrc.m_pBits[1][i][j] = med;
						m_Imagesrc.m_pBits[2][i][j] = med;
						size = 5;
					break;
					}
				}
					
			}	
		}
	}
	m_Image.flag = 1;
	Invalidate(1);
}


void CImage_ProcessingView::OnShowrgb()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	m_Image_r.Load(filename);
	m_Image_g.Load(filename);
	m_Image_b.Load(filename);
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image_r.m_pBits[0][j][k] = 0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image_r.m_pBits[1][j][k] = 0;//G
		}
	}
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image_g.m_pBits[0][j][k] = 0;//B   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image_g.m_pBits[2][j][k] = 0;//R
		}
	}
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image_b.m_pBits[2][j][k] = 0;//R   用循环访问图像的像素值，将它的绿色分量和蓝色分量置为0，图像就只剩下红色分量了
			m_Image_b.m_pBits[1][j][k] = 0;//G
		}
	}
	m_Image.flag = 3;
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像

}


void CImage_ProcessingView::OnShowhsi()
{
	// TODO: 在此添加命令处理程序代码
	if (m_Image.IsNull()) return;//判断图像是否为空，如果对空图像进行操作会出现未知的错误
	int w = m_Image.GetWidth();//获得图像的宽度
	int h = m_Image.GetHeight();//获得图像的高度
	m_Imagesrc.Load(filename);
	m_Image_h.Load(filename);
	m_Image_s.Load(filename);
	m_Image_i.Load(filename);
	
	float theta, S, I, inner;
	inner = 255 / PI;
	int min, max;

	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			int R, G, B;
			R = m_Imagesrc.m_pBits[2][i][j];
			G = m_Imagesrc.m_pBits[1][i][j];
			B = m_Imagesrc.m_pBits[0][i][j];
			int minN = min(R, G);
			minN = min(minN, B);

			theta = 1 / 2 * (2 * R - G - B) / pow((pow((R - G), 2) + (R - B)*(G - B)), 1 / 2);
			theta = acos(theta);
			if (B <= G) m_Image_h.m_pBits[0][i][j] = m_Image_h.m_pBits[1][i][j] = m_Image_h.m_pBits[2][i][j] = int(theta * inner);
			else m_Image_h.m_pBits[0][i][j] = m_Image_h.m_pBits[1][i][j] = m_Image_h.m_pBits[2][i][j] = int((360 - theta) * inner);

			S = (1 - 3.0 / (R + G + B)*minN) * 255;
			m_Image_s.m_pBits[0][i][j] = m_Image_s.m_pBits[1][i][j] = m_Image_s.m_pBits[2][i][j] = S;

			I = float(R + G + B) / 3;
			m_Image_i.m_pBits[0][i][j] = m_Image_i.m_pBits[1][i][j] = m_Image_i.m_pBits[2][i][j] = I;
		}
	}
	m_Image.flag = 4;
	Invalidate(1); //强制调用ONDRAW函数，ONDRAW会绘制图像
}


void CImage_ProcessingView::OnEqualrgb()
{
	// TODO: 在此添加命令处理程序代码
}


void CImage_ProcessingView::OnEquali()
{
	// TODO: 在此添加命令处理程序代码
}
