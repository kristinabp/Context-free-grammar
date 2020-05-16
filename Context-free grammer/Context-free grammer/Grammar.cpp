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

bool Grammar::checkTerminalSet(const char ch) const
{
	for (size_t i = 0; i < terminals.size(); i++)
	{
		if (ch == terminals[i])
		{
			return true;
		}
	}
	return false;
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

Grammar::Grammar() : rules(std::vector<Rule*>()), id("X-X"), variables(std::vector<std::string>()), terminals(std::vector<char>()),
					startVariable("")
{
	this->counter++;
}

Grammar::Grammar(const std::vector<Rule*>& rules, const std::vector<std::string> variables, const std::vector<char> terminals, const std::string startVariable)
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
		if (checkTerminal(terminals[i]))
		{
			this->terminals.push_back(terminals[i]);
		}
		else
		{
			std::cout << "Incorrect terminals set.\n";
			assert(false);
		}
	}
	/*bool check = true;
	for (size_t i = 0; i < productions.size(); i++)
	{
		for (size_t j = 0; j < productions[i].size(); j++)
		{
			if (checkTerminal(productions[i][j]))
			{
				continue;
			}
			else if (checkUpper(productions[i][j]))
			{
				for (size_t k = 0; k < variables.size(); k++)
				{
					if (productions[i][j] == variables[k][0])
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
			this->productions.push_back(productions[i]);
		}
		else
		{
			std::cout << "Incorrect terminals(variable does not exist).\n";
			assert(false);
		}
	}
*/
	bool flag = false;
	if (checkUpper(startVariable[0]))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (variables[i][0] == startVariable[0])
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

std::vector<char> Grammar::getTerminals() const
{
	return this->terminals;
}

std::vector<Rule*> Grammar::getRules() const
{
	return this->rules;
}

std::string Grammar::getStartVariable() const
{
	return this->startVariable;
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
	if (checkVariable(r->getVariable()))
	{
		for (size_t i = 0; i < variables.size(); i++)
		{
			if (r->getVariable() == variables[i])
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

	bool productionCheck = true;
	if (r->getProduction().size() != 0)
	{
		for (size_t i = 0; i < r->getProduction().size(); i++)
		{
			for (size_t j = 0; j < r->getProduction()[i].size(); j++)
			{
				if (checkTerminalSet(r->getProduction()[i][j]))
				{
					continue;
				}
				else if (checkUpper(r->getProduction()[i][j]))
				{
					for (size_t k = 0; k < variables.size(); k++)
					{
						if (r->getProduction()[i][j] == variables[k][0])
						{
							productionCheck = true;
							break;
						}
						else
						{
							productionCheck = false;
						}
					}

					if (!productionCheck)
					{
						break;
					}
				}
				else
				{
					std::cout << "Incorrect productions.\n";
					assert(false);
				}
			}
		}
	}
	else
	{
		std::cout << "Empty productions.\n";
		assert(false);
	}

	if (variableCheck && productionCheck)
	{
		this->rules.push_back(r->clone());
	}
	else
	{
		std::cout << "Incorrect rule."<<variableCheck<<productionCheck<<"\n";
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
	for (size_t i = 0; i < variables.size()-1; i++)
	{
		os << variables[i] << " ";
	}
	os << variables[variables.size() - 1];
	os << '\n';
	for (size_t i = 0; i < terminals.size()-1; i++)
	{
		os << terminals[i] << " ";
	}
	os << terminals[terminals.size() - 1 ];
	os << '\n';
	os << startVariable;
	os<< '\n';
	os << rules.size();
	os << '\n';
	for (size_t i = 0; i < rules.size(); i++)
	{
		rules[i]->print(os);
		os << '\n';
	}
}

void Grammar::chomsky()
{
	bool chomskyCheck = true;
	for (size_t i = 0; i < rules.size(); i++)
	{
		for (size_t k = 0; k < rules[i]->getProduction().size(); k++)
		{
			if (rules[i]->getProduction()[k].size() == 1 && checkTerminal(rules[i]->getProduction()[k][0]))
			{
				chomskyCheck = true;
			}
			else if (rules[i]->getProduction()[k].size() == 2 && checkUpper(rules[i]->getProduction()[k][0])
				&& checkUpper(rules[i]->getProduction()[k][1]))
			{
				chomskyCheck = true;
			}
			else
			{
				chomskyCheck = false;
				break;
			}
		}

		if (!chomskyCheck)
		{
			break;
		}
	}

	if (chomskyCheck)
	{
		std::cout << "The grammar is in normal Chomsky form.\n";
	}
	else
	{
		std::cout << "The grammar is not in normal Chomsky form.\n";
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
