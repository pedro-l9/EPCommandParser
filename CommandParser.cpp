#include "CommandParser.h"

Command::Command() {
	name = "";
	argCount = 0;
}

Command::Command(String _name) {
	name = _name;
	argCount = 0;
}

void Command::addArg(String arg){
	args[argCount++] = arg;
}

void Command::printArgs(){
	Serial.print("Args: ");
	for(int i = 0; i < argCount; i++){
		Serial.print(args[i] + (i < argCount -1 ? "," : ";\n"));
	}
}

Term::Term() {
	name = "";
	state = false;
}

Term::Term(String _name, boolean _state) {
	name = _name;
	state = _state;
}

String Term::toString () {
	return (name + (state ? "+" : "-"));
}

Expression::Expression(){
	name = "";
	termCount = 0;
}

Expression::Expression(String _name){
	name = _name;
	termCount = 0;
}

void Expression::addTerm(Term term){
	terms[termCount++] = term;
}

void Expression::printTerms(){
	Serial.print("Terms: ");
	for(int i = 0; i < termCount; i++){
		Serial.print(terms[i].toString() + (i < termCount -1 ? "," : ";\n"));
	}
}

void CommandParser::parseCommand(String text, Command* cmd){
	int state = 0;
	String arg;

	cmd->name = "";
	cmd->argCount = 0;

	for(int i = 0; i < text.length(); i++){
		char c = text.charAt(i);
		switch(state){
			case 0:
				if(c == '('){
					state++;
				}else{
					cmd->name += c;
				}
				break;
			case 1:
				arg = "";
				state++;
			case 2:
				if(c == ',' || c == ')'){
					state = 1;
					if(arg != "") cmd->addArg(arg);
				}else{
					if(c != ' ') arg += c;
				}
				break;
		}
	}
}

void CommandParser::parseExpression(String text, Expression* exp){
	int state = 0;
	String name = "";
	Term term;

	exp->termCount = 0;

	for(int i = 0; i < text.length(); i++){
		char c = text.charAt(i);
		if(c == '+' || c == '-'){
			term.name = name;
			term.state = c == '+';
			
			exp->addTerm(term);
			
			name = "";
		}else{
			if(c != ' ') name += c;
		}
	}
}