#include "Rule.h"

void Rule::copy(const Rule & other)
{
	this->variable = other.variable;
	this->production = other.production;
}

Rule::Rule() :production(std::vector<std::string>())
{
}

Rule::Rule(const std::string variable, const std::vector<std::string> production) : variable(variable), 
                                                                           production(production)
{
}

Rule::Rule(const Rule & other)
{
	copy(other);
}

Rule::~Rule()
{
}

std::string Rule::getVariable() const
{
	return this->variable;
}

std::vector<std::string> Rule::getProduction() const
{
	return this->production;
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
	os << this->variable << "->";
	for (size_t i = 0; i < production.size()-1; i++)
	{
		os << this->production[i] << "|";
	}
	os << this->production[production.size()-1] ;
}
