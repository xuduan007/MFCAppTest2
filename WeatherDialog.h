// WeatherDialog.h: 头文件
//

#pragma once
#include <afxwin.h>
#include "resource.h"

class CWeatherDialog : public CDialogEx
{
    DECLARE_DYNAMIC(CWeatherDialog)

public:
    CWeatherDialog(CWnd* pParent = nullptr);   // 标准构造函数
    virtual ~CWeatherDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_WEATHER_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()
public:
    CString m_strWeatherInfo;
    virtual BOOL OnInitDialog();
};
