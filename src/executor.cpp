#include "../include/bplustree.h"
#include "../include/executor.h"

struct Executor::CommandExecutor {
    CommandExecutor(Executor& executor) : executor_(executor) {}

    // For table creation
    void operator() (const Create_table tb_schema) const {
        executor_.tableSchemas[tb_schema.table_name] = tb_schema;
        std::cout << "Table : " << tb_schema.table_name << " Created Successfully\n";
    }

    // For insert operating in the tree
    void operator() (const Insert_table tb_schema) const {
        std::cout << "Table : " << tb_schema.table_name << " inserted Successfully\n";
    }

private:
    Executor& executor_;
};

void Executor::Run_command() {
    std::visit(CommandExecutor{*this}, command->var);
}
