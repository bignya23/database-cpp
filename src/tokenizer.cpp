#include "../include/tokenizer.h"

// For character checking in identifiers
bool allowed_chars(char ch){
	if (isalnum(ch)) {
		return true;
	}
	else if (ch == '-' || ch == '_' || ch == '@' || ch == '.') {
		return true;
	}
	
	return false;
}


std::vector<Token> Tokenizer::tokens() {

	std::vector<Token> tokens;
	std::string buffer{};
	//bool is_error = false;

	while (peek().has_value()) {
		if (isalnum(peek().value())){
			while (peek().has_value() && allowed_chars(peek().value())) {
				buffer.push_back(consume());
			}

			if (buffer == "SELECT" || buffer == "select") {
				tokens.push_back({ TokenType::SELECT });
			}
			else if (buffer == "CREATE" || buffer == "create") {
				tokens.push_back({ TokenType::CREATE });
			}
			else if (buffer == "TABLE" || buffer == "table") {
				tokens.push_back({ TokenType::TABLE });
			}
			else if (buffer == "INSERT" || buffer == "insert") {
				tokens.push_back({ TokenType::INSERT });
			}
			else if (buffer == "INTO" || buffer == "into") {
				tokens.push_back({ TokenType::INTO});
			}
			else if (buffer == "SHOW" || buffer == "show") {
				tokens.push_back({ TokenType::SHOW });
			}
			else if (buffer == "ENTRIES" || buffer == "entries") {
				tokens.push_back({ TokenType::ENTRIES });
			}
			else if (buffer == "FROM" || buffer == "from") {
				tokens.push_back({ TokenType::FROM });
			}
			else if (buffer == "DROP" || buffer == "drop") {
				tokens.push_back({ TokenType::DROP});
			}
			// Data types 
			else if (buffer == "INT" || buffer == "int") {
				tokens.push_back({ TokenType::INT , buffer });
			}
			else if (buffer == "STRING" || buffer == "string") {
				tokens.push_back({ TokenType::STRING , buffer });
			}
			else if (buffer == "BOOL" || buffer == "bool") {
				tokens.push_back({ TokenType::BOOLEAN ,buffer });
			}
			else {
				tokens.push_back({ TokenType::IDENTIFIER,buffer});
			}
			buffer.clear();
 		}
		/*else if (std::isdigit(peek().value())) {
			while (peek().has_value() && std::isdigit(peek().value())) {
				buffer.push_back(consume());
			}
			tokens.push_back({ TokenType::INT_LITERAL, buffer});
			buffer.clear();
		}*/
		else if (peek().value() == '(') {
			tokens.push_back({ TokenType::OPEN_PAREN });
			consume();
		}
		else if (peek().value() == ')') {
			tokens.push_back({TokenType::CLOSE_PAREN});
			consume();
		}
		else if (peek().value() == ',') {
			tokens.push_back({ TokenType::COMMA });
			consume();
		}
		else if (peek().value() == ' ') {
			consume();
		}
		else {
			throw std::runtime_error("Unknown Token!!!\n");
		}
	}

	return tokens;


}
