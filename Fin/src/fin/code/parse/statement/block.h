#pragma once
#include "fin/data/collections/set/hashset.h"
#include "fin/code/parse/value/ivariable.h"
#include "fin/code/parse/value/iconstant.h"
#include "fin/code/parse/statement/istatement.h"
#include "fin/data/collections/list/stlvector.h"

namespace fin::code {
  class Block : public IStatement {
    public:

    IValue getValue( std::string name ) {

    }

    IConstant* allocateConstant( std::string name ) {
      IConstant* constant = new IConstant();


    }

    protected:
    void evaulaate_statements() {
      statements.iterate( [] ( IStatement statement, int i ) {
        statement.evaluate();
      } );
    }

    private:
    Block* parent;
    data::StlVector<IStatement> statements;
    data::HashSet<IVariable> blockConstants;
    data::HashSet<IVariable> blockVariables;
  };
}
