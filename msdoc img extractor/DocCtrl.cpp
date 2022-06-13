#include "pch.h"
#include "DocCtrl.h"

CDocCtrl::CDocCtrl(CString filePath)
	: m_filePath(filePath)
{
	m_images = new CAtlList<SImageInfo>;
}

CDocCtrl::~CDocCtrl()
{
	if (m_images != nullptr)
	{
		delete m_images;
	}
}

void CDocCtrl::Parse(CAtlList<SImageInfo>& imageInfo)
{
	FILE* fp = nullptr;
	size_t ret = 0;
	_wfopen_s(&fp, m_filePath, L"r");
	if (fp == nullptr)
	{
		// Todo: implement error handling
		return;
	}
	size_t pkHdrSize = sizeof(SPKZipHeader);
	char* buf = new char[pkHdrSize];
	size_t firstSegmentOffset = 0;
	do
	{
		ZeroMemory(buf, pkHdrSize);
		ret = fread_s(buf, pkHdrSize, sizeof(char), pkHdrSize, fp);
		if (ret < pkHdrSize)
		{
			// Todo: implement error handling
			break;
		}
		fseek(fp, GetSegmentSize(buf) - pkHdrSize, SEEK_CUR);
	} while (IsImageSegment(buf) == FALSE);


	delete[] buf;
}

BOOL CDocCtrl::IsImageSegment(char* buf)
{
	// not implement yet
	return TRUE;
}


size_t CDocCtrl::GetSegmentSize(char* data)
{
	size_t ret = 0;
	SPKZipHeader* hdr = (SPKZipHeader*)data;
	ret += hdr->compressedSize + hdr->fileNameLen + hdr->extraFieldLen + sizeof(hdr);
	return  ret;
}