#pragma once

#include <cstdint>

namespace recom::bin::gb {
  uint8_t NINTENDO_LOGO_BYTES[] = {
    0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83,
    0x00, 0x0C, 0x00, 0x0D, 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
    0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99, 0xBB, 0xBB, 0x67, 0x63,
    0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
  };

  enum class CgbFlag : uint8_t { };

  enum class NewLicenseeCode : uint16_t {
    NONE = 0x00,
    NINTENDO_R_AND_D1 = 0x01,
    ELECTRONIC_ARTS = 0x13,
    BANDAI = 0x32,
  };

  enum class SgbFlag : uint8_t {
    NO_SGB_FUNCTIONS = 0x00,
    SUPPORTS_SGB_FUNCTIONS = 0x03
  };

  enum class CartridgeType : uint8_t {
    ROM_ONLY = 0x00
  };

  enum class RomSize : uint8_t {};

  enum class RamSize : uint8_t {
    NONE = 0x00,
    KB_2 = 0x01,
    KB_8 = 0x02,
    KB_32 = 0x03,
    KB_128 = 0x04,
    KB_64 = 0x05,
  };

  enum class DestinationCode : uint8_t {
    JAPANESE = 0x00,
    NONJAPANESE = 0x01
  };

  typedef struct RomHeaderStruct {
    /*0100-0103*/
    uint8_t entryPoint[4];
    /*0104-0133*/
    uint8_t nintendoLogo[30];
    /*0134-0143*/
    /*013F-0142*/
    /*0143*/
    uint8_t titleManufacturerCodeAndCgbFlag[16];
    /*0144-0145*/
    uint8_t newLicenseeCode[2];
    /*0146*/
    uint8_t sgbFlag;
    /*0147*/
    uint8_t cartridgeType;
    /*0148*/
    uint8_t romSize;
    /*0149*/
    uint8_t ramSize;
    /*014A*/
    uint8_t destinationCode;
    /*014B*/
    uint8_t oldLicenseeCode;
    /*014C*/
    uint8_t maskRomVersionNumber;
    /*014D*/
    uint8_t headerChecksum;
  } RomHeaderStruct;

  class RomHeader {
    public:
    RomHeader(std::vector<uint8_t> romBytes) : romBytes(romBytes) {}

    // TODO: Convert to an instruction class.
    const uint8_t* getEntryPoint() const { return romBytes.data() + 0x0100; }

    bool isNintendoLogoValid() const {
      for (auto i = 0; i < 48; ++i) {
        if (romBytes[0x0104 + i] != NINTENDO_LOGO_BYTES[i]) { return false; }
      }
      return true;
    }

    RomSize getRomSize() const { return static_cast<RomSize>(romBytes[0x148]); }

    RamSize getRamSize() const { return static_cast<RamSize>(romBytes[0x149]); }

    DestinationCode getDestinationCode() const {
      return static_cast<DestinationCode>(romBytes[0x14A]);
    }

    uint8_t getOldLicenseeCode() const { return romBytes[0x014B]; }

    uint8_t getMaskRomVersionNumber() const { return romBytes[0x014C]; }

    bool isHeaderChecksumValid() const {
      uint8_t x = 0;
      for (auto i = 0x0134; i <= 0x14C; ++i) { x = x - romBytes[i] - 1; }
      return x == romBytes[0x14D];
    }

    bool isGlobalChecksumValid() const {
      uint16_t x = 0;
      for (auto i = 0; i < romBytes.size(); ++i) {
        if (i != 0x14E && i != 0x14F) { x += romBytes[i]; }
      }
      const uint16_t globalChecksum = romBytes[0x014E] << 8 | romBytes[0x14F];
      return x == globalChecksum;
    }

    private:
    std::vector<uint8_t> romBytes;
  };
}
