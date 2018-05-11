#pragma once

#include <regex>

#include "fin/algorithm/string/parser.h"
#include "fin/io/file.h"

enum class ParsingLevel {
  STATEMENT,

  TERM,
  FACTOR,
};

namespace recom::src::java {
  class Parser {
    public:
    Program* parse(const fin::io::File file) {
      Statement* statement;
      do {
        
      } while()
    }

    private:
    const std::string RESERVED_WORDS[] = {
      "abstract", "assert", "boolean", "break", "byte", "case", "catch", "char",
      "class", "const", "continue"
    };
    const std::string kValidIdentifier = "[a-zA-Z$_][a-zA-Z0-9$_]*";
    const std::string kValidNumber = "[0-9]*.[0-9]*";

    Statement* parse_statement_() {
      Term* term;
      do {
        term = parse_term();
      } while (term != nullptr);
    }

    Term* parse_term_() {
      
    }

    Factor* parse_factor_() {
      const auto identifier = parse_identifier_();
      if (identifier != "") {
        // Handle variables, methods, enums
        // return
      }
      // TODO: Fix number regex.
      const auto number = parser_->nibble_regex(kValidNumber);
      if (number) {
        // return                
      }
      const auto str = parser_->nibble_between("\"", "\"");
      if (str != "") {
        
      }
      const auto chr = parser_->nibble_between("\'", "\'");
      if (chr != "") {

      }
      return nullptr;
    }

    std::string parse_identifier_() {
      parser_->push();
      const auto identifier = parser_->nibble_regex(kValidIdentifier);
      if (fin::algorithm::array::contains(RESERVED_WORDS, identifier)) {
        parser_->pop();
        return "";
      }
      parser_->pop_ignore();
      return identifier;
    }


    fin::algorithm::Parser* parser_;
  };
}
