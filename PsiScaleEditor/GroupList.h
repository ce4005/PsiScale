#pragma once


// CGroupList

class CGroupList : public CVSListBox
{
	DECLARE_DYNAMIC(CGroupList)

public:
	CGroupList();
	virtual ~CGroupList();

protected:
	DECLARE_MESSAGE_MAP()

	virtual void OnSelectionChanged() override;

	virtual BOOL OnBeforeRemoveItem(int) override;

	virtual void OnAfterAddItem(int) override;

	virtual void OnAfterRenameItem(int) override;

};


