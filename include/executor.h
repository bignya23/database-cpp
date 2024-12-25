#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "db_parser.h"
#include "bplustree.h"


class Executor {
public:
	explicit Executor(std::optional<Table_fn> parse_tokens){
		command = parse_tokens;
	} // Constructor

	void Run_command();

private:
    static std::unordered_map<std::string, struct Create_table> tableSchemas;
	/*std::unordered_map<std::string,std::shared_ptr<BPlusTree<int, std::vector<std::string>>>> tabledata;*/

	struct CommandExecutor;


	std::optional<Table_fn> command{};
	
};



