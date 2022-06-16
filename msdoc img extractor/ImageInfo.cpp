#include "pch.h"
#include "ImageInfo.h"

CImageInfo::CImageInfo(const char* imgName, const size_t length)
	: m_data(nullptr)
	, m_dataSize(0)
{
	ASSERT(imgName && length > 0);

	WCHAR* buf = new WCHAR[length + 1];
	size_t convertedCnt = 0;
	ZeroMemory(buf, sizeof(WCHAR) * (length + 1));
	mbstowcs_s(&convertedCnt, buf, length + 1, imgName, length);
	m_name.Format(buf);
	delete[] buf;
}

CImageInfo::~CImageInfo()
{
	if (m_data != nullptr)
		delete[] m_data;
}

void CImageInfo::CopyToBuffer(const BYTE* srcImg, const size_t srcSize)
{
	ASSERT(srcImg && srcSize > 0);
	if (m_data == nullptr)
	{
		m_data = new BYTE[srcSize];
		ZeroMemory(m_data, srcSize);
		m_dataSize = srcSize;
	}

	memcpy(m_data, srcImg, srcSize);
}

const BYTE* CImageInfo::GetDataRef() const
{
	return m_data ? m_data : nullptr;
}

void CImageInfo::ReleaseData()
{
	if (m_data != nullptr)
	{
		delete[] m_data;
		m_data = nullptr;
		m_dataSize = 0;
	}
}


CString CImageInfo::GetImageName() const
{
	return m_name;
}