
// StringDynamicDlg.h : header file
//

#pragma once


// CStringDynamicDlg dialog
class CStringDynamicDlg : public CDialogEx
{
// Construction
public:
	CStringDynamicDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STRINGDYNAMIC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_Type;
	afx_msg void OnBnClickedButtonGo();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnOK();
	CEdit m_EditInput;
	void Work();
	CString m_EditOutput;
	DWORD ReverseDword(DWORD input);
	CEdit m_EditVariable;
	CArray<DWORD, DWORD>* SplitDword(DWORD sum, int round);
	ULONGLONG RangedRand(ULONGLONG min, ULONGLONG max);
	CEdit m_EditRound;
	void CopyToClipboard();
	int m_Seed;
};
