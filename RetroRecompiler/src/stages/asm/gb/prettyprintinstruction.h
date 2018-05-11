#pragma once
#include <cstdint>
#include "fin/debug/log.h"
#include <map>

namespace recom::bin::gb {
  class ICommand {
    public:
    virtual std::string toString() = 0;
  };

  class UndefinedCommand : public ICommand {
    public:
    explicit UndefinedCommand(uint8_t opcode) : opcode(opcode) {}

    std::string toString() override {
      return fin::algorithm::string_format("UNDEFINED: %x", opcode);
    }

    private:
    uint8_t opcode;
  };

  class NopCommand : public ICommand {
    public:
    std::string toString() override { return "NOP"; }
  };

  class LoadCommand : public ICommand {
    public:
    std::string toString() override { return "LD"; }
  };

  class JumpCommand : public ICommand {
    public:
    std::string toString() override { return "JP"; }
  };

  class JumpReturnCommand : public ICommand {
    public:
    std::string toString() override { return "JR"; }
  };

  class AddCommand : public ICommand {
    public:
    std::string toString() override { return "ADD"; }
  };

  std::map<uint8_t, ICommand*> instructionSet;
  std::map<uint8_t, ICommand*> prefixCbInstructionSet;

  void initialize_commands() {
    if (instructionSet.size() != 0) { return; }
    instructionSet[0x00] = new NopCommand();
    instructionSet[0x01] = new LoadCommand();

    instructionSet[0x08] = new LoadCommand();
    instructionSet[0x09] = new AddCommand();
    instructionSet[0x0A] = new LoadCommand();

    instructionSet[0x19] = new AddCommand();
    instructionSet[0x1A] = new LoadCommand();

    instructionSet[0x29] = new AddCommand();
    instructionSet[0x2A] = new LoadCommand();

    instructionSet[0x39] = new AddCommand();
    instructionSet[0x3A] = new LoadCommand();

    instructionSet[0x50] = new LoadCommand();

    instructionSet[0x80] = new AddCommand();
    instructionSet[0x81] = new AddCommand();
    instructionSet[0x82] = new AddCommand();
    instructionSet[0x83] = new AddCommand();
    instructionSet[0x84] = new AddCommand();
    instructionSet[0x85] = new AddCommand();
    instructionSet[0x86] = new AddCommand();
    instructionSet[0x87] = new AddCommand();

    instructionSet[0xC2] = new JumpCommand();
    instructionSet[0xC3] = new JumpCommand();

    instructionSet[0xD2] = new JumpCommand();
  }

  ICommand* get_command(const uint8_t* address) {
    initialize_commands();
    ICommand* command = instructionSet[*address];
    if (*address == 0xcb) { command = prefixCbInstructionSet[(*address + 1)]; }
    return command;
  }

  void prettyPrintInstruction(const uint8_t* address) {
    initialize_commands();
    auto command = get_command(address);
    if (command == nullptr) {
      command = new UndefinedCommand(*address);
    }
    fin::debug::Log::println(command->toString());
  }

  void prettyPrintInstructions(const uint8_t* address) {
  }
}
