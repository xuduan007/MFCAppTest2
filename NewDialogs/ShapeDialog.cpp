// ShapeDialog.cpp: 实现文件
//

#include "../pch.h"
#include "../framework.h"
#include "../MFCApplication2.h"
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
	, m_shapeType(0)
	, m_totalChanges(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShapeDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CShapeDialog, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CShapeDialog 初始化

BOOL CShapeDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	setIcon(m_hIcon, TRUE);				// 设置大图标
	setIcon(m_hIcon, FALSE);				// 设置小图标

	// 初始化随机数生成器
	srand(static_cast<unsigned int>(time(nullptr)));

	// 启动计时器，每1秒更新一次形状
	SetTimer(1, 1000, nullptr);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CShapeDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CShapeDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		// 绘制当前形状
		DrawCurrentShape(dc);

		CDialogEx::OnPaint();
	}
}

// 当用户拖动最小化窗口时系统调用此函数取得光标
// 显示。
HCURSOR CShapeDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 计时器事件处理函数
void CShapeDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		// 生成随机形状
		GenerateRandomShape();

		// 重绘对话框
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

// 生成随机形状
void CShapeDialog::GenerateRandomShape()
{
	// 随机选择形状类型（0-3）
	m_shapeType = rand() % 4;

	// 随机生成形状的位置和大小
	CRect clientRect;
	GetClientRect(&clientRect);

	int maxWidth = clientRect.Width() / 4;
	int maxHeight = clientRect.Height() / 4;

	m_shapeRect.left = rand() % (clientRect.Width() - maxWidth);
	m_shapeRect.top = rand() % (clientRect.Height() - maxHeight);
	m_shapeRect.right = m_shapeRect.left + maxWidth;
	m_shapeRect.bottom = m_shapeRect.top + maxHeight;

	// 随机生成形状的颜色
	m_shapeColor = RGB(rand() % 256, rand() % 256, rand() % 256);

	// 增加总变化次数
	m_totalChanges++;
}

// 绘制当前形状
void CShapeDialog::DrawCurrentShape(CDC& dc)
{
	// 设置填充颜色
	CBrush brush(m_shapeColor);
	CBrush* pOldBrush = dc.SelectObject(&brush);

	// 设置边框颜色
	CPen pen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = dc.SelectObject(&pen);

	// 根据形状类型绘制形状
	switch (m_shapeType)
	{
	case 0: // 矩形
		dc.Rectangle(m_shapeRect);
		break;
	case 1: // 椭圆
		dc.Ellipse(m_shapeRect);
		break;
	case 2: // 圆角矩形
		dc.RoundRect(m_shapeRect, CPoint(20, 20));
		break;
	case 3: // 多边形
		{
			CPoint points[5];
			int centerX = (m_shapeRect.left + m_shapeRect.right) / 2;
			int centerY = (m_shapeRect.top + m_shapeRect.bottom) / 2;
			int radius = min(m_shapeRect.Width(), m_shapeRect.Height()) / 2;

			for (int i = 0; i < 5; i++)
			{
				double angle = 2 * M_PI * i / 5 - M_PI / 2;
				points[i].x = centerX + static_cast<int>(radius * cos(angle));
				points[i].y = centerY + static_cast<int>(radius * sin(angle));
			}

			dc.Polygon(points, 5);
		}
		break;
	default:
		break;
	}

	// 恢复旧的画笔和画刷
	dc.SelectObject(pOldPen);
	dc.SelectObject(pOldBrush);
}

// 获取总变化次数
int CShapeDialog::GetTotalChanges() const
{
	return m_totalChanges;
}

