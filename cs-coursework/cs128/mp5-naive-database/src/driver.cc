#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  Database database = Database();
  database.CreateTable("table1");
  database.GetTable("table1").AddColumn(std::pair("Name", DataType::kString));
  database.GetTable("table1").AddColumn(std::pair("GPA", DataType::kDouble));
  database.GetTable("table1").AddColumn(std::pair("UIN", DataType::kInt));
  database.GetTable("table1").AddColumn(std::pair("Year", DataType::kString));
  database.CreateTable("table2");
  database.GetTable("table2").AddColumn(std::pair("Name", DataType::kString));
  database.GetTable("table2") = database.GetTable("table1");
  std::cout << database.GetTable("table2") << std::endl;
}