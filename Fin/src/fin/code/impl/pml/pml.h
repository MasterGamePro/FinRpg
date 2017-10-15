#pragma once
#include "fin/code/parse/statement/istatement.h"
#include "fin/algorithm/string/parser.h"
#include "fin/code/parse/expression.h"
#include "fin/code/parse/statement/block.h"
#include "fin/code/parse/statement/ifchainstatement.h"

namespace fin::code {
  class Pml {
    public:

    /*execute_string( std::string str ) {


    }

    execute_file( std::string filename ) {

    }

    private:
    IParameters* parseParameters() {

    }

    Block* nibble_block() {
      parser->munch_whitespace();
      if ( parser->nibble_char( '{' ) ) {
        Block* output = new Block();

        while ( true ) {
          IStatement* statement = nibble_statement();

          if ( statement != nullptr ) {
            output->add_statement( statement );
          } else {
            break;
          }
        }

        parser->munch_whitespace();
        parser->chomp_char( '}' );

        return output;
      }

      return nullptr;
    }

    IStatement* nibble_statement() {
      IStatement* output;

      if ( ( output = nibble_block() ) != nullptr ) {
        return output;
      }

      if ( ( output = nibble_ifchainstatement() ) != nullptr ) {
        return output;
      }

      if ( ( output = nibble_switchstatement() ) != nullptr ) {
        return output;
      }

      if ( ( output = nibble_forloopstatement() ) != nullptr ) {
        return output;
      }

      if ( ( output = nibble_whileloopstatement() ) != nullptr ) {
        return output;
      }

      if ( ( output = nibble_dowhileloopstatement() ) != nullptr ) {
        return output;
      }

      Expression* expression = nibble_expression();
      if ( expression == nullptr ) {
        throw std::exception( "Pml.nibble_statement" );
      }

      parser->munch_whitespace();
      parser->chomp_char( ';' );
      return output;
    }

    IfChainStatement* nibble_ifchainstatement() {
      parser->munch_whitespace();
      if ( parser->nibble_regex( "if\\s*\\(" ) ) {
        Expression* expression = nibble_expression();
        if ( expression == nullptr ) {
          throw std::exception( "Pml.nibble_statement: Failed to parse test expression. " );
        }

        parser->munch_whitespace();
        parser->chomp_char( ')' );

        Block block* = nibble_block();
        if ( block == nullptr ) {
          throw std::exception( "Pml.nibble_statement: Failed to parse test expression. " );
        }

        IfChainStatement* ifChainStatement = new IfChainStatement();
        ifChainStatement->add_block( expression, block );
      }

      return nullptr;
    }

    ForLoopStatement* nibble_forloopstatement() {

    }

    WhileLoopStatement* nibble_whileloopstatement() {

    }

    DoWhileStatement* nibble_dowhileloopstatement() {

    }

    Expression* nibble_expression() {
      parser->munch_whitespace();
    }

    Term* parseTerm() {

    }

    Factor* parseFactor() {

    }

    algorithm::Parser* parser;*/
  };
}
