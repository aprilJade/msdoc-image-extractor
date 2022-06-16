#include "pch.h"
#include "ImageInfos.h"


CImageInfos::CImageInfos()
	: m_isVisualized(FALSE)
{
	// empty now
}

CImageInfos::~CImageInfos()
{
	POSITION pos = m_infos.GetStartPosition();
	CAtlMap<const WCHAR*, CImageInfo*>::CPair* pair = nullptr;
	while (pos)
	{
		pair = m_infos.GetAt(pos);
		delete pair->m_value;
		m_infos.GetNext(pos);
	}
	m_infos.RemoveAll();
}

void CImageInfos::Insert(const WCHAR* key, CImageInfo* value)
{
	ASSERT(key && value);
	m_infos.SetAt(key, value);
}

BOOL CImageInfos::Lookup(const WCHAR* key, CImageInfo** value) const
{
	ASSERT(key);
	return m_infos.Lookup(key, *value);
}

BOOL CImageInfos::Delete(const WCHAR* key)
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

void CImageInfos::GetKeys(WCHAR*** keys) const
{
	int i = 0;
	size_t keyLen = 0;

	*keys = new WCHAR* [m_infos.GetCount()];
	
	POSITION pos = m_infos.GetStartPosition();
	auto pair = m_infos.GetAt(pos);
	while (pos)
	{
		const WCHAR* key = m_infos.GetKeyAt(pos);
		keyLen = wcslen(key);
		(*keys)[i] = new WCHAR[keyLen + 1];
		ZeroMemory((*keys)[i], sizeof(WCHAR) * (keyLen + 1));
		memcpy((*keys)[i], key, keyLen * 2);
		m_infos.GetNext(pos);
		i++;
	}
}

CImageInfo* CImageInfos::GetValue(const WCHAR* key) const
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