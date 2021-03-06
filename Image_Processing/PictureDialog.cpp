// PictureDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PictureDialog.h"
//#include "CvvImage.h"
//#include <opencv2\opencv.hpp>
//#include <opencv2\core\core.hpp>
//#include <opencv2\highgui\highgui.hpp>
//#include <opencv2\imgproc\imgproc.hpp>
//#include <opencv2\objdetect\objdetect.hpp>
//#include <opencv2\imgproc\types_c.h>
//#include <opencv2\objdetect\objdetect_c.h>
#include "MyImage_.h"

//using namespace cv;

// PictureDialog 对话框

IMPLEMENT_DYNAMIC(PictureDialog, CDialogEx)

PictureDialog::PictureDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGPIC, pParent)
{

}

PictureDialog::~PictureDialog()
{
}

void PictureDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PictureDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &PictureDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &PictureDialog::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &PictureDialog::OnBnClickedButton1)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// PictureDialog 消息处理程序

void PictureDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void PictureDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void PictureDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter = "所有文件(*.bmp,*.jpg,*.gif,*tiff)|*.bmp;*.jpg;*.gif;*.tiff| BMP(*.bmp)|*.bmp| JPG(*.jpg)|*.jpg| GIF(*.gif)|*.gif| TIFF(*.tiff)|*.tiff||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filter, NULL);

	//按下确定按钮 dlg.DoModal() 函数显示对话框
	if (dlg.DoModal() == IDOK)
	{
		//打开对话框获取图像信息
		CString BmpName1 = dlg.GetPathName();     //获取文件路径名   如D:\pic\abc.bmp
		CString EntName = dlg.GetFileExt();      //获取文件扩展名
		EntName.MakeLower();                     //将文件扩展名转换为一个小写字符
		
		if (EntName.Compare(_T("bmp")) == 0)
		{
			//定义变量存储图片信息
			BITMAPINFO *pBmpInfo;       //记录图像细节
			BYTE *pBmpData;             //图像数据
			BITMAPFILEHEADER bmpHeader; //文件头
			BITMAPINFOHEADER bmpInfo;   //信息头
			CFile bmpFile;              //记录打开文件
			m_Image.Load(BmpName1);
			//以只读的方式打开文件 读取bmp图片各部分 bmp文件头 信息 数据
			if (!bmpFile.Open(BmpName1, CFile::modeRead | CFile::typeBinary))
				return;
			if (bmpFile.Read(&bmpHeader, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER))
				return;
			if (bmpFile.Read(&bmpInfo, sizeof(BITMAPINFOHEADER)) != sizeof(BITMAPINFOHEADER))
				return;
			pBmpInfo = (BITMAPINFO *)new char[sizeof(BITMAPINFOHEADER)];
			//为图像数据申请空间
			memcpy(pBmpInfo, &bmpInfo, sizeof(BITMAPINFOHEADER));
			DWORD dataBytes = bmpHeader.bfSize - bmpHeader.bfOffBits;
			pBmpData = (BYTE*)new char[dataBytes];
			bmpFile.Read(pBmpData, dataBytes);
			bmpFile.Close();
			
			//显示图像
			CWnd *pWnd = GetDlgItem(IDC_PIC); //获得pictrue控件窗口的句柄
			//CRect rect;
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
			CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
				bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
			flag = true;
		}
	}
}



void PictureDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PIC);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);

	//先获取鼠标相对于屏幕的坐标
	GetCursorPos(&point);
	int temp_x = point.x;
	int temp_y = point.y;
	//然后得到static控件的rect坐标
	CRect pRect;
	pWnd->GetClientRect(&pRect);
	//最后把当前鼠标的坐标转化为相对于rect的坐标
	pWnd->ScreenToClient(&point);
	int x = point.x;
	int y = point.y;

	int width = m_Image.GetWidth();
	int height = m_Image.GetHeight();
	int w = rect.Width();
	int h = rect.Height();

	x = x * width / w;
	y = y * height / h;

	if (flag) {
		CString txt_show;
		CString str;
		str.Format(_T("(%d, %d)"), x, y);
		txt_show.Format(str);
		SetDlgItemText(IDC_EDITSTART, txt_show);
		m_startPoint.x = x;
		m_startPoint.y = y;
		flag = false;
	}
	else{
		CString txt_show;
		CString str;
		str.Format(_T("(%d, %d)"), x, y);
		txt_show.Format(str);
		SetDlgItemText(IDC_EDITEND, txt_show);
		m_endPoint.x = x;
		m_endPoint.y = y;
		flag = true;
	}


	/*if (rect.PtInRect(point))
	{
		ClipCursor(&rect);
		rect_width = rect.right - rect.left;
		rect_height = rect.bottom - rect.top;
		int cols = m_Image.GetHeight();
		int rows = m_Image.GetWidth();
		xscale = cols / rect_width;
		yscale = rows / rect_height;

		m_startPoint.x = (point.x - rect.left) * xscale;
		m_startPoint.y = (point.y - rect.top) * yscale;
		int x = m_startPoint.x;
		int y = m_startPoint.y;
		CString txt_show;
		CString str;
		str = x + ", " + y;
		txt_show.Format(str); SetDlgItemText(IDC_EDITSTART, txt_show);
		move_flag = true;
	}*/

	CDialogEx::OnLButtonDown(nFlags, point);
}


//void PictureDialog::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if (up_flag)
//	{
//		GetCursorPos(&point);
//		GetDlgItem(IDC_PIC)->GetWindowRect(&rect);
//		if (rect.PtInRect(point))
//		{
//			ClipCursor(NULL);
//			rect_width = rect.right - rect.left;
//			rect_height = rect.bottom - rect.top;
//
//			m_endPoint.x = (point.x - rect.left) * xscale;
//			m_endPoint.y = (point.y - rect.top) * yscale;
//
//			int x = m_endPoint.x;
//			int y = m_endPoint.y;
//			CString txt_show;
//			CString str;
//			str = x + ", " + y;
//			txt_show.Format(str); SetDlgItemText(IDC_EDITEND, txt_show);
//		}
//	}
//	up_flag = false;
//
//	/*ROIrect.x = m_startPoint.x;
//	ROIrect.y = m_startPoint.y;
//	ROIrect.width = m_endPoint.x - m_startPoint.x;
//	ROIrect.height = m_endPoint.y - m_startPoint.y;
//
//	rectangle(m_tmpGray, ROIrect, Scalar(0, 255, 0));
//	DrawImgToHDC(m_tmpGray, IDC_PIC);
//
//	ROI = m_repairImg(ROIrect);*/
//
//	CDialogEx::OnLButtonUp(nFlags, point);
//}
//
//
//void PictureDialog::OnMouseMove(UINT nFlags, CPoint point)
//{
//	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	if (move_flag)
//	{
//		GetCursorPos(&point);
//		GetDlgItem(IDC_PIC)->GetWindowRect(&rect);
//		if (rect.PtInRect(point))
//		{
//			rect_width = rect.right - rect.left;
//			rect_height = rect.bottom - rect.top;
//			m_endPoint.x = (point.x - rect.left) * xscale;
//			m_endPoint.y = (point.y - rect.top) * yscale;
//		}
//		move_flag = false;
//	}
//
//	up_flag = true;
//
//	CDialogEx::OnMouseMove(nFlags, point);
//}
