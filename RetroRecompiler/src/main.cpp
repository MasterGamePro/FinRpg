#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

#include "fin/debug/log.h"
#include "fin/algorithm/string/format.h"

#include "compiled/gb/header.h"
#include "compiled/gb/prettyprintinstruction.h"

std::vector<uint8_t> readAllBytes(char const* filename) {
  // open the file:
  std::ifstream file(filename, std::ios::binary);

  // Stop eating new lines in binary mode!!!
  file.unsetf(std::ios::skipws);

  // get its size:
  std::streampos fileSize;

  file.seekg(0, std::ios::end);
  fileSize = file.tellg();
  file.seekg(0, std::ios::beg);

  // reserve capacity
  std::vector<std::uint8_t> vec;
  vec.reserve(fileSize);

  // read the data:
  vec.insert(vec.begin(),
             std::istream_iterator<uint8_t>(file),
             std::istream_iterator<uint8_t>());

  return vec;
}

int main() {
  const std::string directory = "M:/Games/Emulators/GB & GBA/ROMs/GB/";
  const std::string filename = "Marble Madness (USA, Europe).gb";

  const std::string path = directory + filename;

  fin::debug::Log::print("Reading \"%s\"...", path.c_str());
  std::vector<uint8_t> romBytes = readAllBytes(path.c_str());
  fin::debug::Log::println("OK");

  recom::bin::gb::RomHeader romHeader(romBytes);

  fin::debug::Log::println();

  fin::debug::Log::println("LOGO VALID:            %s",
                           romHeader.isNintendoLogoValid() ? "true" : "false");
  fin::debug::Log::println("RAM SIZE:              %x", romHeader.getRamSize());
  fin::debug::Log::println("DESTINATION CODE:      %x",
                           romHeader.getDestinationCode());
  fin::debug::Log::println("HEADER CHECKSUM VALID: %s",
                           romHeader.isHeaderChecksumValid()
                             ? "true"
                             : "false");
  fin::debug::Log::println("GLOBAL CHECKSUM VALID: %s",
                           romHeader.isGlobalChecksumValid()
                             ? "true"
                             : "false");

  recom::bin::gb::prettyPrintInstructions(romBytes.data() + 0x0100);

  std::cin.get();
}
