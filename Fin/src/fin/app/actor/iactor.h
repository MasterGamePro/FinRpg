#pragma once
#include "fin/data/collections/set/hashset.h"
#include "fin/graphics/igraphics.h"
#include "fin/input/iinput.h"
#include "fin/app/iapp.h"
#include "fin/app/components/animation/ianimationcomponent.h"
#include "fin/app/components/audio/iaudiocomponent.h"
#include "fin/app/components/collision/icollisioncomponent.h"
#include "fin/app/components/control/icontrolcomponent.h"
#include "fin/app/components/physics/iphysicscomponent.h"
#include "fin/app/components/render/irendercomponent.h"

/*
 * glMatrixMode( GL_MODELVIEW );
 * glLoadIdentity();
 */

namespace fin::app {
  class IActor {
    public:
    IActor();
    virtual ~IActor() {}

    void add_component(IControlComponent* component) { controlComponents.push_back(component); }
    void add_component(IRenderComponent* component) { renderComponents.push_back(component); }
    void remove_component(IControlComponent* component) { controlComponents.remove(component); }
    void remove_component(IRenderComponent* component) { renderComponents.remove(component); }

    void add_child(IActor* child) {
      children.add(child);
    }

    void tick_control(input::IInput* input) {
      controlComponents.iterate([input](IControlComponent* component, int i) {
        component->tick_control(input);
      });
      on_tick_control(input);
      children.iterate([input](IActor* child, int i) {
        child->tick_control(input);
      });
    }
    void tick_physics() {
      physicsComponents.iterate([](IPhysicsComponent* component, int i) {
        component->tick_physics();
      });
      on_tick_physics();
      children.iterate([](IActor* child, int i) {
        child->tick_physics();
      });
    }
    void tick_collision() {
      collisionComponents.iterate([](ICollisionComponent* component, int i) {
        component->tick_collision();
      });
      on_tick_collision();
      children.iterate([](IActor* child, int i) {
        child->tick_collision();
      });
    }
    void tick_animation() {
      animationComponents.iterate([](IAnimationComponent* component, int i) {
        component->tick_animation();
      });
      on_tick_animation();
      children.iterate([](IActor* child, int i) {
        child->tick_animation();
      });
    }
    void tick_audio() {
      audioComponents.iterate([](IAudioComponent* component, int i) {
        component->tick_audio();
      });
      on_tick_audio();
      children.iterate([](IActor* child, int i) {
        child->tick_audio();
      });
    }
    void tick_render_ortho(graphics::IGraphics* g) {
      graphics::ITransform* t = g->t();

      t->set_target_matrix(graphics::MatrixType::MODELVIEW);
      t->push_matrix();

      on_tick_render_ortho(g);

      children.iterate([g](IActor* child, int i) {
        child->tick_render_ortho(g);
      });

      t->pop_matrix();
    }

    void tick_render_perspective(graphics::IGraphics* g) {
      graphics::ITransform* t = g->t();

      t->set_target_matrix(graphics::MatrixType::MODELVIEW);
      t->push_matrix();

      on_tick_render_perspective(g);

      children.iterate([g](IActor* child, int i) {
        child->tick_render_perspective(g);
      });

      t->pop_matrix();
    }


    protected:
    virtual void on_tick_control(input::IInput* input) {}
    virtual void on_tick_physics() {}
    virtual void on_tick_collision() {}
    virtual void on_tick_animation() {}
    virtual void on_tick_audio() {}
    virtual void on_tick_render_ortho(graphics::IGraphics* graphics) {}
    virtual void on_tick_render_perspective(graphics::IGraphics* graphics) {}

    private:
    data::HashSet<IActor*> children;
    data::StlVector<IControlComponent*> controlComponents;
    data::StlVector<IPhysicsComponent*> physicsComponents;
    data::StlVector<ICollisionComponent*> collisionComponents;
    data::StlVector<IAnimationComponent*> animationComponents;
    data::StlVector<IAudioComponent*> audioComponents;
    data::StlVector<IRenderComponent*> renderComponents;
  };
}
