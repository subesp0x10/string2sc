
// StringDynamicDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "StringDynamic.h"
#include "StringDynamicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CStringDynamicDlg dialog



CStringDynamicDlg::CStringDynamicDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STRINGDYNAMIC_DIALOG, pParent)
	, m_Type(0)
	, m_EditOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStringDynamicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_Type);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_EditInput);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_EditOutput);
	DDX_Control(pDX, IDC_EDIT_VARIABLE, m_EditVariable);
	DDX_Control(pDX, IDC_EDIT_ROUND, m_EditRound);
}

BEGIN_MESSAGE_MAP(CStringDynamicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_GO, &CStringDynamicDlg::OnBnClickedButtonGo)
END_MESSAGE_MAP()


// CStringDynamicDlg message handlers

BOOL CStringDynamicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	m_EditRound.SetWindowText(_T("1"));

	m_Seed = GetTickCount();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CStringDynamicDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CStringDynamicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStringDynamicDlg::OnBnClickedButtonGo()
{
	// TODO: Add your control notification handler code here

	Work();
}


BOOL CStringDynamicDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_KEYDOWN)
	{
		if (/* pMsg->wParam == VK_RETURN || */ pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;                // Do not process further
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CStringDynamicDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	CWnd* f = GetFocus();

	if (f == &m_EditInput || f == &m_EditVariable || f == &m_EditRound)
	{
		// TODO: Add your handling of the Return key here.
		//TRACE0("Return key in edit control pressed\n");

		Work();

		// Call `return` to leave the dialog open.
		return;
	}
	else
	{
		return;
	}

	CDialogEx::OnOK();
}


void CStringDynamicDlg::Work()
{
	// TODO: Add your implementation code here.

	UpdateData(TRUE);

	CString str_input;
	CString str_output;
	CString str_variable;
	CString str_round;
	m_EditInput.GetWindowText(str_input);
	m_EditVariable.GetWindowText(str_variable);
	m_EditRound.GetWindowText(str_round);

	if (str_input.IsEmpty() || str_variable.IsEmpty())
	{
		return;
	}

	m_EditOutput.Empty();

	CString c;
	int d;

	unsigned char input[2048] = { 0 };

	int nBytes = 0;

	if (m_Type == 0) {

		//char aInput[1024] = {0};
		//strcpy_s(aInput, CStringA(str_input).GetString());

		int len = CStringA(str_input).GetLength();

		nBytes = sizeof(char) * (len + 1);

		memcpy(input, CStringA(str_input).GetString(), nBytes);

		c = "char";
		d = sizeof(char);

	}
	else if (m_Type == 1) {

		int len = CStringW(str_input).GetLength();

		nBytes = sizeof(wchar_t) * (len + 1);

		memcpy(input, CStringW(str_input).GetString(), nBytes);

		c = "wchar_t";
		d = sizeof(wchar_t);
	}

	// padding

	int nPaddingBytes = nBytes % 4 == 0 ? 0 : (4 - nBytes % 4);

	int nTotalBytes = nBytes + nPaddingBytes;

	for (int i = nBytes; i < nTotalBytes; i++)
	{
		memset(input + i, 0, sizeof(char));
	}

	//
	int nCount = nTotalBytes / 4;

	DWORD* dwArray = (DWORD*)calloc(nCount, sizeof(DWORD));

	for (int i = 0; i < nCount; i++) {

		memcpy(&dwArray[i], input + i * sizeof(DWORD), sizeof(DWORD));

	}

	str_output.Format(_T("%s %s[%d]={0};\r\n\r\n"), c, str_variable, nTotalBytes / d);

	

	for (int i = 0; i < nCount; i++)
	{
		//DWORD r = ReverseDword(dwArray[i]);

		//str_output.AppendFormat(_T("*(DWORD *)(%s + 0x%04x) = 0x%08x;\r\n"), str_variable, i * 4, dwArray[i]);

		CArray<DWORD, DWORD>* p= SplitDword(dwArray[i], _ttoi(str_round));

		for (int j = 0; j < p->GetCount(); j++)
		{
			DWORD& item = p->ElementAt(j);
			
			str_output.AppendFormat(_T("*((DWORD *)%s + 0x%02x) %-2s 0x%08x;\r\n"), str_variable, i , j == 0 ? _T("=") : _T("+="), item);
		}

	}

	m_EditOutput += str_output;

	CopyToClipboard();
	
	UpdateData(FALSE);
}


DWORD CStringDynamicDlg::ReverseDword(DWORD input)
{
	// TODO: Add your implementation code here.

	DWORD reversed = 0;

	if (m_Type == 0) {

		uint8_t* n1, * n2;
		n1 = (uint8_t*)&input;
		n2 = (uint8_t*)&reversed;

		n2[0] = n1[3];
		n2[1] = n1[2];
		n2[2] = n1[1];
		n2[3] = n1[0];

	}
	else {

	}

	return reversed;
}


CArray<DWORD, DWORD>* CStringDynamicDlg::SplitDword(DWORD sum, int round)
{
	// TODO: Add your implementation code here.

	ULONGLONG sum64 = 0;
	DWORD r = 0;
	ULONGLONG temp_sum = 0;

	sum64 = sum + 0x0000000100000000 * round;
	
	CArray<DWORD, DWORD>* myArray = new CArray<DWORD, DWORD>;

	for (int i = 1; i <= round; i++) {

		if (i != round) {
			r = RangedRand(1, (sum64 - temp_sum) / (round - i) );
			myArray->Add(r);
			temp_sum += r;
		}
		else {
			DWORD last = (sum64 - temp_sum);
			myArray->Add(last);
			temp_sum += last;
		}
	}

	return myArray;

}


ULONGLONG CStringDynamicDlg::RangedRand(ULONGLONG min, ULONGLONG max)
{
	// TODO: Add your implementation code here.

	m_Seed += (m_Seed * 7) ^ (m_Seed << 15) + 8 * 137 - (m_Seed >> 5);
	m_Seed &= ((1 << 32) - 1);

	srand((unsigned)m_Seed);

	return (ULONGLONG)((double)rand() / (double)(RAND_MAX + 1) * (max - min) + min);
}


void CStringDynamicDlg::CopyToClipboard()
{
	// TODO: Add your implementation code here.

	if (!OpenClipboard()) {
		return;
	}

	if (!EmptyClipboard())
	{
		
		return;
	}

	size_t cbStr = (m_EditOutput.GetLength() + 1) * sizeof(TCHAR);
	HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE, cbStr);
	memcpy_s(GlobalLock(hData), cbStr, m_EditOutput.LockBuffer(), cbStr);
	GlobalUnlock(hData);
	m_EditOutput.UnlockBuffer();

	// For the appropriate data formats...
	UINT uiFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
	if (::SetClipboardData(uiFormat, hData) == NULL)
	{

		CloseClipboard();
		return;
	}

	CloseClipboard();
}
