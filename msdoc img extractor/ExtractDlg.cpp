// ExtractDlg.cpp : implementation file
//

#include "pch.h"
#include "msdoc img extractor.h"
#include "afxdialogex.h"
#include "ExtractDlg.h"


// CExtractDlg dialog

IMPLEMENT_DYNAMIC(CExtractDlg, CDialogEx)

CExtractDlg::CExtractDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILE_EXTRACT_DLG, pParent)
{

}

CExtractDlg::~CExtractDlg()
{
}

void CExtractDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExtractDlg, CDialogEx)
	ON_BN_CLICKED(ID_YES_BTN, &CExtractDlg::OnBnClickedYesBtn)
	ON_BN_CLICKED(ID_NO_BTN, &CExtractDlg::OnBnClickedNoBtn)
END_MESSAGE_MAP()


// CExtractDlg message handlers

BOOL CExtractDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetWindowText(L"안내");

	return TRUE;
}

void CExtractDlg::OnBnClickedYesBtn()
{
	CDialogEx::OnOK();
}


void CExtractDlg::OnBnClickedNoBtn()
{
	CDialogEx::OnCancel();
}
