#include "../include/tokenizer.h"



std::vector<Token> Tokenizer::tokens() {

	std::vector<Token> tokens;
	std::string buffer{};
	//bool is_error = false;

	while (peek().has_value()) {
		if (isalpha(peek().value())){
			while (peek().has_value() && isalpha(peek().value())) {
				buffer.push_back(consume());
			}

			if (buffer == "SELECT") {
				tokens.push_back({ TokenType::SELECT });
			}
			else if (buffer == "CREATE") {
				tokens.push_back({ TokenType::CREATE });
			}
			else if (buffer == "TABLE") {
				tokens.push_back({ TokenType::TABLE });
			}
			else if (buffer == "INT") {
				tokens.push_back({ TokenType::INT ,buffer});
			}
			else if (buffer == "STRING") {
				tokens.push_back({ TokenType::STRING , buffer});
			}
			else if (buffer == "BOOL") {
				tokens.push_back({ TokenType::BOOLEAN ,buffer});
			}
			else {
				tokens.push_back({ TokenType::IDENTIFIER,buffer});
			}
			buffer.clear();
 		}
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
			std::cerr << "Unknown token " << buffer << "\n";
			
			break;
		}
	}

	return tokens;


}
