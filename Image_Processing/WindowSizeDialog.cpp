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
	ON_EN_CHANGE(IDC_EDITSIZE, &WindowSizeDialog::OnEnChangeEditsize)
	ON_BN_CLICKED(IDOK, &WindowSizeDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// WindowSizeDialog 消息处理程序

BOOL WindowSizeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pWnd = GetDlgItem(IDC_EDITSIZE);//静态文本框的句柄
	pDC = pWnd->GetDC();//获取DC

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void WindowSizeDialog::OnEnChangeEditsize()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void WindowSizeDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();

	GetDlgItem(IDC_EDITSIZE)->GetWindowText(str);
	//MessageBox(str);
}
