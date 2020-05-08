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
	std::vector <std::string> variables; // A -> non-terminal
	std::vector<std::string> terminals; // -> a terminal
	char startVariable;
	static int counter;

	bool checkVariable(const std::string ch)const;
	bool checkTerminal(const char ch)const;
	bool checkUpper(const char ch) const;
	void copy(const Grammar& other);

	void createId();

public:
	Grammar();
	Grammar(const std::vector<Rule*>& rules, const std::vector<std::string> variables,
		    const std::vector<std::string> terminals, const char startVariable);
	Grammar(const Grammar& other);
	~Grammar();

	Grammar& operator=(const Grammar& other);

	std::string getId()const;
	std::vector<std::string> getVariables()const;
	std::vector<std::string> getTerminals()const;

	void addNewVariable(const std::string& var);
	void setNewVariableName(size_t index, const char var);

	Grammar* clone() const;

	void addRule(const Rule* r);
	void removeRule(int index);
	void save(std::ostream& os);

	void print()const;

};
#endif // !GRAMMER_H

