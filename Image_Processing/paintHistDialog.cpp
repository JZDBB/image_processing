// paintHistDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "Image_ProcessingView.h"
#include"Image_ProcessingDoc.h"
#include "paintHistDialog.h"
#include "afxdialogex.h"


// paintHistDialog 对话框

IMPLEMENT_DYNAMIC(paintHistDialog, CDialogEx)

paintHistDialog::paintHistDialog(CImage_ProcessingView* pParent)
	: CDialogEx(IDD_DIALOGHIST, pParent)
	, pWnd(NULL)
	, pDC(NULL)
	, pv(NULL)	
{
	pv = pParent;
}


paintHistDialog::~paintHistDialog()
{
}

void paintHistDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(paintHistDialog, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// paintHistDialog 消息处理程序

BOOL paintHistDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pWnd = GetDlgItem(IDC_STATIC);//静态文本框的句柄

	pDC = pWnd->GetDC();//获取DC

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void paintHistDialog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	if (pv->m_Image.IsNull()) return;
	int w = pv->m_Image.GetWidth();
	int h = pv->m_Image.GetHeight();

	//使static控件区域无效
	pWnd->Invalidate();
	//更新窗口, 此时才真正向系统发送重绘消息, 
	pWnd->UpdateWindow();

	float M = 0, N;
	for (int i = 0; i < 256; i++)
	{
		if (pv->m_Image.hist[0][i] > M)
		{
			M = pv->m_Image.hist[0][i];
		}
	}
	N = 350 / M;//归一化：将最大值归一到坐标显示的最大值
	SetBkMode(*pDC, TRANSPARENT); //无背景填充

	pDC->MoveTo(110 / 2, 700 / 2);
	pDC->LineTo(1200 / 2, 700 / 2);//绘制横坐标轴

	pDC->MoveTo(1185 / 2, 690 / 2);//箭头下半部分
	pDC->LineTo(1200 / 2, 700 / 2);
	pDC->MoveTo(1185 / 2, 710 / 2);//箭头上半部分
	pDC->LineTo(1200 / 2, 700 / 2);//绘制箭头

	char ch[5];
	CString ch2;//不能重复定义
	for (int i = 0; i < 256; i += 15)
	{
		_itoa_s(i, ch, 10);
		ch2 = ch;
		pDC->TextOut(110 / 2 + i * 2, 710 / 2, ch2);//绘制横坐标标尺
	}

	CString str("灰度值");
	pDC->TextOut(1190 / 2, 710 / 2, str);//横坐标文字标志
	pDC->MoveTo(110 / 2, 700 / 2);
	pDC->LineTo(110 / 2, 0);//绘制纵坐标轴

	pDC->MoveTo(110 / 2, 0);
	pDC->LineTo(100 / 2, 15 / 2);
	pDC->MoveTo(110 / 2, 0);
	pDC->LineTo(120 / 2, 15 / 2);//绘制箭头

	float ii = 1;
	CString ch3;
	CString ch4("%");
	for (int i = 0; i < 700 / 2; i += 80 / 2)
	{
		ii = i / N * 100;
		ch3.Format(_T("%.3f"), ii);

		ch3 = ch3 + ch4;
		if (i != 0)
		{
			pDC->TextOut(5 / 2, 700 / 2 - i, ch3);//绘制纵坐标标尺
		}
	}

	str = "概率";
	pDC->TextOut(40 / 2, 10 / 2, str);//纵坐标文字标志
	
	CPen pen(PS_SOLID, 1, RGB(0, 0, 255));
	CPen *pOldPen = pDC->SelectObject(&pen);//选择自定义颜色画笔
											//pDC->SelectObject(pOldPen);//恢复颜色选择
	for (int i = 0; i < 256; i++)
	{
		pDC->MoveTo(i * 2 + 110 / 2, 700 / 2);
		pDC->LineTo(i * 2 + 110 / 2, 700 / 2 - N * pv->m_Image.hist[0][i]);
		pDC->MoveTo(i * 2 + 1 + 110 / 2, 700 / 2);
		pDC->LineTo(i * 2 + 1 + 110 / 2, 700 / 2 - N * pv->m_Image.hist[0][i]);

	}
}
