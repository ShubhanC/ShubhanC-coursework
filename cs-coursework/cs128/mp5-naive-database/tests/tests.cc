// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu                      //
//  Date ......: 2023/10/02                      Compiler ...: clang++                     //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef CATCH_CONFIG_MAIN
#  undef CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "db.hpp"
#include "db_table.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("Add kString to table with 1 row, 2 col", "") {
  Database database = Database();
  database.CreateTable("table1");
  database.GetTable("table1").AddColumn(std::pair("Name", DataType::kString));
  database.GetTable("table1").AddColumn(std::pair("GPA", DataType::kDouble));
  database.GetTable("table1").AddRow({"Jack", "3.23"});
  database.GetTable("table1").AddColumn(std::pair("Year", DataType::kString));
  std::string jack_year = *(static_cast<std::string*>(
      database.GetTable("table1").GetRows().at(0)[2]));
  std::cout << jack_year << std::endl;
  REQUIRE(jack_year.empty());
}

TEST_CASE("Delete Row by", "") {
  Database database = Database();
  database.CreateTable("table1");
  database.GetTable("table1").AddColumn(std::pair("Name", DataType::kString));
  database.GetTable("table1").AddColumn(std::pair("GPA", DataType::kDouble));
  database.GetTable("table1").AddColumn(std::pair("UIN", DataType::kInt));
  database.GetTable("table1").AddColumn(std::pair("Year", DataType::kString));
  database.GetTable("table1").AddRow({"Jack", "3.23", "834242123", "Freshman"});
  database.GetTable("table1").AddRow(
      {"James", "3.23", "134813433", "Sophomore"});
  database.GetTable("table1").AddRow({"Ella", "3.43", "435839403", "Junior"});
  database.GetTable("table1").AddRow({"Brian", "3.12", "938431933", "Senior"});
  database.GetTable("table1").DeleteRowById(2);
  std::cout << database.GetTable("table1") << std::endl;
  REQUIRE(database.GetTable("table1").GetRows().size() == 3);
}
/////////////////////////////////////////////////////////////////////////////////////////////