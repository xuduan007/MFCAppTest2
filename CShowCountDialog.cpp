// CShowCountDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "CShowCountDialog.h"
#include "CShapeDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShowCountDialog 对话框

CShowCountDialog::CShowCountDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_COUNT_DIALOG, pParent)
{
}

void CShowCountDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShowCountDialog, CDialogEx)
END_MESSAGE_MAP()

BOOL CShowCountDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 更新显示总变化次数
    CString strCount;
    strCount.Format(_T("总变化次数: %d"), CShapeDialog::m_nTotalChanges);
    SetDlgItemText(IDC_STATIC_COUNT, strCount);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
