// StatisticsDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "StatisticsDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStatisticsDialog 对话框


CStatisticsDialog::CStatisticsDialog(int nTotalCount, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STATISTICS_DIALOG, pParent)
	, m_nTotalCount(nTotalCount)
{
}

void CStatisticsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CStatisticsDialog, CDialogEx)
END_MESSAGE_MAP()


// CStatisticsDialog 消息处理程序


BOOL CStatisticsDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置统计信息
	CString strCount;
	strCount.Format(_T("%d"), m_nTotalCount);
	SetDlgItemText(IDC_STATIC_COUNT, strCount);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
