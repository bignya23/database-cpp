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
	// For creation of the table
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
			throw std::runtime_error("Identifier doesn't exist\n");
		}
		if (peek().has_value() && peek().value().token != TokenType::OPEN_PAREN) { // (
			throw std::runtime_error("Open_Paren doesn't exist!!!\n");

		}
		consume();

	
		while (peek().has_value() ) {

			Column new_col;

			new_col.name = peek().value().val.value();
			consume();
			// Checking for Type literals
			if (peek().has_value() && (peek().value().token == TokenType::INT || peek().value().token == TokenType::STRING || peek().value().token == TokenType::BOOLEAN)) {
				new_col.type = peek().value().val.value();
				consume();
			}
			else {
				throw std::runtime_error("Type Literal Not found");
			}

			// Insertion
			tb_schema.columns.push_back(new_col);
		

			if (peek().has_value() && peek().value().token == TokenType::COMMA || peek().has_value() && peek().value().token == TokenType::CLOSE_PAREN) {
				consume();
			}
		}
		return Table_fn{.var = tb_schema};

	}
	// For insertion into table
	else if (peek().has_value() && peek().value().token == TokenType::INSERT && peek(1).has_value() && peek(1).value().token == TokenType::INTO) {
		Insert_table tb_schema;
		consume();
		consume(); // INSERT INTO


		if (peek().has_value() && peek().value().token == TokenType::IDENTIFIER) { // TABLE NAME
			if (auto identifier = ident_get()) {
				tb_schema.table_name = identifier.value().ident;
			}

		}
		else {
			throw std::runtime_error("Identifier Not Found");	
		}
		if (peek().has_value() && peek().value().token != TokenType::OPEN_PAREN) { // (
			throw std::runtime_error("Open_Paren doesn't exist!!!");
		}
		consume();


		while (peek().has_value()) {

			std::string curr_val = peek().value().val.value();
			consume();

			tb_schema.columns.push_back(curr_val);


			if (peek().has_value() && peek().value().token == TokenType::COMMA || peek().has_value() && peek().value().token == TokenType::CLOSE_PAREN) {
				consume();
			}
		}
		return Table_fn{ .var = tb_schema };
	}
	// For getting all the entries
	else if (peek().has_value() && peek().value().token == TokenType::SHOW && peek(1).has_value() && peek(1).value().token == TokenType::ENTRIES && peek(2).has_value() && peek(2).value().token == TokenType::FROM) {
		consume();
		consume();
		consume(); // Show entries from

		Show_Entries new_entries;
		
		if (peek().has_value() && peek().value().token == TokenType::IDENTIFIER) { // TABLE NAME
			if (auto identifier = ident_get()) {
				new_entries.table_name = identifier.value().ident;
			}
		}
		else {
			throw std::runtime_error("Table name Not Found \n");
		}
		return Table_fn{ .var = new_entries };
	}
	// Delete the table
	else if (peek().has_value() && peek().value().token == TokenType::DROP && peek(1).has_value() && peek(1).value().token == TokenType::TABLE) {
		consume();
		consume(); //drop table
		

		Drop_Table dt;

		if (peek().has_value() && peek().value().token == TokenType::IDENTIFIER) { // TABLE NAME
			if (auto identifier = ident_get()) {
				dt.table_name = identifier.value().ident;
			}
		}
		else {
			throw std::runtime_error("Table name Not Found \n");
		}
		return Table_fn{ .var = dt };

	}

	// For errors
	else {
		throw std::runtime_error("Syntax Error");
	}
}