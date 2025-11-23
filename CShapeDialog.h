// CShapeDialog.h: 头文件
//

#pragma once


// CShapeDialog 对话框
class CShapeDialog : public CDialogEx
{
public:
    CShapeDialog(CWnd* pParent = nullptr);   // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnDestroy();
    afx_msg void OnOK();
    int m_nChangeCount;
    POINT m_points[4];
    POINT m_initialPoints[4];
    static int m_nTotalChanges;
};
