#include "stdafx.h"
#include "CppUnitTest.h"

#include "fin/data/collections/list/stlvector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fin::data {
  TEST_CLASS( VectorTest ) {
    public:

    TEST_METHOD( TestVector_IsEmpty ) {
      StlVector<int> list;

      Assert::IsTrue(list.is_empty());

      list.push_back(0);

      Assert::IsFalse(list.is_empty());
    }

    TEST_METHOD( TestVector_At ) {
      StlVector<int> list;

      list.push_back(0);
      list.push_back(1);
      list.push_back(2);

      Assert::AreEqual(0, list.at(0));
      Assert::AreEqual(1, list.at(1));
      Assert::AreEqual(2, list.at(2));
    }

    TEST_METHOD( TestVector_Brackets ) {
      StlVector<int> list;

      list.push_back(0);
      list.push_back(1);
      list.push_back(2);

      Assert::AreEqual(0, list[0]);
      Assert::AreEqual(1, list[1]);
      Assert::AreEqual(2, list[2]);
    }

    TEST_METHOD( TestVector_FrontBack ) {
      StlVector<int> list;

      list.push_back(0);
      list.push_back(1);
      list.push_back(2);

      Assert::AreEqual(0, list.front());
      Assert::AreEqual(2, list.back());
    }
  };
}
