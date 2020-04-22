#include "Grammar.h"

void Grammar::copy(const Grammar & other)
{
	this->rules = other.rules;
	this->id = other.id;
}

Grammar::Grammar(): rules(std::vector<Rule*>()), id("XXX-XXX")
{
}

Grammar::Grammar(const std::vector<Rule*> rules, const std::string id)
{
	this->rules = rules;
	this->id = id;
}

Grammar::Grammar(const Grammar & other)
{
	copy(other);
}

Grammar::~Grammar()
{
}

Grammar & Grammar::operator=(const Grammar & other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

Grammar & Grammar::addRule(Rule* rule)
{
	rules.push_back(rule->clone());
	return *this;
}

void Grammar::removeRule(int n)
{
	for(int i=n-1; i<rules.size()-1; i++)
	{ 
		rules[i] = rules[i + 1];
	}
	rules.pop_back();
}

void Grammar::print() const
{
	for (size_t i = 0; i < rules.size(); i++)
	{
		std::cout << i+1 << ".";
		rules[i]->print();
	}
}
