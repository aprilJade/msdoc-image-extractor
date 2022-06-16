#pragma once
#include <atlcoll.h>
#include "ImageInfo.h"

class CImageInfos
{
public:
	CImageInfos();
	~CImageInfos();

	BOOL Lookup(const WCHAR* key, CImageInfo** value) const;
	
	void Insert(const WCHAR* key, CImageInfo* value);
	
	BOOL Delete(const WCHAR* key);
	
	BOOL DeleteAll();
	
	size_t GetCount() const;
	
	void GetKeys(WCHAR*** keys) const;
	
	CImageInfo* GetValue(const WCHAR* key) const;

	BOOL IsVisualized() const;

	void SetVisualized(BOOL value);

private:
	BOOL m_isVisualized;
	CAtlMap<const WCHAR*, CImageInfo*> m_infos;
};

