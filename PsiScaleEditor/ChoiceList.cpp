// ChoiceList.cpp : implementation file
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "ChoiceList.h"
#include <stdexcept>


// CChoiceList

IMPLEMENT_DYNAMIC(CChoiceList, CVSListBox)

CChoiceList::CChoiceList()
{

}

CChoiceList::~CChoiceList()
{
}

BOOL CChoiceList::OnBeforeRemoveItem(int)
{
	return TRUE;
}

void CChoiceList::OnAfterAddItem(int)
{
}

void CChoiceList::OnAfterRenameItem(int)
{
}

BEGIN_MESSAGE_MAP(CChoiceList, CVSListBox)
END_MESSAGE_MAP()



// CChoiceList message handlers


