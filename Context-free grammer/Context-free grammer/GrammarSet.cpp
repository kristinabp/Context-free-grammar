#include "GrammarSet.h"

int GrammarSet::counter = 0;

bool GrammarSet::checkVariablesSet(const Grammar & first, const Grammar & second)
{
	bool flag = true;
	for (size_t i = 0; i < first.getVariables().size(); i++)
	{
		if (std::find(second.getVariables().begin(), second.getVariables().end(), first.getVariables()[i]) != second.getVariables().end())
		{
			continue;
		}
		else {
			return false;
			break;
		}
	}

	return true;
}

GrammarSet::GrammarSet(): grammarSet(std::vector<Grammar*>())
{
}

GrammarSet::GrammarSet(std::vector<Grammar*> grammars)
{
	this->grammarSet = grammars;
}

void GrammarSet::addGrammar(const Grammar * grammar)
{
	this->grammarSet.push_back(grammar->clone());
}

void GrammarSet::help()
{
	std::cout << "> help\n";
	std::cout << "------ The following commands are supported : -------------------------------------------------\n";
	std::cout << "|open <file>				opens <file>\n";
	std::cout << "|close					closes currently opened file\n";
	std::cout << "|save <id> <fileName>			saves a grammar in a file\n";
	std::cout << "|saveas <file>				saves the currently open file in <file>\n";
	std::cout << "|help					prints this information\n";
	std::cout << "|exit					exists the program\n";
	std::cout << "|addgrammar <grammarName>		adds new grammar\n";
	std::cout << "|list 					lists all grammar ids\n";
	std::cout << "|print <id>				prints a grammar\n";
	std::cout << "|addRule <id> <rule> 			adds a new rule\n";
	std::cout << "|removeRule <id> <n> 			removes a rule with a number\n";
	std::cout << "-----------------------------------------------------------------------------------------------\n";
}

void GrammarSet::open(std::string fileName)
{
	std::fstream inputFile;
	inputFile.open(fileName, std::ios::in);
	if (!isOpen)
	{
		if (inputFile.is_open())
		{
			this->isOpen = true;
			this->fileName = fileName;
			std::vector<std::string> variables;
			std::vector<char> terminals;
			std::vector<std::string> rules;;
			std::string startVariable;
			std::string numRules;
			std::string temp;

				//variables -> A B C D ...
				std::getline(inputFile, temp);
				int k = 0;
				std::string tempVar;
				while (k < temp.size())
				{
					if (temp[k] != ' ')
					{
						tempVar.push_back(temp[k]);
						k++;
					}
					else
					{
						variables.push_back(tempVar);
						tempVar = "";
						k++;
					}
				}
				variables.push_back(tempVar);

				//terminals -> a b c d ....
				std::getline(inputFile, temp);
				k = 0;
				while (k < temp.size())
				{
					if (temp[k] != ' ')
					{
						terminals.push_back(temp[k]);
						k++;
					}
					else
					{
						k++;
					}
				}
				getline(inputFile, startVariable);

				//creating new grammar to save the current input
				Grammar gr({}, variables, terminals, startVariable);

				std::string firstPart, curr;
				std::vector<std::string> secondPart;
				int j = 0;
				getline(inputFile, numRules);
				int num = stoi(numRules);

				//rules : firstPart -> secondPart
				//firstPart : variables
				//secondPart :terminals

				while (num > 0)
				{
					getline(inputFile, temp);
					while (temp[j] != '-')
					{
						firstPart.push_back(temp[j]);
						j++;
					}
					j += 2;
					while (j < temp.size())
					{
						while (temp[j] != '|' && j < temp.size())
						{
							curr.push_back(temp[j]);
							j++;
						}
						secondPart.push_back(curr);
						curr = "";
						j++;
					}
					j = 0;
					num--;
					gr.addRule(new Rule(firstPart, secondPart));
					firstPart = "";
					secondPart.clear();
				}

				addGrammar(&gr);
			inputFile.close();
		}
		
	}
	else
	{
		std::cout << "You have already opened a file.Close it to open a new file.\n";
	}
}

void GrammarSet::exit()
{
	std::cout << "> exit\n";
	std::cout << "Exiting the program...\n";
}

void GrammarSet::list()
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		std::cout << grammarSet[i]->getId();
	}
}

void GrammarSet::print(std::string id)
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (id == grammarSet[i]->getId())
		{
			grammarSet[i]->print();
		}
	}
}

