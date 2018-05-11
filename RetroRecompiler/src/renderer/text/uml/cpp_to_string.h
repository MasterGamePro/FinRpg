#pragma once

#include <string>

std::string to_string(Block* block) {
  std::string str = "";
  return str;
}

std::string to_string(Statement* statement) {
  std::string str = "";

  return str;
}

std::string to_string(Class* cls) {
  std::string str = "";
  str += "class " + cls->get_name();
  str += "{";
  str += "};";
  return str;
}