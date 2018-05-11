#pragma once

#include <memory>

#include "stages/uml/memory/scope.h"

#include "istatement.h"

namespace recom::uml {
  class Block {
    public:
    explicit
    Block(std::unique_ptr<Scope> scope,
          std::unique_ptr<std::vector<IStatement*>> statements) :
      scope_(std::move(scope)),
      statements_(std::move(statements)) {}

    const std::unique_ptr<std::vector<IStatement*>> getStatements() const {
      return statements_;
    }

    private:
    std::unique_ptr<Scope> scope_;
    std::unique_ptr<std::vector<IStatement*>> statements_;
  };

}
