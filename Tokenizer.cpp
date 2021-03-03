#include "compiler.h"
#include "tokenizer.h"

namespace parser {
	using namespace std;

	vector<Token> Tokenizer::parse(const string& input) {
		vector<Token> tokens;
		Token currentToken;

		currentToken.lineNumber = 1;

		for (char currentChar : input) {
			switch (currentChar) {
			case'0':
			case'1':
			case'2':
			case'3':
			case'4':
			case'5':
			case'6':
			case'7':
			case'8':
			case'9':
				if (currentToken.type == WHITESPACE) {
					currentToken.type = NUMBER;
					currentToken.value.append(1, currentChar);
				} else if (currentToken.type == POTENTIAL_DOUBLE) {
					currentToken.type = DOUBLE;
					currentToken.value.append(1, currentChar);
				} else {
					currentToken.value.append(1, currentChar);
				}
				break;
			case'.':
				if (currentToken.type == WHITESPACE) {
					currentToken.type = POTENTIAL_DOUBLE;
					currentToken.value.append(1, currentChar);
				} else if(currentToken.type == NUMBER) {
					currentToken.type = DOUBLE;
					currentToken.value.append(1, currentChar);
				} else if (currentToken.type == STRING) {
					currentToken.value.append(1, currentChar);
				} else {
					endToken(currentToken, tokens);
					currentToken.type = OPERATOR;
					currentToken.value.append(1, currentChar);
					endToken(currentToken, tokens);
				}
				break;
			case'=':
			case'-':
			case'+':
				if (currentToken.type != STRING) {
					endToken(currentToken, tokens);
					currentToken.type = OPERATOR;
					currentToken.value.append(1, currentChar);
					endToken(currentToken, tokens);
				}
				else {
					currentToken.value.append(1, currentChar);
				}
				break;
			case' ':
				break;
			case'\t':
				endToken(currentToken, tokens);
				break;
			case'\r':
			case'\n':
				endToken(currentToken, tokens);
				++currentToken.lineNumber;
				break;
			case'"':
				if (currentToken.type != STRING) {
					endToken(currentToken, tokens);
					currentToken.type = STRING;
					currentToken.value.append(1, currentChar);
				} else if(currentToken.type == STRING) {
					endToken(currentToken, tokens);
				}
				break;
			default:
				if (currentToken.type == WHITESPACE || currentToken.type == NUMBER || currentToken.type == DOUBLE) {
					endToken(currentToken, tokens);
					currentToken.type = IDENTIFIER;
					currentToken.value.append(1, currentChar);
				} else {
					currentToken.value.append(1, currentChar);
				}
				break;
			}
		}

		endToken(currentToken, tokens);

		return tokens;
	}

	void Tokenizer::endToken(Token &token, vector<Token> &tokens) {
		if (token.type != WHITESPACE) {
			tokens.push_back(token);
		}
		token.type = WHITESPACE;
		token.value.erase();
	}

	void Token::DebugPrint() {
		cout << "Token(" << sToken_Type[type] << ", " << "\"" << value << "\", " << lineNumber << ")" << endl;
	}
}