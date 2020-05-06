#include "GrammarSet.h"

int main()
{
	//Rule r1('S', { "ab", "K" });
	//Rule r2('K', { "kk", "K"});
	//std::vector<Rule*> r;
	//r.push_back(new Rule(r1));
	///*Grammar g(r, { "S","K" }, {'a', 'k', 'b'}, 'S');
	//g.addRule(&r1);
	//g.addRule(&r2);
	//g.print();*/
	//GrammarSet s;
	//Grammar g2(r, { "K", "S" }, { 'a', 'k', 'b' }, 'K');
	//g2.print();
	//s.addGrammar(&g2);
	//s.print("1-K");
	//s.removeRule("1-K", 1);
	//s.print("1-K");

	std::string rule = "S->ab|k";
	std::string firstPart, secondPart;
	int i = 0;
	while (rule[i] != '-')
	{
		firstPart.push_back(rule[i]);
		i++;
	}
	std::cout << firstPart<< "\n";
	i += 2;
	while (i<rule.size())
	{
		secondPart.push_back(rule[i]);
		i++;
	}
	std::cout << secondPart;
	return system("pause");
}  