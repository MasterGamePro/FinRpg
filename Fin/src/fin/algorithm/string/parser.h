#pragma once
#include <string>
#include <boost/regex.hpp>
#include "fin/debug/exception.h"

namespace fin::algorithm {
  class Parser {
    public:
    Parser( std::string str ) {
      this->str = str;
      rowIndex = columnIndex = position = 0;
      length = str.length();
    }

    /**
     * Assert position.
     */
    void assert_position( int row, int column ) const {
      assert( row == rowIndex && column == columnIndex );
    }

    /**
      * Check if all done "eating".
     */
    bool all_done() const {
      return amount_left() == 0;
    }

    /**
     * Nibble
     * For the given item, go through tentatively/safely. Will only process if
     * possible. Will not throw exceptions if reached the end.
     */
    bool nibble_whitespace() {
      if ( nibble_char( ' ' ) || nibble_char( '\t' ) ) {
        return true;
      }
      if ( nibble_char( '\n' ) ) {
        rowIndex++;
        columnIndex = 0;
        return true;
      }
      return false;
    }

    bool nibble_char( char c ) {
      if ( all_done() ) {
        return false;
      }

      if ( str[position] == c ) {
        position++;
        columnIndex++;
        return true;
      }
      return false;
    }

    bool nibble_string( std::string other ) {
      const int otherLen = other.length();
      if ( otherLen > amount_left() ) {
        return false;
      }

      for ( int i = 0; i < otherLen; i++ ) {
        if ( str[position + i] != other[i] ) {
          return false;
        }
      }

      position += otherLen;
      return true;
    }

    bool nibble_regex( const std::string& regex ) {
      std::string::const_iterator start, end;
      start = str.begin() + position;
      end = str.end();
      boost::match_results<std::string::const_iterator> matches;
      boost::match_flag_type flags = boost::match_default | boost::match_continuous;

      if ( boost::regex_search( start,
                                end,
                                matches,
                                boost::regex( regex ),
                                flags
      ) ) {
        position += matches[0].length();
        return true;
      }
      return false;
    }

    /**
     * Munch
     * For the given item, repeatedly process mindlessly until no longer
     * possible. Mainly for clearing out whitespace.
     */
    void munch_whitespace() {
      while ( nibble_whitespace() );
    }

    /**
     * Chomp
     * For the given item, assert that processing it is possible. If this fails,
     * throws relevant exceptions.
     */
    void chomp_whitespace( char c ) {
      if ( all_done() ) {
        vomit( "chomp_whitespace", "Reached the end of the input string." );
      }

      if ( !nibble_whitespace() ) {
        vomit( "chomp_whitespace", "Failed to chomp whitespace." );
      }
    }

    void chomp_char( char c ) {
      if ( all_done() ) {
        vomit( "chomp_char", "Reached the end of the input string." );
      }

      if ( !nibble_char( c ) ) {
        std::string error = "Failed to chomp expected character '";
        error += c;
        error += "'.";
        vomit( "chomp_char", error );
      }
    }

    void chomp_string( std::string other ) {
      const int otherLen = other.length();
      if ( otherLen > amount_left() ) {
        vomit( "chomp_string", "Reached the end of the input string." );
      }

      for ( int i = 0; i < otherLen; i++ ) {
        char c = str[position + i];
        if ( c != other[i] ) {
          std::string error = "Reached unexpected character '";
          error += c;
          error += "'.";
          vomit( "chomp_string", error );
        }
      }

      position += otherLen;
    }

    void chomp_regex( const std::string& regex ) {
      std::string::const_iterator start, end;
      start = str.begin() + position;
      end = str.end();
      boost::match_results<std::string::const_iterator> matches;
      boost::match_flag_type flags = boost::match_default | boost::match_continuous;

      if ( boost::regex_search( start,
                                end,
                                matches,
                                boost::regex( regex ),
                                flags
      ) ) {
        position += matches[0].length();
        return;
      }

      vomit( "chomp_regex", "Failed to match \"" + regex + "\"." );
    }

    /**
    * Pick
    * "Pick at" the string and pull a substring out while going through.
    */
    std::string pick_word() {
      munch_whitespace();

      std::string word = "";

      char c;
      while ( true ) {
        bool shouldBreak = true;

        if ( !all_done() ) {
          c = str[position];

          if ( c != ' ' && c != '\t' && c != '\n' ) {
            word += c;
            position++;
            shouldBreak = false;
          }
        }

        if ( shouldBreak ) {
          break;
        }
      }

      return word;
    }

    /**
     * Vomit
     * Throw (up) an error at the given position.
     */
    template<typename ... Args>
    void vomit( std::string methodName, std::string errorMessageFormatString, Args&& ... args ) const {
      throw debug::Exception( "Parser", methodName, 
                              "At (" + std::to_string(rowIndex)+ ", " + std::to_string(columnIndex) + "): \n" + errorMessageFormatString, std::forward<Args>(args) ... );
    }

    private:
    int amount_left() const {
      return length - position;
    }

    std::string str;
    int rowIndex, columnIndex;
    int position, length;
  };
}
