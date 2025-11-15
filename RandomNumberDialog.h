// RandomNumberDialog.h: 头文件
//

#pragma once

// CRandomNumberDialog 对话框
class CRandomNumberDialog : public CDialogEx
{
// 构造
public:
    CRandomNumberDialog(CWnd* pParent = nullptr);    // 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_RANDOM_NUMBER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
    DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};