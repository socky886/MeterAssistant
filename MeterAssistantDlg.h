
// MeterAssistantDlg.h: 头文件
//

#pragma once


// CMeterAssistantDlg 对话框
class CMeterAssistantDlg : public CDialogEx
{
// 构造
public:
	CMeterAssistantDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_METERASSISTANT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStringToHexArray();
	int Convert_String_To_Hex_Array(char * p);
	CString sArray;
	int Verify_Valid_Hex(char c);
};
