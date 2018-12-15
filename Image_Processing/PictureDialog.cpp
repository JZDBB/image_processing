// PictureDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "PictureDialog.h"
#include "afxdialogex.h"


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
	ON_STN_CLICKED(IDC_PIC, &PictureDialog::OnStnClickedPic)
	ON_BN_CLICKED(IDC_BUTTON1, &PictureDialog::OnBnClickedButton1)
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


void PictureDialog::OnStnClickedPic()
{
	// TODO: 在此添加控件通知处理程序代码
	
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
			CRect rect;
			pWnd->GetClientRect(&rect); //获得pictrue控件所在的矩形区域
			CDC *pDC = pWnd->GetDC(); //获得pictrue控件的DC
			pDC->SetStretchBltMode(COLORONCOLOR);
			StretchDIBits(pDC->GetSafeHdc(), 0, 0, rect.Width(), rect.Height(), 0, 0,
				bmpInfo.biWidth, bmpInfo.biHeight, pBmpData, pBmpInfo, DIB_RGB_COLORS, SRCCOPY);
		}
	}
}
