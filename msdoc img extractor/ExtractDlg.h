#pragma once
#include "afxdialogex.h"


// CExtractDlg dialog

class CExtractDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExtractDlg)

public:
	CExtractDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CExtractDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILE_EXTRACT_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};
