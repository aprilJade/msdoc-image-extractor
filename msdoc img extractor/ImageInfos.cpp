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
	CAtlMap<CString, CImageInfo*, CStringElementTraits<CString>>::CPair* pair = nullptr;
	while (pos)
	{
		pair = m_infos.GetAt(pos);
		delete pair->m_value;
		m_infos.GetNext(pos);
	}
	m_infos.RemoveAll();
}

void CImageInfos::Insert(CString key, CImageInfo* value)
{
	ASSERT(key && value);
	m_infos.SetAt(key, value);
}

BOOL CImageInfos::Lookup(CString key, CImageInfo** value) const
{
	ASSERT(key);
	return m_infos.Lookup(key, *value);
}

BOOL CImageInfos::Delete(CString key)
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

void CImageInfos::GetKeys(CString** keys) const
{
	int i = 0;
	size_t keyLen = 0;

	*keys = new CString[m_infos.GetCount()];
	
	POSITION pos = m_infos.GetStartPosition();
	auto pair = m_infos.GetAt(pos);
	while (pos)
	{
		(*keys)[i] = m_infos.GetKeyAt(pos);
		m_infos.GetNext(pos);
		i++;
	}
}

CImageInfo* CImageInfos::GetValue(CString key) const
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