void GrammarSet::save(std::string id, std::string fileName)
{
	std::ofstream myfile;
	myfile.open(fileName);
	if (myfile.good())
	{
		for (size_t i = 0; i < grammarSet.size(); i++)
		{
			if (grammarSet[i]->getId() == id)
			{
				grammarSet[i]->save(myfile);
				myfile.close();
				std::cout << "Successfully saved as " << fileName << "\n";
				return;
			}
			else
			{
				std::cout << "Grammar with this id does not exist.\n";
			}
		}
		myfile.close();
		std::cout << "Could not saved as " << fileName << "\n";
		
	}
	else
	{
		std::cout << "Couldn't open " << fileName << "\n";
	}
}

void GrammarSet::addRule(const std::string id, const std::string rule)
{
	if (rule == "")
	{
		std::cout << "Incorrect input.\n";
	}

	if (!rule.find("->"))
	{
		std::cout << "Incorrect input.\n";
	}

	std::string firstPart, curr;
	std::vector<std::string> secondPart;
	int i = 0;
	while (rule[i] != '-')
	{
		firstPart.push_back(rule[i]);
		i++;
	}
	i += 2;
	while (i < rule.size())
	{
		while (rule[i] != '|' && i < rule.size())
		{
			curr.push_back(rule[i]);
			i++;
		}
		secondPart.push_back(curr);
		curr = "";
		i++;
	}

	bool findGrammar = true;
	if (firstPart.size() >= 2)
	{
		std::cout << "Incorrect input.\n";
	}
	else
	{
		for (size_t i = 0; i < grammarSet.size(); i++)
		{
			if (grammarSet[i]->getId() == id)
			{
				findGrammar = true;
				grammarSet[i]->addRule(new Rule(firstPart,secondPart));
				break;
			}
			else
			{
				findGrammar = false;
			}
		}
		if (findGrammar)
		{
			std::cout << "Sucessfully added rule " << firstPart << " -> ";
			for (size_t i = 0; i < secondPart.size(); i++)
			{
				std::cout << secondPart[i] << " | ";
			}
			std::cout << std:: endl;
		}
		else
		{
			std::cout << "Couldn't find grammar with this id.\n";
		}
	}
}

void GrammarSet::removeRule(std::string id, int index)
{
	bool flag = true;
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id)
		{
			grammarSet[i]->removeRule(index);
			flag = true;
			break;
		}
		else
		{
			flag = false;
		}
	}
	if (!flag)
	{
		std::cout << "Incorrect Id.\n";
	}
}

void GrammarSet::unionn(const std::string & id1, const std::string & id2)
{
	if (id1 == id2)
	{
		std::cout << "Try to union the same grammars.\n";
		assert(false);
	}
	//first step: arrange it so the two grammars have no variables(non-terminals) in common

	Grammar* firstGrammar = nullptr;
	Grammar* secondGrammar=nullptr;
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id1)
		{
			firstGrammar = grammarSet[i];
			break;
		}
	}

	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id2)
		{
			secondGrammar = grammarSet[i];
			break;
		}
	}
	this->counter++;
	std::string newStartingVariable = "S0" + std::to_string(counter);
	Grammar* newGrammar = new Grammar({}, { newStartingVariable }, firstGrammar->getTerminals(), newStartingVariable);

	//check if terminals sets are equal, if not return error
	if (firstGrammar->getTerminals() == secondGrammar->getTerminals())
	{
		if (checkVariablesSet(*firstGrammar, *secondGrammar))
		{

		}
		else
		{
			for (size_t i = 0; i < firstGrammar->getVariables().size(); i++)
			{
				newGrammar->addNewVariable(firstGrammar->getVariables()[i]);
			}
			
			for (size_t i = 0; i < secondGrammar->getVariables().size(); i++)
			{
				newGrammar->addNewVariable(secondGrammar->getVariables()[i]);
			}

            newGrammar->addRule(new Rule(newStartingVariable, { firstGrammar->getStartVariable() , secondGrammar->getStartVariable() }));
			for (size_t i = 0; i < firstGrammar->getRules().size(); i++)
			{
				newGrammar->addRule(firstGrammar->getRules()[i]);
			}

			for (size_t i = 0; i < secondGrammar->getRules().size(); i++)
			{
				newGrammar->addRule(secondGrammar->getRules()[i]);
			}
			addGrammar(newGrammar);
		}

	}
	else
	{
		std::cout << "Not equal terminal sets.\n";
		assert(false);
	}
}
