// WindowSizeDialog.cpp: 实现文件
//

#include "stdafx.h"
#include "Image_Processing.h"
#include "WindowSizeDialog.h"
#include "afxdialogex.h"


// WindowSizeDialog 对话框

IMPLEMENT_DYNAMIC(WindowSizeDialog, CDialogEx)

WindowSizeDialog::WindowSizeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOGSIZE, pParent)
{

}

WindowSizeDialog::~WindowSizeDialog()
{
}

void WindowSizeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WindowSizeDialog, CDialogEx)
END_MESSAGE_MAP()


// WindowSizeDialog 消息处理程序
