// Basic_Wasm_Compiler.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include "compiler.h"
#include "Lexer.cpp"

using namespace std;


/// <summary>
/// Prints a token for use in debugging and error correcting.
/// </summary>
/// <param name="myToken"> Token Type Defined In Lexer </param>
void printTokens(vector<TOKEN*> tokenList) {
    for (int i = 0; i < tokenList.size(); i++) {
        cout << "Token " << i << endl << "\tType: " << tokenList.at(i)->type << endl;
        cout << "\tValue: " << tokenList.at(i)->value << endl;
    }
}

int main(int argc, char* argv[]) {

    string inputString = {};

    // Dynamic Array of Tokens
    vector<TOKEN*> tokenList;

    // File System Setup
    string fileName = "BASIC_SOURCE.txt";
    fstream infp;
    infp.open(fileName);

    cout << "Build Test v1" << endl;

    if (infp.is_open()) {
        while (!infp.eof()) {
            infp >> inputString;
            tokenList.push_back(getToken(inputString));
        }
        infp.close();
    }
    printTokens(tokenList);
}
