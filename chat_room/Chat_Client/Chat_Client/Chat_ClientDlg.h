
// Chat_ClientDlg.h : header file
//

#pragma once


// CChatClientDlg dialog
class CChatClientDlg : public CDialogEx
{
// Construction
public:
	CChatClientDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_CLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CWinThread* hListenThread;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	afx_msg HCURSOR OnQueryDragIcon();
	static UINT ListenThread(LPVOID lpParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	CEdit Ediit_IP;
	CEdit Edit_Port;
	CButton Button_check;
	CButton Button_send;
	CEdit Edit_mess;
	CListBox List_mess;
	afx_msg void OnBnClickedButton1();
	bool is_Connect;
	typedef struct _MultiCardThreadParam {
		CWnd* wndHandler;
		LPVOID lpParam;
	} MultiCardThreadParam;
	MultiCardThreadParam cTh_Param;
	afx_msg void OnBnClickedButton3();
	CButton Button_send1;
};
