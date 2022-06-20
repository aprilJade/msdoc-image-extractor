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

	struct STR_LOCALE
	{
		struct EXTRACT_SELECT_DIALOG
		{
			CString strText;
			CString checkBox;
			CString yes;
			CString no;
			CString title;
		};
		struct MAIN_DIALOG
		{
			CString title;
			CString setting;
			CString selAll;
			CString extract;
		};
		struct SETTING_DIALOG
		{
			CString title;
			CString startPath;

			CString compressOrNot;
			CString compress;
			CString notCompress;
			
			CString language;
			CString handlingOverwrite;
			CString alwaysAsk;
			CString alwaysOverwrite;
			CString alwaysChangeName;

			CString folderSelect;
			CString apply;
			CString confirm;
			CString close;
		};
	};

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
};

