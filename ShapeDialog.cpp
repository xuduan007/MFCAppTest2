// ShapeDialog.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ShapeDialog.h"
#include "afxdialogex.h"
#include <cstdlib>
#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShapeDialog 对话框

CShapeDialog::CShapeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAPE_DIALOG, pParent)
{
	m_nChangeCount = 0;
	m_nTimerID = 0;
}

CShapeDialog::~CShapeDialog()
{
	if (m_nTimerID != 0)
	{
		KillTimer(m_nTimerID);
	}
}

void CShapeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShapeDialog, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CShapeDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// CShapeDialog 消息处理程序

BOOL CShapeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);			// 设置小图标

	// 初始化随机数生成器
	srand((unsigned int)time(nullptr));

	// 获取对话框客户区大小
	CRect rect;
	GetClientRect(&rect);

	// 计算初始四边形的四个顶点（居中显示）
	int centerX = rect.Width() / 2;
	int centerY = rect.Height() / 2;
	int size = min(rect.Width(), rect.Height()) / 3;

	m_initialPoints[0] = CPoint(centerX - size / 2, centerY - size / 2);
	m_initialPoints[1] = CPoint(centerX + size / 2, centerY - size / 2);
	m_initialPoints[2] = CPoint(centerX + size / 2, centerY + size / 2);
	m_initialPoints[3] = CPoint(centerX - size / 2, centerY + size / 2);

	// 复制初始点到当前点
	for (int i = 0; i < 4; i++)
	{
		m_points[i] = m_initialPoints[i];
	}

	// 设置定时器，每秒触发一次
	m_nTimerID = SetTimer(1, 1000, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShapeDialog::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	// 绘制四边形
	dc.Polygon(m_points, 4);

	// 绘制关闭按钮
	CRect btnRect;
	GetDlgItem(IDCANCEL)->GetWindowRect(&btnRect);
	ScreenToClient(&btnRect);
	dc.Draw3dRect(&btnRect, RGB(0, 0, 0), RGB(255, 255, 255));
}

void CShapeDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		// 每5次变化后恢复初始形状
		m_nChangeCount++;
		if (m_nChangeCount % 5 == 0)
		{
			for (int i = 0; i < 4; i++)
			{
				m_points[i] = m_initialPoints[i];
			}
		}
		else
		{
			// 获取对话框客户区大小
			CRect rect;
			GetClientRect(&rect);

			// 随机生成四个顶点，确保在对话框内
			for (int i = 0; i < 4; i++)
			{
				m_points[i].x = rand() % (rect.Width() - 20) + 10;
				m_points[i].y = rand() % (rect.Height() - 20) + 10;
			}
		}

		// 重绘对话框
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CShapeDialog::OnBnClickedCancel()
{
	// 销毁定时器
	if (m_nTimerID != 0)
	{
		KillTimer(m_nTimerID);
		m_nTimerID = 0;
	}

	CDialogEx::OnCancel();
}
