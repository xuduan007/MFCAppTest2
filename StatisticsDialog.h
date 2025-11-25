// StatisticsDialog.h: 头文件
//

#pragma once


// CStatisticsDialog 对话框
class CStatisticsDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CStatisticsDialog)

public:
    CStatisticsDialog(int nTotalCount, CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CStatisticsDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_STATISTICS_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    int m_nTotalCount;
    virtual BOOL OnInitDialog();
};
