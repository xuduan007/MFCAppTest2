// CShapeDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "CShapeDialog.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShapeDialog 对话框

int CShapeDialog::m_nTotalChanges = 0;

CShapeDialog::CShapeDialog(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_SHAPE_DIALOG, pParent)
{
    m_nChangeCount = 0;
}

void CShapeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShapeDialog, CDialogEx)
    ON_WM_PAINT()
    ON_WM_TIMER()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDOK, &CShapeDialog::OnOK)
END_MESSAGE_MAP()

BOOL CShapeDialog::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置初始四边形的四个顶点
    CRect rect;
    GetClientRect(&rect);
    int cx = rect.Width();
    int cy = rect.Height();

    // 初始四边形为中心的矩形
    m_initialPoints[0] = { cx / 2 - 50, cy / 2 - 50 };
    m_initialPoints[1] = { cx / 2 + 50, cy / 2 - 50 };
    m_initialPoints[2] = { cx / 2 + 50, cy / 2 + 50 };
    m_initialPoints[3] = { cx / 2 - 50, cy / 2 + 50 };

    // 复制初始点到当前点
    for (int i = 0; i < 4; i++)
    {
        m_points[i] = m_initialPoints[i];
    }

    // 设置定时器，每秒触发一次
    SetTimer(1, 1000, nullptr);

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShapeDialog::OnPaint()
{
    CPaintDC dc(this); // 用于绘制的设备上下文
    CDialogEx::OnPaint();

    // 绘制四边形
    dc.Polygon(m_points, 4);
}

void CShapeDialog::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        m_nChangeCount++;
        m_nTotalChanges++;

        // 每5次变化后恢复初始形状
        if (m_nChangeCount % 5 == 0)
        {
            for (int i = 0; i < 4; i++)
            {
                m_points[i] = m_initialPoints[i];
            }
        }
        else
        {
            // 随机变化四边形的形状
            CRect rect;
            GetClientRect(&rect);
            int cx = rect.Width();
            int cy = rect.Height();

            // 随机生成四个顶点，确保在对话框内
            for (int i = 0; i < 4; i++)
            {
                m_points[i].x = rand() % (cx - 20) + 10;
                m_points[i].y = rand() % (cy - 100) + 10; // 留出底部按钮的空间
            }
        }

        // 重绘对话框
        Invalidate();
    }

    CDialogEx::OnTimer(nIDEvent);
}

void CShapeDialog::OnOK()
{
    // 清理定时器
    KillTimer(1);

    // 通知父窗口对话框即将关闭
    if (GetParent() != nullptr)
    {
        GetParent()->PostMessage(WM_COMMAND, IDOK, (LPARAM)m_hWnd);
    }

    CDialogEx::OnOK();
}

void CShapeDialog::OnDestroy()
{
    CDialogEx::OnDestroy();

    // 清理定时器
    KillTimer(1);
}
