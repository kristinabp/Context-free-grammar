#ifndef RULE_H
#define RULE_H

#include <iostream>
#include <string>
#include <vector>

class Rule
{
private:
	std::string variable;
	std::vector<std::string> production;

	void copy(const Rule& other);

public:
	Rule();
	Rule(const std::string variable, const std::vector<std::string> production);
	Rule(const Rule& other);
	~Rule();

	std::string getVariable()const;
	std::vector<std::string> getProduction()const;

	Rule* clone() const;

	Rule& operator=(const Rule& other);

	void print(std::ostream& os)const;
};
#endif // !RULE_H

