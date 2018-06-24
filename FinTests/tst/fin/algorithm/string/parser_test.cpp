#include "stdafx.h"
#include "CppUnitTest.h"
#include "fin/algorithm/string/parser.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace fin::algorithm {
  TEST_CLASS( ParserTest ) {
    public:

    TEST_METHOD( TestParser_NibbleChar ) {
      Parser parser("cat");

      Assert::IsFalse(parser.all_done());

      parser.assert_position(0, 0);
      Assert::IsFalse(parser.nibble_char('a'));
      parser.assert_position(0, 0);
      Assert::IsTrue(parser.nibble_char('c'));
      parser.assert_position(0, 1);
      Assert::IsFalse(parser.nibble_char('c'));
      parser.assert_position(0, 1);
      Assert::IsTrue(parser.nibble_char('a'));
      parser.assert_position(0, 2);
      Assert::IsTrue(parser.nibble_char('t'));
      parser.assert_position(0, 3);
      Assert::IsFalse(parser.nibble_char('t'));
      parser.assert_position(0, 3);

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_NibbleString ) {
      Parser parser("catcher");

      Assert::IsFalse(parser.all_done());

      Assert::IsTrue(parser.nibble_string(""));
      Assert::IsFalse(parser.nibble_string("cap"));
      Assert::IsTrue(parser.nibble_string("cat"));
      Assert::IsTrue(parser.nibble_string(""));
      Assert::IsTrue(parser.nibble_string("c"));
      Assert::IsFalse(parser.nibble_string("herr"));
      Assert::IsTrue(parser.nibble_string("her"));
      Assert::IsFalse(parser.nibble_string("c"));
      Assert::IsTrue(parser.nibble_string(""));

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_NibbleRegex ) {
      Parser parser("  \t  \n  catcher in the rye     ");

      Assert::IsFalse(parser.all_done());

      Assert::IsTrue(parser.nibble_regex("\\s*") == "  \t  \n  ");
      Assert::IsTrue(parser.nibble_regex("") == "");
      Assert::IsTrue(parser.nibble_regex("rye") == "");
      Assert::IsTrue(parser.nibble_regex("cat") == "cat");
      Assert::IsTrue(parser.nibble_regex("") == "");
      Assert::IsTrue(parser.nibble_regex("c") == "");
      Assert::IsTrue(parser.nibble_regex("herr") == "");
      Assert::IsTrue(parser.nibble_regex("[her]*") == "her");
      Assert::IsTrue(parser.nibble_regex("\\sin ") == " in");
      Assert::IsTrue(parser.nibble_regex("(the) ") == "the ");
      Assert::IsTrue(parser.nibble_regex("[r]?ye") == "rye");
      Assert::IsTrue(parser.nibble_regex("[ ]*") == "     ");
      Assert::IsTrue(parser.nibble_regex("") == "");

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_MunchWhitespace ) {
      Parser parser("  \t  \n  cat");

      Assert::IsFalse(parser.all_done());

      parser.munch_whitespace();
      Assert::IsTrue(parser.nibble_string("cat"));

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_ChompChar ) {
      Parser parser("cat");

      Assert::IsFalse(parser.all_done());

      parser.chomp_char('c');
      parser.chomp_char('a');
      parser.chomp_char('t');

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_ChompString ) {
      Parser parser("catcher");

      Assert::IsFalse(parser.all_done());

      parser.chomp_string("");
      parser.chomp_string("cat");
      parser.chomp_string("");
      parser.chomp_string("c");
      parser.chomp_string("her");
      parser.chomp_string("");

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_ChompRegex ) {
      Parser parser("  \t  \n  catcher in the rye     ");

      Assert::IsFalse(parser.all_done());

      parser.chomp_regex("\\s*");
      parser.chomp_regex("");
      parser.chomp_regex("cat");
      parser.chomp_regex("");
      parser.chomp_regex("c");
      parser.chomp_regex("[her]*");
      parser.chomp_regex("\\sin ");
      parser.chomp_regex("(the) ");
      parser.chomp_regex("[r]?ye");
      parser.chomp_regex("[ ]*");

      Assert::IsTrue(parser.all_done());
    }

    TEST_METHOD( TestParser_PickWord ) {
      Parser parser("  \n  \t\t  cat dog \t  \n   man");

      Assert::IsFalse(parser.all_done());

      Assert::AreEqual(parser.pick_word(), std::string("cat"));
      Assert::AreEqual(parser.pick_word(), std::string("dog"));
      Assert::AreEqual(parser.pick_word(), std::string("man"));

      Assert::IsTrue(parser.all_done());
    }
  };
}
