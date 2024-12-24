
#include "../include/database.h"
#include "../include/tokenizer.h"
#include "../include/db_parser.h"
#include "../include/executor.h"



// Starting line Printing
void Database::startPrint() {
	std::cout << "db > ";
}


// Starting the db_cli_engine
void Database::db_start() {


	while (true)  {
		startPrint();

		std::string line{};
		std::getline(std::cin, line); // Taking line input 
		
		std::cout << line << "\n";

		Tokenizer tokenize(line); // Tokenization
		std::vector<Token> tokens = tokenize.tokens();
		std::cout << "Tokenization Successful\n";
		

		// Parsing
		Parser parse(tokens);
		std::optional<Table_fn> parse_tokens = parse.parse_tokens();
		std::cout << "Parsing Successful\n";


		// Executing
		Executor execute(parse_tokens);
		execute.Run_command();
	
	}
}


