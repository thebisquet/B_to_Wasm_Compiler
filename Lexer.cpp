//The lexer will read information from the Visual Basic source file and create tokens which get passed to the parser.
#include "compiler.h"

using namespace std;

enum T_Token_Type {
	T_PRINT = -2,
	T_NUMBER = -3
};

struct TOKEN
{
	string type = "";
	TOKEN* expression = nullptr;
	double value = INT64_MIN;
	string strValue = {};
};

static string identifier;
static double numberValue;

//Return next token from standard input.
static TOKEN* getToken(string input) {
	int lastChar = {};
	int i = 0;
	size_t length = input.length();
	TOKEN* currentToken = new TOKEN();

	lastChar = input[i];
	while(input[i] != NULL) {		

		//Skip whitespace.
		if (isspace(lastChar)) {
			i++;
			lastChar = input[i];
		}

		//Check if lastChar is alphanumeric::Adds each alnum character to the global string
		while (isalpha(lastChar)) {
			i++;
			identifier += lastChar;
			lastChar = input[i];
		}

		//Return print token for print keyword
		if (identifier == "PRINT") {
			currentToken->type = "printStatement";
			currentToken->expression = new TOKEN();
			return currentToken;
		}

		//Check if lastChar is [0-9]
		if (isdigit(lastChar) || lastChar == '.') {
			string numberString;

			//Append all digits of the number to our string. There will be at least one.
			do {
				numberString += lastChar;
				i++;
				lastChar = input[i];
			} while (isdigit(lastChar) || lastChar == '.');

			//Convert string to digit, store digit in global variable, and return number token.
			numberValue = strtod(numberString.c_str(), nullptr);
			currentToken->type = "numericLiteral";
			currentToken->value = numberValue;
			return currentToken;
		}

		//otherwise pass generic "identifier" token. Could also be a string to print
		currentToken->type = "stringLiteral";
		currentToken->strValue = identifier;
		return currentToken;
	}
}


