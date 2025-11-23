// ShapeDialog.h: 头文件
//

#pragma once


// CShapeDialog 对话框
class CShapeDialog : public CDialogEx
{
// 构造
public:
	CShapeDialog(CWnd* pParent = nullptr);	// 标准构造函数
	~CShapeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	int m_nChangeCount;
	CPoint m_points[4];
	CPoint m_initialPoints[4];
	UINT_PTR m_nTimerID;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
