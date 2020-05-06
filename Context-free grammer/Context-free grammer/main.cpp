#include "GrammarSet.h"

int main()
{
	Grammar g({}, { 'A','B' }, {"aAB", "b"}, 'A');
	g.print();
	return system("pause");
}  