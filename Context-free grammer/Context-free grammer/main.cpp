#include "GrammarSet.h"

int main()
{
	Grammar g1 = { {}, {"A", "B", "C"}, {'a', 'b', 'c'}, 'A' };
	Grammar g2 = { {}, {"D", "A", "F"}, {'a', 'b', 'c'}, 'D' };
	g1.addRule(new Rule('A', { "BC" }));
	g1.addRule(new Rule('B', { "aBb", "ab" }));
	g1.addRule(new Rule('C', { "cC", "C" }));
	g2.addRule(new Rule('D', { "AF" }));
	g2.addRule(new Rule('A', { "aA", "a" }));
	g2.addRule(new Rule('F', { "bFc", "bc" }));

	g1.print();
	g2.print();
	std::cout << "--------------------------------------------\n";

	GrammarSet gs({ &g1,&g2 });
	gs.print("2-D");
	return system("pause");
}  