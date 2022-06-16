#pragma once
#include <atlcoll.h>
#include "ImageInfo.h"

class CImageInfos
{
public:
	CImageInfos();
	~CImageInfos();

	BOOL Lookup(const char* key, CImageInfo** value) const;
	
	void Insert(const char* key, CImageInfo* value);
	
	BOOL Delete(const char* key);
	
	BOOL DeleteAll();
	
	size_t GetCount() const;
	
	void GetKeys(char*** keys) const;
	
	CImageInfo* GetValue(const char* key) const;

	BOOL IsVisualized() const;

	void SetVisualized(BOOL value);

private:
	BOOL m_isVisualized;
	CAtlMap<const char*, CImageInfo*> m_infos;
};

