
// PsiScaleEditorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "QuestionEditorDlg.h"
#include "afxdialogex.h"
#include "../PsiCommon/TestManager.h"
#include "InputStringDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

CQuestionEditorDlg::CQuestionEditorDlg(shared_ptr<PsiScale> scale, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_QUESTION_EDITOR, pParent)
	, _question_text(_T(""))
	, _scale(scale)
	, _reverse_score(FALSE)
	, _current_question(-1)
	, _question_number(_T(""))
{
	ASSERT(_scale);
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuestionEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_QUESTION, _question_text);
	DDX_Control(pDX, IDC_COMBO_GROUPS, _group_combo);
	DDX_Control(pDX, IDC_CHOICE_LIST, _choice_list);
	DDX_Check(pDX, IDC_CHECK_REVERSE_SCORE, _reverse_score);
	DDX_Control(pDX, IDC_BUTTON_DELETE, _delete_button);
	DDX_Control(pDX, IDC_BUTTON_PREV, _prev_button);
	DDX_Control(pDX, IDC_BUTTON_NEXT, _next_button);
	DDX_Control(pDX, IDC_BUTTON_NEW, _new_button);
	DDX_Control(pDX, IDOK, _return_button);
	DDX_Control(pDX, IDC_STATIC_CHOICE_LIST_LABEL, _choice_list_label);
	DDX_Control(pDX, IDC_GROUP_LABEL, _group_label);
	DDX_Text(pDX, IDC_STATIC_QUESTION_NUMBER, _question_number);
}

