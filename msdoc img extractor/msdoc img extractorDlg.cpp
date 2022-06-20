
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
	DDX_Control(pDX, IDC_DIR_TREE, m_fileTree);
	DDX_Control(pDX, IDC_IMG_TREE, m_ImageTree);
	DDX_Control(pDX, IDC_IMG_PREVIEW, m_ImagePreview);
	DDX_Control(pDX, IDC_SEL_ALL_BTN, m_selAllBtn);
}

BEGIN_MESSAGE_MAP(CmsdocimgextractorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_DIR_TREE, &CmsdocimgextractorDlg::OnTvnItemexpandingDirTree)
	ON_NOTIFY(TVN_SELCHANGED, IDC_DIR_TREE, &CmsdocimgextractorDlg::OnTvnSelchangedDirTree)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_EXTRACT_BTN, &CmsdocimgextractorDlg::OnBnClickedExtractBtn)
	ON_NOTIFY(TVN_SELCHANGED, IDC_IMG_TREE, &CmsdocimgextractorDlg::OnTvnSelchangedImgTree)
	ON_BN_CLICKED(IDC_SEL_ALL_BTN, &CmsdocimgextractorDlg::OnBnClickedSelAllBtn)
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
	someDlg.DoModal();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	SetBackgroundColor(RGB(255, 255, 255));
	m_docParser = new CDocParser();
	
	InitializeFileTree();
	m_ImagePreview.GetWindowRect(&m_previewRect);
	ScreenToClient(&m_previewRect);
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
	CPaintDC dc(this);
	if (IsIconic())
	{

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
		if (m_imageCtrl.IsNull() == FALSE)
		{
			RECT rect;
			BITMAP bmpInfo;
			GetObject(m_imageCtrl, sizeof(BITMAP), &bmpInfo);
			dc.FillSolidRect(&m_previewRect, RGB(255, 255, 255));
			GetPerfectFitRect(bmpInfo.bmWidth, bmpInfo.bmHeight, m_previewRect, &rect);
			dc.SetStretchBltMode(COLORONCOLOR);
			m_imageCtrl.Draw(dc, rect);
		}
		CDialogEx::OnPaint();
	}
}

void CmsdocimgextractorDlg::GetPerfectFitRect(int imgWidth, int imgHeight, RECT frame, LPRECT fitRect)
{
	int frameWidth = frame.right - frame.left;
	int frameHeight = frame.bottom -frame.top;
	float scaleValue = 0.0;
	int offset = 0;

	CopyRect(fitRect, &frame);
	if (imgWidth - imgHeight > 0)
	{
		scaleValue = (float)frameWidth / (float)imgWidth;
		int newHeight = (float)imgHeight * scaleValue;
		offset = (frameHeight - newHeight) / 2;
		fitRect->top += offset;
		fitRect->bottom -= offset;
	} 
	else
	{
		scaleValue = (float)frameHeight / (float)imgHeight;
		int newWidth = (float)imgWidth * scaleValue;
		offset = (frameWidth - newWidth) / 2;
		fitRect->left += offset;
		fitRect->right -= offset;
	}
}

HCURSOR CmsdocimgextractorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CmsdocimgextractorDlg::IsSupportedFile(CString path)
{
	int i = path.ReverseFind('.');
	if (i > 0)
	{
		TCHAR* buf = path.GetBuffer();

		for (int idx = 0; idx < SUPPORT_EXT_CNT; idx++)
			if (StrCmpW(buf + i + 1, m_supportExt[idx]) == 0)
				return true;
	}
	return false;
}

void CmsdocimgextractorDlg::InitializeFileTree()
{
	CString defualtPath = L"C:/Users/apriljade/Desktop";
	
	// Todo: add item icon
	HTREEITEM hItem = m_fileTree.InsertItem(defualtPath);

	CFileFind finder;
	BOOL bWorking = finder.FindFile(defualtPath + L"/*");

	while (bWorking) 
	{
		bWorking = finder.FindNextFileW();
		
		if (!finder.IsDots() && !finder.IsHidden())
		{
			if (finder.IsDirectory() == false)
			{
				if (IsSupportedFile(finder.GetFilePath()) == false)
					continue;
			}
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
		ret = m_fileTree.GetItemText(hParent) + L"/" + ret;
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
			break;

		CString selectedPath = GetSelectedItemPath(hItem);
		bFlag = finder.FindFile(selectedPath + L"/*");

		while (bFlag)
		{
			bFlag = finder.FindNextFileW();
			if (!finder.IsDots() && !finder.IsHidden())
			{
				if (!finder.IsDirectory() && !IsSupportedFile(finder.GetFilePath()))
					continue;
				
				m_fileTree.InsertItem(finder.GetFileName(), hItem);
			}
		}

		hItem = m_fileTree.GetNextSiblingItem(hItem);
	}

	*pResult = 0;
}

void CmsdocimgextractorDlg::ListUpImages(CImageInfos* imageInfo, CString filePath)
{
	HTREEITEM hItem = m_ImageTree.InsertItem(filePath);
	
	if (imageInfo->IsVisualized())
		return;

	CString* keys = nullptr;
	imageInfo->GetKeys(&keys);

	for (int i = 0; i < imageInfo->GetCount(); i++)
		m_ImageTree.InsertItem(keys[i], hItem);

	m_ImageTree.EnsureVisible(hItem);
	m_ImageTree.Expand(hItem, TVE_EXPAND);
	imageInfo->SetVisualized(TRUE);

	delete[] keys;
}

void CmsdocimgextractorDlg::OnTvnSelchangedDirTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CString filePath = GetSelectedItemPath(hItem);
	
	if (!IsSupportedFile(filePath))
		return;

	auto pair = m_map.Lookup(filePath);
	if (pair != nullptr)
		return;

	CImageInfos* imageInfo = new CImageInfos();
	m_docParser->Parse(filePath, imageInfo);

	ListUpImages(imageInfo, filePath);
	m_map.SetAt(filePath, imageInfo);

	*pResult = 0;
}


void CmsdocimgextractorDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	delete m_docParser;

	POSITION pos = m_map.GetStartPosition();
	CAtlMap<CString, CImageInfos*, CStringElementTraits<CString>>::CPair* pair = nullptr;
	while (pos)
	{
		pair = m_map.GetAt(pos);
		delete pair->m_value;
		m_map.GetNext(pos);
	}
	m_map.RemoveAll();
}

void CmsdocimgextractorDlg::OnBnClickedExtractBtn()
{
	// TODO: Add your control notification handler code here
	CFolderPickerDialog dlg;
	if (IDOK == dlg.DoModal())
	{
		CFile fileCtrl;
		CString dirPath = dlg.GetFolderPath();
		
		HTREEITEM hChild = NULL;
		HTREEITEM hParent = m_ImageTree.GetFirstVisibleItem();
		while (hParent)
		{
			hChild = m_ImageTree.GetChildItem(hParent);
			while (hChild)
			{
				//CString str = m_ImageTree.GetItemText(hChild);
				//BOOL res = m_ImageTree.GetCheck(hChild);
				if (m_ImageTree.GetCheck(hChild))
				{
					CString filePath = m_ImageTree.GetItemText(hParent);
					auto pair = m_map.Lookup(filePath);
					if (pair == nullptr)
					{
						// Todo: handling fail to lookup
						continue;
					}
					// Todo: If file exist already, then ask to user how to handle.
					// 1. Replace file
					// 2. Rename file (eg. add number to file name or append "- copy")
					// 3. Default is append -copy
					CString imagePath = m_ImageTree.GetItemText(hChild);
					CImageInfo* info = pair->m_value->GetValue(imagePath);
					imagePath = imagePath.Right(imagePath.GetLength() - imagePath.ReverseFind(L'/') - 1);
					
					CString newFilePath = dirPath + L"\\" + imagePath;

					// if replace or numbering copy setting value is invalid
					// ask to user...
					if (MessageBox(L"중복된 파일이 있어요. 덮어쓰시겠어요?", L"알림", MB_YESNO) == IDNO)
					{
						for (int i = 0; PathFileExists(newFilePath); i++) // when select or set numbering copy
						{
							size_t idx = imagePath.GetLength() - imagePath.ReverseFind(L'.');
							CString ext = imagePath.Right(idx - 1);
							CString name = imagePath.Left(idx + 1);
							CString numbering;
							numbering.Format(L"(%d).", i);
							newFilePath = dirPath + L"\\" + name + numbering + ext;
						}
					}

					if (fileCtrl.Open(dirPath + L"\\" + imagePath, CFile::modeCreate | CFile::modeWrite) == FALSE)
					{
						// Todo: handling fail to create file
						continue;
					}
					fileCtrl.Write(info->GetDataRef(), info->GetDataSize());
					fileCtrl.Close();
				}
				hChild = m_ImageTree.GetNextSiblingItem(hChild);
			}
			hParent = m_ImageTree.GetNextSiblingItem(hParent);
		}

		MessageBox(L"추출이 완료되었어요!", L"안내", MB_OK);
	}
}


void CmsdocimgextractorDlg::OnTvnSelchangedImgTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	CString imgPath = m_ImageTree.GetItemText(hItem);
	HTREEITEM hParent = m_ImageTree.GetParentItem(hItem);
	CString filePath = m_ImageTree.GetItemText(hParent);

	auto pair = m_map.Lookup(filePath);
	if (pair == nullptr)
	{
		// Todo: handling error
		return;
	}
	CImageInfo* info = nullptr;
	if (pair->m_value->Lookup(imgPath, &info) == FALSE)
	{
		// Todo: handling error
		return;
	}
	ULONG result;
	// Todo: alloc global buffer just once at application started. and reuse buffer.
	HGLOBAL h_buffer = GlobalAlloc(GMEM_MOVEABLE, 1024 * 1024 * 8);
	auto a = info->GetDataRef();
	if (h_buffer != NULL) 
	{   
		IStream* p_stream = NULL;
		if (CreateStreamOnHGlobal(h_buffer, FALSE, &p_stream) == S_OK) 
		{
			p_stream->Write((void*)info->GetDataRef(), info->GetDataSize(), &result);
			if (m_imageCtrl.IsNull() == FALSE)
				m_imageCtrl.Destroy();
			
			if (m_imageCtrl.Load(p_stream) == S_OK)
				InvalidateRect(&m_previewRect, FALSE);
			
			p_stream->Release();  
		}
		GlobalFree(h_buffer); 
	}
	*pResult = 0;
}


void CmsdocimgextractorDlg::OnBnClickedSelAllBtn()
{
	HTREEITEM hItem = m_ImageTree.GetFirstVisibleItem();
	if (bAllChecked == FALSE)
	{
		m_selAllBtn.SetWindowTextW(L"전체 해제");
		bAllChecked = TRUE;
	}
	else
	{
		m_selAllBtn.SetWindowTextW(L"전체 선택");
		bAllChecked = FALSE;
	}
	while (hItem)
	{
		m_ImageTree.SetCheck(hItem, bAllChecked);
		hItem = m_ImageTree.GetNextVisibleItem(hItem);
	}
}
