
// PsycologyTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PsycologyTest.h"
#include "PsycologyTestDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static int buttons[10] = { IDC_RADIO_A, IDC_RADIO_B, IDC_RADIO_C,
IDC_RADIO_D, IDC_RADIO_E, IDC_RADIO_F, IDC_RADIO_G, IDC_RADIO_H, IDC_RADIO_I, IDC_RADIO_J };

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPsycologyTestDlg dialog


CPsycologyTestDlg::CPsycologyTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PSYCOLOGYTEST_DIALOG, pParent),
	_psi_scale(nullptr),
	_current_question_index(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPsycologyTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PROLOGUE, _prologue);
	DDX_Text(pDX, IDC_QUESTION, _question);
	DDX_Control(pDX, IDC_QUESTIONINDEXT, _question_index);
}

BEGIN_MESSAGE_MAP(CPsycologyTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, &CPsycologyTestDlg::OnBnClickedStart)
	ON_BN_CLICKED(ID_PREV, &CPsycologyTestDlg::OnBnClickedPrev)
	ON_BN_CLICKED(ID_NEXT, &CPsycologyTestDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_RADIO_A, &CPsycologyTestDlg::OnBnClickedRadioA)
	ON_BN_CLICKED(IDC_RADIO_B, &CPsycologyTestDlg::OnBnClickedRadioB)
	ON_BN_CLICKED(IDC_RADIO_C, &CPsycologyTestDlg::OnBnClickedRadioC)
	ON_BN_CLICKED(IDC_RADIO_D, &CPsycologyTestDlg::OnBnClickedRadioD)
	ON_BN_CLICKED(IDC_RADIO_E, &CPsycologyTestDlg::OnBnClickedRadioE)
	ON_BN_CLICKED(IDC_RADIO_F, &CPsycologyTestDlg::OnBnClickedRadioF)
	ON_BN_CLICKED(IDC_RADIO_G, &CPsycologyTestDlg::OnBnClickedRadioG)
	ON_BN_CLICKED(IDC_RADIO_H, &CPsycologyTestDlg::OnBnClickedRadioH)
	ON_BN_CLICKED(IDC_RADIO_I, &CPsycologyTestDlg::OnBnClickedRadioI)
	ON_BN_CLICKED(IDC_RADIO_J, &CPsycologyTestDlg::OnBnClickedRadioJ)
	ON_CBN_SELCHANGE(IDC_QUESTIONINDEXT, &CPsycologyTestDlg::OnCbnSelchangeQuestionindext)
END_MESSAGE_MAP()


// CPsycologyTestDlg message handlers


BOOL CPsycologyTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	// 让所有的按钮都隐藏掉
	/*static int buttons[10] = { IDC_RADIO_A, IDC_RADIO_B, IDC_RADIO_C,
		IDC_RADIO_D, IDC_RADIO_E, IDC_RADIO_F, IDC_RADIO_G, IDC_RADIO_H, IDC_RADIO_I, IDC_RADIO_J };*/
	for (unsigned int i = 0; i < 10; ++i)
	{
		GetDlgItem(buttons[i])->ShowWindow(SW_HIDE);
	}

	GetDlgItem(IDC_QUESTIONINDEXT)->ShowWindow(SW_HIDE);


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPsycologyTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPsycologyTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPsycologyTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPsycologyTestDlg::OnBnClickedStart()
{
	_psi_scale = _test_manager.LoadPsiScale(_T("..\\PsycologyTest\\TestTemplate1.xml"));
	// _test_manager.AddScale(_test_manager.LoadPsiScale(_T("..\\PsycologyTest\\TestTemplate.xml")));
	// _psi_scale = &_test_manager.GetPsiScale(1);

	//_test_manager = shared_ptr<CAnswerManager>(new CAnswerManager(_psi_scale));

	ShowQuestion(0);

	GetDlgItem(IDC_QUESTIONINDEXT)->ShowWindow(SW_SHOW);
	InitialQuestionComBox();
}

