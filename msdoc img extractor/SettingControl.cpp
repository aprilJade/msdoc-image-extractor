#include "pch.h"
#include "SettingControl.h"

CSettingControl::CSettingControl()
	: m_settingFileName(L"res\\profile.ini")
{
	if (PathFileExists(m_settingFileName))
		Load();
	else
	{
		optionValues.locale = LOCALE::KO;
		optionValues.bCompress = FALSE;
		optionValues.overwrite = OVERWRITE::ALWAYS_ASK;
		WCHAR path[MAX_PATH] = { 0 };
		SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE);
		optionValues.startDir = path;
	}
}

CSettingControl::~CSettingControl()
{
	// empty now
}

BOOL CSettingControl::Save()
{
	CString value;

	if (optionValues.locale != optionValuesBuffer.locale)
	{
		optionValues.locale = optionValuesBuffer.locale;
		switch (optionValues.locale)
		{
		case LOCALE::KO:
			value = L"KO";
			break;
		case LOCALE::EN:
			value = L"EN";
			break;
		case LOCALE::JP:
			value = L"JP";
			break;
		default:
			value = L"KO";
			break;
		}
		WritePrivateProfileString(STR_OPTION, L"locale", value, m_settingFileName);
	}

	if (optionValues.bCompress != optionValuesBuffer.bCompress)
	{
		optionValues.bCompress = optionValuesBuffer.bCompress;
		if (optionValues.bCompress)
			value = L"true";
		else
			value = L"false";
		WritePrivateProfileString(STR_OPTION, L"compress", value, m_settingFileName);
	}

	if (optionValues.overwrite != optionValuesBuffer.overwrite)
	{
		optionValues.overwrite = optionValuesBuffer.overwrite;
		switch (optionValues.overwrite)
		{
		case OVERWRITE::ALWAYS_ASK:
			value = L"ALWAYS_ASK";
			break;
		case OVERWRITE::ALWAYS_OVERWRITE:
			value = L"ALWAYS_OVERWRITE";
			break;
		case OVERWRITE::ALWAYS_CHANGE_FILE_NAME:
			value = L"ALWAYS_CHANGE_FILE_NAME";
			break;
		default:
			value = L"ALWAYS_ASK";
			break;
		}
		WritePrivateProfileString(STR_OPTION, L"overwrite", value, m_settingFileName);
	}

	if (optionValues.startDir != optionValuesBuffer.startDir)
	{
		optionValues.startDir = optionValuesBuffer.startDir;
		value = optionValues.startDir;
		WritePrivateProfileString(STR_OPTION, L"startPath", value, m_settingFileName);
	}

	return TRUE;
}

BOOL CSettingControl::Load()
{
	WCHAR buf[64];

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"locale", NULL, buf, 64, m_settingFileName);
	if (wcscmp(buf, L"KO") == 0)
		optionValues.locale = LOCALE::KO;
	else if (wcscmp(buf, L"EN") == 0)
		optionValues.locale = LOCALE::EN;
	else if (wcscmp(buf, L"JP") == 0)
		optionValues.locale = LOCALE::JP;
	else
		optionValues.locale = LOCALE::KO;

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"startPath", NULL, buf, 64, m_settingFileName);
	if (wcslen(buf) == 0)
	{
		WCHAR path[MAX_PATH] = { 0 };
		SHGetSpecialFolderPath(HWND_DESKTOP, path, CSIDL_DESKTOP, FALSE);
		optionValues.startDir = path;
	}
	else
		optionValues.startDir = buf;

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"compress", NULL, buf, 64, m_settingFileName);
	if (wcscmp(buf, L"true") == 0)
		optionValues.bCompress = TRUE;
	else if (wcscmp(buf, L"false") == 0)
		optionValues.bCompress = FALSE;
	else
		optionValues.bCompress = FALSE;

	ZeroMemory(buf, 64);
	GetPrivateProfileString(STR_OPTION, L"overwrite", NULL, buf, 64, m_settingFileName);
	if (wcscmp(buf, L"ALWAYS_ASK") == 0)
		optionValues.overwrite = OVERWRITE::ALWAYS_ASK;
	else if (wcscmp(buf, L"ALWAYS_OVERWRITE") == 0)
		optionValues.overwrite = OVERWRITE::ALWAYS_OVERWRITE;
	else if (wcscmp(buf, L"ALWAYS_CHANGE_FILE_NAME") == 0)
		optionValues.overwrite = OVERWRITE::ALWAYS_CHANGE_FILE_NAME;
	else
		optionValues.overwrite = OVERWRITE::ALWAYS_ASK;

	optionValuesBuffer = optionValues;

	return TRUE;
}

LOCALE CSettingControl::GetLocale() const
{
	return optionValuesBuffer.locale;
}

BOOL CSettingControl::GetCompress() const
{
	return optionValuesBuffer.bCompress;
}

OVERWRITE CSettingControl::GetOverwrite() const
{
	return optionValuesBuffer.overwrite;
}

CString CSettingControl::GetStartDirectory() const
{
	return optionValuesBuffer.startDir;
}

void CSettingControl::SetLocale(const LOCALE value)
{
	optionValuesBuffer.locale = value;
}

void CSettingControl::SetCompress(const BOOL value)
{
	optionValuesBuffer.bCompress = value;
}

void CSettingControl::SetOverwirte(const OVERWRITE value)
{
	optionValuesBuffer.overwrite = value;
}

void CSettingControl::SetStartDirectory(const CString value)
{
	optionValuesBuffer.startDir = value;
}