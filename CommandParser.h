#ifndef CMD_PARSER_H
#define CMD_PARSER_H
#define MAX_ARGS 10
 
#include <Arduino.h>

class Command{
  public:
  	String name;
  	String args[MAX_ARGS];
  	int argCount;

	Command (String a);

	void addArg(String arg);

	void printArgs();
};

class CommandParser{
  public:
	static void parseCommand(String text, Command* cmd);
};

#endif