BEGIN_MESSAGE_MAP(CQuestionEditorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CQuestionEditorDlg::OnBnClickedButtonNew)
	ON_EN_CHANGE(IDC_EDIT_QUESTION, &CQuestionEditorDlg::OnEnChangeEditQuestion)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CQuestionEditorDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CQuestionEditorDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CQuestionEditorDlg::OnBnClickedDeleteQuestion)
	ON_BN_CLICKED(IDOK, &CQuestionEditorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CQuestionEditorDlg 消息处理程序

BOOL CQuestionEditorDlg::OnInitDialog()
{
	ASSERT(_scale);

	__super::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	if (_scale->IsSameChoice())
	{
		Shrink();
	}
	if (_scale->GetGroupCount() != 0)
	{
		for (auto group : _scale->Groups())
		{
			_group_combo.AddString(group);
		}
	}
	else
	{
		_group_combo.ShowWindow(SW_HIDE);
		_group_label.ShowWindow(SW_HIDE);
	}

	if (_scale->GetQuestionCount() == 0)
	{
		OnBnClickedButtonNew();
	}
	else
	{
		_current_question = 0;
		UpdateUi();
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQuestionEditorDlg::Shrink()
{
	_choice_list.ShowWindow(SW_HIDE);
	_choice_list_label.ShowWindow(SW_HIDE);

	CRect label_rect;
	_choice_list_label.GetWindowRect(&label_rect);
	ScreenToClient(&label_rect);

	MoveButtonUp(_delete_button, label_rect.top);
	MoveButtonUp(_new_button, label_rect.top);
	MoveButtonUp(_prev_button, label_rect.top);
	MoveButtonUp(_next_button, label_rect.top);
	MoveButtonUp(_return_button, label_rect.top);

	CRect markrect;
	CRect dlgrect;
	CRect clientrect;

	GetClientRect(&clientrect);  // client area of the dialog
	GetWindowRect(&dlgrect);	  // rectangle of the dialog window

								  // get height of the title bar
								  //int offset = dlgrect.Width() - clientrect.right ;
	int offset = dlgrect.Height() - clientrect.bottom;

	_delete_button.GetWindowRect(&markrect);
	ScreenToClient(&markrect);

	// calculate the new rectangle of the dialog window
	//dlgrect.right = dlgrect.left + offset + (expand ? (markrect.right + 10) : markrect.left) ;
	dlgrect.bottom = dlgrect.top + offset + markrect.bottom + 10;

	MoveWindow(dlgrect.left, dlgrect.top, dlgrect.Width(), dlgrect.Height());
}

void CQuestionEditorDlg::MoveButtonUp(CButton& button, 
	unsigned int y_pos)
{
	CRect rect;
	button.GetWindowRect(rect);
	ScreenToClient(rect);

	rect.bottom = y_pos + rect.Height();
	rect.top = y_pos;
	button.MoveWindow(rect);
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CQuestionEditorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		__super::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQuestionEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQuestionEditorDlg::OnBnClickedButtonNew()
{
	PsiScaleQuestion new_question;

	_scale->AddQuestion(new_question);
	_current_question = _scale->GetQuestionCount() - 1;

	UpdateUi();
}

void CQuestionEditorDlg::UpdateUi()
{
	if (!_scale)
		return;

	ASSERT(_current_question < int(_scale->GetQuestionCount()));

	auto question = _scale->GetQuestion(_current_question);

	_question_text = question.GetText();
	_reverse_score = question.GetReverseScore();
	_group_combo.SelectString(0, question.GetGroup());

	if (!_scale->IsSameChoice())
	{
		// 更新当前问题的选择。
		for (auto choice : question.Choices())
		{
			_choice_list.AddItem(choice.text, choice.id);
		}
	}
	_next_button.EnableWindow(_current_question < _scale->GetQuestionCount() - 1);
	_prev_button.EnableWindow(_current_question > 0);

	_question_number.Format(_T("%d / %d"), _current_question + 1, _scale->GetQuestionCount());
	GetDlgItem(IDC_STATIC_QUESTION_NUMBER)->SetWindowText(_question_number);
	UpdateData(FALSE);
}

void CQuestionEditorDlg::OnEnChangeEditQuestion()
{
	ASSERT(_scale);
	ASSERT(_current_question < int(_scale->GetQuestionCount()) && _current_question >= 0);

	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData();

	_scale->Question(_current_question).SetText(_question_text);
}


void CQuestionEditorDlg::OnBnClickedButtonNext()
{
	UpdateQuestion(); // 保存当前的问题

	if (_current_question < int(_scale->GetQuestionCount()) - 1)
	{
		++_current_question;
	}
	UpdateUi();
}


void CQuestionEditorDlg::OnBnClickedButtonPrev()
{
	UpdateQuestion(); // 保存当前的问题

	if (_current_question > 0)
	{
		--_current_question;
	}
	UpdateUi();
}


void CQuestionEditorDlg::OnBnClickedDeleteQuestion()
{
	if (AfxMessageBox(_T("是否确定要删除当前的问题？"), MB_OK | MB_OKCANCEL) == IDOK)
	{
		_scale->DeleteQuestion(_current_question);
		if (_current_question >= int(_scale->GetQuestionCount()))
		{
			_current_question = _scale->GetQuestionCount() - 1;
		}
		UpdateUi();
	}
}

void CQuestionEditorDlg::UpdateQuestion()
{
	ASSERT(_scale);
	if (_current_question < 0)
		return;

	UpdateData();

	ASSERT(_current_question < int(_scale->GetQuestionCount()));
	auto& question = _scale->Question(_current_question);

	question.SetText(_question_text);
	question.SetReverseScore(_reverse_score != FALSE);
	if (_group_combo.GetCurSel() != LB_ERR)
	{
		CString group;
		_group_combo.GetLBText(_group_combo.GetCurSel(), group);
		question.SetGroup(group);
	}

	if (!_scale->IsSameChoice())
	{
		// 更新当前问题的选择。
		auto& choices = question.Choices();
		choices.resize(_choice_list.GetCount());

		for (int i = 0; i < _choice_list.GetCount(); ++i)
		{
			choices[i].id = i + 1;
			choices[i].text = _choice_list.GetItemText(i);
		}
	}
}


void CQuestionEditorDlg::OnBnClickedOk()
{
	UpdateQuestion();
	CDialogEx::OnOK();
}
