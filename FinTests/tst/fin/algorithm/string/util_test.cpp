#include "stdafx.h"
#include "CppUnitTest.h"
#include "fin/algorithm/string/util.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fin::common::string {
  TEST_CLASS(ParserTest) {
    public:

    TEST_METHOD(TestUtil_Split) {
      const auto parts = split("  123  4   567  ", " ");
      Assert::IsTrue(parts[0] == "123");
      Assert::IsTrue(parts[1] == "4");
      Assert::IsTrue(parts[2] == "567");
    }
  };
}