#ifndef CMD_PARSER_H
#define CMD_PARSER_H
#define MAX_ARGS 10
#define MAX_TERMS 40
 
#include <Arduino.h>

class Command{
  public:
  	String name;
  	String args[MAX_ARGS];
  	int argCount;

  	Command();
	Command(String _name);

	void addArg(String arg);

	void printArgs();
};

class Term{
  public:
  	String name;
  	boolean state;
	
	Term();
	Term(String _name, boolean _state);
	
	String toString();
};

class Expression{
  public:
  	String name;
  	Term terms[MAX_TERMS];
  	int termCount;
	
	Expression ();
	Expression (String _name);

	void addTerm(Term term);

	void printTerms();
};

class CommandParser{
  public:
	static void parseCommand(String text, Command* cmd);
	
	static void parseExpression(String text, Expression* exp);
};

#endif