#pragma once

#include <string>

#include <fin/data/collections/list/stlvector.h>

class Class {
  public:
  std::string get_name() const { return name_; }

  private:
  Class* super_class_;
  std::string name_;
  fin::data::StlVector<Method*> methods_;
  fin::data::StlVector<IVariable*> variables_;
};
