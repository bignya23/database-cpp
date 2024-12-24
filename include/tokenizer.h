#pragma once

#include <iostream>
#include <string>
#include <vector> 
#include <optional>

enum class TokenType {
    // Keywords
    SELECT, FROM, WHERE, AND, OR, NOT, INSERT, INTO, VALUES, UPDATE, DELETE, CREATE, TABLE,
    // Data Types
    INT, STRING, BOOLEAN, DATE,
    // Operators
    EQUAL, GREATER_THAN, LESS_THAN, PLUS, MINUS, MULTIPLY, DIVIDE, MOD,
    // Punctuation
    COMMA, SEMICOLON, OPEN_PAREN, CLOSE_PAREN,
    // Literals
    STRING_LITERAL, INT_LITERAL, IDENTIFIER,
    // End of input
    END_OF_INPUT
};

struct Token {
    TokenType token;
    std::optional<std::string> val{};
};

class Tokenizer {

public:
    explicit Tokenizer(const std::string syntax) : syntax_(syntax) {
    }

    std::vector<Token> tokens();

private:
    std::string syntax_{};
    int index_{};
    
    // To get the character at a particular position using offset
    [[nodiscard]] std::optional<char> peek(int offset = 0) const {
        if (index_ + offset < syntax_.length()) {
            return syntax_.at(index_ + offset);
        }
        else {
            return {};
        }
    }

    // To get the current character and move to the next character
    char consume() {
        return syntax_.at(index_++);
    }

};