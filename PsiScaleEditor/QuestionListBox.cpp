// QuestionListBox.cpp : implementation file
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "QuestionListBox.h"
#include <stdexcept>


// CQuestionListBox

IMPLEMENT_DYNAMIC(CQuestionListBox, CVSListBox)

CQuestionListBox::CQuestionListBox()
{

}

CQuestionListBox::~CQuestionListBox()
{
}


void CQuestionListBox::OnEndEditLabel(LPCTSTR lpszLabel)
{
}

BOOL CQuestionListBox::OnBeforeRemoveItem(int)
{
	return TRUE;
}

void CQuestionListBox::OnAfterAddItem(int)
{
}

void CQuestionListBox::OnAfterMoveItemUp(int)
{
}

void CQuestionListBox::OnAfterMoveItemDown(int)
{
}

void CQuestionListBox::CreateNewItem()
{
}

BEGIN_MESSAGE_MAP(CQuestionListBox, CVSListBox)
END_MESSAGE_MAP()



// CQuestionListBox message handlers


