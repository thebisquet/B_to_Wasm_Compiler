//The lexer will read information from the Visual Basic source file and create tokens which get passed to the parser.
#include "compiler.h"

using namespace std;

/// <summary>
/// T_Token_Type defines what each token type is and what its numeric value is.
/// </summary>
enum class T_Token_Type {
	IDENTIFIER = 0,
	NUMBER = 1,
	PRINT = 5,
};

/// <summary>
/// Structure of a single token.
/// Type refers to the corresponding enum.
/// strValue refers to the literal value grabbed from the token.
/// </summary>
struct TOKEN
{
	T_Token_Type type = T_Token_Type::IDENTIFIER;
	string strValue = {};
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

		//Return print token for print keyword
		if (identifier == "PRINT") {
			currentToken->type = T_Token_Type::PRINT;
			currentToken->strValue = "PRINT";
			identifier = {};
			return currentToken;
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
			currentToken->type = T_Token_Type::NUMBER;
			currentToken->strValue = identifier;
			return currentToken;
		}

		//otherwise pass generic "identifier" token. Could also be a string to print. CatchAll
		currentToken->type = T_Token_Type::IDENTIFIER;
		currentToken->strValue = identifier;
		identifier = {};
		return currentToken;
	}
}


