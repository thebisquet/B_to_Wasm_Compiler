// Basic_Wasm_Compiler.cpp : This file contains the 'main' function. Program execution begins and ends here.
#include "compiler.h"
#include "Lexer.cpp"

using namespace std;


/// <summary>
/// Prints a token for use in debugging and error correcting.
/// </summary>
/// <param name="myToken"> Token Type Defined In Lexer </param>
void printToken(TOKEN* myToken) {

    cout << "Type: " << myToken->type << endl;
    cout << "Value: " << myToken->value << endl;
    cout << endl;
}

int main(int argc, char* argv[]) {

    string inputString = {}, fileName = "BASIC_SOURCE.txt";
    TOKEN* myToken = new TOKEN();
    fstream infp;

    infp.open(fileName);

    cout << "Test..." << endl << endl;

    if (infp.is_open()) {
        while (!infp.eof()) {
            infp >> inputString;
            myToken = getToken(inputString);
            printToken(myToken);
        }
        infp.close();
    }
}
