
// PsiScaleEditorDlg.h : 头文件
//

#pragma once

#include <memory>
#include "afxwin.h"
#include "afxvslistbox.h"
#include "ChoiceList.h"

class PsiScale;
class PsiScaleQuestion;

// CQuestionEditorDlg 对话框
class CQuestionEditorDlg : public CDialogEx
{
// 构造
public:
	CQuestionEditorDlg(std::shared_ptr<PsiScale> scale, CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_QUESTION_EDITOR };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	std::shared_ptr<PsiScale> _scale;

	int _current_question;

	BOOL _reverse_score;
	CString _question_text;
	CComboBox _group_combo;
	CChoiceList _choice_list;

	void UpdateUi();
	void MoveButtonUp(CButton& button, unsigned int y_pos);
	void Shrink();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedAddQuestion();
	afx_msg void OnEnChangeEditQuestion();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedDeleteQuestion();
	void UpdateQuestion();
public:
	CButton _delete_button;
	CButton _prev_button;
	CButton _next_button;
	CButton _new_button;
	CButton _return_button;
	CStatic _choice_list_label;
	CStatic _group_label;
};
