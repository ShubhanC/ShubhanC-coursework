#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
  tables_[table_name] = static_cast<DbTable*>(new DbTable());
}

void Database::DropTable(const std::string& table_name) {
  if (!(tables_.contains(table_name))) {
    throw std::invalid_argument("table name not found");
  }
  delete tables_.find(table_name)->second;
  tables_.erase(tables_.find(table_name));
}

DbTable& Database::GetTable(const std::string& table_name) {
  return *(tables_[table_name]);
}

Database::Database(const Database& rhs) {
  for (const auto& [table_name, table] : tables_) {
    delete table;
  }
  tables_.clear();
  for (const auto& [table_name, table] : rhs.tables_) {
    tables_[table_name] = new DbTable(*table);
  }
}

Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (const auto& [table_name, table] : tables_) {
    delete table;
  }
  tables_.clear();
  for (const auto& [table_name, table] : rhs.tables_) {
    tables_[table_name] = new DbTable(*table);
  }
  return *this;
}

Database::~Database() {
  for (const auto& [table_name, table] : tables_) {
    delete table;
  }
  tables_.clear();
}