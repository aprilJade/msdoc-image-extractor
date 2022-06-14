#include "pch.h"
#include "DocCtrl.h"

CDocCtrl::CDocCtrl(CString filePath)
	: m_filePath(filePath)
{
}

CDocCtrl::~CDocCtrl()
{
}

int CDocCtrl::Parse(CAtlList<SImageInfo*>& imageInfo)
{
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
	const char* mediaPath = "xl/media";
	SPKZipHeader* pkHdr;
	while (TRUE)
	{
		pkHdr = (SPKZipHeader*)pData;
		if (pkHdr->signature != PK_ZIP_SIGNATURE)
		{
			// Todo: implement error handling
			// Notify file signature is not valid
			UnmapViewOfFile(data);
			CloseHandle(hMMF);
			CloseHandle(hFile);
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

		SImageInfo* info = new SImageInfo;
		ZeroMemory(info, sizeof(SImageInfo));


		info->name = new char[pkHdr->fileNameLen + 1];
		ZeroMemory(info->name, pkHdr->fileNameLen + 1);
		memcpy(info->name, pData + sizeof(SPKZipHeader), pkHdr->fileNameLen);
		
		info->dataSize = pkHdr->uncompressedSize;
		info->data = new BYTE[pkHdr->uncompressedSize];
		ZeroMemory(info->data, pkHdr->uncompressedSize);
		pData += sizeof(SPKZipHeader) + pkHdr->fileNameLen + pkHdr->extraFieldLen;
		memcpy(info->data, pData, pkHdr->compressedSize);
		
		imageInfo.InsertAfter(imageInfo.GetTailPosition(), info);
		pData += pkHdr->compressedSize;
	} while (strncmp(pData + sizeof(SPKZipHeader), mediaPath, strlen(mediaPath)) == 0);
	

	UnmapViewOfFile(data);
	CloseHandle(hMMF);
	CloseHandle(hFile);

	return imageInfo.GetCount();
}