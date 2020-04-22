#include "Rule.h"

void Rule::copy(const Rule & other)
{
	this->variable = other.variable;
	this->terminals = other.terminals;
}

Rule::Rule():terminals("")
{
}

Rule::Rule(const char variable, const std::string terminals) : variable(variable), terminals(terminals)
{
}

Rule::Rule(const Rule & other)
{
	copy(other);
}

Rule::~Rule()
{
}

Rule * Rule::clone() const
{
	return new Rule(*this);
}

char Rule::getVariable() const
{
	return this->variable;
}

std::string Rule::getTerminals() const
{
	return this->terminals;
}

Rule & Rule::operator=(const Rule & other)
{
	if (this != &other)
	{
		copy(other);
	}

	return *this;
}

void Rule::print() const
{
	std::cout << this->variable << "->" << this->terminals << std::endl;
}
