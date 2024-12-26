
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

	std::cout << "Welcome to DB_Engine - The Scalable and Fast Relational Database Engine!\n";
	std::cout <<
		"Type 'HELP' for available commands or 'EXIT' to terminate the session.\n";
	std::cout << std::endl;

	while (true)  {
		startPrint();

		std::string line{};
		std::getline(std::cin, line); // Taking line input 

		// For stopping db_engine
		if (line == "EXIT") {
			break;
		}
		// For help
		if (line == "HELP") {
			std::cout << "Not Implemented now!!!" << std::endl;
		}
		
		//std::cout << line << "\n";
		

		// Tokenization
		Tokenizer tokenize(line);
		std::vector<Token> tokens;
		try {
			tokens = tokenize.tokens();
		}
		catch (std::exception& e) {
			std::cout << "ERROR : " << e.what() << std::endl;
			continue;
		}

		
		//std::cout << "Tokenization Successful\n";
		

		// Parsing
		Parser parse(tokens);
		std::optional<Table_fn> parse_tokens;
		try {
			parse_tokens = parse.parse_tokens();
		}
		catch (std::exception& e) {
			std::cout << "ERROR : " << e.what() << std::endl;
			continue;
		}
		//std::cout << "Parsing Successful\n";


		// Executing
		Executor execute(parse_tokens);
		try {
			execute.Run_command();
		}
		catch (std::exception& e) {
			std::cout << "ERROR : " << e.what() << std::endl;
			continue;
		}
	
	}
}


