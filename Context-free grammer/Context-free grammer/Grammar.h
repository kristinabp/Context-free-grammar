#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Rule.h"
#include <iostream>
#include <vector>
#include <string>


class Grammar
{
private: 
	std::vector<Rule*> rules;
	std::string id;
	std::vector<char> variables;
	std::vector<std::string> terminals;
	char startVariable;

	bool checkVariable(const char ch)const;
	bool checkTerminal(const char ch)const;

	void copy(const Grammar& other);

public:
	Grammar();
	Grammar(const std::vector<Rule*> rules, const std::string id, const std::vector<char> variables,
		    const std::vector<std::string> terminals, const char startVariable);
	Grammar(const Grammar& other);
	~Grammar();

	Grammar& operator=(const Grammar& other);

	Grammar& addRule(Rule* rule);
	void removeRule(int n);



	void print()const;

};
#endif // !GRAMMER_H

