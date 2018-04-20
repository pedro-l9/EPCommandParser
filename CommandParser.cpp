#include "CommandParser.h"

Command::Command (String a) {
	name = a;
	argCount = 0;
}

void Command::addArg(String arg){
	args[argCount] = arg;
	argCount++;
}

void Command::printArgs(){
	Serial.print("Args: ");
	for(int i = 0; i < argCount; i++){
		Serial.print(args[i] + (i < argCount -1 ? "," : ";\n"));
	}
}

static void CommandParser::parseCommand(String text, Command* cmd){
	int state = 0;
	String arg, name = "";

	cmd->argCount = 0;

	for(int i = 0; i < text.length(); i++){
		char c = text.charAt(i);
		switch(state){
			case 0:
				if(c == '('){
					cmd->name = name;
					state++;
				}else{
					name += c;
				}
				break;
			case 1:
				arg = "";
				state++;
			case 2:
				if(c == ',' || c == ')'){
					state = 1;
					cmd->addArg(arg);
				}else{
					arg += c;
				}
				break;
		}
	}
}