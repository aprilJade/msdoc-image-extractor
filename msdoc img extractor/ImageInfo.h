#pragma once

class CImageInfo
{
public:
	CImageInfo(const char* imgName, const size_t length);
	~CImageInfo();

	void CopyToBuffer(const BYTE* srcImg, const size_t srcSize);
	const BYTE* GetDataRef() const;
	void ReleaseData();
	const char* GetImageName() const;

private:
	size_t m_dataSize;
	BYTE* m_data;
	char* m_name;
};

