#include "GrammarSet.h"
#include "Invoker.h"

int main()
{
	/*Grammar g1 = { {}, {"A", "B", "C"}, {'a', 'b', 'c'}, "A" };
	Grammar g2 = { {}, {"D", "A", "F"}, {'a', 'b', 'c'}, "D" };
	g1.addRule(new Rule("A", { "BC" }));
	g1.addRule(new Rule("B", { "aBb", "ab" }));
	g1.addRule(new Rule("C", { "cC", "C" }));
	g2.addRule(new Rule("D", { "AF" }));
	g2.addRule(new Rule("A", { "aA", "a" }));
	g2.addRule(new Rule("F", { "bFc", "bc" }));

	g1.print();
	g2.print();
	std::cout << "--------------------------------------------\n";

	GrammarSet gs({&g1,&g2});
	gs.unionn("1-A", "2-D");
	gs.print("3-S01");*/

	Invoker remote;
	std::string input;
	while (true)
	{
		getline(std::cin, input);
		remote.executeCommand(input);
	}

	return system("pause");
}  