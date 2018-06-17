#pragma once

#include <map>
#include "pressabledefs.h"
#include "ikeyconverter.h"
#include "fin/data/collections/list/stlvector.h"

namespace fin::input {
  class IKeyboard {
    typedef struct keyUpdate {
      Keycode keycode;
      PressableState pressableState;
      bool operator==(const keyUpdate& other) const {
        return keycode == other.keycode &&
          pressableState == other.pressableState;
      }
    } keyUpdate;

    public:
    IKeyboard(IKeyConverter* key_converter) {
      this->key_converter = key_converter;
    }
    virtual ~IKeyboard() {}

    void handle(const int tkeycode, const PressableState pressableState) {
      keyUpdate update;
      update.keycode = key_converter->get_keycode(tkeycode);
      update.pressableState = pressableState;
      beforeKeyUpdates.push_front(update);
    }

    PressableState get_key_state(const Keycode& keycode) const {
      if (pressableStateMap.find(keycode) != pressableStateMap.end()) {
        return pressableStateMap.at(keycode);
      }
      return PressableState::UP;
    }

    bool check_key_state(const Keycode& keycode, const PressableState& expected_state) const {
      const auto actual_state = get_key_state(keycode);
      return check_pressable_state(actual_state, expected_state);
    }

    // Copy stored inputs into map.
    virtual void before_tick() {
      while (!beforeKeyUpdates.is_empty()) {
        keyUpdate update = beforeKeyUpdates.front();
        beforeKeyUpdates.pop_front();

        pressableStateMap[update.keycode] = update.pressableState;

        if (update.pressableState == PressableState::RELEASED) {
          update.pressableState = PressableState::UP;
          afterKeyUpdates.push_front(update);
        }
        else if (update.pressableState == PressableState::PRESSED) {
          update.pressableState = PressableState::DOWN;
          afterKeyUpdates.push_front(update);
        }
      }
    }

    // Convert recently added press/releases into down/ups.
    virtual void after_tick() {
      while (!afterKeyUpdates.is_empty()) {
        const auto update = afterKeyUpdates.front();
        afterKeyUpdates.pop_front();
        pressableStateMap[update.keycode] = update.pressableState;
      }
    }

    private:
    IKeyConverter * key_converter;
    std::map<Keycode, PressableState> pressableStateMap;
    data::StlVector<keyUpdate> beforeKeyUpdates, afterKeyUpdates;
  };
}
