// ShapeDialog.h: 头文件
//

#pragma once

#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxcontrolbars.h>
#include <afxdialogex.h>

// 定义形状变化定时器ID
#define TIMER_SHAPE_CHANGE 1

// CShapeDialog 对话框
class CShapeDialog : public CDialogEx
{
public:
	CShapeDialog(CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CShapeDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();

public:
	int m_totalChanges;	// 总变化次数

private:
	POINT m_points[4];	// 当前四边形顶点
	POINT m_initialPoints[4];	// 初始四边形顶点
	int m_changeCount;	// 当前变化次数（每5次重置）
};
