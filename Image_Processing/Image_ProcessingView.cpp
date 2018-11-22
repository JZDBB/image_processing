
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
#include<cmath>
using namespace std;
#include "Image_ProcessingDoc.h"
#include "paintHistDialog.h"
#include "Image_ProcessingView.h"


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
	ON_COMMAND(ID_HISTNORM, &CImage_ProcessingView::OnHistnorm)
	ON_COMMAND(ID_HISTEQUAL, &CImage_ProcessingView::OnHistequal)
	ON_COMMAND(ID_MEANFILTER, &CImage_ProcessingView::OnMeanfilter)
	ON_COMMAND(ID_MIDFILTER, &CImage_ProcessingView::OnMidfilter)
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
		m_Image.Draw(pDC->m_hDC,0,0); 
	}
	return;
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
				/*if (j % 5 == 0 && k % 5 == 0)
				{
					for (int x = 0; x < 5; x++) 
					{
						for (int y = 0; y < 5; y++) 
						{
							try 
							{
								m_Image.m_pBits[c][j + x][k + y] = m_Image.m_pBits[c][j][k];
								throw 1;
								throw "error";
							}
							catch(char *str){}
						}
					}
					
				}*/
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

	int K = 4;
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
		{
			//strArrFilePaths.Add(dlg.GetNextPathName(pos));
			if (!m_Image2.IsNull())
				m_Image2.Destroy();
			m_Image2.Load(dlg.GetNextPathName(pos));
			if (m_Image2.IsNull())
				return;
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

	paintHistDialog dlg(this);//用一个CImage_ProcessingView的指针取初始化dlg
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistnorm()
{
	// TODO: 在此添加命令处理程序代码
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
			m_Image.m_pBits[0][i][j] = m_Image2.m_pBits[0][i - 1][j - 1] / 16 + m_Image2.m_pBits[0][i][j - 1] * 2 / 16 + m_Image2.m_pBits[0][i + 1][j - 1] / 16 + m_Image2.m_pBits[0][i - 1][j] * 2 / 16 + m_Image2.m_pBits[0][i][j] * 4 / 16 + m_Image2.m_pBits[0][i + 1][j] * 2 / 16 + m_Image2.m_pBits[0][i - 1][j + 1] / 16 + m_Image2.m_pBits[0][i][j + 1] * 2 / 16 + m_Image2.m_pBits[0][i + 1][j + 1] / 16;
			m_Image.m_pBits[1][i][j] = m_Image2.m_pBits[1][i - 1][j - 1] / 16 + m_Image2.m_pBits[1][i][j - 1] * 2 / 16 + m_Image2.m_pBits[1][i + 1][j - 1] / 16 + m_Image2.m_pBits[1][i - 1][j] * 2 / 16 + m_Image2.m_pBits[1][i][j] * 4 / 16 + m_Image2.m_pBits[1][i + 1][j] * 2 / 16 + m_Image2.m_pBits[1][i - 1][j + 1] / 16 + m_Image2.m_pBits[1][i][j + 1] * 2 / 16 + m_Image2.m_pBits[1][i + 1][j + 1] / 16;
			m_Image.m_pBits[2][i][j] = m_Image2.m_pBits[2][i - 1][j - 1] / 16 + m_Image2.m_pBits[2][i][j - 1] * 2 / 16 + m_Image2.m_pBits[2][i + 1][j - 1] / 16 + m_Image2.m_pBits[2][i - 1][j] * 2 / 16 + m_Image2.m_pBits[2][i][j] * 4 / 16 + m_Image2.m_pBits[2][i + 1][j] * 2 / 16 + m_Image2.m_pBits[2][i - 1][j + 1] / 16 + m_Image2.m_pBits[2][i][j + 1] * 2 / 16 + m_Image2.m_pBits[2][i + 1][j + 1] / 16;
		}
	}
	Invalidate(1);
}
