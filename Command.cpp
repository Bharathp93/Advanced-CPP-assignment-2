#include<string>
#include<iostream>
#include "Command.h"

//parse the text and return bool
/*
* Finds content in command string.
* Searches the string for the first , second line number and also the command letter

* @return A boolean value if the entered command is valid or not
*/

bool Command::parse()
{
	//char a[3] = { '\0','\0','\0', };
	for (int i = 0; i < cmd.size(); i++)// remove white spaces
		if (cmd[i] == ' ')
		{
			cmd.erase(i, 1);
			i--;
		}
	//std::cout << "1: " << cmd << std::endl;
	if (!cmd.empty())		//when string id not empty
	{
		if (iscomma())		//when there is a comma in the command line
		{
			//std::cout << "2: " << std::endl;
			if (isalpha(cmd.back()))
			{
				//std::cout << "3: " << std::endl;
				cmdSymbol = cmd.back();
				cmd.pop_back();
			}
			else
			{
				//std::cout << "4: " << std::endl;
				cmdSymbol = 'p';
			}
			size_t comma_pos = cmd.find_first_of(",");
			firstLineNum = cmd.substr(0, comma_pos);		//check the position of comma should it be -1 or not
			secondLineNum = cmd.substr(comma_pos + 1, cmd.length() - 1);
			if (firstLineNum == "\0")
			{
				//std::cout << "5: " << std::endl;
				firstLineNum = ".";
			}
			if (secondLineNum == "\0")
			{
				//std::cout << "6: " << std::endl;
				secondLineNum = ".";
			}
		}

		else
		{
			if (cmd.back() == '+' || cmd.back() == '-')
			{
				//std::cout << "7: " << std::endl;
				cmdSymbol = cmd.back();
				cmd.pop_back();
				if (cmd.empty())
				{
					//std::cout << "8: " << std::endl;
					firstLineNum = "1";
					secondLineNum = "1";
				}
				else
				{
					//std::cout << "9: " << std::endl;
					firstLineNum = cmd;
					secondLineNum = cmd;
				}
			}
			else if (cmd.back() == '*')
			{
				//std::cout << "10: " << std::endl;
				cmdSymbol = 'p';
				firstLineNum = "1";
				secondLineNum = "$";
			}
			else
			{
				if (isalpha(cmd.back()))
				{
					//std::cout << "11: " << std::endl;
					cmdSymbol = cmd.back();
					cmd.pop_back();
				}
				else
				{
					//std::cout << "12: " << std::endl;
					cmdSymbol = 'g';
				}
				if (!cmd.empty())
				{
					firstLineNum = secondLineNum = cmd;
				}
				else
				{
					firstLineNum = secondLineNum = ".";
				}
			}
		}
	}
	else
	{
		cmdSymbol = '+';
		firstLineNum = "1";
		secondLineNum = "1";
	}

	/*int j = 0;
	for (std::string::iterator i = cmd.begin(); i != cmd.end(); ++i)
	{
		if (*i != ' ' && *i != ',')//this part wont work for two digit number
		{
			a[j] = *i;
			j++;
		}
	}
	this->cmdSymbol = a[2];
	this->secondLineNum = a[1];
	this->firstLineNum = a[0];*/

	if (firstLineNum == ".")
	{
		firstLineNum = std::to_string(currLine);
	}
	if (secondLineNum == ".")
	{
		secondLineNum = std::to_string(currLine);
	}
	if (firstLineNum == "$")
	{
		firstLineNum = std::to_string(ceilingLineNum);
	}
	if (secondLineNum == "$")
	{
		secondLineNum = std::to_string(ceilingLineNum);
	}
	if (!LineNum_valid(firstLineNum, secondLineNum))
		return false;
	if (stoi(firstLineNum) == 0 && stoi(secondLineNum) == 0 && cmdSymbol == 'i')
		return true;
	if (stoi(firstLineNum) > stoi(secondLineNum))
		return false;
	if (stoi(firstLineNum) < 1)
		return false;
	if (stoi(secondLineNum) > ceilingLineNum)
		return false;
	return true;

}

//fetch first line num
/*
* @return the first line number from the command entered "string"

*/

std::string Command::fetch_firstLineNum() const
{
	return this->firstLineNum;
}

//fetch second line num
/*
* @return the second line number from the command entered "string"

*/
std::string Command::fetch_secondLineNum() const
{
	return this->secondLineNum;
}

//fetch command letter
/*
* @return the command letter from the command entered "char"

*/
char Command::fetch_cmdSymbol() const
{
	return this->cmdSymbol;
}

/*
* @return a boolean value if a comma ',' is present
			in the command entered or not

*/
bool Command::iscomma()
{
	for (std::string::iterator i = cmd.begin(); i != cmd.end(); ++i)
	{
		if (*i == ',')
			return true;
	}
	return false;
}

/*

* @param  firstLine the first deduced line number.

* @param  secondLine the second deduced line number.

* @return a boolean value if the line numbers are valid
			or not, to check if they have unrecognized symbols

*/
bool Command::LineNum_valid(std::string firstLine, std::string secondLine)
{
	for (size_t n = 0; n < firstLine.length(); n++)
	{
		if (!isdigit(firstLine[n]))
		{
			return false;
		}
	}
	for (size_t  m= 0; m < secondLine.length(); m++)
	{
		if (!isdigit(secondLine[m]))
		{
			return false;
		}
	}
	return true;
}