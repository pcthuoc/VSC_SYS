
// Chat_ClientDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Chat_Client.h"
#include "Chat_ClientDlg.h"
#include "afxdialogex.h"

#include <Windows.h>
#include <WS2tcpip.h>
#include <cstring>
#include <string>
#include <winsock2.h>
#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatClientDlg dialog



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_CLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, Ediit_IP);
	DDX_Control(pDX, IDC_EDIT2, Edit_Port);
	DDX_Control(pDX, IDC_BUTTON1, Button_check);
	//DDX_Control(pDX, IDC_BUTTON2, Button_send);
	DDX_Control(pDX, IDC_EDIT3, Edit_mess);
	DDX_Control(pDX, IDC_LIST1, List_mess);
	DDX_Control(pDX, IDC_BUTTON3, Button_send1);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, &CChatClientDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CChatClientDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	Button_send1.EnableWindow(FALSE);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatClientDlg::OnPaint()
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
BOOL CChatClientDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
			pMsg->wParam = VK_TAB;
	}
	return CDialog::PreTranslateMessage(pMsg);
}
void CChatClientDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
		case VK_UP:
			AfxMessageBox(_T("gfgfgfgfgfg"));
			break;
		default:
			break;
	}
}


// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
SOCKET Connect_Socket;
UINT CChatClientDlg::ListenThread(LPVOID lpParam)
{
	MultiCardThreadParam* cTh_Param = (MultiCardThreadParam*)lpParam;
	CChatClientDlg* is_tmp = (CChatClientDlg*)cTh_Param->wndHandler;
	SOCKET Listen_Socket = (SOCKET)cTh_Param->lpParam;
	CString str_Status, str_Msg;
	CStringA stra_Msg;
	char	str_read[4000];
	while (is_tmp->is_Connect)
	{
		int number_byte = recv(Listen_Socket, str_read, 4000, 0);
		if (number_byte == 0)
			continue;
		if (number_byte < 0)
			return FALSE;
		stra_Msg.Format("%.*s", number_byte, str_read);
		str_Msg = stra_Msg;
		is_tmp->List_mess.InsertString(-1, str_Msg);
	}
}


void CChatClientDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	CString str_Status, str_Error, str_IP, str_Port;
	WSADATA wsa_DATA;

	Edit_Port.GetWindowText(str_Port);
	Ediit_IP.GetWindowText(str_IP);
	if ((str_IP.GetLength() == 0 )|| (str_Port.GetLength()) == 0)
	{
		AfxMessageBox(_T("Please fill IP and port"));
		return;

	}
	Button_check.GetWindowText(str_Status);
	if (str_Status == _T("Connect"))
	{
		if (WSAStartup(MAKEWORD(2, 2), &wsa_DATA)) {
			AfxMessageBox(_T("Winsock intializing failed!"));
			return;
		}
		addrinfo hints;
		memset(&hints, 0, sizeof hints);
		hints.ai_socktype = SOCK_STREAM;
		addrinfo* result;
		CStringA stra_IP(str_IP), stra_Port(str_Port);
		if (getaddrinfo(stra_IP, stra_Port, &hints, &result))
		{
			AfxMessageBox(_T("getaddrinfo failed "));
			return;
		}
		Connect_Socket = INVALID_SOCKET;
		Connect_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (Connect_Socket == INVALID_SOCKET)
		{
			AfxMessageBox(_T("Socket creating failed"));
			return;
		}
		if (connect(Connect_Socket, result->ai_addr, result->ai_addrlen))
		{
			AfxMessageBox(_T("Unable to connect to server!"));
			WSACleanup();
			return;
		}
		freeaddrinfo(result);
		// creata muti thread
		is_Connect = TRUE;
		cTh_Param.wndHandler = this;
		cTh_Param.lpParam = (LPVOID)Connect_Socket;
		hListenThread = AfxBeginThread(ListenThread, (LPVOID)&cTh_Param);

		Button_check.SetWindowText(_T("Disconnect"));
		Button_send1.EnableWindow(TRUE);
		
	}
	else
	{
		is_Connect = FALSE;
		closesocket(Connect_Socket);
		WSACleanup();
		Connect_Socket = INVALID_SOCKET;
		CloseHandle(hListenThread->m_hThread);
		hListenThread->m_hThread = NULL;
		List_mess.ResetContent();
		Button_check.SetWindowText(_T("Connect"));
		Button_send1.EnableWindow(FALSE);
	}
	UpdateData(FALSE);
	

	// TODO: Add your control notification handler code here
}


void CChatClientDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	USES_CONVERSION;
	CString str_Send;
	CStringA stra_Send;
	Edit_mess.GetWindowText(str_Send);
	stra_Send = str_Send;
	std::string msg = CStringA(stra_Send);
	//std::string msg= std::string(str_Send.GetString());
	send(Connect_Socket, msg.c_str(), msg.size(), 0);
	UpdateData(FALSE);
	Edit_mess.SetWindowText(_T(""));
	// TODO: Add your control notification handler code here
}
