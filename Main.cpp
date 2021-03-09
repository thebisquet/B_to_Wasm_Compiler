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


struct expressionNode {
	string type = {};
	double value = -1;
};

struct statementNode {
	string type = {};
	expressionNode* express = nullptr;
};

struct rootNode {
	vector<statementNode*> myRoot;
};

static expressionNode* parseExpression(TOKEN* currentTokens) {
	expressionNode* myNode = new expressionNode;

	if (currentTokens->type == NUMBER) {
		myNode->type = "numericLiteral";
		myNode->value = stoi(currentTokens->value);
		return myNode;
	}
}

static rootNode* parseTokens(vector<TOKEN*> tokenLists) {

	int i = 0;
	rootNode* theRoot = new rootNode();
	statementNode* newNode = new statementNode();
	TOKEN* currentToken = tokenLists.at(i);

	while (i < tokenLists.size()) {
		if (currentToken->type == KEYWORD) {
			if (currentToken->value == "PRINT") {
				newNode->type = "printStatement";
				newNode->express = new expressionNode();
				i++;
				currentToken = tokenLists.at(i);
				if (currentToken->type == NUMBER) {
					newNode->express->type = "numericLiteral";
					newNode->express->value = stoi(currentToken->value);
					theRoot->myRoot.push_back(newNode);
				}
			}
		}
		i++;
		currentToken = tokenLists.at(i);
	}
	
	return theRoot;
}
#pragma endregion

#pragma region Main
/// <summary>
/// Prints a dynamic array of tokens for use in debugging and error correction.
/// </summary>
/// <param name="tokenList"> Vector list of Tokens -=- Token Type Defined In Lexer </param>
void printTokens(vector<TOKEN*> tokenList) {
    for (int i = 0; i < tokenList.size(); i++) {
        cout << "Token " << i << endl << "\tType: " << tokenList.at(i)->type << endl;
        cout << "\tValue: " << tokenList.at(i)->value << endl;
    }
}

void printTree(statementNode* myNode) {
	cout << "[" << endl << "\t{" << "\tType: " << myNode->type << endl << "\t\tExpression: {" << endl;
	cout << "\t\t\tType: " << myNode->express->type << endl << "\t\t\tValue: " << myNode->express->value << endl;
	cout << "\t\t}" << endl << "\t}" << endl << "]" << endl;
}

int main(int argc, char* argv[]) {

    // Dynamic Array of Tokens
	vector<TOKEN*> correctList;
    vector<TOKEN*> tokenList;
	TOKEN* temp;
	rootNode theProgram;

    // File System Setup
    string fileName = "BASIC_SOURCE.txt";
    fstream infp;
    infp.open(fileName);

    cout << "Build Test v1" << endl;

//++++++++++++++++++++++++ WORKHORSE +++++++++++++++++++++//

    if (infp.is_open()) {
        string inputString = {};
        while (!infp.eof()) {
            infp >> inputString;
            tokenList.push_back(getToken(inputString));
        }
        infp.close();
    }

    printTokens(tokenList);


//++++++++++++++++++++++++ WORKHORSE +++++++++++++++++++++//
}
#pragma endregion