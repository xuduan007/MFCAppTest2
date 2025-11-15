// RandomNumberDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "RandomNumberDialog.h"
#include "afxdialogex.h"
#include <cstdlib>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CRandomNumberDialog 对话框

CRandomNumberDialog::CRandomNumberDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_RANDOM_NUMBER_DIALOG, pParent)
{
}

void CRandomNumberDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CRandomNumberDialog, CDialogEx)
END_MESSAGE_MAP()

// CRandomNumberDialog 消息处理程序

BOOL CRandomNumberDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 生成6位随机数
    srand((unsigned)time(NULL));
    int randomNumber = rand() % 900000 + 100000;
    CString strRandom;
    strRandom.Format(_T("%d"), randomNumber);

    // 在静态文本控件中显示随机数
    SetDlgItemText(IDC_STATIC_RANDOM_NUMBER, strRandom);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}