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
	std::vector <std::string> variables; // A -> non-terminal
	std::vector<char> terminals; // -> a
	char startVariable;
	static int counter;

	bool checkVariable(const char ch)const;
	bool checkTerminal(const char ch)const;
	void copy(const Grammar& other);

	void createId();

public:
	Grammar();
	Grammar(const std::vector<Rule*>& rules, const std::vector<std::string> variables,
		    const std::vector<char> terminals, const char startVariable);
	Grammar(const Grammar& other);
	~Grammar();

	Grammar& operator=(const Grammar& other);

	std::string getId()const;

	Grammar* clone() const;

	void addRule(const Rule* r);
	void save(std::ostream& os);

	void print()const;

};
#endif // !GRAMMER_H

