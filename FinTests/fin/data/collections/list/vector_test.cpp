#include "stdafx.h"
#include "CppUnitTest.h"

#include "fin/data/collections/list/vector.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fin::data {
  TEST_CLASS( VectorTest ) {
  public:

  TEST_METHOD( TestVector_IsEmpty ) {
    Vector<int> list;

    Assert::IsTrue( list.isEmpty() );

    list.pushBack( 0 );

    Assert::IsFalse( list.isEmpty() );
  }

  TEST_METHOD( TestVector_At ) {
    Vector<int> list;

    list.pushBack( 0 );
    list.pushBack( 1 );
    list.pushBack( 2 );

    Assert::AreEqual( 0, list.at( 0 ) );
    Assert::AreEqual( 1, list.at( 1 ) );
    Assert::AreEqual( 2, list.at( 2 ) );
  }

  TEST_METHOD( TestVector_Brackets ) {
    Vector<int> list;

    list.pushBack( 0 );
    list.pushBack( 1 );
    list.pushBack( 2 );

    Assert::AreEqual( 0, list[0] );
    Assert::AreEqual( 1, list[1] );
    Assert::AreEqual( 2, list[2] );
  }

  TEST_METHOD( TestVector_FrontBack ) {
    Vector<int> list;

    list.pushBack( 0 );
    list.pushBack( 1 );
    list.pushBack( 2 );

    Assert::AreEqual( 0, list.front() );
    Assert::AreEqual( 2, list.back() );
  }
  };
}