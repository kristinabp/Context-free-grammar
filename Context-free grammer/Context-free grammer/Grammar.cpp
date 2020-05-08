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

bool Grammar::checkUpper(const char ch) const
{
	return ch >= 'A' && ch <= 'Z';
}

bool Grammar::checkVariable(const std::string ch) const
{
	return ch[0]>='A' && ch[0]<='Z';
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

Grammar::Grammar() : rules(std::vector<Rule*>()), id("X-X"), variables(std::vector<std::string>()), terminals(std::vector<std::string>()),
					startVariable(' ')
{
	this->counter++;
}

Grammar::Grammar(const std::vector<Rule*>& rules, const std::vector<std::string> variables, const std::vector<std::string> terminals, const char startVariable)
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
	bool check = true;
	for (size_t i = 0; i < terminals.size(); i++)
	{
		for (size_t j = 0; j < terminals[i].size(); j++)
		{
			if (checkTerminal(terminals[i][j]))
			{
				continue;
			}
			else if (checkUpper(terminals[i][j]))
			{
				for (size_t k = 0; k < variables.size(); k++)
				{
					if (terminals[i][j] == variables[k][0])
					{
						check = true;
						break;
					}
					else
					{
						check = false;
					}
				}
				if (!check)
				{
					break;
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

	bool flag = false;
	if (checkUpper(startVariable))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (variables[i][0] == startVariable)
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

std::vector<std::string> Grammar::getVariables() const
{
	return this->variables;
}

std::vector<std::string> Grammar::getTerminals() const
{
	return this->terminals;
}

void Grammar::addNewVariable(const std::string & var)
{
	this->variables.push_back(var);
}

//void Grammar::setNewVariableName(size_t index, const char var)
//{
//	this->variables[index] = this->variables[index] + '2';
//
//	//update terminals with the new variable
//	for (size_t i = 0; i < terminals.size(); i++)
//	{
//		for (size_t j = 0; j < terminals[i].size(); j++)
//		{
//			if (terminals[i][j] == var)
//			{
//				
//				terminals[i].insert(j + 1, "2");
//			}
//		}
//	}
//}

Grammar * Grammar::clone() const
{
	return new Grammar(*this);
}

void Grammar::addRule(const Rule * r)
{
	bool variableCheck = true;
	if (checkUpper(r->getVariable()))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (r->getVariable() == variables[i][0])
			{
				variableCheck = true;
				break;
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
				else if (checkUpper(r->getTerminals()[i][j]))
				{
					for (size_t k = 0; k < variables.size(); k++)
					{
						if (r->getTerminals()[i][j] == variables[k][0])
						{
							terminalCheck = true;
							break;
						}
						else
						{
							terminalCheck = false;
						}
					}

					if (!terminalCheck)
					{
						break;
					}
				}
				else
				{
					std::cout << "Incorrect terminals.\n";
					assert(false);
				}
			}
		}
	}
	else
	{
		std::cout << "Empty terminals.\n";
		assert(false);
	}

	if (variableCheck && terminalCheck)
	{
		for (size_t i = 0; i < r->getTerminals().size(); i++)
		{
			this->terminals.push_back(r->getTerminals()[i]);
		}
		this->rules.push_back(r->clone());
	}
	else
	{
		std::cout << terminalCheck << variableCheck;
		std::cout << "Incorrect rule.\n";
		assert(false);
	}
}

void Grammar::removeRule(int index)
{
	if (index<=rules.size())
	{
		for (size_t i = 0; i < rules.size(); i++)
		{
			if (index-1 == i)
			{
				rules.erase(rules.begin() + i);
				std::cout << "Rule removed.\n";
				break;
			}
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
	if (variables.size() > 1)
	{
		for (size_t i = 0; i < variables.size() - 1; i++)
		{
			std::cout << variables[i] << ", ";
		}
	}
	std::cout << variables[variables.size()-1] << "\t";
	if (terminals.size() > 1)
	{
		for (size_t i = 0; i < terminals.size() - 1; i++)
		{
			std::cout << terminals[i] << ", ";
		}
	}
	if (!terminals.size() == 0)
	{
		std::cout << terminals[terminals.size() - 1];
	}
	std::cout << "\t "<<startVariable << "\n";
	for (size_t i = 0; i < rules.size(); i++)
	{
		std::cout << i + 1 << ".";
		rules[i]->print(std::cout);
		std::cout << "\n";
	}
}
