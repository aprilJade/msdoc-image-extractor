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

int CDocCtrl::Parse(CAtlList<SImageInfo>& imageInfo)
{
	size_t ret = 0;

	// Disk I/O version
	// Error: I try to read 30 bytes, but fread_s() is return zero with no error....
	// I don't know what is wrong...
#if 0
	FILE* fp = nullptr;
	_wfopen_s(&fp, m_filePath, L"r");
	if (fp == nullptr)
	{
		// Todo: implement error handling
		return -1;
	}

	char buf[PK_ZIP_HEADER_SIZE];
	size_t firstSegmentOffset = 0;
	size_t size;
	char fileNameBuf[64];
	while (TRUE)
	{
		ZeroMemory(buf, PK_ZIP_HEADER_SIZE);
		size = 0;
		while ((ret = fread_s(buf + size, 30 - size, sizeof(char), 30 - size, fp)) != EOF)
		{
			size += ret;
			if (size == PK_ZIP_HEADER_SIZE)
				break;
			if (ret == 0)
			{
				auto err = GetLastError();
				int adsf = 3;
			}
		}
		ZeroMemory(fileNameBuf, 64);
		SPKZipHeader* hdr = (SPKZipHeader*)buf;
		ret = fread_s(fileNameBuf, PK_ZIP_HEADER_SIZE, sizeof(char), hdr->fileNameLen, fp);
		fseek(fp, hdr->compressedSize + hdr->extraFieldLen, SEEK_CUR);
	}

#else
	// MMF version... let's try this.
	HANDLE hFile = CreateFile(m_filePath, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		// Todo: implement error handling

		auto err = GetLastError();
		return -1;
	}

	HANDLE hMMF = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, nullptr);
	if (hMMF == nullptr)
	{
		// Todo: implement error handling
		auto err = GetLastError();
		CloseHandle(hFile);
		return -1;
	}

	char* data = (char*)MapViewOfFile(hMMF, FILE_MAP_READ, 0, 0, 0);
	if (data == nullptr)
	{
		// Todo: implement error handling
		auto err = GetLastError();
		CloseHandle(hMMF);
		CloseHandle(hFile);
		return -1;
	}

	char* pData = data;
	char* mediaPath = "xl/media";
	SPKZipHeader* pkHdr;
	while (TRUE)
	{
		pkHdr = (SPKZipHeader*)pData;
		if (pkHdr->signature != 0x04034b50)
		{
			// Todo: implement error handling
			// Notify file signature is not valid
			return -2;
		}
		if (strncmp(pData + sizeof(SPKZipHeader), mediaPath, strlen(mediaPath)) == 0)
		{
			break;
		}
		pData += sizeof(SPKZipHeader) + pkHdr->compressedSize + pkHdr->fileNameLen + pkHdr->extraFieldLen;
	}

	do
	{
		pkHdr = (SPKZipHeader*)pData;
		if (pkHdr->compressedSize != pkHdr->uncompressedSize)
		{
			// this image file is compressed. 
			// decompress using zlib
			// Not implemented yet
			continue;
		}

		BYTE* imgBuf = new BYTE[pkHdr->uncompressedSize];
		ZeroMemory(imgBuf, pkHdr->uncompressedSize);
		SImageInfo info;
		ZeroMemory(&info, sizeof(SImageInfo));
		info.data = imgBuf;
		info.dataSize = pkHdr->uncompressedSize;
		info.name = new char[pkHdr->fileNameLen + 1];
		ZeroMemory(info.name, pkHdr->fileNameLen + 1);
		memcpy(info.name, pData + sizeof(SPKZipHeader), pkHdr->fileNameLen);
		pData += sizeof(SPKZipHeader) + pkHdr->fileNameLen + pkHdr->extraFieldLen;
		memcpy(info.data, pData, pkHdr->compressedSize);
		imageInfo.InsertAfter(imageInfo.GetTailPosition(), info);
		pData += pkHdr->compressedSize;
	} while (strncmp(pData + sizeof(SPKZipHeader), mediaPath, strlen(mediaPath)) == 0);
	

	UnmapViewOfFile(data);
	CloseHandle(hMMF);
	CloseHandle(hFile);

#endif
	return imageInfo.GetCount();
}

BOOL CDocCtrl::IsImageSegment(char* buf)
{
	SPKZipHeader* hdr = (SPKZipHeader*)buf;
	return TRUE;
}


size_t CDocCtrl::GetSegmentSize(char* data)
{
	size_t ret = 0;
	SPKZipHeader* hdr = (SPKZipHeader*)data;
	ret += hdr->compressedSize + hdr->fileNameLen + hdr->extraFieldLen + sizeof(hdr);
	return  ret;
}