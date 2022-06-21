#pragma once

enum LOCALE
{
	KO,
	EN,
	JP
};

enum OVERWRITE
{
	ALWAYS_ASK,
	ALWAYS_OVERWRITE,
	ALWAYS_CHANGE_FILE_NAME
};

class CSettingControl
{
public:
	CSettingControl();
	~CSettingControl();

	BOOL Save();
	BOOL Load();

	LOCALE GetLocale() const;
	BOOL GetCompress() const;
	OVERWRITE GetOverwrite() const;
	CString GetStartDirectory() const;

	void SetLocale(const LOCALE);
	void SetCompress(const BOOL);
	void SetOverwirte(const OVERWRITE);
	void SetStartDirectory(const CString);

private:
	LOCALE m_locale;
	BOOL b_compress;
	OVERWRITE m_overwrite;
	CString m_startDirectory;
	CString m_settingFileName;
	const WCHAR* STR_OPTION = L"OPTION";
};

