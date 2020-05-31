#include "GrammarSet.h"

GrammarSet::GrammarSet(): grammarSet(std::vector<Grammar*>()), isOpen(false), fileName("")
{
}

GrammarSet::GrammarSet(std::vector<Grammar*> grammars): isOpen(false), fileName("")
{
	this->grammarSet = grammars;
}

void GrammarSet::addGrammar(const Grammar * grammar)
{
	this->grammarSet.push_back(grammar->clone());
}

void GrammarSet::help()
{
	if (isOpen)
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
		std::cout << "|chomsky <id> 			checks whether a grammar is in normal chomsky form\n";
		std::cout << "|iter <id> 			    \n";
		std::cout << "-----------------------------------------------------------------------------------------------\n";
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::open(std::string fileName)
{
	std::ifstream inputFile;
	inputFile.open(fileName, std::ios::in);
	if (!isOpen)
	{
		if (inputFile.is_open())
		{
			this->isOpen = true;
			this->fileName = fileName;
			std::vector<std::string> variables;
			std::vector<char> terminals;
			std::vector<std::string> rules;
			std::string startVariable;
			std::string numRules;
			std::string temp;

			/*while (!inputFile.eof())
			{*/
				//variables -> A B C D ...
				std::getline(inputFile, temp); // first line - only variables
				int k = 0;
				while (k < temp.size())
				{
					if (temp[k] != ' ')
					{
						variables.push_back(std::string(&temp[k], 1));
						k++;
					}
					else
					{
						k++;
					}
				}

				//terminals -> a b c d ....
				std::getline(inputFile, temp); // second line - only terminals
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

				getline(inputFile, startVariable); // third line - starting variable
				//creating new grammar to save the current input, because by the current input we will validate the rules
				Grammar gr({}, variables, terminals, startVariable[0]);

				std::string firstPart, curr;
				std::vector<std::string> secondPart;
				int j = 0;
				getline(inputFile, numRules);
				int num = stoi(numRules); // number of rules

				//rules : firstPart -> secondPart
				//firstPart : variables
				//secondPart : production

				while (num > 0)
				{
					getline(inputFile, temp); // next lines are only rules
					while (temp[j] != '-')
					{
						firstPart.push_back(temp[j]);
						j++;
					}
					j += 2; // we skip "->"
					while (j < temp.size())
					{
						while (temp[j] != '|' && j < temp.size()) // if we read '|' it means that there is more than one production
						{
							curr.push_back(temp[j]);// that is why we need a variable curr to save the different productions
							j++;
						}
						secondPart.push_back(curr);
						curr = "";
						j++;
					}
					j = 0;
					num--;
					gr.addRule(new Rule(firstPart, secondPart)); // if the rule is incorrect addRule will return error
					firstPart = "";
					secondPart.clear();
				}

				addGrammar(&gr);

				/*variables.clear();
				terminals.clear();
				rules.clear();
				startVariable.clear();
				numRules="";
			}*/

			inputFile.close();

			std::cout << "> open " << fileName << "\n";
			std::cout << "Successfully opened " << fileName << "\n";
			std::cout << "------------------------------------------\n";
			std::cout << "----------- Grammars:--------------\n";
			for (size_t i = 0; i < grammarSet.size(); i++)
			{
				grammarSet[i]->print();
			}
			std::cout << "------------------------------------------\n";
		}
		else
		{
			std::cout << "Couldn't open " << fileName << "\n";
			std::cout << "Creating new file..\n";

			inputFile.open(fileName, std::ios::in | std::ios::out | std::ios::trunc);
			this->isOpen = true;
			this->fileName = fileName;
			inputFile.close();
			std::cout << "Please, add grammars.\n";
        }
		
		
	}
	else
	{
		std::cout << "You have already opened a file.Close it to open a new file.\n";
	}
}

void GrammarSet::close()
{
	if (isOpen)
	{
		std::cout << "> close\n";
		std::cout << "Successfully closed " << fileName << ".\n";

		this->isOpen = false;
		this->fileName = "";
		this->grammarSet.clear();
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::saveAs(std::string fileName)
{
	if (isOpen)
	{
		std::ofstream myFile;
		myFile.open(fileName);
		if (myFile.good())
		{
			for (size_t i = 0; i < grammarSet.size(); i++)
			{
				grammarSet[i]->save(myFile);
			}
			myFile.close();
			std::cout << "> save as " << fileName << "\n";
			std::cout << "Successfully saved as " << fileName << "\n";
		}
		else
		{
			std::cout << "Couldn't open " << fileName << "\n";
		}
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

int GrammarSet::exit()
{
	std::cout << "> exit\n";
	std::cout << "Exiting the program...\n"; 
	return system("pause");
}

void GrammarSet::list()
{
	if (isOpen)
	{
		for (size_t i = 0; i < grammarSet.size(); i++)
		{
			std::cout << grammarSet[i]->getId() << "\n";
		}
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::print(std::string id)
{
	if (isOpen)
	{
		for (size_t i = 0; i < grammarSet.size(); i++)
		{
			if (id == grammarSet[i]->getId())
			{
				grammarSet[i]->print();
			}
		}
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::save(std::string id, std::string fileName)
{
	if (isOpen)
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
			}
			std::cout << "Grammar with this id does not exist.\n";
			myfile.close();
		}
		else
		{
			std::cout << "Couldn't open " << fileName << "\n";
		}
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::addRule(const std::string id, const std::string rule)
{
	if (isOpen)
	{
		if (rule == "") // if the input is empty
		{
			std::cout << "Incorrect input.\n";
			assert(false);
		}

		if (!rule.find("->")) // check if there is "->"
		{
			std::cout << "Incorrect input.\n";
			assert(false);
		}

		//rules : firstPart -> secondPart
		//firstPart : variables
		//secondPart : production

		std::string firstPart, curr;
		std::vector<std::string> secondPart;

		int i = 0;
		while (rule[i] != '-')
		{
			firstPart.push_back(rule[i]);
			i++;
		}
		i += 2; //skip "->"
		while (i < rule.size())
		{
			while (rule[i] != '|' && i < rule.size()) // if we read '|' it means that trere is more than one production
			{
				curr.push_back(rule[i]);
				i++;
			}
			secondPart.push_back(curr);
			curr = "";
			i++;
		}

		bool findGrammar = true;
		if (firstPart.size() > 1) //if the firstPart is "AA ->" returns error
		{
			std::cout << "Incorrect input.\n";
			assert(false);
		}
		else
		{
			for (size_t i = 0; i < grammarSet.size(); i++)
			{
				if (grammarSet[i]->getId() == id)
				{
					findGrammar = true;
					grammarSet[i]->addNewVariable(firstPart);
					grammarSet[i]->addRule(new Rule(firstPart, secondPart)); // function addRule checks if the rule is correct
					break;                                                // if the rule is incorrect it will return error
				}
				else
				{
					findGrammar = false;
				}
			}
			if (findGrammar)
			{
				std::cout << "Sucessfully added rule " << firstPart << "->";
				for (size_t i = 0; i < secondPart.size()-1; i++)
				{
					std::cout << secondPart[i] << "|";
				}
				std::cout << secondPart[secondPart.size() - 1] << "\n";
			}
			else
			{
				std::cout << "Couldn't find grammar with this id.\n";
			}
		}
	}
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::removeRule(std::string id, int index)
{
	if (isOpen)
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
	else
	{
		std::cout << "Please, open a file.\n";
	}
}

void GrammarSet::chomsky(std::string id)
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id)
		{
			grammarSet[i]->chomsky();
		}
	}
}

void GrammarSet::iter(const std::string id)
{
	for (size_t i = 0; i < grammarSet.size(); i++)
	{
		if (grammarSet[i]->getId() == id)
		{
			grammarSet[i]->iter();
			grammarSet[i]->print();
			return;
		}
	}
	std::cout << "Couldn't find grammar with this ID.\n";
}
