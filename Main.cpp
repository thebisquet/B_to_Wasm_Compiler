// Basic_Wasm_Compiler.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include "compiler.h"
#include "Lexer.cpp"

using namespace std;

void printToken(TOKEN* myToken) {
    bool hasNode = false;

    if (myToken->expression != nullptr)
        hasNode = true;
    else
        hasNode = false;

    cout << "Type: " << myToken->type << endl;

    if (hasNode)
        cout << "Expression: " << hasNode << endl;
    if (myToken->strValue.length() != 0)
        cout << "String: " << myToken->strValue << endl;
    if (myToken->value != INT64_MIN)
        cout << "Value: " << myToken->value << endl;
}

int main(int argc, char* argv[]) {

    string inputString = {}, fileName = "BASIC_SOURCE.txt";
    TOKEN* myToken;
    fstream infp;

    infp.open(fileName);

    cout << "Opening File In Main...5"<< endl;

    if (infp.is_open()) {
        while (!infp.eof()) {
            infp >> inputString;
            cout << inputString << endl;
            myToken = getToken(inputString);
            printToken(myToken);
        }
        infp.close();
    }
}
