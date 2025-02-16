#include "db_table.hpp"

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    for (unsigned int i = 0; i < rows_.size(); i++) {
      void** row = rows_.at(i);
      void** row_replace = new void*[row_col_capacity_ * 2];
      for (unsigned int j = 0; j < row_col_capacity_; j++) {
        row_replace[j] = row[j];
      }
      delete[] rows_.at(i);
      rows_.at(i) = row_replace;
    }
    row_col_capacity_ *= 2;
  }
  col_descs_.push_back(col_desc);

  for (unsigned int i = 0; i < rows_.size(); i++) {
    if (col_desc.second == DataType::kString) {
      rows_.at(i)[col_descs_.size() - 1] =
          static_cast<void*>(new std::string(""));
    } else if (col_desc.second == DataType::kInt) {
      rows_.at(i)[col_descs_.size() - 1] = static_cast<void*>(new int(0));
    } else if (col_desc.second == DataType::kDouble) {
      rows_.at(i)[col_descs_.size() - 1] = static_cast<void*>(new double(0.0));
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if ((col_idx >= col_descs_.size()) || (col_idx < 0)) {
    throw std::out_of_range("invalid index");
  }
  if ((col_descs_.size() == 1) && (!(rows_.empty()))) {
    throw std::runtime_error("need at least one column leftover");
  }
  for (unsigned int i = 0; i < rows_.size(); i++) {
    if (col_descs_[col_idx].second == DataType::kString) {
      delete static_cast<std::string*>(rows_.at(i)[col_idx]);
    } else if (col_descs_[col_idx].second == DataType::kInt) {
      delete static_cast<int*>(rows_.at(i)[col_idx]);
    } else if (col_descs_[col_idx].second == DataType::kDouble) {
      delete static_cast<double*>(rows_.at(i)[col_idx]);
    }
    for (unsigned int j = col_idx + 1; j < col_descs_.size(); j++) {
      rows_.at(i)[j - 1] = rows_.at(i)[j];
    }
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument("not enough elements");
  }
  rows_[next_unique_id_] = new void*[row_col_capacity_];
  unsigned int i = 0;
  for (const std::string& str : col_data) {
    if (col_descs_[i].second == DataType::kDouble) {
      rows_.at(next_unique_id_)[i] =
          static_cast<void*>(new double(std::stod(str)));
    } else if (col_descs_[i].second == DataType::kInt) {
      rows_.at(next_unique_id_)[i] =
          static_cast<void*>(new int(std::stoi(str)));
    } else if (col_descs_[i].second == DataType::kString) {
      rows_.at(next_unique_id_)[i] = static_cast<void*>(new std::string(str));
    }
    i++;
  }
  next_unique_id_++;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (!(rows_.contains(id))) {
    throw std::invalid_argument("id not found");
  }
  for (unsigned int i = 0; i < col_descs_.size(); i++) {
    void* row_col = rows_.at(id)[i];
    if (col_descs_[i].second == DataType::kString) {
      delete static_cast<std::string*>(row_col);
    } else if (col_descs_[i].second == DataType::kInt) {
      delete static_cast<int*>(row_col);
    } else if (col_descs_[i].second == DataType::kDouble) {
      delete static_cast<double*>(row_col);
    }
  }
  delete[] rows_.at(id);
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs): row_col_capacity_(rhs.row_col_capacity_) {
  for (unsigned int i = 0; i < next_unique_id_; i++) {
    if (rows_.contains(i)) {
      for (unsigned int j = 0; j < col_descs_.size(); j++) {
        void* row_col = rows_.at(i)[j];
        if (col_descs_[j].second == DataType::kString) {
          delete static_cast<std::string*>(row_col);
        } else if (col_descs_[j].second == DataType::kInt) {
          delete static_cast<int*>(row_col);
        } else if (col_descs_[j].second == DataType::kDouble) {
          delete static_cast<double*>(row_col);
        }
      }
      delete[] rows_.at(i);
    }
  }
  rows_.clear();
  col_descs_ = rhs.col_descs_;
  row_col_capacity_ = rhs.row_col_capacity_;
  next_unique_id_ = rhs.next_unique_id_;
  for (unsigned i = 0; i < rhs.next_unique_id_; i++) {
    void** row = new void*[row_col_capacity_];
    void** rhs_row = rhs.rows_.at(i);
    for (unsigned int j = 0; j < col_descs_.size(); j++) {
      if (col_descs_[j].second == DataType::kString) {
        row[j] = (static_cast<void*>(
            new std::string(*(static_cast<std::string*>(rhs_row[j])))));
      } else if (col_descs_[j].second == DataType::kInt) {
        row[j] =
            (static_cast<void*>(new int(*(static_cast<int*>(rhs_row[j])))));
      } else if (col_descs_[j].second == DataType::kDouble) {
        row[j] = (static_cast<void*>(
            new double(*(static_cast<double*>(rhs_row[j])))));
      }
    }
    rows_[i] = row;
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) {
    return *this;
  }
  for (unsigned int i = 0; i < next_unique_id_; i++) {
    if (rows_.contains(i)) {
      for (unsigned int j = 0; j < col_descs_.size(); j++) {
        if (col_descs_[j].second == DataType::kString) {
          delete static_cast<std::string*>(rows_.at(i)[j]);
        } else if (col_descs_[j].second == DataType::kInt) {
          delete static_cast<int*>(rows_.at(i)[j]);
        } else if (col_descs_[j].second == DataType::kDouble) {
          delete static_cast<double*>(rows_.at(i)[j]);
        }
      }
      delete[] rows_.at(i);
    }
  }
  rows_.clear();
  col_descs_ = rhs.col_descs_;
  row_col_capacity_ = rhs.row_col_capacity_;
  next_unique_id_ = rhs.next_unique_id_;
  for (unsigned i = 0; i < rhs.next_unique_id_; i++) {
    void** row = new void*[row_col_capacity_];
    void** rhs_row = rhs.rows_.at(i);
    for (unsigned int j = 0; j < col_descs_.size(); j++) {
      if (col_descs_[j].second == DataType::kString) {
        row[j] = (static_cast<void*>(
            new std::string(*(static_cast<std::string*>(rhs_row[j])))));
      } else if (col_descs_[j].second == DataType::kInt) {
        row[j] =
            (static_cast<void*>(new int(*(static_cast<int*>(rhs_row[j])))));
      } else if (col_descs_[j].second == DataType::kDouble) {
        row[j] = (static_cast<void*>(
            new double(*(static_cast<double*>(rhs_row[j])))));
      }
    }
    rows_[i] = row;
  }
  return *this;
}

DbTable::~DbTable() {
  for (unsigned int i = 0; i < next_unique_id_; i++) {
    if (rows_.contains(i)) DeleteRowById(i);
  }
  rows_.clear();
  col_descs_.clear();
  next_unique_id_ = 0;
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (unsigned int i = 0; i < table.col_descs_.size(); i++) {
    std::string type;
    if (table.col_descs_[i].second == DataType::kString) {
      type = "(std::string)";
    } else if (table.col_descs_[i].second == DataType::kInt) {
      type = "(int)";
    } else if (table.col_descs_[i].second == DataType::kDouble) {
      type = "(double)";
    }
    if (i == table.col_descs_.size() - 1) {
      os << table.col_descs_[i].first << type << '\n';
    } else {
      os << table.col_descs_[i].first << type << ", ";
    }
  }
  std::cout << table.rows_.size() << std::endl;
  for (unsigned int i = 0; i < table.next_unique_id_; i++) {
    if (table.rows_.contains(i)) {
      for (unsigned int j = 0; j < table.col_descs_.size(); j++) {
        if (table.col_descs_[j].second == DataType::kString) {
          os << *(static_cast<std::string*>(table.rows_.at(i)[j]));
        } else if (table.col_descs_[j].second == DataType::kInt) {
          os << *(static_cast<int*>(table.rows_.at(i)[j]));
        } else if (table.col_descs_[j].second == DataType::kDouble) {
          os << *(static_cast<double*>(table.rows_.at(i)[j]));
        }
        if (j == table.col_descs_.size() - 1) {
          os << '\n';
        } else {
          os << ", ";
        }
      }
    }
  }
  return os;
}