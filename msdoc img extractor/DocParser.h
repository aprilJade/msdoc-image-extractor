#pragma once
#include <atlcoll.h>
#include "ImageInfo.h"

#define PK_ZIP_SIGNATURE 0x04034b50	// little endian

typedef struct s_PKZipHeader
{
	UINT signature;
	USHORT version;
	USHORT flag;
	USHORT compressionMethod;
	USHORT modTime;
	USHORT modDate;
	UINT crc32Checksum;
	UINT compressedSize;
	UINT uncompressedSize;
	USHORT fileNameLen;
	USHORT extraFieldLen;
} SPKZipHeader;

typedef CAtlList<CImageInfo*> ImageInfos;

class CDocParser
{
public:
	CDocParser();
	CDocParser(CString filePath);
	~CDocParser();

	CString GetFilePath() { return m_filePath; }
	CString SetFilePath(CString filePath) { m_filePath = filePath; }

	int Parse(CString filePath, ImageInfos& imageInfo);

private:
	CString m_filePath;
};

