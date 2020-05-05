#include "Rule.h"

void Rule::copy(const Rule & other)
{
	this->variable = other.variable;
	this->terminals = other.terminals;
}

Rule::Rule() :terminals(std::vector<std::string>())
{
}

Rule::Rule(const char variable, const std::vector<std::string> terminals) : variable(variable), 
                                                                           terminals(terminals)
{
}

Rule::Rule(const Rule & other)
{
	copy(other);
}

Rule::~Rule()
{
}

char Rule::getVariable() const
{
	return this->variable;
}

std::vector<std::string> Rule::getTerminals() const
{
	return this->terminals;
}

Rule * Rule::clone() const
{
	return new Rule(*this);
}

Rule & Rule::operator=(const Rule & other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

void Rule::print(std::ostream& os) const
{
	os << this->variable << " -> ";
	for (size_t i = 0; i < terminals.size()-1; i++)
	{
		os << this->terminals[i] << " | ";
	}
	os << this->terminals[terminals.size()-1] ;
}
