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

void CDocCtrl::Parse(CAtlList<SImageInfo>& imageInfo)
{
	// Not implemented yet
}
