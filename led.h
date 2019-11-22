#ifndef LED_H
#define LED_H
#include<string>
#include<list>
#include<vector>

class Led
{
private:
	std::list<std::string> buffer;
	std::vector<std::string> clipboard;
	int currentLine;
	int LastLine;
	std::string filename = "?";

	void append(int LineNum);		//append after
	void insert(int LineNum);		//insert before
	void paste_below(int LineNum);		
	void paste_above(int LineNum);
	void deleteLines(int startLine, int endLine);
	void cuts(int startLine, int endLine);		//cuts and store it in clipboard
	void replace(int startLine, int endLine);		//similar to delete and then add
	void join(int startLine, int endLine);		//joins all lines in the range into a singlr line
	void print(int startLine, int endLine);		//prints all lines in range but does not affect current line
	void change(int startLine, int endLine);		//replaces all occurances of the specified text bw the range
	void moveUp(int times);		//moves up by specified no of times and sets as current line
	void moveDown(int times);		//moves down by specified no of times and sets as current line
	void goTo(int LineNum);		//moves to specified line no and print that line
	void writeToFile(std::string filename);		//writes entire buffer to file
	void quit();		//quit


public:
	Led(std::string fileName);
	void run();

};
#endif LED_H
