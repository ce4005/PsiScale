// GroupList.cpp : implementation file
//

#include "stdafx.h"
#include "PsiScaleEditor.h"
#include "GroupList.h"
#include <stdexcept>


// CGroupList

IMPLEMENT_DYNAMIC(CGroupList, CVSListBox)

CGroupList::CGroupList()
{

}

CGroupList::~CGroupList()
{
}


bool CGroupList::SelectString(const CString& text)
{
	for (int i = 0; i < GetCount(); ++i)
	{
		if (GetItemText(i) == text)
		{
			SelectItem(i);
			return true;
		}
	}

	return false;
}

void CGroupList::OnSelectionChanged()
{
}

BOOL CGroupList::OnBeforeRemoveItem(int)
{
	return TRUE;
}

void CGroupList::OnAfterAddItem(int)
{
}

void CGroupList::OnAfterRenameItem(int)
{
}

BEGIN_MESSAGE_MAP(CGroupList, CVSListBox)
END_MESSAGE_MAP()



// CGroupList message handlers


