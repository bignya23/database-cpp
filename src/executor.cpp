#include "../include/bplustree.h"
#include "../include/executor.h"


std::unordered_map<std::string, struct Create_table> Executor::tableSchemas;

std::unordered_map<std::string, std::shared_ptr<BPlusTree<int, std::vector<std::string>>>> Executor::tabledata;

std::unordered_map<std::string, int> Executor::keys;


struct Executor::CommandExecutor {
    CommandExecutor(Executor& executor) : executor_(executor) {}

    // For table creation
    void operator() (const Create_table tb_schema) const {

        // Checking if database name already exist
        if (executor_.tabledata.find(tb_schema.table_name) == executor_.tabledata.end()) {
            // Inserting the table schema
            executor_.tableSchemas[tb_schema.table_name] = tb_schema;
            // Initializing counting the keys map
            executor_.keys[tb_schema.table_name] = 0;
            //Creation of b+ tree
            executor_.tabledata[tb_schema.table_name] = std::make_shared<BPlusTree<int, std::vector<std::string>>>();

            std::cout << "Table: " << tb_schema.table_name << " Created Successfully\n";
        }
        else {
            throw std::runtime_error("Table already exist!!!\n");
        }
        
    }

    // For insert operating in the tree
    void operator() (const Insert_table tb_schema) const {
        // Searching if table exist
        if (executor_.tabledata.find(tb_schema.table_name) != executor_.tabledata.end()) {
            // Calling the insertion function in the bplustree
            executor_.tabledata[tb_schema.table_name]->insert(executor_.keys[tb_schema.table_name]++, tb_schema.columns);
            
            //std::cout << executor_.keys[tb_schema.table_name] << "\n";
            std::cout << "Inserted into Table: " << tb_schema.table_name << " Successfully\n";

        }
        else {
            throw std::runtime_error("Table not found\n");

        }
   
       
    }
    // Show all the entries present in a particular database
    void operator()(const Show_Entries new_entry) {
        if (executor_.tabledata.find(new_entry.table_name) != executor_.tabledata.end()) {
            // Calling the insertion function in the bplustree
            executor_.tabledata[new_entry.table_name]->print();
         
        }
        else {
            throw std::runtime_error("Table not found\n");
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
        throw std::runtime_error("Invalid Instruction!!!\n");

    }
}
