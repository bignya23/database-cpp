#include "../include/bplustree.h"
#include "../include/executor.h"


std::unordered_map<std::string, struct Create_table> Executor::tableSchemas;


struct Executor::CommandExecutor {
    CommandExecutor(Executor& executor) : executor_(executor) {}

    // For table creation
    void operator() (const Create_table tb_schema) const {

        // Inserting the table schema
        executor_.tableSchemas[tb_schema.table_name] = tb_schema;

        // Creation of b+ tree
      /*  executor_.tabledata[tb_schema.table_name] = std::make_shared<BPlusTree<int, std::vector<std::string>>>();*/

        std::cout << "Table: " << tb_schema.table_name << " Created Successfully\n";
    }

    // For insert operating in the tree
    void operator() (const Insert_table tb_schema) const {
        // Searching if table exist
        bool found = false;
        for (auto& table_name : executor_.tableSchemas) {
            if (table_name.first == tb_schema.table_name) {
                std::cout << "Inserted into Table: " << tb_schema.table_name << " Successfully\n";
                found = true;
            }
        }

        if (!found)
        {
            std::cerr << "Table not found\n";
        }
       
    }

private:
    Executor& executor_;
};

void Executor::Run_command() {
    if (command.has_value()) {
        std::visit(CommandExecutor{*this}, command->var);
    }
    else {
        std::cerr << "Invalid Instruction!!!";
        exit(EXIT_FAILURE);
    }
}
