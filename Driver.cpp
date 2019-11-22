#include<iostream>
#include<string>
#include "Led.h"
using std::cout;
using std::endl;
using std::string;
int main(int argc, char* argv[])
{
	/*Command c(".,  $ p", 13, 12);
	cout << c.parse() << endl;
	cout << "symbol" << c.fetch_cmdSymbol() << endl;
	cout << "first" << c.fetch_firstLineNum() << endl;
	cout << "last" << c.fetch_secondLineNum() << endl;*/
	string filenme;
	switch (argc)
	{
	case 1:
		break;
	case 2:
		filenme = argv[1];
		break;
	default: cout << ("Too many arguments - All discarded") << endl;
		break;
	}
	Led editor(filenme);
	editor.run();
	return 0;
}