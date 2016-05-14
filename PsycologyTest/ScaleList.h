#pragma once

#include <vector>
#include <utility>
// CScaleList

class CScaleList : public CListCtrl
{
	DECLARE_DYNAMIC(CScaleList)

public:
	CScaleList();
	virtual ~CScaleList();
	void Init();
	void InsertScale(const CString& scale_name, bool finished);
	void Clear();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	std::vector<std::pair<CString, bool>> _scale_states;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


