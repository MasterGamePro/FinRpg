#pragma once

#include <map>
#include "fin/data/collections/list/vector.h"
#include "../components/icomponent.h"
#include "iactor.h"
#include "fin/graphics/igraphics.h"
#include "fin/app/components/render/irendercomponent.h"

namespace fin::app {
  class ComponentActor : public IActor {
    public:

    ComponentActor() {
      componentListMap[COMPONENT_CONTROL] = new data::Vector<IComponent*>();
      componentListMap[COMPONENT_PHYSICS] = new data::Vector<IComponent*>();
      componentListMap[COMPONENT_COLLISION] = new data::Vector<IComponent*>();
      componentListMap[COMPONENT_ANIMATION] = new data::Vector<IComponent*>();
      componentListMap[COMPONENT_AUDIO] = new data::Vector<IComponent*>();
    }

    void tickControl() override final { tickComponents( COMPONENT_CONTROL ); }
    void tick_physics() override final { tickComponents( COMPONENT_PHYSICS ); }
    void tick_collision() override final { tickComponents( COMPONENT_COLLISION ); }
    void tickAnimation() override final { tickComponents( COMPONENT_ANIMATION ); }
    void tickAudio() override final { tickComponents( COMPONENT_AUDIO ); }
    void tickRender( graphics::IGraphics* g ) override final {
      renderComponents.iterate( [g] ( IRenderComponent* component, int i ) {
        component->render( g );
      } );
    }

    void tickComponents( ComponentType type ) {
      componentListMap[type]->iterate( [] ( IComponent* component, int i ) {
        component->tick();
      } );
    }

    private:
    std::map<ComponentType, data::IList<IComponent*>*> componentListMap;
    data::Vector<IRenderComponent*> renderComponents;
  };
}
