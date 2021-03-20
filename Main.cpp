// Basic_Wasm_Compiler.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include "compiler.h"

#pragma region Lexer
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
	while (input[i] != NULL) {

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

		//Check for any KEYWORDS
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
#pragma endregion

#pragma region Parser

/// <summary>
/// A node for a numeric literal argument attached to a statement.
/// </summary>
struct argument {
	string type = {};
	double value = INT64_MIN;
};

/// <summary>
/// Individual component of a program. Has a type and arguments related to its type.
/// </summary>
struct statement {
	string type = {};
	argument* args = new argument();
};

/// <summary>
/// Takes in a token and parses the meaning behind the text.
/// </summary>
/// <param name="currentToken">Token that the statement will be requiring.</param>
/// <returns>Returns a pointer to an argument node.</returns>
static argument* findArgument(TOKEN* currentToken) {

	argument* thisArgument = new argument();

	if (currentToken->type == NUMBER) {
		thisArgument->type = "numericLiteral";
		thisArgument->value = stoi(currentToken->value);
	}

	return thisArgument;
}

/// <summary>
/// Takes in a dynamic array of tokens and begins parsing the relations between tokens.
/// </summary>
/// <param name="tokenLists">Dynamic Array of Tokens created by the Lexer.</param>
/// <returns>Returns a dynamic array of parsed statements which will be our whole program.</returns>
static vector<statement*> parseTokens(vector<TOKEN*> tokenLists) {

	double i = 0;
	vector<statement*> bigList;
	statement* program = nullptr;

	while (i < tokenLists.size()) {
		if (tokenLists.at(i)->type == KEYWORD) {
			if (tokenLists.at(i)->value == "PRINT") {
				if (tokenLists.at(i) != NULL) {
					program = new statement();
					program->type = "printStatement";
					program->args = findArgument(tokenLists.at(i+1));
					bigList.push_back(program);
				}
			}
		}
		i++;
	}
	return bigList;
}
#pragma endregion

#pragma region Emitter



void wasmGenerator(vector<statement*> parsedProgram) {

	ofstream ofp;
	ofp.open("wasmExample.wasm");

	//WebAssembly Module Header
	vector<uint8_t> byteBuffer = {
				0x00, 0x61, 0x73, 0x6d,  0x01, 0x00, 0x00, 0x00,
				0x01, 0x85, 0x80, 0x80,  0x80, 0x00, 0x01, 0x60,
				0x00, 0x01, 0x7f, 0x03,  0x82, 0x80, 0x80, 0x80,
				0x00, 0x01, 0x00, 0x04,  0x84, 0x80, 0x80, 0x80,
				0x00, 0x01, 0x70, 0x00,  0x00, 0x05, 0x83, 0x80,
				0x80, 0x80, 0x00, 0x01,  0x00, 0x01, 0x06, 0x81,
				0x80, 0x80, 0x80, 0x00,  0x00, 0x07, 0x96, 0x80,
				0x80, 0x80, 0x00, 0x02,  0x06, 0x6d, 0x65, 0x6d,
				0x6f, 0x72, 0x79, 0x02,  0x00, 0x09, 0x5f, 0x5a,
				0x35, 0x50, 0x52, 0x49,  0x4e, 0x54, 0x76, 0x00,
				0x00, 0x0a, 0x8a, 0x80,  0x80, 0x80, 0x00, 0x01,
				0x84, 0x80, 0x80, 0x80,  0x00, 0x00, 0x41, 0x2a,
				0x0b };

	for (statement* current : parsedProgram) {
		if (current->type == "printStatement") {

		}
	}

	//Write WASM Binary to output file.
	for (int i = 0; i < byteBuffer.size(); i++) {
		ofp << byteBuffer.at(i);
	}

	ofp.close();
}


#pragma endregion

#pragma region Main

#pragma region Print Functions
/// <summary>
/// Prints a dynamic array of tokens for use in debugging and error correction.
/// </summary>
/// <param name="tokenList"> Vector list of Tokens -=- Token Type Defined In Lexer </param>
void printTokens(vector<TOKEN*> tokenList) {
    for (int i = 0; i < tokenList.size(); i++) {
		cout << "Token{" << i << "} : " << "[Type: " << tokenList.at(i)->type << ", Value: " << tokenList.at(i)->value << "]" << endl;
    }
}

/// <summary>
/// Prints a dynamic array of statements which comprise our entire program.
/// </summary>
/// <param name="start">A very crude, basic syntax tree.</param>
void printProgram(vector<statement*> start) {
	for (int i = 0; i < start.size() ; i++) {
		if (start.at(i)->type == "printStatement" ) {
			cout << "Type: " << start.at(i)->type << endl;
			cout << "\tArguments: " << start.at(i)->args->type << endl;
			cout << "\tValue: " << start.at(i)->args->value << endl << endl;
		}
	}
}

/// <summary>
/// Displays buffer of wasm binary file.
/// </summary>
/// <param name="byteBuffer">Integer array of the buffer.</param>
void printBuffer() {
	int i = 0;
	string filename = "wasmExample.wasm";
	fstream infp;
	infp.open(filename);

	if (infp.is_open()) {
		uint8_t myByte;
		cout << "-----------WASM BUFFER-----------" << endl << endl;
		while (!infp.eof()) {
			infp >> myByte;
			cout << showbase << setw(5) << hex << (int) myByte ;
			i++;
			if (i % 8 == 0) {
				cout << endl;
			}
		}
		infp.close();
	}
	cout << endl;
}

#pragma endregion

int main(int argc, char* argv[]) {

    // Dynamic Arrays for printing and debugging
    vector<TOKEN*> tokenList;
	vector<statement*> start;

    // File System Setup
    string fileName = "BASIC_SOURCE.txt";
    fstream infp;
    infp.open(fileName);

//++++++++++++++++++++++++ WORKHORSE +++++++++++++++++++++//

    if (infp.is_open()) {
        string inputString = {};
		cout << "-----------BASIC FILE-----------" << endl << endl;
        while (!infp.eof()) {
            infp >> inputString;
			cout << inputString << endl;
            tokenList.push_back(getToken(inputString));
        }
        infp.close();
    }


	cout << endl << "----------LIST OF TOKENS----------" << endl << endl;
    printTokens(tokenList);
	start = parseTokens(tokenList);
	cout << endl << "------------PARSE TREE------------" << endl << endl;
	printProgram(start);
	wasmGenerator(start);
	printBuffer();

//++++++++++++++++++++++++ WORKHORSE +++++++++++++++++++++//
}
#pragma endregion