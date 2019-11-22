#ifndef COMMAND_H
#define COMMAND_H
#include<string>

class Command
{
private:
	std::string cmd;
	std::string firstLineNum;
	std::string secondLineNum;
	int ceilingLineNum;
	int currLine;
	char cmdSymbol;

	bool LineNum_valid(std::string, std::string);
public:
	Command(std::string, int, int);
	bool parse();		//parse the text and return bool
	std::string fetch_firstLineNum() const;		//fetch first line num
	std::string fetch_secondLineNum() const;		//fetch second line num
	char fetch_cmdSymbol() const;		//fetch command letter
	bool iscomma();
};
inline Command::Command(std::string cmd1, int ceilingLineNum1, int currLine1) : cmd{ cmd1 }, ceilingLineNum{ ceilingLineNum1 }, currLine{ currLine1 } {}
#endif
