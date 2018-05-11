#pragma once

// Copied from http://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html.

namespace recom::bin::gb {
  enum PinkCodes {
    NOP, STOP
  };

  enum OrangeCodes {
    ORANGE_CALL, ORANGE_JP, ORANGE_JR, ORANGE_RET, ORANGE_RST, ORANGE_RETI
  };

  enum GreenCodes {
    GREEN_LD, GREEN_POP, GREEN_PUSH
  };

  enum PurpleCodes {
    PURPLE_LD, PURPLE_LDH
  };

  enum SalmonCodes {
    SALMON_ADD, SALMON_DEC, SALMON_INC
  };

  enum YellowCodes {
    YELLOW_ADC, YELLOW_ADD, YELLOW_AND, YELLOW_CP, YELLOW_DAA, YELLOW_DEC,
    YELLOW_INC, YELLOW_OR, YELLOW_SBC, YELLOW_SCF, YELLOW_SUB, YELLOW_XOR
  };

  enum CyanCodes {
    CYAN_BIT, CYAN_RES, CYAN_RL, CYAN_RLC, CYAN_RR, CYAN_RRC, CYAN_SET,
    CYAN_SLA, CYAN_SRA, CYAN_SRL, CYAN_SWAP
  };

  enum HighRegisters {
    HI_A, HI_B, HI_D, HI_H
  };

  enum LowRegisters {
    LO_F, LO_C, LO_E, LO_L
  };

  enum FlagRegisterBits {
    FLAG_Z, FLAG_N, FLAG_H, FLAG_C
  };
}
