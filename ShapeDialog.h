// ShapeDialog.h: 头文件
//

#pragma once


// CShapeDialog 对话框
class CShapeDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CShapeDialog)

public:
    CShapeDialog(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CShapeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    CPoint m_points[4];
    CPoint m_initialPoints[4];
    int m_changeCount;
    int m_totalChangeCount;
    virtual BOOL OnInitDialog();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual void OnPaint();
    void GenerateRandomShape();
    void ResetToInitialShape();
    int GetTotalChangeCount() const;

};
