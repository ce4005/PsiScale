#pragma once

#include <vector>
#include <map>
#include <TChar.h>
#include <afxstr.h>
#include <memory>

struct QuestionChoice
{
	unsigned int id;
	CString text;
};

struct PsiScaleGroup
{
	unsigned int id;
	CString description;
};

class PsiScaleQuestion
{
public:
	PsiScaleQuestion();
	PsiScaleQuestion(unsigned id, const CString& text, bool reverse_score, unsigned short group_id);

	void SetId(unsigned id);
	unsigned GetId() const;
	void SetText(const CString& text);
	const CString& GetText() const;
	void SetReverseScore(bool reverse_score);
	const bool GetReverseScore() const;
	void SetGroup(unsigned short group_id);
	const unsigned short GetGroupId() const;

	std::vector<QuestionChoice>& Choices();
private:
	unsigned _id;
	std::vector<QuestionChoice> _choices;
	CString _text;
	unsigned short _level_count;
	bool _reverse_score;
	unsigned short _group_id;
};

class PsiScale
{
public:
	PsiScale();
	PsiScale(unsigned id, const TCHAR* name, const TCHAR* description, const TCHAR* prologue, bool samechoice);

	void SetId(unsigned id);
	unsigned GetId() const;
	void SetName(const TCHAR* name);
	const CString& GetName() const;
	void SetDescription(const TCHAR* description);
	const CString& GetDescription() const;
	void SetPrologue(const TCHAR* prologue);
	const CString& GetPrologue() const;

	void AddGroup(const PsiScaleGroup& group);
	const PsiScaleGroup& GetGroup(unsigned index) const;
	unsigned int GetGroupCount() const;
	std::vector<PsiScaleGroup>& Groups();

	void AddQuestion(const PsiScaleQuestion& question);
	void DeleteQuestion(unsigned int index);
	const PsiScaleQuestion& GetQuestion(unsigned int index) const;
	PsiScaleQuestion& Question(unsigned index);
	unsigned int GetQuestionCount() const;

	bool Save(const CString& file_path);
	const bool IsSameChoice() const;
	void SetSameChoice(bool samechoice);;
	std::vector<QuestionChoice>& Choices();
private:
	unsigned _id;
	CString _name;
	CString _description;
	CString _prologue;

	std::vector<PsiScaleGroup> _groups;
	std::vector<PsiScaleQuestion> _questions;
	std::vector<QuestionChoice> _choices;

	bool _same_choice;
};

struct Score
{
	CString id;
	CString answer;
};

class CTestManager
{
public:
	CTestManager();
	~CTestManager();

	std::shared_ptr<PsiScale> LoadPsiScale(const CString& file_path);
	bool SavePsiScale(const CString& file_path, PsiScale& scale);

	bool AddScale(std::shared_ptr<PsiScale> scale);


	PsiScale & GetPsiScale(unsigned id);
protected:
	std::map<unsigned, std::shared_ptr<PsiScale>> _scales;
};

