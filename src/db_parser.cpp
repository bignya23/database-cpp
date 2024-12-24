#include "../include/db_parser.h"

// To get the identifier
std::optional<Ident> Parser::ident_get() {

	Ident id;

	if (peek().value().val.has_value()) {
		id.ident = consume().val.value();
	}

	return id;
}


// Main parsing 
std::optional<Table_fn> Parser::parse_tokens() {

	if (peek().has_value() && peek().value().token == TokenType::CREATE && peek(1).has_value() && peek(1).value().token == TokenType::TABLE ) {
		Create_table  tb_schema;
		consume();
		consume(); // CREATE TABLE


		

		if (peek().has_value() && peek().value().token == TokenType::IDENTIFIER) { // TABLE NAME
			if (auto identifier = ident_get()) {
				tb_schema.table_name = identifier.value().ident;
			}
			
		}
		else {
			std::cerr << "Identifier Not Found \n";
			exit(EXIT_FAILURE);
		}
		if (peek().has_value() && peek().value().token != TokenType::OPEN_PAREN) { // (
			throw std::runtime_error("Open_Paren doesn't exist!!!");
		}
		consume();

	
		while (peek().has_value() ) {

			Column new_col;

			new_col.name = peek().value().val.value();
			consume();
			new_col.type = peek().value().val.value();
			consume();
			tb_schema.columns.push_back(new_col);
		

			if (peek().has_value() && peek().value().token == TokenType::COMMA || peek().has_value() && peek().value().token == TokenType::CLOSE_PAREN) {
				consume();
			}
		}
		return Table_fn{.var = tb_schema};

	}
	else {
		throw std::runtime_error("Syntax Error!!!");
	}

	
}