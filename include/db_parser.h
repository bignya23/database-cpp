#pragma once
#include <iostream>
#include "tokenizer.h"
#include <variant>

struct Ident {
    std::string ident{};
};

struct Column {
    std::string name{};
    std::string type{};
};
struct Insert_Col {
    std::string value{};
};

struct Create_table {
	std::string table_name;
	std::vector<Column> columns;
};
struct Insert_table {
    std::string table_name;
    std::vector<std::string> columns;
};
struct Show_Entries {
    std::string table_name{};
};

struct Drop_Table {
    std::string table_name{};
};

struct Table_fn {
    std::variant<Create_table, Insert_table, Show_Entries, Drop_Table> var;
};

class Parser { 
public:

	explicit Parser(std::vector<Token> tokens) : tokens_(tokens) {} // constructor


	std::optional<Table_fn> parse_tokens();
    std::optional<Ident> ident_get();




private:
	std::vector<Token> tokens_; 
    std::size_t idx{};


    // To get the token at a particular position using offset
    [[nodiscard]] std::optional<Token> peek(int offset = 0) const {
        if (idx + offset < tokens_.size()) {
            return tokens_.at(idx + offset);
        }
        else {
            return {};
        }
    }

    // To get the current token and move to the next token
    Token consume() {
        return tokens_.at(idx++);
    }

};