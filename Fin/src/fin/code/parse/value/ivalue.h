#pragma once
#include <string>

namespace fin::code {

  enum ValueType {
    VALUETYPE_BOOL,
    VALUETYPE_NUMBER,
    VALUETYPE_STRING,
  };

  class IValue {
    public:
    bool get_bool() {
      switch ( type ) {
        case VALUETYPE_BOOL: return boolValue;
        case VALUETYPE_NUMBER: return numberValue != 0;
        case VALUETYPE_STRING: return !stringValue.empty();
        default: throw std::exception( "IValue.get_bool: type is undefined" );
      }
    }

    double get_number() {
      switch ( type ) {
        case VALUETYPE_BOOL: return (boolValue) ? 1 : 0;
        case VALUETYPE_NUMBER: return numberValue;
        case VALUETYPE_STRING: return 0;
        default: throw std::exception("IValue.get_number: type is undefined");
      }
    }

    std::string get_string() {
      switch ( type ) {
        case VALUETYPE_BOOL: return std::to_string( boolValue );
        case VALUETYPE_NUMBER: return std::to_string(numberValue);
        case VALUETYPE_STRING: return stringValue;
        default: return "undefined";
      }
    }

    protected:

    ValueType type;
    bool boolValue;
    double numberValue;
    std::string stringValue;
  };
}
