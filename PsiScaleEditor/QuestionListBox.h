#pragma once


// CQuestionListBox

class CQuestionListBox : public CVSListBox
{
	DECLARE_DYNAMIC(CQuestionListBox)

public:
	CQuestionListBox();
	virtual ~CQuestionListBox();

protected:
	DECLARE_MESSAGE_MAP()

	virtual void OnEndEditLabel(LPCTSTR lpszLabel) override;

	virtual BOOL OnBeforeRemoveItem(int) override;

	virtual void OnAfterAddItem(int) override;

	virtual void OnAfterMoveItemUp(int) override;

	virtual void OnAfterMoveItemDown(int) override;

	virtual void CreateNewItem() override;
};


