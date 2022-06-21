#include "pch.h"
#include "SettingControl.h"

CSettingControl::CSettingControl()
	: m_settingFileName(L"res\\profile.ini")
{
	if (PathFileExists(m_settingFileName))
		Load();
	else
	{
		m_locale = LOCALE::KO;
		b_compress = FALSE;
		m_overwrite = OVERWRITE::ALWAYS_ASK;
		WCHAR path[MAX_PATH] = { 0 };
		SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE);
		m_startDirectory = path;
	}
}

CSettingControl::~CSettingControl()
{
	// empty now
}

BOOL CSettingControl::Save()
{
	// not implemented yet
	return TRUE;
}

BOOL CSettingControl::Load()
{
	WCHAR buf[64];

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"locale", NULL, buf, 64, m_settingFileName);
	if (wcscmp(buf, L"KO") == 0)
		m_locale = LOCALE::KO;
	else if (wcscmp(buf, L"EN") == 0)
		m_locale = LOCALE::EN;
	else if (wcscmp(buf, L"JP") == 0)
		m_locale = LOCALE::JP;
	else
		m_locale = LOCALE::KO;

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"startPath", NULL, buf, 64, m_settingFileName);
	if (wcslen(buf) == 0)
	{
		WCHAR path[MAX_PATH] = { 0 };
		SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE);
		m_startDirectory = path;
	}
	else
		m_startDirectory = buf;

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"compress", NULL, buf, 64, m_settingFileName);
	if (wcscmp(buf, L"true") == 0)
		b_compress = TRUE;
	else if (wcscmp(buf, L"false") == 0)
		b_compress = FALSE;
	else
		b_compress = FALSE;

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"overwrite", NULL, buf, 64, m_settingFileName);
	if (wcscmp(buf, L"ALWAYS_ASK") == 0)
		m_overwrite = OVERWRITE::ALWAYS_ASK;
	else if (wcscmp(buf, L"ALWAYS_OVERWRITE") == 0)
		m_overwrite = OVERWRITE::ALWAYS_OVERWRITE;
	else if (wcscmp(buf, L"ALWAYS_CHANGE_FILE_NAME") == 0)
		m_overwrite = OVERWRITE::ALWAYS_CHANGE_FILE_NAME;
	else
		m_overwrite = OVERWRITE::ALWAYS_ASK;

	return TRUE;
}

LOCALE CSettingControl::GetLocale() const
{
	return m_locale;
}

BOOL CSettingControl::GetCompress() const
{
	return b_compress;
}

OVERWRITE CSettingControl::GetOverwrite() const
{
	return m_overwrite;
}

CString CSettingControl::GetStartDirectory() const
{
	return m_startDirectory;
}

void CSettingControl::SetLocale(const LOCALE value)
{
	m_locale = value;
}

void CSettingControl::SetCompress(const BOOL value)
{
	b_compress = value;
}

void CSettingControl::SetOverwirte(const OVERWRITE value)
{
	m_overwrite = value;
}

void CSettingControl::SetStartDirectory(const CString value)
{
	m_startDirectory = value;
}