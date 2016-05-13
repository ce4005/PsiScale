#include "stdafx.h"
#include "TestManager.h"

#include "../Utilities/xml.h"

using namespace Utilities;
using namespace std;


const TCHAR * XML_ID = _T("Id");
const TCHAR * XML_NAME = _T("Name");
const TCHAR * XML_DESCRIPTION = _T("Description");
const TCHAR * XML_PROLOGUE = _T("Prologue");
const TCHAR * XML_GROUPS = _T("Groups");
const TCHAR * XML_QUESTIONS = _T("Questions");
const TCHAR * XML_TEXT = _T("Text");
const TCHAR * XML_LEVEL_COUNT = _T("LevelCount");
const TCHAR * XML_REVERSE_SCORE = _T("ReverseScore");
const TCHAR * XML_GROUP_ID = _T("GroupId");
const TCHAR * XML_CHOICES = _T("Choices");
const TCHAR * XML_SAME_CHOICES = _T("SameChoices");
const TCHAR * XML_PSYCOLOGYTEST = _T("PsycologyTest");

CTestManager::CTestManager()
{
}


CTestManager::~CTestManager()
{
}

bool CTestManager::AddScale(std::shared_ptr<PsiScale> scale)
{
	if (!scale)
		return false;

	if (_scales.find(scale->GetId()) != _scales.end())
		return false;

	_scales.insert(make_pair(scale->GetId(), scale));

	return true;
}

shared_ptr<PsiScale> CTestManager::LoadPsiScale(const CString& file_path)
{
	CXml xml;
	if (!xml.Load(file_path))
		return shared_ptr<PsiScale>();

	auto scale = shared_ptr<PsiScale>(new PsiScale);

	scale->SetId(xml.GetIntegerAttrib(XML_ID));
	scale->SetName(xml.GetAttrib(XML_NAME));
	scale->SetDescription(xml.GetAttrib(XML_DESCRIPTION));

	auto prologue_element = xml.GetElement(XML_PROLOGUE);
	if (prologue_element == nullptr)
		return shared_ptr<PsiScale>();

	scale->SetPrologue(prologue_element->GetAttrib(XML_TEXT));

	auto groups_element = xml.GetElement(XML_GROUPS);
	if (groups_element == nullptr)
		return shared_ptr<PsiScale>();

	auto& group_items = groups_element->GetChildElements();
	for (auto item : group_items)
	{
		PsiScaleGroup group;
		group.id = item->GetIntegerAttrib(XML_ID);
		group.description = item->GetAttrib(XML_DESCRIPTION);
		scale->AddGroup(group);
	}

	bool same_choices = xml.GetBoolAttrib(XML_SAME_CHOICES);
	scale->SetSameChoice(same_choices);
	if (same_choices)
	{
		auto choices_element = xml.GetElement(XML_CHOICES);
		if (choices_element == nullptr)
			return shared_ptr<PsiScale>();

		for (auto item : choices_element->GetChildElements())
		{
			QuestionChoice choice;
			choice.id = item->GetIntegerAttrib(XML_ID);
			choice.text = item->GetAttrib(XML_TEXT);
			scale->Choices().push_back(choice);
		}
	}

	auto questions_element = xml.GetElement(XML_QUESTIONS);
	if (questions_element == nullptr)
		return shared_ptr<PsiScale>();

	auto& question_items = questions_element->GetChildElements();
	for (auto item : question_items)
	{
		PsiScaleQuestion question(item->GetIntegerAttrib(XML_ID), 
			item->GetAttrib(XML_TEXT), 
			item->GetBoolAttrib(XML_REVERSE_SCORE),
			item->GetIntegerAttrib(XML_GROUP_ID));

		scale->AddQuestion(question);
	}

	return scale;
}

bool CTestManager::SavePsiScale(const CString& file_path, PsiScale& scale)
{
	CXml xml(XML_PSYCOLOGYTEST);
	xml.SetIntegerAttrib(XML_ID, scale.GetId());
	xml.SetAttrib(XML_NAME, scale.GetName());
	xml.SetAttrib(XML_DESCRIPTION, scale.GetDescription());
	xml.SetBoolAttrib(XML_SAME_CHOICES, scale.IsSameChoice());
	if (scale.IsSameChoice())
	{
		auto choices = xml.AddElement(XML_CHOICES);
		for (auto choice : scale.Choices())
		{
			auto choice_element = choices->AddElement(_T("Item"));
			choice_element->SetIntegerAttrib(XML_ID, choice.id);
			choice_element->SetAttrib(XML_TEXT, choice.text);
		}
	}

	auto prologue = xml.AddElement(XML_PROLOGUE);
	prologue->SetAttrib(XML_TEXT, scale.GetPrologue());

	auto groups = xml.AddElement(XML_GROUPS);
	for (unsigned int i = 0; i < scale.GetGroupCount(); ++i)
	{
		auto group_element = groups->AddElement(_T("Item"));
		group_element->SetIntegerAttrib(XML_ID, scale.Groups()[i].id);
		group_element->SetAttrib(XML_DESCRIPTION, scale.Groups()[i].description);
	}
	auto Question = xml.AddElement(XML_QUESTIONS);
	for (unsigned int i = 0; i < scale.GetQuestionCount(); ++i)
	{
		auto question_element = Question->AddElement(_T("Item"));
		question_element->SetIntegerAttrib(XML_ID, i );
		question_element->SetAttrib(XML_TEXT, scale.GetQuestion(i).GetText());
		question_element->SetBoolAttrib(XML_REVERSE_SCORE, scale.GetQuestion(i).GetReverseScore());
		question_element->SetIntegerAttrib(XML_GROUP_ID, scale.GetQuestion(i).GetGroupId());
		if (scale.IsSameChoice() == false)
		{
			auto choices = question_element->AddElement(XML_CHOICES);
			for (auto iter : scale.Choices())
			{
				auto choice_element = choices->AddElement(_T("Item"));
				choice_element->SetIntegerAttrib(XML_ID, iter.id);
				choice_element->SetAttrib(XML_TEXT, iter.text);
			}
		}

	}
	xml.Save(file_path);
	return true;
}

