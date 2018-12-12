
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

		if (m_Image.flag == 2)//��ʾ������ĶԱ�
		{
			m_Image.Draw(pDC->m_hDC, 0, 0);
			image2.Draw(pDC->m_hDC, m_Image.GetWidth(), 0);
		}

		else if (m_Image.flag == 1)//�Ա�ԭͼ
		{
			m_Image.Draw(pDC->m_hDC, 0, 0);
			m_Imagesrc.Draw(pDC->m_hDC, m_Image.GetWidth(), 0);
		}

		else if (m_Image.flag == 0)//ֻ��ʾԭͼ
		{
			m_Image.Draw(pDC->m_hDC, 0, 0);
		}
		else if (m_Image.flag == 3)//�Ա�ԭͼ
		{
			m_Image_r.Draw(pDC->m_hDC, 0, 0);
			m_Image_g.Draw(pDC->m_hDC, m_Image_r.GetWidth(), 0);
			m_Image_b.Draw(pDC->m_hDC, m_Image_r.GetWidth() + m_Image_g.GetWidth(), 0);
		}
		else if (m_Image.flag == 4)//�Ա�ԭͼ
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

	//// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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
		m_Image.flag = 0;
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

	int K = 2; //�Ҷȷֱ��ʵȼ�
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
		{//�������Ӷ��ͼƬ
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
	/*m_Image.histEqual();*/

	float s[256] = { 0 };//����
	int hist_equal[256] = { 0 };//�����

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

	paintHistDialog dlg(this);//��һ��CImage_ProcessingView��ָ��ȡ��ʼ��dlg
	dlg.DoModal();

	Invalidate(1);
}


void CImage_ProcessingView::OnHistmatch()
{
	// TODO: �ڴ���������������
	MyImage_ m_Image_Match;
	CFileDialog dlg(TRUE);//ͬ���Ǵ�һ���µĶԻ��򣬴洢�������ͼƬ
	if (IDOK == dlg.DoModal())
	{
		if (!m_Image_Match.IsNull())
			m_Image_Match.Destroy();
		m_Image_Match.Load(dlg.GetPathName());
		if (m_Image_Match.IsNull())
			return;

		int w = m_Image_Match.GetWidth();//���ͼ��Ŀ��
		int h = m_Image_Match.GetHeight();//���ͼ��ĸ߶�
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
		
		if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
		int w0 = w;
		int h0 = h;
		w = m_Image.GetWidth();//���ͼ��Ŀ��
		h = m_Image.GetHeight();//���ͼ��ĸ߶�
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

		paintHistDialog dlg1(this);//��һ��CImage_ProcessingView��ָ��ȡ��ʼ��dlg
		dlg1.DoModal();

		Invalidate(1);
	}
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) //�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	{
		OnFileOpen();
		//_T("���ȴ�һ��ͼ��"));
		return;
	}
	UpdateData();//��ñ༭���û����������

	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в�������ִ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
	int h = m_Image.GetHeight();

	float p_a = 0.15;//��ȡ������ĸ���,p_a(��),p_b���ף�
	float p_b = 0.08;


	float P_Sum = p_a + p_b;
	float xishu = 1 / P_Sum;
	float p_a_1 = p_a*xishu;
	for (int i = 0; i <w; i++)
		for (int j = 0; j <h; j++)
		{
			if (rand() / 32767.0<P_Sum)//ָ������rand()��������Ľ���1-32767����
			{
				if (rand() / 32767.0<p_a_1)
				{
					m_Image.m_pBits[0][j][i] = 1;         //�����ص���ʾΪ��ɫ
					m_Image.m_pBits[1][j][i] = 1;
					m_Image.m_pBits[2][j][i] = 1;

				}
				else
				{
					m_Image.m_pBits[0][j][i] = 255;         //�����ص���ʾΪ��ɫ
					m_Image.m_pBits[1][j][i] = 255;
					m_Image.m_pBits[2][j][i] = 255;
				}

			}
		}
	Invalidate(1);
}


