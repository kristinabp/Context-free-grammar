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
	std::string i = std::to_string(counter) + '-' + startVariable;
	this->id = i;
}

Grammar::Grammar() : rules(std::vector<Rule*>()), id("X-X"), variables(std::vector<char>()), terminals(std::vector<std::string>()),
					startVariable(' ')
{
	this->counter++;
}

Grammar::Grammar(const std::vector<Rule*>& rules, const std::vector<char> variables, const std::vector<std::string> terminals, const char startVariable)
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
	bool check = false;
	if (terminals.size() != 0)
	{
		for (size_t i = 0; i < terminals.size(); i++)
		{
			for (size_t j = 0; j < terminals[i].size(); j++)
			{
				if (checkTerminal(terminals[i][j]))
				{
					continue;
				}
				else if (checkVariable(terminals[i][j]))
				{
					for (size_t k = 0; k < variables.size(); k++)
					{
						if (terminals[i][j] == variables[k])
						{
							check = true;
						}
					}
				}
				else
				{
					std::cout << "Incorrect terminals(terminal&variable).\n";
					assert(false);
				}
			}

			if (check)
			{
				this->terminals.push_back(terminals[i]);
			}
			else
			{
				std::cout << "Incorrect terminals(variable does not exist).\n";
				assert(false);
			}
		}
	}
	else
	{
	std::cout << "Empty terminals.\n";
	assert(false);
	}

	bool flag = false;
	if (checkVariable(startVariable))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (variables[i] == startVariable)
			{
				this->startVariable = startVariable;
				flag = true;
			}
		}

		if (!flag)
		{
			std::cout << "Incorrect starting variable.Does not exist in variable set.\n";
			assert(false);
		}
	}
	else
	{
		std::cout << "Incorrect starting variable.\n";
		assert(false);
	}
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
	bool variableCheck = true;
	if (checkVariable(r->getVariable()))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (r->getVariable() == variables[i])
			{
				variableCheck = true;
			}
			else
			{
				variableCheck = false;
			}
		}
	}
	else
	{
		std::cout << "Incorrect variable.\n";
		assert(false);
	}

	bool terminalCheck = true;
	if (r->getTerminals().size() != 0)
	{
		for (size_t i = 0; i < r->getTerminals().size(); i++)
		{
			for (size_t j = 0; j < r->getTerminals()[i].size(); j++)
			{
				if (checkTerminal(r->getTerminals()[i][j]))
				{
					continue;
				}
				else if (checkVariable(r->getTerminals()[i][j]))
				{
					for (size_t k = 0; k < variables.size(); k++)
					{
						if (r->getTerminals()[i][j] == variables[k])
						{
							terminalCheck = true;
						}
						else
						{
							terminalCheck = false;
						}
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Empty terminals.\n";
		assert(false);
	}
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
