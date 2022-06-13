#pragma once
#include <atlcoll.h>

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

typedef struct s_ImageCtrl
{
	UINT dataSize;
	BYTE* data;
	UINT position;
} SImageInfo;

class CDocCtrl
{
public:
	CDocCtrl(CString filePath);
	~CDocCtrl();

	CString GetFilePath() { return m_filePath; }
	CString SetFilePath(CString filePath) { m_filePath = filePath; }

	void Parse(CAtlList<SImageInfo>& imageInfo);

private:
	BOOL IsImageSegment(char* buf);
	size_t GetSegmentSize(char* data);

private:
	CString m_filePath;
	CAtlList<SImageInfo>* m_images;
};

