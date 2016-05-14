// TestOverviewDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PsycologyTest.h"
#include "TestOverviewDialog.h"
#include "afxdialogex.h"
#include "../Utilities/FileSystem.h"
#include "../PsiCommon/TestManager.h"
#include "PsycologyTestDlg.h"

// CTestOverviewDialog dialog

IMPLEMENT_DYNAMIC(CTestOverviewDialog, CDialogEx)

CTestOverviewDialog::CTestOverviewDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_OVERVIEW, pParent)
	, _working_folder(_T(""))
{

}

CTestOverviewDialog::~CTestOverviewDialog()
{
}

void CTestOverviewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_WORKING_FOLDER, _working_folder_edit);
	DDX_Text(pDX, IDC_EDIT_WORKING_FOLDER, _working_folder);
	DDX_Control(pDX, IDC_LIST_SCALES, _scale_list);
}


BEGIN_MESSAGE_MAP(CTestOverviewDialog, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_WORKING_FOLDER, &CTestOverviewDialog::OnEnChangeEditWorkingFolder)
	ON_BN_CLICKED(IDC_START, &CTestOverviewDialog::OnBnClickedStart)
END_MESSAGE_MAP()


// CTestOverviewDialog message handlers


void CTestOverviewDialog::OnEnChangeEditWorkingFolder()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	UpdateData();
	if (FileSystem::FileExists(_working_folder))
	{
		_scale_list.Clear();
		FileSystem::ForEachFile(_working_folder, _T("*.scale"), false, [this](const CString& file) {
			CString filename = FileSystem::GetFileNameFromPath(file);
			this->_scale_list.InsertScale(filename, true);
		});

		CRegKey regkey;
		if (regkey.Open(HKEY_CURRENT_USER, _T("Software\\SKMR\\PsiScale"), KEY_WRITE) == ERROR_SUCCESS ||
			regkey.Create(HKEY_CURRENT_USER, _T("Software\\SKMR\\PsiScale")) == ERROR_SUCCESS)
		{
			regkey.SetStringValue(_T("TestFolder"), _working_folder);
			regkey.Close();
		}
	}
}

BOOL CTestOverviewDialog::OnInitDialog()
{
	__super::OnInitDialog();

	_working_folder_edit.EnableFolderBrowseButton();
	_scale_list.Init();

	CRegKey regkey;
	if (regkey.Open(HKEY_CURRENT_USER, _T("Software\\SKMR\\PsiScale"), KEY_READ) == ERROR_SUCCESS)
	{
		static TCHAR buffer[512];
		ULONG count = 512;
		if (regkey.QueryStringValue(_T("TestFolder"), buffer, &count) == ERROR_SUCCESS)
		{
			if (FileSystem::FileExists(buffer))
			{
				_working_folder_edit.SetWindowText(buffer);
			}
		}
	}
	return TRUE;
}

void CTestOverviewDialog::OnOK()
{
	// __super::OnOK();
}

void CTestOverviewDialog::OnCancel()
{
	if (AfxMessageBox(_T("确认退出？"), MB_OKCANCEL) == IDOK)
	{
		__super::OnCancel();
	}
}


void CTestOverviewDialog::OnBnClickedStart()
{
	POSITION position = _scale_list.GetFirstSelectedItemPosition();
	int index = _scale_list.GetNextSelectedItem(position);
	
	CTestManager test_manager;

	CString file_path = _working_folder + _T("\\");
	file_path += _scale_list.GetItemText(index, 0) + _T(".scale");
	_scale = test_manager.LoadPsiScale(file_path);

	if (!_scale)
	{
		AfxMessageBox(_T("无法打开量表文件。"));
	}
	else
	{
		CPsycologyTestDlg dlg(_scale);
		dlg.DoModal();
	}
}