bool CPsycologyTestDlg::ShowQuestion(unsigned question_index)
{
	if (_psi_scale == nullptr)
		return false;

	if (question_index >= _psi_scale->GetQuestionCount())
		return false;

	_current_question_index = question_index;
	_prologue = _psi_scale->GetPrologue();
	_question = _psi_scale->Question(_current_question_index).GetText();

	ShowRadioButtons(_psi_scale->Choices().size());

	if (_answer_manager.IsAnswered(_psi_scale->GetId(), _current_question_index))
	{
		CheckRadioButton(buttons[0], buttons[9], buttons[_answer_manager.GetAnswer(_psi_scale->GetId(), _current_question_index)]);
	}
	else
	{
		CheckRadioButton(buttons[0], buttons[9], buttons[9]);
	}
	
	UpdateData(FALSE);
	return true;
}

bool CPsycologyTestDlg::ShowRadioButtons(unsigned level_count)
{
	if (level_count > 10)
		return false;

	for (unsigned int i = 0; i < level_count; ++i)
	{
		GetDlgItem(buttons[i])->ShowWindow(SW_SHOW);
	}
	for (unsigned int i = level_count; i < 10; ++i)
	{
		GetDlgItem(buttons[i])->ShowWindow(SW_HIDE);
	}

	return true;
}


void CPsycologyTestDlg::InitialQuestionComBox()
{
	int nums = _psi_scale->GetQuestionCount();
	CString str;

	for (int i = 0; i < nums; ++i)
	{
		str.Format(_T("第%d题"), i + 1);
		_question_index.AddString(str);
	}
	_question_index.SetCurSel(0);
}

void CPsycologyTestDlg::OnBnClickedPrev()
{
	if (_current_question_index > 0)
	{
		ShowQuestion(_current_question_index - 1);
		_question_index.SetCurSel(_current_question_index);
	}
}


void CPsycologyTestDlg::OnBnClickedNext()
{
	ASSERT(_psi_scale);
	if (_current_question_index < _psi_scale->GetQuestionCount() - 1)
	{
		ShowQuestion(_current_question_index + 1);
		_question_index.SetCurSel(_current_question_index);
	}
}

void CPsycologyTestDlg::OnBnClickedRadioA()
{
	ProcessAnswer(_T('A'));
}
void CPsycologyTestDlg::OnBnClickedRadioB()
{
	ProcessAnswer(_T('B'));
}
void CPsycologyTestDlg::OnBnClickedRadioC()
{
	ProcessAnswer(_T('C'));
}
void CPsycologyTestDlg::OnBnClickedRadioD()
{
	ProcessAnswer(_T('D'));
}
void CPsycologyTestDlg::OnBnClickedRadioE()
{
	ProcessAnswer(_T('E'));
}
void CPsycologyTestDlg::OnBnClickedRadioF()
{
	ProcessAnswer(_T('F'));
}
void CPsycologyTestDlg::OnBnClickedRadioG()
{
	ProcessAnswer(_T('G'));
}
void CPsycologyTestDlg::OnBnClickedRadioH()
{
	ProcessAnswer(_T('H'));
}
void CPsycologyTestDlg::OnBnClickedRadioI()
{
	ProcessAnswer(_T('I'));
}
void CPsycologyTestDlg::OnBnClickedRadioJ()
{
	ProcessAnswer(_T('J'));
	
}

void CPsycologyTestDlg::ProcessAnswer(const TCHAR answer)
{
	// 1. 记录
	_answer_manager.AddAnswer(_psi_scale->GetId(), _current_question_index, answer - _T('A'));

	// 2. 下一道题。
	if (_current_question_index < _psi_scale->GetQuestionCount() - 1)
	{
		ShowQuestion(_current_question_index + 1);
		_question_index.SetCurSel(_current_question_index);
	}
}


void CPsycologyTestDlg::OnCbnSelchangeQuestionindext()
{
	ShowQuestion(_question_index.GetCurSel());
}
