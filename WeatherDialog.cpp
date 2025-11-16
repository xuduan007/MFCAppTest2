// WeatherDialog.cpp: 实现文件
//

#include "pch.h"
#include "WeatherDialog.h"
#include "resource.h"
#include "afxdialogex.h"


// CWeatherDialog 对话框

IMPLEMENT_DYNAMIC(CWeatherDialog, CDialogEx)

CWeatherDialog::CWeatherDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_WEATHER_DIALOG, pParent)
    , m_strWeatherInfo(_T(""))
{

}

CWeatherDialog::~CWeatherDialog()
{
}

void CWeatherDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_WEATHER_INFO, m_strWeatherInfo);
}

BEGIN_MESSAGE_MAP(CWeatherDialog, CDialogEx)
END_MESSAGE_MAP()


// CWeatherDialog 消息处理程序

BOOL CWeatherDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetDlgItemText(IDC_STATIC_WEATHER_INFO, m_strWeatherInfo);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}
