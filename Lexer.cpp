//The lexer will read information from the Visual Basic source file and create tokens which get passed to the parser.
#include "compiler.h"

using namespace std;

enum Tokens {
	//End of File
	t_eof = -1,

	//Commands
	t_print = -2,
	t_define = -3,

	//Primary Tokens
	t_identifier = -4,
	t_number = -5
};

//Global variables to store token return values
//Correspond to relative Token enum's. If [PrimaryToken] Then fill the global variable.
static string identifier;
static double numberValue;

//Return next token from standard input.
static int getToken() {
	static int lastChar = ' ';

	//Skip over whitespace.
	while (isspace(lastChar)) {
		lastChar = getchar();
	}

	//Check if lastChar is [a-zA-Z]
	if (isalpha(lastChar)) {
		identifier = lastChar;

		//Check if lastChar is alphanumeric::Adds each alnum character to the global string
		while (isalnum((lastChar = getchar()))) {
			identifier += lastChar;
		}

		//Comment to the end of line
		if (identifier == "REM") {
			do {
				lastChar = getchar();
			} while (lastChar != EOF && lastChar != '\n' && lastChar != '\r');
			
			//If we haven't reached the end of the file yet, we can safely proceed to get the next token.
			if (lastChar != EOF) {
				return getToken();
			}
		}

		//Return print token for print keyword
		if (identifier == "PRINT") {
			return t_print;
		}
		
		//otherwise pass generic "identifier" token. Could also be a string to print
		return t_identifier;
	}

	//Check if lastChar is [0-9]
	if (isdigit(lastChar) || lastChar == '.') {
		string numberString;

		//Append all digits of the number to our string. There will be at least one.
		do {
			numberString += lastChar;
			lastChar = getchar();
		} while (isdigit(lastChar) || lastChar == '.');

		//Convert string to digit, store digit in global variable, and return number token.
		numberValue = strtod(numberString.c_str(), nullptr);
		return t_number;
	}
	
	//Return end of file token at the end of the file.
	if (lastChar == EOF) {
		return t_eof;
	}

	//Otherwise return the character as its ASCII value
	int thisChar = lastChar;
	lastChar = getchar();
	return thisChar;
}

