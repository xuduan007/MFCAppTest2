// CountDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "CountDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCountDialog 对话框

CCountDialog::CCountDialog(int nCount, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_COUNT_DIALOG, pParent), m_nCount(nCount)
{
}

CCountDialog::~CCountDialog()
{
}

void CCountDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	// 设置计数显示
	CString strCount;
	strCount.Format(_T("%d"), m_nCount);
	SetDlgItemText(IDC_STATIC_COUNT, strCount);
}

BEGIN_MESSAGE_MAP(CCountDialog, CDialogEx)
END_MESSAGE_MAP()

// CCountDialog 消息处理程序
