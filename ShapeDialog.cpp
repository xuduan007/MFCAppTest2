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
	, m_changeCount(0)
	, m_totalChangeCount(0)
{
	// 初始化初始形状（矩形）
	m_initialPoints[0] = { 50, 50 };
	m_initialPoints[1] = { 250, 50 };
	m_initialPoints[2] = { 250, 200 };
	m_initialPoints[3] = { 50, 200 };

	// 复制初始形状到当前形状
	int i;
	for (i = 0; i < 4; ++i)
	{
		m_points[i] = m_initialPoints[i];
	}
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

	// 初始化随机数生成器
	srand(static_cast<unsigned int>(time(nullptr)));

	// 设置定时器，每秒触发一次
	setTimer(1, 1000, nullptr);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CShapeDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		if (m_changeCount < 5)
		{
			GenerateRandomShape();
			m_changeCount++;
			m_totalChangeCount++;
		}
		else
		{
			ResetToInitialShape();
			m_changeCount = 0;
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


void CShapeDialog::GenerateRandomShape()
{
	// 随机生成四边形的四个顶点
	int i;
	for (i = 0; i < 4; ++i)
	{
		m_points[i].x = 50 + rand() % 200;
		m_points[i].y = 50 + rand() % 150;
	}
}


void CShapeDialog::ResetToInitialShape()
{
	// 恢复到初始形状
	int i;
	for (i = 0; i < 4; ++i)
	{
		m_points[i] = m_initialPoints[i];
	}
}

int CShapeDialog::GetTotalChangeCount() const
{
	return m_totalChangeCount;
}
