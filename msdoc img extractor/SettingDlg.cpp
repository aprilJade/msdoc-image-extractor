// SettingDlg.cpp : implementation file
//

#include "pch.h"
#include "msdoc img extractor.h"
#include "afxdialogex.h"
#include "SettingDlg.h"


// CSettingDlg dialog

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DLG, pParent)
{

}

CSettingDlg::CSettingDlg(LOCALE locale, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DLG, pParent)
	, m_locale(locale)
{
}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SETDLG_CLOSE_BTN, m_closeBtn);
	DDX_Control(pDX, IDC_SETDLG_OK_BTN, m_okBtn);
	DDX_Control(pDX, IDC_SETDLG_APPLY_BTN, m_applyBtn);
	DDX_Control(pDX, IDC_SETDLG_DIRSEL_BTN, m_selDirBtn);
	DDX_Control(pDX, IDC_SETDLG_DIR_PATH, m_pathEdit);
	DDX_Control(pDX, IDC_STATIC_BASIC_PATH, m_pathText);
	DDX_Control(pDX, IDC_STATIC_COMPRESS, m_compText);
	DDX_Control(pDX, IDC_STATIC_LANGUAGE, m_langText);
	DDX_Control(pDX, IDC_STATIC_OVERWRITE, m_overwriteText);
}

BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_SETDLG_CLOSE_BTN, &CSettingDlg::OnBnClickedSetdlgCloseBtn)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_LANG_KO_RAD, IDC_LANG_JP_RAD, CSettingDlg::OnClickLangRad)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_ALWAYS_ASK_RAD, IDC_ALWAYS_CHANGE_RAD, CSettingDlg::OnClickOverRad)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_COMP_NO_RAD, IDC_COMP_ZIP_RAD, CSettingDlg::OnClickCompRad)
END_MESSAGE_MAP()

BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	InitLocale(m_locale);

	return TRUE;
}

// CSettingDlg message handlers

void CSettingDlg::OnClickLangRad(UINT id)
{
	switch (id)
	{
	case IDC_LANG_KO_RAD:
		break;
	case IDC_LANG_EN_RAD:
		break;
	case IDC_LANG_JP_RAD:
		break;
	default:
		break;
	}
}

void CSettingDlg::OnClickCompRad(UINT id)
{
	switch (id)
	{
	case IDC_COMP_NO_RAD:
		break;
	case IDC_COMP_ZIP_RAD:
		break;
	default:
		break;
	}
}

void CSettingDlg::OnClickOverRad(UINT id)
{
	switch (id)
	{
	case IDC_ALWAYS_ASK_RAD:
		break;
	case IDC_ALWAYS_OVER_RAD:
		break;
	case IDC_ALWAYS_CHANGE_RAD:
		break;
	default:
		break;
	}
}

void CSettingDlg::InitLocale(LOCALE locale)
{
	CString iniName;
	switch (locale)
	{
	case LOCALE::KO:
		iniName = L"res\\locale.ko.ini";
		break;
	case LOCALE::EN:
		iniName = L"res\\locale.en.ini";
		break;
	case LOCALE::JP:
		iniName = L"res\\locale.jp.ini";
		break;
	default:
		iniName = L"res\\locale.ko.ini";
		break;
	}
	WCHAR buf[64];

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"title", NULL, buf, 64, iniName);
	this->SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"startPath", NULL, buf, 64, iniName);
	m_pathText.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"compressOrNot", NULL, buf, 64, iniName);
	m_compText.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"language", NULL, buf, 64, iniName);
	m_langText.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"handlingOverWrite", NULL, buf, 64, iniName);
	m_overwriteText.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"folderSelect", NULL, buf, 64, iniName);
	m_selDirBtn.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"apply", NULL, buf, 64, iniName);
	m_applyBtn.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"confirm", NULL, buf, 64, iniName);
	m_okBtn.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"close", NULL, buf, 64, iniName);
	m_closeBtn.SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"compressZip", NULL, buf, 64, iniName);
	GetDlgItem(IDC_COMP_ZIP_RAD)->SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"notCompress", NULL, buf, 64, iniName);
	GetDlgItem(IDC_COMP_NO_RAD)->SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"alwaysAsk", NULL, buf, 64, iniName);
	GetDlgItem(IDC_ALWAYS_ASK_RAD)->SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"alwaysOverwrite", NULL, buf, 64, iniName);
	GetDlgItem(IDC_ALWAYS_OVER_RAD)->SetWindowTextW(buf);

	ZeroMemory(buf, 64);
	GetPrivateProfileString(L"SETTING", L"alwaysChangeName", NULL, buf, 64, iniName);
	GetDlgItem(IDC_ALWAYS_CHANGE_RAD)->SetWindowTextW(buf);
}

void CSettingDlg::OnBnClickedSetdlgCloseBtn()
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE, NULL, NULL);
}

INT_PTR CSettingDlg::DoModal(LOCALE locale)
{
	m_locale = locale;
	return CDialogEx::DoModal();
}
