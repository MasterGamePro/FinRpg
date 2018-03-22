#pragma once

namespace fin::math {
  class Binary {
    public:
    static bool xor(bool a, bool b) { return (!a && b) || (a && !b); }

    private:
    Binary() {}
  };
}
