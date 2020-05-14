#include "GrammarSet.h"
#include "Invoker.h"

int main()
{
    GrammarSet g;
	g.open("grammar1.txt");
	g.print("1-A");

	return system("pause");
}  