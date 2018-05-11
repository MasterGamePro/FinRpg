#pragma once
#include <string>
#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/regex.hpp>
#include "fin/debug/exception.h"
#include <stack>

namespace fin::algorithm {
  struct Position {
    int rowIndex, columnIndex;
    int position;
  };

  class Parser {
    public:
    Parser(std::string str) {
      this->str = str;
      current_position_.rowIndex =
        current_position_.columnIndex = current_position_.position = 0;
      length = str.length();
    }

    /**
     * Assert position.
     */
    void assert_position(int row, int column) const {
      assert( row == current_position_.rowIndex && column == current_position_.
        columnIndex );
    }

    /**
      * Check if all done "eating".
     */
    bool all_done() const { return amount_left() == 0; }

    /**
     * Nibble
     * For the given item, go through tentatively/safely. Will only process if
     * possible. Will not throw exceptions if reached the end.
     */
    bool nibble_whitespace() {
      if (nibble_char(' ') || nibble_char('\t')) { return true; }
      if (nibble_char('\n')) {
        current_position_.rowIndex++;
        current_position_.columnIndex = 0;
        return true;
      }
      return false;
    }

    bool nibble_char(char c) {
      if (all_done()) { return false; }

      if (str[current_position_.position] == c) {
        current_position_.position++;
        current_position_.columnIndex++;
        return true;
      }
      return false;
    }

    bool nibble_string(std::string other) {
      const int otherLen = other.length();
      if (otherLen > amount_left()) { return false; }

      for (int i = 0; i < otherLen; i++) {
        if (str[current_position_.position + i] != other[i]) { return false; }
      }

      current_position_.position += otherLen;
      return true;
    }

    std::string nibble_between() {
      
    }

    std::string nibble_regex(const std::string& regex) {
      const std::string::const_iterator start =
        str.begin() + current_position_.position, end =
        str.end();
      boost::match_results<std::string::const_iterator> matches;
      boost::match_flag_type flags =
        boost::match_default | boost::match_continuous;

      if (boost::regex_search(start,
                              end,
                              matches,
                              boost::regex(regex),
                              flags
                             )) {
        current_position_.position += matches[0].length();
        return matches[0];
      }
      return nullptr;
    }

    /**
     * Munch
     * For the given item, repeatedly process mindlessly until no longer
     * possible. Mainly for clearing out whitespace.
     */
    void munch_whitespace() { while (nibble_whitespace()); }

    /**
     * Chomp
     * For the given item, assert that processing it is possible. If this fails,
     * throws relevant exceptions.
     */
    void chomp_whitespace(char c) {
      if (all_done()) {
        vomit("chomp_whitespace", "Reached the end of the input string.");
      }

      if (!nibble_whitespace()) {
        vomit("chomp_whitespace", "Failed to chomp whitespace.");
      }
    }

    void chomp_char(char c) {
      if (all_done()) {
        vomit("chomp_char", "Reached the end of the input string.");
      }

      if (!nibble_char(c)) {
        std::string error = "Failed to chomp expected character '";
        error += c;
        error += "'.";
        vomit("chomp_char", error);
      }
    }

    void chomp_string(std::string other) {
      const int otherLen = other.length();
      if (otherLen > amount_left()) {
        vomit("chomp_string", "Reached the end of the input string.");
      }

      for (int i = 0; i < otherLen; i++) {
        char c = str[current_position_.position + i];
        if (c != other[i]) {
          std::string error = "Reached unexpected character '";
          error += c;
          error += "'.";
          vomit("chomp_string", error);
        }
      }

      current_position_.position += otherLen;
    }

    std::string chomp_regex(const std::string& regex) {
      const std::string::const_iterator start =
        str.begin() + current_position_.position, end =
        str.end();
      boost::match_results<std::string::const_iterator> matches;
      boost::match_flag_type flags =
        boost::match_default | boost::match_continuous;

      if (boost::regex_search(start,
                              end,
                              matches,
                              boost::regex(regex),
                              flags
                             )) {
        current_position_.position += matches[0].length();
        return matches[0];
      }

      vomit("chomp_regex", "Failed to match \"" + regex + "\".");
      return nullptr;
    }

    /**
    * Pick
    * "Pick at" the string and pull a substring out while going through.
    */
    std::string pick_word() {
      munch_whitespace();

      std::string word = "";

      char c;
      while (true) {
        bool shouldBreak = true;

        if (!all_done()) {
          c = str[current_position_.position];

          if (c != ' ' && c != '\t' && c != '\n') {
            word += c;
            current_position_.position++;
            shouldBreak = false;
          }
        }

        if (shouldBreak) { break; }
      }

      return word;
    }

    /**
     * Vomit
     * Throw (up) an error at the given position.
     */
    template <typename ... Args>
    void vomit(std::string methodName, std::string errorMessageFormatString,
               Args&& ... args) const {
      throw debug::Exception("Parser", methodName,
                             "At (" + std::to_string(rowIndex) + ", " + std::
                             to_string(columnIndex) + "): \n" +
                             errorMessageFormatString,
                             std::forward<Args>(args) ...);
    }

    void push() { position_stack_.push(current_position_); }

    void pop_ignore() {
      position_stack_.pop();
    }

    void pop() {
      current_position_ = position_stack_.top();
      position_stack_.pop();
    }

    private:
    int amount_left() const { return length - current_position_.position; }

    std::string str;
    Position current_position_;
    std::stack<Position> position_stack_;
    int length;
  };
}
