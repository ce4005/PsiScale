#pragma once


// CChoiceList

class CChoiceList : public CVSListBox
{
	DECLARE_DYNAMIC(CChoiceList)

public:
	CChoiceList();
	virtual ~CChoiceList();

protected:
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnBeforeRemoveItem(int) override;

	virtual void OnAfterAddItem(int) override;

	virtual void OnAfterRenameItem(int) override;

};


