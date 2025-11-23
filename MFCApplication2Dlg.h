
// MFCApplication2Dlg.h: ͷ�ļ�
//

#pragma once

// 前向声明CShapeDialog类
class CShapeDialog;

// CMFCApplication2Dlg �Ի���
class CMFCApplication2Dlg : public CDialogEx
{
// ����
public:
	CMFCApplication2Dlg(CWnd* pParent = nullptr);	// ��׼���캯��
	~CMFCApplication2Dlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedModalBtn();
	afx_msg void OnBnClickedModelessBtn();
	void OnSize(UINT nType, int cx, int cy);

private:
	CShapeDialog* m_pModelessDlg;
};
