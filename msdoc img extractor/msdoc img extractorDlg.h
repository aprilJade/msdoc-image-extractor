
// msdoc img extractorDlg.h : header file
//

#pragma once

#include "DocParser.h"

#define SUPPORT_EXT_CNT 3

// CmsdocimgextractorDlg dialog
class CmsdocimgextractorDlg : public CDialogEx
{
// Construction
public:
	CmsdocimgextractorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MSDOC_IMG_EXTRACTOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CTreeCtrl m_fileTree;
	CTreeCtrl m_ImageTree;
	
	void InitializeFileTree();
	CString GetSelectedItemPath(HTREEITEM hItem);
	afx_msg void OnTvnItemexpandingDirTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTvnSelchangedDirTree(NMHDR* pNMHDR, LRESULT* pResult);

private:
	CDocParser* m_docParser;
	TCHAR* m_supportExt[SUPPORT_EXT_CNT] = { L"pptx", L"xlsx", L"docx" };
	bool IsSupportedFile(CString path);
	void ListUpImages(CAtlList<CImageInfo*>& imageInfo, CString filePath);
public:
	afx_msg void OnDestroy();
};
