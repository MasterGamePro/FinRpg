#pragma once

namespace recom::uml {
  class Statement {
    private:
    Variable* lhs_;
    Expression* rhs_;
  };
}
