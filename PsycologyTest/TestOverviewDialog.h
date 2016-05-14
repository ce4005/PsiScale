#pragma once
#include "afxeditbrowsectrl.h"
#include "afxcmn.h"
#include "ScaleList.h"
#include <memory>

class PsiScale;
// CTestOverviewDialog dialog

class CTestOverviewDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CTestOverviewDialog)

public:
	CTestOverviewDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTestOverviewDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OVERVIEW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CMFCEditBrowseCtrl _working_folder_edit;
public:
	CString _working_folder;
	afx_msg void OnEnChangeEditWorkingFolder();

	virtual BOOL OnInitDialog() override;

	virtual void OnOK() override;

	virtual void OnCancel() override;

	CScaleList _scale_list;
	std::shared_ptr<PsiScale> _scale;

	afx_msg void OnBnClickedStart();
};
