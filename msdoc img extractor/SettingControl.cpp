#include "pch.h"
#include "SettingControl.h"

CSettingControl::CSettingControl()
	: m_settingFileName(L"config.ini")
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
	// not implemented yet
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