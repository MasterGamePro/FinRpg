#pragma once
#include "pressabledefs.h"
#include "fin/debug/log.h"

namespace fin::input {
  typedef struct gamepadButtonUpdate {
    int buttonIndex;
    PressableState pressableState;
    bool operator==(const gamepadButtonUpdate& other) const {
      return buttonIndex == other.buttonIndex &&
        pressableState == other.pressableState;
    }
  } gamepadButtonUpdate;

  typedef struct gamepadAxisUpdate {
    int axisIndex;
    float axisState;
    bool operator==(const gamepadAxisUpdate& other) const {
      return axisIndex == other.axisIndex &&
        axisState == other.axisState;
    }
  } gamepadAxisUpdate;

  class IGamepad {
    public:
    virtual bool is_plugged_in() const {
      return true;
    }

    virtual int get_button_count() const {
      return buttonStateMap.size();
    }
    virtual PressableState get_button_state(const int buttonIndex) const {
      if (buttonStateMap.find(buttonIndex) != buttonStateMap.end()) {
        return buttonStateMap.at(buttonIndex);
      }
      return PressableState::UP;
    }
    virtual bool check_button(const int buttonIndex, const PressableState expectedState) {
      return check_pressable_state(get_button_state(buttonIndex), expectedState);
    }

    virtual int get_axis_count() const { return axisStateMap.size(); }
    virtual float get_axis_state(const int axisIndex) const {
      if (axisStateMap.find(axisIndex) != axisStateMap.end()) {
        return axisStateMap.at(axisIndex);
      }
      return 0;
    }
    virtual PressableState get_axis_button_state(const int axisIndex) const {
      if (axisButtonStateMap.find(axisIndex) != axisButtonStateMap.end()) {
        return axisButtonStateMap.at(axisIndex);
      }
      return PressableState::UP;
    }

    virtual bool check_axis(const int axisIndex, const PressableState expectedState) {
      return check_pressable_state(get_axis_button_state(axisIndex), expectedState);
    }

    void handle_button(const int buttonIndex, const PressableState pressableState) {
      if (!check_pressable_state(pressableState, get_button_state(buttonIndex))) {
        gamepadButtonUpdate update;
        update.buttonIndex = buttonIndex;
        update.pressableState = pressableState;
        beforeButtonUpdates.push_front(update);
      }
    }

    void handle_axis(const int axisIndex, const float axisState) {
      gamepadAxisUpdate axisUpdate;
      axisUpdate.axisIndex = axisIndex;
      axisUpdate.axisState = axisState;
      beforeAxisUpdates.push_back(axisUpdate);
      const auto threshold = .75;
      const auto pressableState = axisState >= threshold ?
        PressableState::PRESSED : PressableState::RELEASED;
      if (!check_pressable_state(pressableState, get_axis_button_state(axisIndex))) {
        gamepadButtonUpdate axisButtonUpdate;
        axisButtonUpdate.buttonIndex = axisIndex;
        axisButtonUpdate.pressableState = pressableState;
        beforeAxisButtonUpdates.push_front(axisButtonUpdate);
      }
    }

    // Copy stored inputs into map.
    void before_tick() {
      while (!beforeButtonUpdates.is_empty()) {
        auto update = beforeButtonUpdates.front();
        beforeButtonUpdates.pop_front();
        buttonStateMap[update.buttonIndex] = update.pressableState;
        if (update.pressableState == PressableState::RELEASED) {
          update.pressableState = PressableState::UP;
          afterButtonUpdates.push_front(update);
        }
        else if (update.pressableState == PressableState::PRESSED) {
          update.pressableState = PressableState::DOWN;
          afterButtonUpdates.push_front(update);
        }
      }
      while (!beforeAxisUpdates.is_empty()) {
        const auto update = beforeAxisUpdates.front();
        beforeAxisUpdates.pop_front();
        axisStateMap[update.axisIndex] = update.axisState;
      }
      while (!beforeAxisButtonUpdates.is_empty()) {
        gamepadButtonUpdate update = beforeAxisButtonUpdates.front();
        beforeAxisButtonUpdates.pop_front();
        axisButtonStateMap[update.buttonIndex] = update.pressableState;
        if (update.pressableState == PressableState::RELEASED) {
          update.pressableState = PressableState::UP;
          afterAxisButtonUpdates.push_front(update);
        }
        else if (update.pressableState == PressableState::PRESSED) {
          update.pressableState = PressableState::DOWN;
          afterAxisButtonUpdates.push_front(update);
        }
      }
    }

    // Convert recently added press/releases into down/ups.
    void after_tick() {
      while (!afterButtonUpdates.is_empty()) {
        const auto update = afterButtonUpdates.front();
        afterButtonUpdates.pop_front();
        buttonStateMap[update.buttonIndex] = update.pressableState;
      }
      while (!afterAxisButtonUpdates.is_empty()) {
        const auto update = afterAxisButtonUpdates.front();
        afterAxisButtonUpdates.pop_front();
        axisButtonStateMap[update.buttonIndex] = update.pressableState;
      }
    }

    virtual void poll() = 0;

    private:
    std::map<int, PressableState> buttonStateMap, axisButtonStateMap;
    std::map<int, float> axisStateMap;
    data::StlVector<gamepadButtonUpdate>
      beforeButtonUpdates,
      afterButtonUpdates,
      beforeAxisButtonUpdates,
      afterAxisButtonUpdates;
    data::StlVector<gamepadAxisUpdate> beforeAxisUpdates;
  };
}
