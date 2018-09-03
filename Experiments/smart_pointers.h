#pragma once
#include <cstdio>
#include <memory>

namespace smart_pointers {
  class A {
    public:
    A() { printf("A()\n"); }
    ~A() { printf("~A()\n"); }
  };

  void print_pointer(A* a_ptr) {
    printf("%s\n", a_ptr == nullptr ? "null" : "exists");
  }

  void inner_block(A* a_ptr) {
    std::unique_ptr<A> a(a_ptr);
    print_pointer(a_ptr);
  }

  void experiment() {
    A* a_ptr = new A();
    inner_block(a_ptr);
    print_pointer(a_ptr);
  }
}
