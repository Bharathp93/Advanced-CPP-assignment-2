#include<iostream>
#include<fstream>
#include<string>
#include<list>
#include<vector>
#include "Command.h"
#include "Led.h"
using namespace std;

/*
* is the constructor to the Led class, intializes all the data members in the class

* @param  fileName the filename entered by the user as an argument.
*/

Led::Led(std::string fileName)
{
	this->filename = fileName;
	ifstream fin(fileName);
	if (!fin)
	{
		cout << "\"" << fileName << "\"" << "[New File]" << endl;
		buffer;
		clipboard;
		cout << "ENTERING COMMAND MODE" << endl;
		LastLine = currentLine = 0;
		run();
		//exit(1);
	}
	else
	{
		int linenum = 0;
		string line;
		//getline(fin, line);
		//cout << line;
		while (getline(fin, line))
		{
			//cout << "1:" << endl;
			//getline(fin, line);
			++linenum;
			buffer.push_back(line);
			//istringstream sin(line);
			//string word;
			/*while (sin >> word)
			{
				//trimming a word


				char* charArrayWord = new char[word.length() + 1];
				strcpy(charArrayWord, word.c_str());
				//process line number and charArrayWord
			}*/
		}
		this->LastLine = linenum;
		this->currentLine = linenum;
		cout << "\"" << fileName << "\" " << linenum << " line(s)" << endl;
		clipboard;
		cout << "ENTERING COMMAND MODE" << endl;
		run();
	}
}

/*
* main method of the Led class which calls the respective methods according to the 
			command specified by the used in the line editor
*/