PsiScale & CTestManager::GetPsiScale(unsigned id)
{
	auto iter = _scales.find(id);
	if (iter != _scales.end())
	{
		return *(iter->second);
	}
	else
	{
		throw CString(_T("����δ�ҵ���"));
	}
}

const PsiScaleQuestion& PsiScale::GetQuestion(unsigned int index) const
{
	if (index >= _questions.size())
		throw (CString(_T("ָ������������δ�ҵ�������̫��")));
	
	return _questions[index];
}

PsiScaleQuestion& PsiScale::Question(unsigned index)
{
	return _questions[index];
}

PsiScale::PsiScale() : _id(0)
{

}

PsiScale::PsiScale(unsigned id, const TCHAR* name, const TCHAR* description, const TCHAR* prologue,bool samechoice) :
	_id(id), _name(name), _description(description), _prologue(prologue), _same_choice(samechoice)
{

}

void PsiScale::SetId(unsigned id)
{
	_id = id;
}

unsigned PsiScale::GetId() const
{
	return _id;
}

void PsiScale::SetName(const TCHAR* name)
{
	_name = name;
}

const CString& PsiScale::GetName() const
{
	return _name;
}

void PsiScale::SetDescription(const TCHAR* description)
{
	_description = description;
}

const CString& PsiScale::GetDescription() const
{
	return _description;
}

void PsiScale::SetPrologue(const TCHAR* prologue)
{
	_prologue = prologue;
}

const CString& PsiScale::GetPrologue() const
{
	return _prologue;
}

void PsiScale::AddGroup(const PsiScaleGroup& group)
{
	_groups.push_back(group);
}

const PsiScaleGroup& PsiScale::GetGroup(unsigned index) const
{
	ASSERT(index < _groups.size());
	return _groups[index];
}

unsigned int PsiScale::GetGroupCount() const
{
	return _groups.size();
}

std::vector<PsiScaleGroup>& PsiScale::Groups()
{
	return _groups;
}

void PsiScale::AddQuestion(const PsiScaleQuestion& question)
{
	_questions.push_back(question);
}

void PsiScale::DeleteQuestion(unsigned int index)
{
	if (index < _questions.size())
	{
		_questions.erase(_questions.begin() + index);
	}
}

unsigned int PsiScale::GetQuestionCount() const
{
	return _questions.size();
}

bool PsiScale::Save(const CString& file_path)
{
	return false;
}

std::vector<QuestionChoice>& PsiScale::Choices()
{
	return _choices;
}

const bool PsiScale::IsSameChoice() const
{
	return _same_choice;
}

void PsiScale::SetSameChoice(bool samechoice)
{
	_same_choice = samechoice;
}

PsiScaleQuestion::PsiScaleQuestion() :
	_reverse_score(false), _group_id(0)
{
}

PsiScaleQuestion::PsiScaleQuestion(unsigned id, 
	const CString& text,
	bool reverse_score, 
	unsigned short group_id) :
	_id(id), _text(text), _reverse_score(reverse_score), _group_id(group_id)
{
}

void PsiScaleQuestion::SetId(unsigned id)
{
	_id = id;
}

unsigned PsiScaleQuestion::GetId() const
{
	return _id;
}

void PsiScaleQuestion::SetText(const CString& text)
{
	_text = text;
}

const CString& PsiScaleQuestion::GetText() const
{
	return _text;
}

void PsiScaleQuestion::SetReverseScore(bool reverse_score)
{
	_reverse_score = reverse_score;
}

const bool PsiScaleQuestion::GetReverseScore() const
{
	return _reverse_score;
}

void PsiScaleQuestion::SetGroup(unsigned short group_id)
{
	_group_id = group_id;
}

const unsigned short PsiScaleQuestion::GetGroupId() const
{
	return _group_id;
}

std::vector<QuestionChoice>& PsiScaleQuestion::Choices()
{
	return _choices;
}
