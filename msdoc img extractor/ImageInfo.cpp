#include "pch.h"
#include "ImageInfo.h"

CImageInfo::CImageInfo(const char* imgName, const size_t length)
	: m_data(nullptr)
	, m_dataSize(0)
{
	ASSERT(imgName && length > 0);
	m_name = new char[length + 1];
	ZeroMemory(m_name, length + 1);
	memcpy(m_name, imgName, length);
}

CImageInfo::~CImageInfo()
{
	if (m_data != nullptr)
		delete[] m_data;
	if (m_name != nullptr)
		delete[] m_name;
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
	return m_data;
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


const char* CImageInfo::GetImageName() const
{
	return m_name;
}