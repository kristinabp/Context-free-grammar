#include "Grammar.h"

bool Grammar::checkVariable(const char ch) const
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

bool Grammar::checkTerminal(const char ch) const
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

Grammar::Grammar(): rules(std::vector<Rule*>()), id("XXX-XXX"), variables(std::vector<char>()),
                    terminals(std::vector<std::string> ())
{

}

Grammar::Grammar(const std::vector<Rule*> rules, const std::string id, const std::vector<char> variables,
	             const std::vector<std::string> terminals, const char startVariable):rules(rules),id(id),
	             variables(variables),terminals(terminals), startVariable(startVariable)
{

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
	std::cout <<"G=({";
	for (size_t i = 0; i < terminals.size()-1; i++)
	{
		std::cout << terminals[i] << ", ";
	}
	std::cout << terminals[terminals.size() - 1] ;
	std::cout << "}, {";
	for (size_t i = 0; i < variables.size()-1; i++)
	{
		std::cout << variables[i] << ", ";
	}
	std::cout << variables[variables.size() - 1];
	std::cout << "}, " << this->startVariable<< " , {";
	for (size_t i = 0; i < rules.size(); i++)
	{
		std::cout << " " <<i + 1 << ".";
		rules[i]->print();
	}
	std::cout << "})\n";
	
}
