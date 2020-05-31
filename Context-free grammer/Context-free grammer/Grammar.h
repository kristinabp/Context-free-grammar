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
	std::vector<Rule*> rules; // A -> ab
	std::string id;
	std::vector <std::string> variables; // A ->
	std::vector<char> terminals; // alphabet
	char startVariable; 
	static int counter;

	bool checkVariable(const std::string& ch)const;
	bool checkTerminal(const char& ch)const;
	bool checkTerminalSet(const char& ch)const;
	bool checkVariablesSet(const char& ch)const;
	bool checkUpper(const char& ch) const;
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
	std::vector<std::string> getVariables()const;
	std::vector<char> getTerminals()const;
	std::vector<Rule*> getRules()const;
	char getStartVariable()const;

	void setStartingVariable(const char& var);
	void addNewVariable(const std::string& var);

	Grammar* clone() const;

	void addRule(const Rule* r);
	void removeRule(int index);
	void save(std::ostream& os);
	void chomsky()const;
	void iter();

	void print()const;
};
#endif // !GRAMMER_H

