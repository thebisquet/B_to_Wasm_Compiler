//Parser takes tokens and transforms them into an Abstract Syntax Tree for the emitter.
#include "Lexer.cpp"
#include "compiler.h"

using namespace std;

namespace N_ParseTree {
	
	/// C_ExpressionAST - Base class for all expression nodes.
	class C_ExpressionAST {
		public: 
			virtual	~C_ExpressionAST() = default;
	
			virtual value* codeGenerator() = 0;
	};

	/// C_NumberExpressionAST - Expression class for numeric literals like '1.0'
	class C_NumberExpressionAST : public C_ExpressionAST {
		double val;

	public: 
		C_NumberExpressionAST(double val) : val(val) {}

		value* codeGenerator() override;
	};

	/// C_VariableExpressionAST - Expression class for referencing a variable
	class C_VariableExpressionAST : public C_ExpressionAST {
		string name;

	public: 
		C_VariableExpressionAST(const string& name) : name(name) {}

		value* codeGenerator() override;
	};

	/// C_CallExpressionAST - Expression Class for function calls
	class C_CallExpressionAST : public C_ExpressionAST {
		string callee;
		vector<unique_ptr<C_ExpressionAST>> Args;

	public:
		C_CallExpressionAST(const string& callee, vector<unique_ptr<C_ExpressionAST>> Args) : callee(callee), Args(move(Args)) {}

		value* codeGenerator() override;
	};


} // End namespace

using namespace N_ParseTree;

// currentToken - The current token the parser is looking at
static int currentToken;
// getNextToken - Reads the next token from the lexer and updates currentToken with its results
static int getNextToken() {
	return currentToken = getToken();
}

/// LogError - Helper function for error handling
unique_ptr<C_ExpressionAST> LogError(const char* str) {
	fprintf(stderr, "Error: %s\n", str);
	return nullptr;
}

// Parses numeric literal expressions and eats a number token
static unique_ptr<C_ExpressionAST> ParseNumberExpression() {
	auto Result = make_unique<C_NumberExpressionAST>(numberValue);
	// Consume the number token
	getNextToken();
	return move(Result);
}

static unique_ptr<C_ExpressionAST> ParseIdentifierExpression() {
	string name = identifier;

	getNextToken();

	return make_unique<C_VariableExpressionAST>(name);
}

static unique_ptr<C_ExpressionAST> ParsePrimaryToken() {
	switch (currentToken) {
	case t_identifier:
		return ParseIdentifierExpression();
	case t_number: 
		return ParseNumberExpression();
	default:
		return LogError("Unknown token when expecting an expression");
	}
}


}