void Led::run()
{
	string command;
	cout << "? ";
	while (getline(cin, command))
	{
		Command c(command, LastLine, currentLine);
		bool parsing = c.parse();
		//cout << currentLine << endl;
		//cout << LastLine << endl;
		/*cout << "command: " << command << endl;
		cout << "cmd: " << c.fetch_cmdSymbol() << endl;
		cout << "first: " << c.fetch_firstLineNum() << endl;
		cout << "second: " << c.fetch_secondLineNum() << endl;*/
		if (buffer.empty())
		{
			//if (parsing)
			//{
				//cout << "1:" << endl;
				//char cmd = c.fetch_cmdSymbol();
				switch (c.fetch_cmdSymbol())
				{
				case 'a': {
					append(stoi(c.fetch_firstLineNum()));
					break;
				}
				case 'i': {//cout << "1:" << endl;
					insert(stoi(c.fetch_firstLineNum()));
					break;
				}
				case '-': {
					if (!buffer.empty())
					{
						moveUp(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case '+': {
					if (!buffer.empty())
					{
						moveDown(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'g': {
					if (!buffer.empty())
					{
						goTo(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
						  //case '*':
				default: {
					cout << "Enter a valid command" << endl;
				}
				}
				cin.clear();
			/*}
			else
			{
				cout << "2:" << endl;
				cout << "empty buffer" << endl;
				cout << "? ";
			}*/
		}
		else
		{
			if (parsing)
			{
				//cout << "3:" << endl;
				char cmd = c.fetch_cmdSymbol();
				switch (cmd)
				{
				case 'a': {
					append(stoi(c.fetch_firstLineNum()));
					break;
				}
				case 'i': {
					insert(stoi(c.fetch_firstLineNum()));
					break;
				}
				case 'v': {
					if (!buffer.empty())
					{
						paste_below(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'u': {
					if (!buffer.empty())
					{
						paste_above(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'd': {
					if (!buffer.empty())
					{
						deleteLines(stoi(c.fetch_firstLineNum()), stoi(c.fetch_secondLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'x': {
					if (!buffer.empty())
					{
						cuts(stoi(c.fetch_firstLineNum()), stoi(c.fetch_secondLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'r': {
					if (!buffer.empty())
					{
						replace(stoi(c.fetch_firstLineNum()), stoi(c.fetch_secondLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'j': {
					if (!buffer.empty())
					{
						join(stoi(c.fetch_firstLineNum()), stoi(c.fetch_secondLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'p': {
					if (!buffer.empty())
					{
						print(stoi(c.fetch_firstLineNum()), stoi(c.fetch_secondLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'c': {
					if (!buffer.empty())
					{
						change(stoi(c.fetch_firstLineNum()), stoi(c.fetch_secondLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case '-': {
					if (!buffer.empty())
					{
						moveUp(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case '+': {
					if (!buffer.empty())
					{
						moveDown(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'g': {
					if (!buffer.empty())
					{
						goTo(stoi(c.fetch_firstLineNum()));
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'w': {
					if (!buffer.empty())
					{
						writeToFile(filename);
					}
					else
					{
						cout << "Buffer empty" << endl;
					}
					break;
				}
				case 'q': {
					quit();
					exit(1);
				}
						  //case '*':
				default: {
					cout << "Enter a valid command" << endl;
				}
				}
				cin.clear();
			}
			else
			{
				//cout << "4:" << endl;
				cout << "invalid range" << endl;
			}
		}

		cout << "? ";
	}
}

//append "a" operation
/*
* inserts lines in the buffer after the specified line number
	and places the current line to the last modified line

* @param  LineNum the line number after which the line has to be appended
*/

void Led::append(int LineNum)
{
	currentLine = LineNum;
	list<string>::iterator i = buffer.begin();
	int i1 = 0;
	int newLines = 0;
	if (LineNum == LastLine)
	{
		string input;
		while (getline(cin, input))
		{
			buffer.push_back(input);
			newLines++;
		}
	}
	else
	{
		while (i != buffer.end()) {
			if (i1 == LineNum)
			{
				string input;
				while (getline(cin, input))
				{
					buffer.insert(i, input);
					newLines++;
				}
			}
			i++;
			i1++;
		}
	}
	if (newLines > 0)
	{
		currentLine = LineNum + newLines;
		LastLine = LastLine + newLines;
	}
}

//insert "i" operation
/*
* inserts lines in the buffer before the specified line number
	and places the current line to the last modified line

* @param  LineNum the line number before which the line has to be appended
*/
void Led::insert(int LineNum)
{
	/*if (LastLine == 0 && currentLine == 0)
	{
		int newLines = 0;
		string input;
		while (getline(cin, input))
		{
			buffer.push_back(input);
			newLines++;
		}
		if (newLines > 0)
		{
			currentLine = LastLine = newLines;
		}
	}
	else
	{*/
		//cout<< currentLine<<"-"<< LineNum;
		currentLine = LineNum;
		list<string>::iterator i = buffer.begin();
		if (LineNum == 0)				//when there is nothing in the buffer
			advance(i, LineNum);
		else
			advance(i, LineNum - 1);
		//int i1 = 0;
		int newLines = 0;
		//while (i != buffer.end()) {
			//if (i1 == LineNum - 1)
			//{
		string input;
		while (getline(cin, input))
		{
			buffer.insert(i, input);
			newLines++;
		}
		//exit(1);
	//}
	//i++;
	//i1++;
//}
		if (newLines > 0)
		{
			if (currentLine != 0)
			{
				currentLine = LineNum + (newLines - 1);
				LastLine = LastLine + newLines;
			}
			else
				currentLine = LastLine = newLines;
		}
	//}

}

//paste below "v" operation
/*
* pastes lines in the clipboard after the specified line number
	and places the current line to the last modified line

* @param  LineNum the line number after which the lines have to be put in
*/
void Led::paste_below(int LineNum)
{
	currentLine = LineNum;
	list<string>::iterator i = buffer.begin();
	int i1 = 0;
	int newLines = 0;
	while (i != buffer.end()) {
		if (i1 == LineNum)
		{
			for (vector<string>::iterator j = clipboard.begin(); j != clipboard.end(); j++)
			{
				buffer.insert(i, *j);
				newLines++;
			}
			break;
		}
		i++;
		i1++;
	}
	currentLine = LineNum + newLines;
	LastLine = LastLine + newLines;
	clipboard.clear();
}

//paste above "u" operation
/*
* pastes lines in the clipboard before the specified line number
	and places the current line to the last modified line

* @param  LineNum the line number before which the lines have to be put in
*/
void Led::paste_above(int LineNum)
{
	currentLine = LineNum;
	list<string>::iterator i = buffer.begin();
	int i1 = 0;
	int newLines = 0;
	while (i != buffer.end()) {
		if (i1 == LineNum - 1)
		{
			for (vector<string>::iterator j = clipboard.begin(); j != clipboard.end(); j++)
			{
				buffer.insert(i, *j);
				newLines++;
			}
			break;
		}
		i++;
		i1++;
	}
	currentLine = LineNum + (newLines - 1);
	LastLine = LastLine + newLines;
	clipboard.clear();
}

//delete "d" operation
/*
* deletes the lines specifed by the line range
	and places the cutrent line to the following line

* @param  startLine starting line range.

* @param  endLine terminating line range.
*/

void Led::deleteLines(int startLine, int endLine)
{
	currentLine = startLine;
	list<string>::iterator i = buffer.begin();
	list<string>::iterator j = buffer.begin();
	advance(i, startLine - 1);
	advance(j, endLine - 1);
	while (i != j) {
		i = buffer.erase(i);
		LastLine--;
		endLine--;
	}
	if (endLine == LastLine)
	{
		buffer.erase(i);
		LastLine = currentLine = startLine - 1;
	}
	else
	{
		buffer.erase(i);
		LastLine = LastLine - ((endLine - startLine) + 1);
	}
}

//cut "x" operation
/*
* cuts the lines specifed by the line range and copies it to the clipboard
and places the current line to the following line

* @param  startLine starting line range.

* @param  endLine terminating line range.
*/
void Led::cuts(int startLine, int endLine)
{
	clipboard.clear();
	currentLine = startLine;
	list<string>::iterator i = buffer.begin();
	list<string>::iterator j = buffer.begin();
	advance(i, startLine - 1);
	advance(j, endLine - 1);
	while (i != j) {
		clipboard.push_back(*i);
		i = buffer.erase(i);
		LastLine--;
		endLine--;
		//i++;
	}
	if (endLine == LastLine)
	{
		clipboard.push_back(*i);
		buffer.erase(i);
		LastLine = currentLine = startLine - 1;
	}
	else
	{
		clipboard.push_back(*i);
		buffer.erase(i);
		LastLine = LastLine - ((endLine - startLine) + 1);
	}
}

//replace "r" operation
/*
* replaces the lines specifed by the line range by the ones entered by the user
and places the current line to the most recently changed line

* @param  startLine starting line range.

* @param  endLine terminating line range.
*/
void Led::replace(int startLine, int endLine)
{
	deleteLines(startLine, endLine);
	insert(currentLine);
}

//join "j" operation
/*
* joins all the line within the range specified
and places the current line to the most recently changed line

* @param  startLine starting line range.

* @param  endLine terminating line range.
*/
void Led::join(int startLine, int endLine)
{
	list<string>::iterator i = buffer.begin();
	list<string>::iterator i1 = buffer.begin();
	list<string>::iterator j = buffer.begin();
	advance(i, startLine - 1);
	advance(i1, startLine);
	advance(j, endLine - 1);
	while (i1 != j) {
		*i = *i + " " + *i1;
		i1++;
	}
	*i = *i + " " + *i1;
	deleteLines(startLine + 1, endLine);
	currentLine = startLine;
}

//print "p" operation
/*
* prints the lines in the specified range

* @param  startLine starting line range.

* @param  endLine terminating line range.
*/
void Led::print(int startLine, int endLine)
{
	int line = startLine;
	list<string>::iterator i = buffer.begin();
	list<string>::iterator j = buffer.begin();
	list<string>::iterator curr = buffer.begin();
	advance(i, startLine - 1);
	advance(j, endLine - 1);
	advance(curr, currentLine - 1);
	while(i != j)
	{
		if(i != curr)
			cout << line << ": " << *i << endl;
		else
			cout << line << "> " << *i << endl;
		i++;
		line++;
	}
	if (i != curr)
		cout << line << ": " << *i << endl;
	else
		cout << line << "> " << *i << endl;

}

//change "c" operation
/*
* changes all the occurances of the user specified text within the line number range
	with the text that is specified by the user

* @param  startLine starting line range.

* @param  endLine terminating line range.
*/
void Led::change(int startLine, int endLine)
{
	string find1;
	string replace1;
	cout << "Change what? ";
	cin >> find1;
	cout << "To what? ";
	cin >> replace1;
	int count = 0;
	list<string>::iterator i = buffer.begin();
	list<string>::iterator j = buffer.begin();
	advance(i, startLine - 1);
	advance(j, endLine);
	do
	{
		size_t start_pos = 0;
		while (true)
		{
			start_pos = (*i).find(find1, start_pos);
			if (start_pos == std::string::npos)
				break;
			(*i).replace(start_pos, find1.length(), replace1);
			count++;
			start_pos = start_pos + find1.length();
		}
		i++;
	} while (i != j);
	cout << "Changed " << count << " occurance(s)" << endl;
}

//move up "-" operation
/*
* moves the current line cursor up by the amount specified

* @param  times the number of times to move up
*/
void Led::moveUp(int times)
{
	while (times != 0)
	{
		if (currentLine != 1)
		{
			currentLine--;
			times--;
		}
		else
		{
			cout << "Top of file reached" << endl;
			break;
		}
	}
}

//move down "+" operation
/*
* moves the current line cursor down by the amount specified

* @param  times the number of times to move down
*/
void Led::moveDown(int times)
{
	while (times != 0)
	{
		if (currentLine != LastLine)
		{
			currentLine++;
			times--;
		}
		else
		{
			cout << "End of file reached" << endl;
			break;
		}
	}
}

//go to "g" operation
/*
* go to the line number specified

* @param  LineNum the line number to mive the cursor to
*/
void Led::goTo(int LineNum)
{
	if (LineNum < 1 && LineNum > LastLine)
	{
		cout << "invalid range" << endl;
	}
	else
	{
		currentLine = LineNum;
		print(LineNum, LineNum);
	}
}

//write "w" operation
/*
* writes the contents of the buffer to the filename specified by the user when prompted

* @param  filename file name where wo tbe written
*/
void Led::writeToFile(string filename)		//some changes to be made to the function
{
	int lines = 0;
	ofstream fout(filename);
	for (list<string>::iterator i = buffer.begin(); i != buffer.end(); i++)
	{
		fout << *i << endl;
		lines++;
	}
	cout << lines << " line(s) written to the file: \"" << filename << "\"" << endl;
}

//quit "q" operation
/*
* writes the contents of the buffer to the filename specified by the user when prompted
	and then quits upon conformation
*/
void Led::quit()
{
	char answer;
	cout << "Save changes to the file (y/n)? ";
	cin >> answer;
	while (answer != 'y' && answer != 'n')
	{
		cout << "bad answer: " << answer << endl;
		cout << "Enter y for yes and n for no." << endl;
		cout << "Save changes to the file (y/n)? ";
		cin >> answer;
	}
	if (answer == 'y')
	{
		string f;
		cout << "Enter a file name: ";
		cin >> f;
		cout << endl;
		writeToFile(f);
		cout << "Bye";
	}
	else if (answer == 'n')
	{
		cout << "Bye";
	}
}