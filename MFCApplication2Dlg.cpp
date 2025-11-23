// MFCApplication2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2.h"
#include "MFCApplication2Dlg.h"
#include "afxdialogex.h"
#include <afxtempl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 对话框


CMFCApplication2Dlg::CMFCApplication2Dlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_MFCAPPLICATION2_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pModelessDlg = nullptr;
}

void CMFCApplication2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication2Dlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDOK, &CMFCApplication2Dlg::OnBnClickedOk)
    ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2Dlg::OnBnClickedButton1)
    ON_WM_TIMER()
    ON_BN_CLICKED(IDC_MODAL_DLG, &CMFCApplication2Dlg::OnBnClickedModalDlg)
    ON_BN_CLICKED(IDC_MODELLESS_DLG, &CMFCApplication2Dlg::OnBnClickedModelessDlg)
    ON_BN_CLICKED(IDC_SHOW_COUNT, &CMFCApplication2Dlg::OnBnClickedShowCount)
    ON_WM_DESTROY()
    ON_MESSAGE(WM_COMMAND, &CMFCApplication2Dlg::OnModelessDlgClose)
END_MESSAGE_MAP()


// CMFCApplication2Dlg 消息处理程序

BOOL CMFCApplication2Dlg::OnInitDialog()
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

    // TODO: 在此添加额外的初始化代码

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication2Dlg::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);    
}

void CMFCApplication2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication2Dlg::OnPaint()
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

    CRect rect(100, 0, 200, 300);
    //GetClientRect(&rect);
    GetDlgItem(IDC_STATIC)->MoveWindow(&rect);

    CBitmap bitmap;
    //加载指定位图资源 Bmp图片ID
    bitmap.LoadBitmap(IDB_BITMAP1);
    //获取对话框上的句柄 图片控件ID
    CStatic* p = (CStatic*)GetDlgItem(IDC_STATIC);
    //设置静态控件窗口风格为位图居中显示
    p->ModifyStyle(0xf, SS_BITMAP | SS_CENTERIMAGE);
    //将图片设置到Picture控件上
    p->SetBitmap(bitmap);

}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication2Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication2Dlg::OnBnClickedOk()
{
    // TODO: 在此添加控件通知处理程序代码
    CDialogEx::OnOK();
}

void CMFCApplication2Dlg::OnBnClickedButton1()
{
    /*
    CString text;
    CWnd* wnd = GetDlgItem(IDC_SHOW);
    wnd->GetWindowText(text);
    wnd->SetWindowText(text + _T("Hello, MFC!"));
    */        
}

void CMFCApplication2Dlg::OnBnClickedModalDlg()
{
    // 打开模态对话框
    CShapeDialog dlgModal(this);
    dlgModal.DoModal();
}

void CMFCApplication2Dlg::OnBnClickedModelessDlg()
{
    // 打开非模态对话框
    if (m_pModelessDlg == nullptr)
    {
        m_pModelessDlg = new CShapeDialog(this);
        m_pModelessDlg->Create(IDD_SHAPE_DIALOG, this);
        m_pModelessDlg->ShowWindow(SW_SHOW);
    }
    else
    {
        // 如果对话框已经存在但被最小化或隐藏，将其激活并显示
        if (m_pModelessDlg->IsIconic())
        {
            m_pModelessDlg->ShowWindow(SW_RESTORE);
        }
        m_pModelessDlg->SetForegroundWindow();
    }
}

LRESULT CMFCApplication2Dlg::OnModelessDlgClose(WPARAM wParam, LPARAM lParam)
{
    // 检查是否是非模态对话框关闭的消息
    if (lParam == (LPARAM)m_pModelessDlg->m_hWnd && (wParam == IDOK || wParam == IDCANCEL || wParam == IDCLOSE))
    {
        // 清理非模态对话框
        m_pModelessDlg->DestroyWindow();
        delete m_pModelessDlg;
        m_pModelessDlg = nullptr;
    }

    // 传递消息给默认处理函数
    return CDialogEx::OnCommand(wParam, lParam);
}

void CMFCApplication2Dlg::OnBnClickedShowCount()
{
    // 显示变化次数的模态对话框
    CShowCountDialog dlgCount(this);
    dlgCount.DoModal();
}

void CMFCApplication2Dlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // 清理非模态对话框
    if (m_pModelessDlg != nullptr)
    {
        m_pModelessDlg->DestroyWindow();
        delete m_pModelessDlg;
        m_pModelessDlg = nullptr;
    }
}