void CImage_ProcessingView::OnTransformfft()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��ȡ�߶ȺͿ��
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
	fft2<float>(F.y, w, h);//���ڵ�F.y����fft��Ľ��
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

//���ɸ�˹����
double CImage_ProcessingView::generateGaussianNoise(double mu, double sigma)
{
	//����Сֵ  
	const double epsilon = 0.00000001;
	static double z0, z1;
	static bool flag = false;
	flag = !flag;
	//flagΪ�ٹ����˹�������X  
	if (!flag)
		return z1 * sigma + mu;
	double u1, u2;
	//�����������  
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);
	} while (u1 <= epsilon);
	//flagΪ�湹���˹�������
	z0 = sqrt(-2.0*log(u1))*cos(2 * PI*u2);
	z1 = sqrt(-2.0*log(u1))*sin(2 * PI*u2);
	return z0 * sigma + mu;
	return mu;
}

void CImage_ProcessingView::OnAddimpulsenoise()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��õ�һ��ͼ��Ŀ��
	int h = m_Image.GetHeight();//��õ�һ��ͼ��ĸ߶�
	int n = 0.2*h*w;//����������0.1
	for (int k = 0; k < n; k++)
	{
		//���ȡֵ����  
		int i = rand() % w;
		int j = rand() % h;
		m_Image.m_pBits[0][j][i] = 255;
		m_Image.m_pBits[1][j][i] = 255;
		m_Image.m_pBits[2][j][i] = 255;
	}
	int d = 0.2*h*w;
	for (int k = 0; k < d; k++)
	{
		//���ȡֵ����  
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��õ�һ��ͼ��Ŀ��
	int h = m_Image.GetHeight();//��õ�һ��ͼ��ĸ߶�
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//��õ�һ��ͼ��Ŀ��
	int h = m_Image.GetHeight();//��õ�һ��ͼ��ĸ߶�
	m_Imagesrc.Load(filename);
	for (int i = 0; i < h; i++){
		for (int j = 0; j < w; j++)
		{
			m_Imagesrc.m_pBits[0][i][j] = m_Image.m_pBits[0][i][j];
			m_Imagesrc.m_pBits[1][i][j] = m_Image.m_pBits[0][i][j];
			m_Imagesrc.m_pBits[2][i][j] = m_Image.m_pBits[0][i][j];
		}
	}
	int W_size = 11;//�����ֶ�����
	int size = 5;//��ʼ���ڴ�С
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
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
	m_Image_r.Load(filename);
	m_Image_g.Load(filename);
	m_Image_b.Load(filename);
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image_r.m_pBits[0][j][k] = 0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image_r.m_pBits[1][j][k] = 0;//G
		}
	}
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image_g.m_pBits[0][j][k] = 0;//B   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image_g.m_pBits[2][j][k] = 0;//R
		}
	}
	for (int j = 0; j < h; j++)
	{
		for (int k = 0; k < w; k++)
		{
			m_Image_b.m_pBits[2][j][k] = 0;//R   ��ѭ������ͼ�������ֵ����������ɫ��������ɫ������Ϊ0��ͼ���ֻʣ�º�ɫ������
			m_Image_b.m_pBits[1][j][k] = 0;//G
		}
	}
	m_Image.flag = 3;
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��

}


void CImage_ProcessingView::OnShowhsi()
{
	// TODO: �ڴ���������������
	if (m_Image.IsNull()) return;//�ж�ͼ���Ƿ�Ϊ�գ�����Կ�ͼ����в��������δ֪�Ĵ���
	int w = m_Image.GetWidth();//���ͼ��Ŀ��
	int h = m_Image.GetHeight();//���ͼ��ĸ߶�
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
	Invalidate(1); //ǿ�Ƶ���ONDRAW������ONDRAW�����ͼ��
}


void CImage_ProcessingView::OnEqualrgb()
{
	// TODO: �ڴ���������������
}


void CImage_ProcessingView::OnEquali()
{
	// TODO: �ڴ���������������
}
