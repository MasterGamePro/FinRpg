#include "stdafx.h"
#include "CppUnitTest.h"

#include "fin/math/binary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fin::math {
  TEST_CLASS(BinaryTest) {
    public:

    TEST_METHOD(TestVector_Xor_BothFalse) {
      Assert::IsFalse(xor(true, true));
      Assert::IsFalse(xor(false, false));
    }

    TEST_METHOD(TestVector_Xor_Different) {
      Assert::IsTrue(xor(true, false));
      Assert::IsTrue(xor(false, true));
    }
  };
}
