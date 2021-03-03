#pragma once
#include "compiler.h"

namespace parser {
	using namespace std;

	enum Token_Type {
		WHITESPACE,
		IDENTIFIER,
		NUMBER,
		DOUBLE,
		STRING,
		OPERATOR,
		POTENTIAL_DOUBLE,
	};

	static const char* sToken_Type[] = {
		"WHITESPACE",
		"IDENTIFIER",
		"NUMBER",
		"DOUBLE",
		"STRING",
		"OPERATOR",
		"POTENTIAL_DOUBLE",
	};

	class Token {
	public: 
		enum Token_Type type {WHITESPACE};
		string value;
		size_t lineNumber{ 0 };

		void DebugPrint();
	};

	class Tokenizer {
	public:
		vector<Token> parse(const string& input);
		void endToken(Token& token, vector<Token>& tokens);
	};
}