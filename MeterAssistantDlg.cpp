
// MeterAssistantDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MeterAssistant.h"
#include "MeterAssistantDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DONGLE_SEND_SET_CONFIG_REQUEST "68 20 00 43 45 aa aa aa aa aa aa fe 83 62 05 02 00 03 f4 00 02 00 f4 00 04 00 f4 00 06 00 00 fe 57 16"
#define DONGLE_RESPONSE_TO_SET_CONFIG  "68 7f 00 c3 05 02 00 00 00 00 00 fe ca 07 85 02 00 03 f4 00 02 00 01 01 01 02 04 11 00 02 02 0a 20 \
										00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 45 4c 42 20 72 65 74 65 4d \
										09 06 c0 00 00 00 00 01 00 00 f4 00 04 00 01 01 01 02 02 09 06 c0 00 00 00 00 02 09 08 ff ff ff ff ff \
										ff ff f0 f4 00 06 00 01 01 01 02 04 51 f4 00 02 01 16 01 12 00 28 12 00 32 00 00 18 ed 16"

// CMeterAssistantDlg 对话框



CMeterAssistantDlg::CMeterAssistantDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_METERASSISTANT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMeterAssistantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMeterAssistantDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STRING_TO_HEX_ARRAY, &CMeterAssistantDlg::OnBnClickedStringToHexArray)
END_MESSAGE_MAP()


// CMeterAssistantDlg 消息处理程序

BOOL CMeterAssistantDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMeterAssistantDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMeterAssistantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// generate text file
// author : weijunfeng
// date   : 20200322
void CMeterAssistantDlg::OnBnClickedStringToHexArray()
{
	CStdioFile newfile;
	BOOL rs;

	// create new file
	rs = newfile.Open("D:\\meter_assistant.txt", CStdioFile::modeCreate | CStdioFile::modeWrite, NULL);
	if (rs)
	{

		Convert_String_To_Hex_Array(DONGLE_SEND_SET_CONFIG_REQUEST);
		newfile.WriteString(sArray);

		Convert_String_To_Hex_Array(DONGLE_RESPONSE_TO_SET_CONFIG);
		newfile.WriteString(sArray);

		newfile.Close();

		AfxMessageBox("convert string to hex array successfully");
	}
	else
	{
		AfxMessageBox("create new file failed");
	}
}

// Convert string to hex array
// author : weijunfeng
// date   : 20200322
int CMeterAssistantDlg::Convert_String_To_Hex_Array(char *p)
{

	CString txt, array;
	char xx[1000];
	char yy[10];
	int len, i, k, m;

	strcpy_s(xx, p);
	len = strlen(xx);
	k = 0;
	m = 0;
	for (i = 0; i < len; i++)
	{
		//if (xx[i] != ' ')
		if(Verify_Valid_Hex(xx[i]))
		{
			yy[k++] = xx[i];
		}

		if (k == 2)
		{
			k = 0;
			txt.Format("0x%c%c,", yy[0], yy[1]);
			m++;
			array += txt;
		}
	}

	array += "\n";
	txt.Format("//the length of the array is %d\n", m);
	array += txt;

	sArray = array;

	return 0x01;
}


int CMeterAssistantDlg::Verify_Valid_Hex(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else if (c >= 'a' && c <= 'f')
		return 1;
	else if (c >= 'A' && c <= 'F')
		return 1;
	else
		return 0;
}
