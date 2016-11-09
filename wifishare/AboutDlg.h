#pragma once
#include "afxwin.h"


// CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAboutDlg)

public:
	CAboutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUT_DIALOG };
#endif

private:
	void ChangeState_RestartButton(int state);
	int m_State_RestartButton;

	static UINT RestartICSService(LPVOID p);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton1();
	// //��������ICS����ť
	CButton m_Button_Restart;
	CEdit m_EditBox_Link;
};
