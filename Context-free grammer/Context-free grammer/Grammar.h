#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Rule.h"
#include <iostream>
#include <vector>
#include <string>
#include <cassert>


class Grammar
{
private: 
	std::vector<Rule*> rules;
	std::string id;
	std::vector <char> variables; // A -> non-terminal
	std::vector<std::string> terminals; // -> a terminal
	std::string startVariable;
	static int counter;

	bool checkVariable(const char ch)const;
	bool checkTerminal(const char ch)const;
	bool checkExistingVariable(const std::string ch) const;
	void copy(const Grammar& other);

	void createId();

public:
	Grammar();
	Grammar(const std::vector<Rule*>& rules, const std::vector<char> variables,
		    const std::vector<std::string> terminals, const std::string startVariable);
	Grammar(const Grammar& other);
	~Grammar();

	Grammar& operator=(const Grammar& other);

	std::string getId()const;

	Grammar* clone() const;

	void addRule(const Rule* r);
	void removeRule(int index);
	void save(std::ostream& os);

	void print()const;

};
#endif // !GRAMMER_H

