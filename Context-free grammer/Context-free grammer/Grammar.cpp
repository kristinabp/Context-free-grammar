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

bool Grammar::checkExistingVariable(const char ch) const
{
	for (size_t i = 0; i < variables.size(); i++) 
	{
		if (variables[i] == ch)
		{
			return true;
		}
	}

	return false;
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
	std::string i = std::to_string(counter) + '-' + startVariable;
	this->id = i;
}

Grammar::Grammar() : rules(std::vector<Rule*>()), id("X-X"), variables(std::vector<char>()), terminals(std::vector<std::string>()),
					startVariable("")
{
}

Grammar::Grammar(const std::vector<Rule*>& rules, const std::vector<char> variables, const std::vector<std::string> terminals, const std::string startVariable)
{
	this->rules = rules;
	for (size_t i = 0; i < variables.size(); i++)
	{
		if (checkVariable(variables[i]))
		{
			this->variables.push_back(variables[i]);
		}
		else
		{
			std::cout << "Incorrect variables set.\n";
			assert(false);
		}
	}
	for (size_t i = 0; i < terminals.size(); i++)
	{
		if()
	}
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

void Grammar::removeRule(int index)
{
	if (index<rules.size() || index>rules.size())
	{
		for (size_t i = 0; i < rules.size(); i++)
		{
			if (index == i)
			{
				rules.erase(rules.begin() + i);
				std::cout << "Rule removed.\n";
			}
			break;
		}
	}
	else
	{
		std::cout << "Incorrect index.\n";
	}
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
		std::cout << "\n";
	}
	std::cout << this->id<< "\n";
}
