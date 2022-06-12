
// msdoc img extractorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "msdoc img extractor.h"
#include "msdoc img extractorDlg.h"
#include "afxdialogex.h"

#include "ZlibWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CmsdocimgextractorDlg::CmsdocimgextractorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MSDOC_IMG_EXTRACTOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmsdocimgextractorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEL_PATH_EDIT, m_pathEdit);
	DDX_Control(pDX, IDC_DIR_TREE, m_fileTree);
}

BEGIN_MESSAGE_MAP(CmsdocimgextractorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_DIR_TREE, &CmsdocimgextractorDlg::OnTvnItemexpandingDirTree)
END_MESSAGE_MAP()

BOOL CmsdocimgextractorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	
	InitializeFileTree();

	CZlibWrapper zlib;

	return TRUE; 
}

void CmsdocimgextractorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CmsdocimgextractorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CmsdocimgextractorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmsdocimgextractorDlg::InitializeFileTree()
{
	CString defualtPath = L"C:";
	
	// Todo: add item icon
	HTREEITEM hItem = m_fileTree.InsertItem(defualtPath);

	CFileFind finder;
	BOOL bWorking = finder.FindFile(defualtPath + L"\\*");

	while (bWorking) 
	{
		bWorking = finder.FindNextFileW();
		
		if (!finder.IsDots() && !finder.IsHidden())
		{
			m_fileTree.InsertItem(finder.GetFileName(), hItem);
		}
	}

	m_fileTree.EnsureVisible(hItem);
	m_fileTree.Expand(hItem, TVE_EXPAND);
}

CString CmsdocimgextractorDlg::GetSelectedItemPath(HTREEITEM hItem)
{
	CString ret = m_fileTree.GetItemText(hItem);

	HTREEITEM hParent = m_fileTree.GetParentItem(hItem);
	while (hParent)
	{
		ret = m_fileTree.GetItemText(hParent) + L"\\" + ret;
		hParent = m_fileTree.GetParentItem(hParent);
	}

	return ret;
}

void CmsdocimgextractorDlg::OnTvnItemexpandingDirTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CFileFind finder;
	BOOL bFlag;

	hItem = m_fileTree.GetChildItem(hItem);
	
	while (hItem)
	{
		if (m_fileTree.ItemHasChildren(hItem))
		{
			break;
		}

		CString selectedPath = GetSelectedItemPath(hItem);
		bFlag = finder.FindFile(selectedPath + L"\\*");

		while (bFlag)
		{
			bFlag = finder.FindNextFileW();
			if (!finder.IsDots() && !finder.IsHidden())
			{
				m_fileTree.InsertItem(finder.GetFileName(), hItem);
			}
		}

		hItem = m_fileTree.GetNextSiblingItem(hItem);
	}

	*pResult = 0;
}

