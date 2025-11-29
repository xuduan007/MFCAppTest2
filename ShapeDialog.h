// ShapeDialog.h: Header file
//
#pragma once

#include <vector>
#include <afxwin.h>

// CShapeDialog dialog
class CShapeDialog : public CDialogEx
{
// Construction
public:
	CShapeDialog(CWnd* pParent = nullptr);   // standard constructor
	~CShapeDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
	int m_nShapeChanges;
	int m_nTotalChanges; // Total changes across all dialog instances
	CRect m_rectClient; // Client area of the dialog
	std::vector<POINT> m_points; // Points of the quadrilateral

	void InitializeQuadrilateral();
	void GenerateRandomShape();
	void DrawQuadrilateral(CDC* pDC);
	void UpdateButtonPosition();

public:
	static int s_nGlobalTotalChanges; // Static variable to track total changes across all dialogs
	void SetTotalChanges(int nTotal);
};
