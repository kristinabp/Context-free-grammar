#include "Grammar.h"

int Grammar::counter = 0;

bool Grammar::checkTerminal (const char ch) const
{
	if (ch >= 'a' && ch <= 'z')
	{
		return true;
	}
	else if (ch >= '0' && ch <= '9')
	{
		return true;
	}
	else return false;
}

bool Grammar::checkVariable(const char ch) const
{
	return ch>='A' && ch<='Z';
}

void Grammar::copy(const Grammar & other)
{
	this->rules = other.rules;
	this->id = other.id;
	this->variables = other.variables;
	this->terminals = other.terminals;
	this->startVariable = other.startVariable;
}

void Grammar::createId()
{
	std::string i = std::to_string(counter) + '-' + startVariable+ '-' + std::to_string(rules.size());
	this->id = i;
}

Grammar::Grammar() : rules(std::vector<Rule*>()), id("X-X-X"), variables(std::vector<std::string>()), terminals(std::vector<char>()),
					startVariable(' ')
{
}

Grammar::Grammar(const std::vector<Rule*>& rules, const std::vector<std::string> variables, const std::vector<char> terminals, const char startVariable)
{
	this->rules = rules;
	this->variables = variables;
	this->terminals = terminals;
	this->startVariable = startVariable;
	this->counter++;
	createId();
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

std::string Grammar::getId() const
{
	return this->id;
}

Grammar * Grammar::clone() const
{
	return new Grammar(*this);
}

void Grammar::addRule(const Rule * r)
{
	this->rules.push_back(r->clone());
}

void Grammar::save(std::ostream & os)
{
	for (size_t i = 0; i < variables.size(); i++)
	{
		os << variables[i] << "\t";
	}
	os << "\n";
	for (size_t i = 0; i < terminals.size(); i++)
	{
		os << terminals[i] << "\t";
	}
	os << "\n";
	for (size_t i = 0; i < rules.size(); i++)
	{
		rules[i]->print(os);
		os << "\t";
	}
}

void Grammar::print() const
{
	for (size_t i = 0; i < variables.size(); i++)
	{
		std::cout << variables[i] << ", ";
	}
	std::cout << "\t";
	for (size_t i = 0; i < terminals.size(); i++)
	{
		std::cout << terminals[i] << ", ";
	}
	std::cout << "\t "<<startVariable << "\n";
	for (size_t i = 0; i < rules.size(); i++)
	{
		rules[i]->print(std::cout);
	}
	std::cout << this->id;
}
