// OSInfoDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "OSInfoDialog.h"
#include "afxdialogex.h"
#include <Windows.h>
#include <VersionHelpers.h>

IMPLEMENT_DYNAMIC(COSInfoDialog, CDialogEx)

COSInfoDialog::COSInfoDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OS_INFO_DIALOG, pParent)
{
}

COSInfoDialog::~COSInfoDialog()
{
}

void COSInfoDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_STATIC_OS_INFO, m_strOSInfo);
}

BEGIN_MESSAGE_MAP(COSInfoDialog, CDialogEx)
END_MESSAGE_MAP()

// COSInfoDialog 消息处理程序

BOOL COSInfoDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置对话框标题
    SetWindowText(_T("操作系统信息"));

    // 获取操作系统信息
    OSVERSIONINFOEX osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    CString strOSInfo;

#pragma warning(push)
#pragma warning(disable: 4996) // 禁用GetVersionExW弃用警告
    if (GetVersionExW(reinterpret_cast<OSVERSIONINFOW*>(&osvi)))
    {
#pragma warning(pop)
        if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0)
        {
            if (osvi.dwBuildNumber >= 22000)
                strOSInfo = _T("Windows 11");
            else
                strOSInfo = _T("Windows 10");
        }
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3)
        {
            strOSInfo = _T("Windows 8.1");
        }
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
        {
            strOSInfo = _T("Windows 8");
        }
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
        {
            strOSInfo = _T("Windows 7");
        }
        else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
        {
            strOSInfo = _T("Windows Vista");
        }
        else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
        {
            strOSInfo = _T("Windows Server 2003 / Windows XP x64 Edition");
        }
        else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
        {
            strOSInfo = _T("Windows XP");
        }
        else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
        {
            strOSInfo = _T("Windows 2000");
        }
        else
        {
            strOSInfo.Format(_T("未知操作系统版本: %d.%d"), osvi.dwMajorVersion, osvi.dwMinorVersion);
        }

        // 构建完整的操作系统信息
        m_strOSInfo = _T("操作系统: ") + strOSInfo + _T("\n");
        m_strOSInfo += _T("版本: ") + CString(osvi.szCSDVersion) + _T("\n");
        CString strBuildNumber;
        strBuildNumber.Format(_T("%d"), osvi.dwBuildNumber);
        m_strOSInfo += _T("内部版本号: ") + strBuildNumber + _T("\n");
        m_strOSInfo += _T("平台: ") + CString((osvi.dwPlatformId == VER_PLATFORM_WIN32_NT ? _T("Win32 NT") : _T("其他")));
    }
    else
    {
        m_strOSInfo = _T("无法获取操作系统信息");
    }

    // 设置静态文本框内容
    SetDlgItemText(IDC_STATIC_OS_INFO, m_strOSInfo);

    return TRUE;
}
