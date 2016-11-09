// AboutDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "wifishare.h"
#include "AboutDlg.h"
#include "afxdialogex.h"
#include "wifishareKernel.h"


// CAboutDlg �Ի���

IMPLEMENT_DYNAMIC(CAboutDlg, CDialogEx)

CAboutDlg::CAboutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ABOUT_DIALOG, pParent)
{

}

CAboutDlg::~CAboutDlg()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_Button_Restart);
	DDX_Control(pDX, IDC_EDIT2, m_EditBox_Link);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CAboutDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CAboutDlg ��Ϣ�������


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ChangeState_RestartButton(0);
	m_EditBox_Link.SetWindowTextW(L"https://github.com/liuqx0717/wifishare");

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CAboutDlg::OnPaint()
{
					   // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CAboutDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


UINT CAboutDlg::RestartICSService(LPVOID p)
{
	CAboutDlg *dlg = (CAboutDlg*)p;
	int ret;

	ret = lqx::ChangeServiceStatusW(L"SharedAccess", false, 25);
	if (ret == ERROR_SERVICE_REQUEST_TIMEOUT) {
		AfxMessageBox(L"������ʱ��");
		dlg->ChangeState_RestartButton(0);
		return 0;
	}
	else if (ret != ERROR_SUCCESS && ret != ERROR_SERVICE_NOT_ACTIVE) {
		AfxMessageBox(L"����ʧ�ܡ�");
		dlg->ChangeState_RestartButton(0);
		return 0;
	}

	dlg->ChangeState_RestartButton(2);
	ret = lqx::ChangeServiceStatusW(L"SharedAccess", true, 25);
	if (ret == ERROR_SERVICE_REQUEST_TIMEOUT) {
		AfxMessageBox(L"������ʱ��");
		dlg->ChangeState_RestartButton(0);
		return 0;
	}
	else if (ret != ERROR_SUCCESS ) {
		AfxMessageBox(L"����ʧ�ܡ�");
		dlg->ChangeState_RestartButton(0);
		return 0;
	}

	dlg->ChangeState_RestartButton(0);
	return 0;

}

void CAboutDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ChangeState_RestartButton(1);
	AfxBeginThread(&RestartICSService, this);

}



//0����ʾ����������ICS����  1����ʾ������ֹͣICS����...��  2����ʾ����������ICS����...�� 
void CAboutDlg::ChangeState_RestartButton(int state)
{

	switch (state)
	{
	case 0:
		m_Button_Restart.SetWindowTextW(L"��������ICS����");
		m_Button_Restart.EnableWindow(TRUE);
		m_State_RestartButton = state;
		break;
	case 1:
		m_Button_Restart.SetWindowTextW(L"����ֹͣICS����...");
		m_Button_Restart.EnableWindow(FALSE);
		m_State_RestartButton = state;
		break;
	case 2:
		m_Button_Restart.SetWindowTextW(L"��������ICS����...");
		m_Button_Restart.EnableWindow(FALSE);
		m_State_RestartButton = state;
		break;

	default:
		break;
	}
}