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
	class COptionValues
	{
	public:
		BOOL operator==(COptionValues& ref)
		{
			if (this->locale != ref.locale)
				return FALSE;
			if (this->bCompress != ref.bCompress)
				return FALSE;
			if (this->overwrite != ref.overwrite)
				return FALSE;
			if (this->startDir != ref.startDir)
				return FALSE;
			return TRUE;
		};

		BOOL operator!=(COptionValues& ref)
		{
			return *this == ref ? FALSE : TRUE;
		};

		COptionValues& operator=(COptionValues& ref)
		{
			this->locale = ref.locale;
			this->bCompress = ref.bCompress;
			this->overwrite = ref.overwrite;
			this->startDir = ref.startDir;
			return *this;
		};

		LOCALE locale;
		BOOL bCompress;
		OVERWRITE overwrite;
		CString startDir;
	};

	COptionValues optionValues;
	COptionValues optionValuesBuffer;

	CString m_settingFileName;
	const WCHAR* STR_OPTION = L"OPTION";
};

