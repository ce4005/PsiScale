
// PsycologyTestDlg.h : header file
//

#pragma once

#include "../PsiCommon/TestManager.h"
#include "afxwin.h"
#include <memory>
#include "AnswerManager.h"

// CPsycologyTestDlg dialog
class CPsycologyTestDlg : public CDialogEx
{
// Construction
public:
	CPsycologyTestDlg(std::shared_ptr<PsiScale> scale, CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PSYCOLOGYTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CTestManager _test_manager;
	CAnswerManager _answer_manager;
	std::shared_ptr<PsiScale> _psi_scale;
	unsigned _current_question_index;

	// Generated message map functions
	bool ShowQuestion(unsigned question_index);
	bool ShowRadioButtons(unsigned level_count);
	void InitialQuestionComBox();

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedNext();
	CString _prologue;
	CString _question;

	afx_msg void OnBnClickedRadioA();
	afx_msg void OnBnClickedRadioB();
	afx_msg void OnBnClickedRadioC();
	afx_msg void OnBnClickedRadioD();
	afx_msg void OnBnClickedRadioE();
	afx_msg void OnBnClickedRadioF();
	afx_msg void OnBnClickedRadioG();
	afx_msg void OnBnClickedRadioH();
	afx_msg void OnBnClickedRadioI();
	afx_msg void OnBnClickedRadioJ();

	void ProcessAnswer(const TCHAR answer);
public:
	CComboBox _question_index;
	afx_msg void OnCbnSelchangeQuestionindext();
};
