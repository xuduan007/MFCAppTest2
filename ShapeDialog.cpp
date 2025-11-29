// ShapeDialog.cpp: 实现文件
//
#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "ShapeDialog.h"
#include "afxdialogex.h"
#include <random>

// 静态成员初始化
int CShapeDialog::s_nGlobalTotalChanges = 0;

// CShapeDialog 对话框
CShapeDialog::CShapeDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAPE_DIALOG, pParent)
	, m_nShapeChanges(0)
	, m_nTotalChanges(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CShapeDialog::~CShapeDialog()
{
	KillTimer(1); // Kill the timer when dialog is destroyed
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
	ON_BN_CLICKED(IDC_CLOSE_BUTTON, &CShapeDialog::OnBnClickedClose)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CShapeDialog 消息处理程序
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
	SetIcon(m_hIcon, TRUE);            // 设置大图标
	SetIcon(m_hIcon, FALSE);        // 设置小图标

	// 初始化四边形
	GetClientRect(&m_rectClient);
	InitializeQuadrilateral();

	// 设置定时器，每秒触发一次
	SetTimer(1, 1000, nullptr);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CShapeDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		// CAboutDlg dlgAbout;
		// dlgAbout.DoModal();
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
		CDialogEx::OnPaint();
	}

	// 绘制四边形
	CPaintDC dc(this);
	DrawQuadrilateral(&dc);
}

// 当用户拖动最小化窗口时系统调用此函数取得光标
// 显示。
HCURSOR CShapeDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CShapeDialog::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_nShapeChanges++;
		m_nTotalChanges++;
		s_nGlobalTotalChanges++;

		if (m_nShapeChanges % 5 == 0)
		{
			// 每5次变化后恢复初始形状
			InitializeQuadrilateral();
		}
		else
		{
			// 生成随机形状
			GenerateRandomShape();
		}

		// 重绘对话框
		Invalidate();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CShapeDialog::OnBnClickedClose()
{
	// 关闭对话框
	EndDialog(IDCANCEL);
}

void CShapeDialog::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (cx == 0 || cy == 0) return;

	// 更新客户端区域
	GetClientRect(&m_rectClient);

	// 重新初始化四边形
	InitializeQuadrilateral();

	// 更新按钮位置
	UpdateButtonPosition();

	// 重绘
	Invalidate();
}

void CShapeDialog::InitializeQuadrilateral()
{
	// 计算四边形的初始位置（居中）
	int nWidth = m_rectClient.Width();
	int nHeight = m_rectClient.Height();
	int nCenterX = nWidth / 2;
	int nCenterY = nHeight / 2;
	int nSize = min(nWidth, nHeight) / 3;

	m_points.clear();
	m_points.push_back(POINT{nCenterX - nSize, nCenterY - nSize}); // 左上角
	m_points.push_back(POINT{nCenterX + nSize, nCenterY - nSize}); // 右上角
	m_points.push_back(POINT{nCenterX + nSize, nCenterY + nSize}); // 右下角
	m_points.push_back(POINT{nCenterX - nSize, nCenterY + nSize}); // 左下角
}

void CShapeDialog::GenerateRandomShape()
{
	if (m_points.size() != 4) return;

	// 获取客户端大小
	int nWidth = m_rectClient.Width();
	int nHeight = m_rectClient.Height();
	int nCenterX = nWidth / 2;
	int nCenterY = nHeight / 2;
	int nSize = min(nWidth, nHeight) / 3;

	// 使用随机数生成器
	static std::mt19937 rng(std::random_device{}());
	std::uniform_int_distribution<int> distX(nCenterX - nSize, nCenterX + nSize);
	std::uniform_int_distribution<int> distY(nCenterY - nSize, nCenterY + nSize);

	// 为每个点生成随机位置
	for (int i = 0; i < 4; i++)
	{
		m_points[i].x = distX(rng);
		m_points[i].y = distY(rng);
	}
}

void CShapeDialog::DrawQuadrilateral(CDC* pDC)
{
	if (m_points.size() != 4) return;

	// 设置画笔和画刷
	CPen pen(PS_SOLID, 2, RGB(0, 0, 255)); // 蓝色边框
	CBrush brush(RGB(173, 216, 230)); // 浅蓝色填充
	CPen* pOldPen = pDC->SelectObject(&pen);
	CBrush* pOldBrush = pDC->SelectObject(&brush);

	// 绘制四边形
	pDC->Polygon(m_points.data(), m_points.size());

	// 恢复原来的画笔和画刷
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldBrush);
}

void CShapeDialog::UpdateButtonPosition()
{
	// 将关闭按钮放在右下角
	CWnd* pBtn = GetDlgItem(IDC_CLOSE_BUTTON);
	if (pBtn != nullptr)
	{
		CRect btnRect;
		pBtn->GetWindowRect(&btnRect);
		int nBtnWidth = btnRect.Width();
		int nBtnHeight = btnRect.Height();

		// 按钮位置：右下角，距离边缘10个像素
		pBtn->MoveWindow(m_rectClient.right - nBtnWidth - 10, m_rectClient.bottom - nBtnHeight - 10, nBtnWidth, nBtnHeight);
	}
}

void CShapeDialog::SetTotalChanges(int nTotal)
{
	m_nTotalChanges = nTotal;
}
