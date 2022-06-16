#pragma once
#include <atlcoll.h>
#include "ImageInfo.h"

class CImageInfos
{
public:
	CImageInfos();
	~CImageInfos();

	BOOL Lookup(CString key, CImageInfo** value) const;
	
	void Insert(CString key, CImageInfo* value);
	
	BOOL Delete(CString key);
	
	BOOL DeleteAll();
	
	size_t GetCount() const;
	
	void GetKeys(CString** keys) const;
	
	CImageInfo* GetValue(CString key) const;

	BOOL IsVisualized() const;

	void SetVisualized(BOOL value);

private:
	BOOL m_isVisualized;
	CAtlMap<CString, CImageInfo*, CStringElementTraits<CString>> m_infos;
};

