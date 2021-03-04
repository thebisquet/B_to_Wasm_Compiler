//The lexer will read information from the Visual Basic source file and create tokens which get passed to the parser.
#include "compiler.h"

using namespace std;

/// <summary>
/// Token_Type defines what each token type is and what its numeric value is.
/// </summary>
enum Token_Type {
	IDENTIFIER,//0
	NUMBER,//1
	STRING,//2
	KEYWORD,//3
};

/// <summary>
/// Structure of a single token.
/// Type refers to the corresponding enum.
/// value refers to the literal value grabbed from the token.
/// </summary>
struct TOKEN
{
	Token_Type type = IDENTIFIER;
	string value = {};
};

//Global Variables used for temporarily holding data.
static string identifier;

/// <summary>
/// getToken takes a string and iterates through each character to determine if it is a keyword or literal value.
/// This version will skip whitespace.
/// </summary>
/// <param name="input">string passed to getToken from main which is a single consecutive word never more than one.</param>
/// <returns>The result of getToken is a TOKEN* defined in lexer.cpp. TYPE: and VALUE:</returns>
static TOKEN* getToken(string input) {
	int lastChar = {};
	int i = 0;
	size_t length = input.length();
	TOKEN* currentToken = new TOKEN();

	//Initialize lastChar and while loop for iteration through the string
	lastChar = input[i];
	identifier.erase();
	while(input[i] != NULL) {		

		//Skip whitespace. Although there shouldn't be any.
		if (isspace(lastChar)) {
			i++;
			lastChar = input[i];
		}

		//Check if lastChar is a letter [a-zA-Z]::Adds each character to the global string named "identifier"
		while (isalpha(lastChar)) {
			i++;
			identifier += lastChar;
			lastChar = input[i];
		}

		//Check if lastChar is [0-9]
		if (isdigit(lastChar) || lastChar == '.') {

			//Append all digits of the number to "identifier" string. There will be at least one.
			do {
				identifier += lastChar;
				i++;
				lastChar = input[i];
			} while (isdigit(lastChar) || lastChar == '.');

			//Returns the number token we were able to create.
			currentToken->type = NUMBER;
			currentToken->value = identifier;
			return currentToken;
		}

		if (identifier == "PRINT") {
			currentToken->type = KEYWORD;
			currentToken->value = identifier;
			return currentToken;
		}
		if (identifier == "IF") {
			currentToken->type = KEYWORD;
			currentToken->value = identifier;
			return currentToken;
		}
		if (identifier == "GOTO") {
			currentToken->type = KEYWORD;
			currentToken->value = identifier;
			return currentToken;
		}

		//otherwise pass generic "identifier" token. Could also be a string to print. CatchAll
		currentToken->type = STRING;
		currentToken->value = identifier;
		return currentToken;
	}
}


