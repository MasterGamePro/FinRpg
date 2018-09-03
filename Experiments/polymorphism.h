#pragma once
#include <cstdio>

namespace polymorphism {
  class ACollider;
  class BCollider;

  class ICollider {
    public:
    void collide_with(ICollider* other) {
      printf("ICollider.collide_with(ICollider*)\n");
    }
  };

  class ACollider : public ICollider {
    public:
    void collide_with(ICollider* other) {
      printf("ACollider.collide_with(ICollider*)\n");    
    }

    void collide_with(BCollider* other) {
      printf("ACollider.collide_with(BCollider*)\n");
    }
  };

  class BCollider : public ICollider {
    void collide_with(ICollider* other) {
      printf("BCollider.collide_with(ICollider*)\n");
    }

    void collide_with(ACollider* other) {
      printf("BCollider.collide_with(ACollider*)\n");
    }
  };

  void experiment() {
    ICollider* aCollider = new ACollider();
    ICollider* bCollider = new BCollider();

    aCollider->collide_with(bCollider);
  }
}
