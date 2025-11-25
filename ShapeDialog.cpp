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
	m_changeCount = 0;
	m_totalChanges = 0;
}

CShapeDialog::~CShapeDialog()
{
}

void CShapeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShapeDialog, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CShapeDialog 消息处理程序

BOOL CShapeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 初始化初始四边形顶点
	CRect rect;
	GetClientRect(&rect);
	int centerX = rect.Width() / 2;
	int centerY = rect.Height() / 2;
	int size = 100;

	m_initialPoints[0] = { centerX - size, centerY - size };
	m_initialPoints[1] = { centerX + size, centerY - size };
	m_initialPoints[2] = { centerX + size, centerY + size };
	m_initialPoints[3] = { centerX - size, centerY + size };

	// 复制初始顶点到当前顶点
	for (int i = 0; i < 4; i++)
	{
		m_points[i] = m_initialPoints[i];
	}

	// 启动定时器，每秒触发一次
	srand(time(NULL));
	SetTimer(TIMER_SHAPE_CHANGE, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CShapeDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_SHAPE_CHANGE)
	{
		m_changeCount++;
		m_totalChanges++;

		// 每5次变化后恢复初始形状
		if (m_changeCount == 5)
		{
			m_changeCount = 0;
			for (int i = 0; i < 4; i++)
			{
				m_points[i] = m_initialPoints[i];
			}
		}
		else
		{
			// 随机变化四边形形状
			CRect rect;
			GetClientRect(&rect);
			int maxOffset = 50;

			for (int i = 0; i < 4; i++)
			{
				// 在初始位置附近随机偏移
				m_points[i].x = m_initialPoints[i].x + (rand() % (2 * maxOffset + 1)) - maxOffset;
				m_points[i].y = m_initialPoints[i].y + (rand() % (2 * maxOffset + 1)) - maxOffset;

				// 确保点在对话框内
				m_points[i].x = max(0, min(m_points[i].x, rect.Width() - 1));
				m_points[i].y = max(0, min(m_points[i].y, rect.Height() - 1));
			}
		}

		// 重绘对话框
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CShapeDialog::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	// 绘制四边形
	dc.Polygon(m_points, 4);

	CDialogEx::OnPaint();
}
