#include "pch.h"
#include "ImageInfos.h"


CImageInfos::CImageInfos()
	: m_isVisualized(FALSE)
{
	// empty now
}

CImageInfos::~CImageInfos()
{
	// not implemented yet
	// implement delete every CImageInfo data...
	m_infos.RemoveAll();
}

void CImageInfos::Insert(const char* key, CImageInfo* value)
{
	ASSERT(key && value);
	m_infos.SetAt(key, value);
}

BOOL CImageInfos::Lookup(const char* key, CImageInfo** value) const
{
	ASSERT(key);
	return m_infos.Lookup(key, *value);
}

BOOL CImageInfos::Delete(const char* key)
{
	ASSERT(key);
	return m_infos.RemoveKey(key);
}


BOOL CImageInfos::DeleteAll()
{
	m_infos.RemoveAll();
	return m_infos.GetCount() == 0 ? TRUE : FALSE;
}

size_t CImageInfos::GetCount() const
{
	return m_infos.GetCount();
}

void CImageInfos::GetKeys(char*** keys) const
{
	int i = 0;
	size_t keyLen = 0;

	*keys = new char* [m_infos.GetCount() + 1];
	*keys[m_infos.GetCount()] = nullptr;
	
	POSITION pos = m_infos.GetStartPosition();
	auto pair = m_infos.GetAt(pos);
	while (pos)
	{
		const char* key = m_infos.GetKeyAt(pos);
		keyLen = strlen(key);
		*keys[i] = new char[keyLen + 1];
		ZeroMemory(&(*keys[i]), keyLen + 1);
		memcpy(&(*keys[i]), key, keyLen);
		pair = m_infos.GetNext(pos);
		i++;
	}
}

CImageInfo* CImageInfos::GetValue(const char* key) const
{
	ASSERT(key);
	auto pair = m_infos.Lookup(key);
	if (pair != nullptr)
		return pair->m_value;
	else
		return nullptr;
}

BOOL CImageInfos::IsVisualized() const
{
	return m_isVisualized;
}

void CImageInfos::SetVisualized(BOOL value)
{
	m_isVisualized = value;
}