#pragma once

namespace fin::collision {
  class ICollider {
    public:
    void collide_with(ICollider* other) {
      
    }

    /* Whether this collider is active. */
    virtual bool is_active() = 0;

    /* Whether this collider can be pushed by other colliders. */
    virtual bool is_pushable() = 0;

    /* Whether this collider can push other colliders. */
    virtual bool can_push() = 0;

    private:
  };
}