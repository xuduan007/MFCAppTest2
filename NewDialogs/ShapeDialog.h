// ShapeDialog.h: 头文件
//

#pragma once


// CShapeDialog 对话框
class CShapeDialog : public CDialogEx
{
// 构造
public:
	CShapeDialog(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()

private:
	CPoint m_points[4];
	CPoint m_initialPoints[4];
	int m_changeCount;
	int m_totalChanges;

	void GenerateRandomShape();
	void ResetToInitialShape();

public:
	int GetTotalChanges() const { return m_totalChanges; }
};
