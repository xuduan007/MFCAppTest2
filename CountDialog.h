// CountDialog.h: 头文件
//

#pragma once

#include <afxwin.h>
#include <afxext.h>
#include <afxcmn.h>
#include <afxcontrolbars.h>
#include <afxdialogex.h>

// CCountDialog 对话框
class CCountDialog : public CDialogEx
{
public:
	CCountDialog(int nCount, CWnd* pParent = nullptr);	// 标准构造函数
	virtual ~CCountDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUNT_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	int m_nCount;	// 变化次数
};
