#pragma once
#include "afxdialogex.h"
#include "SettingControl.h"

// CSettingDlg dialog

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // standard constructor
	CSettingDlg(LOCALE locale, CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSettingDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_DLG };
#endif
	virtual BOOL OnInitDialog();
	virtual INT_PTR DoModal(LOCALE locale);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	void OnClickLangRad(UINT id);
	void OnClickCompRad(UINT id);
	void OnClickOverRad(UINT id);
	void InitLocale(LOCALE locale);
	LOCALE m_locale;
	
public:
	CButton m_closeBtn;
	CButton m_okBtn;
	CButton m_applyBtn;
	CButton m_selDirBtn;
	CEdit m_pathEdit;
	CStatic m_pathText;
	CStatic m_compText;
	CStatic m_langText;
	CStatic m_overwriteText;
	afx_msg void OnBnClickedSetdlgCloseBtn();
};
