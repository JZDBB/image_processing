
// Image_ProcessingView.cpp : CImage_ProcessingView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CImage_ProcessingView ����/����

CImage_ProcessingView::CImage_ProcessingView()
{
	// TODO: �ڴ˴���ӹ������

}


CImage_ProcessingView::~CImage_ProcessingView()
{
}

BOOL CImage_ProcessingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CScrollView::PreCreateWindow(cs);
}

// CImage_ProcessingView ����

void CImage_ProcessingView::OnDraw(CDC* pDC)
{
	CImage_ProcessingDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
	// TODO: �������ͼ�ĺϼƴ�С
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImage_ProcessingView ��ӡ


void CImage_ProcessingView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImage_ProcessingView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CImage_ProcessingView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CImage_ProcessingView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CImage_ProcessingView ���

#ifdef _DEBUG
void CImage_ProcessingView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImage_ProcessingView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImage_ProcessingDoc* CImage_ProcessingView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImage_ProcessingDoc)));
	return (CImage_ProcessingDoc*)m_pDocument;
}
#endif //_DEBUG


// CImage_ProcessingView ��Ϣ�������


void CImage_ProcessingView::OnFileOpen()
{
	// TODO: �ڴ���������������
	CFileDialog dlg(TRUE);    //Ϊ���ļ�����һ������
	if(IDOK == dlg.DoModal())    //���ú�����һ���Ի��򣬲��ж��Ƿ�򿪳ɹ�
	{
		if(!m_Image.IsNull()) m_Image.Destroy();//�ж��Ƿ��Ѿ���ͼƬ���еĻ��������
		filename = dlg.GetPathName();
		m_Image.Load(filename);//���ͼƬ�ĵ�ַ�����Ҽ���ͼƬ

		//���ͼƬ�Ĵ�С���������С���ù������ĳ�ʼ���ڴ�С�Ȳ���
		CSize sizeTotal;
		int w=m_Image.GetWidth();
		int h=m_Image.GetHeight();
		sizeTotal.cx =w;
		sizeTotal.cy =h;
		SetScrollSizes(MM_TEXT, sizeTotal);

		//Window_Image_w=m_Image.GetWidth();//���ͼƬ�ĳ�ʼ��С��Ϊ�Ŵ���С������׼��
		//Window_Image_h=m_Image.GetHeight();//


		Invalidate(1); //ǿ�Ƶ���ONDRAW����
	}
}


void CImage_ProcessingView::OnDrawline()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) return;
	
	int w=m_Image.GetWidth();
	int h=m_Image.GetHeight();

	for (int k=0;k<w;k++)
	{
		m_Image.m_pBits[0][10][k]=0;//B
		m_Image.m_pBits[1][10][k]=0;//G
		m_Image.m_pBits[2][10][k]=0;//R

	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW����

}


void CImage_ProcessingView::OnFileSaveAs()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) {
		MessageBox(_T("�㻹û�д�һ��Ҫ�����ͼ���ļ���"));
		return;
	}
	CString strFilter;
	//strFilter ="λͼ�ļ�|*.bmp|JPEG ͼ���ļ�|*.jpg|GIF ͼ���ļ�|*.gif|PNG ͼ���ļ�|*.png||";   //
	strFilter ="�����ļ�|*.*||";   //

	CFileDialog dlg(FALSE,NULL,NULL,NULL,strFilter);
	//CFileDialog dlg(FALSE,NULL,NULL,NULL);

	if ( IDOK != dlg.DoModal()) 
		return;
	// ����û�û��ָ���ļ���չ������Ϊ�����һ��
	CString strFileName;
	//CString strExtension;
	strFileName = dlg.m_ofn.lpstrFile;   //  ����ļ���
	//if(dlg.m_ofn.nFileExtension == 0)     //����ļ���չ��
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
	// ͼ�񱣴�
	HRESULT hResult = m_Image.Save(strFileName);
	if (FAILED(hResult))
	{
		MessageBox(_T("����ͼ���ļ�ʧ�ܣ�"));
	}

}


void CImage_ProcessingView::OnShowred()
{
	// TODO: �ڴ���������������
	if(m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w=m_Image.GetWidth();//���ͼ��Ŀ��
	int h=m_Image.GetHeight();//���ͼ��ĸ߶�
	for (int j=0;j<h;j++)
	{
		for (int k=0;k<w;k++)
		{
			m_Image.m_pBits[0][j][k]=0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image.m_pBits[1][j][k]=0;//G
		}
	}

	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::OnResolution()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�

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
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::OnGraychange()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�

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
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::OnDiff()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	MyImage_ m_Image2;
	CFileDialog dlg(TRUE);//ͬ���Ǵ�һ���µĶԻ��򣬴洢�������ͼƬ
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	int bits = m_Image.GetBPP();
	int hierarchical = 2;

	MyImage_ m_Image2;
	CFileDialog dlg(TRUE);//ͬ���Ǵ�һ���µĶԻ��򣬴洢�������ͼƬ
	dlg.m_ofn.Flags |= OFN_ALLOWMULTISELECT;//����ѡ�����ļ�

	dlg.m_ofn.nMaxFile = 20 * 101;//�����Դ�20���ļ���ÿ���ļ������ַ���<=100

	const DWORD numberOfFileNames = 32;//�������32���ļ�
	const DWORD fileNameMaxLength = MAX_PATH + 1;
	const DWORD bufferSize = (numberOfFileNames * fileNameMaxLength) + 1;
	TCHAR* filenamesBuffer = new TCHAR[bufferSize];
	// Initialize beginning and end of buffer.
	filenamesBuffer[0] = NULL;//�����
	filenamesBuffer[bufferSize - 1] = NULL;

	// Attach buffer to OPENFILENAME member.
	dlg.m_ofn.lpstrFile = filenamesBuffer;
	dlg.m_ofn.nMaxFile = bufferSize;

	CStringArray strArrFilePaths;
	if (dlg.DoModal() == IDOK)
	{
		int k = 0;
		POSITION pos = dlg.GetStartPosition();//��ȡ��һ���ļ�����λ��
		while (pos != NULL) //GetNextPathName()���ص�ǰpos���ļ�����������һ���ļ�����λ�ñ��浽pos��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�

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

	paintHistDialog dlg(this);//��һ��CImage_ProcessingView��ָ��ȡ��ʼ��dlg
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistequal()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
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

	paintHistDialog dlg(this);//��һ��CImage_ProcessingView��ָ��ȡ��ʼ��dlg
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistnorm()
{
	// TODO: �ڴ���������������
}


void CImage_ProcessingView::OnMeanfilter()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���

	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
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
