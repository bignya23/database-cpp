#include "../include/bplustree.h"
#include "../include/executor.h"

// Making maps scopes last till the end
std::unordered_map<std::string, struct Create_table> Executor::tableSchemas;

std::unordered_map<std::string, std::shared_ptr<BPlusTree<int, std::vector<std::string>>>> Executor::tabledata;

std::unordered_map<std::string, int> Executor::keys;


// To match the columns of insertion with the table created
bool match_cols(std::vector<std::string> values, std::vector<Column> cols) {
    if (values.size() != cols.size()) {
        return false;
    }

    for (std::size_t i = 0; i < values.size(); i++) {
        if (cols[i].type == "INT") {
            if (std::isdigit(values[i][0])) {
                for (auto& it : values[i]) {
                    if (isdigit(it) == false) {
                        throw std::runtime_error("INT field doesn't match");
                    }
                }
            }
            else {
                throw std::runtime_error("INT field doesn't match");
            }
        }
        else if (cols[i].type == "BOOL") {
            if (values[i] == "false" || values[i] == "FALSE" || values[i] == "true" || values[i] == "TRUE") {

            }
            else {
                throw std::runtime_error("BOOL field doesn't match");
            }
        }
        
    }
    return true;
}


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
            // To match cols
            if(match_cols(tb_schema.columns, executor_.tableSchemas[tb_schema.table_name].columns) == false) {
                throw std::runtime_error("Table Format Does't Match!!!");
            }

            

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
            // Printing the Schema
            std::cout << "Table - ";
            for (auto& it : executor_.tableSchemas[new_entry.table_name].columns) {
                std::cout << it.name << "(" << it.type << ")  ";
            }
            std::cout << std::endl;
            std::cout << std::endl;
            // Calling the insertion function in the bplustree
            executor_.tabledata[new_entry.table_name]->print();
        }
        else {
            throw std::runtime_error("Table not found\n");
        }
    }

    // Delete the table 
    void operator()(const Drop_Table dt) {
        auto it = executor_.tabledata.find(dt.table_name);
        if (it != executor_.tabledata.end()) {
            // Erase the table data
            executor_.tabledata.erase(it);
            // Erase the table schema
            executor_.tableSchemas.erase(dt.table_name);
            std::cout << "Table : " << dt.table_name <<
                "deleted.\n";
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
