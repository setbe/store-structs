#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

// sstruct
#include "sstruct.hpp"

// std
#include <iostream>

namespace st = sstruct;
namespace de = sstruct::detail;

TEST_CASE("Validate Version", "[unit]") 
{
  de::Version version(1, 2, 3);
  REQUIRE(version.major == 1);
  REQUIRE(version.minor == 2);
  REQUIRE(version.patch == 3);
}

TEST_CASE("Validate Debug Mode", "[unit]") 
{
  constexpr bool debug_mode = de::isDebugMode();
  #if defined(CATCH_CONFIG_MAIN) || defined(SSTRUCT_DEBUG) || defined(DEBUG) || defined(_DEBUG)
    REQUIRE(debug_mode == true);
  #else
    REQUIRE(debug_mode == false);
  #endif
}

TEST_CASE("Validate Struct Padding", "[unit]") 
{
  { // No padding, case 1, .....
    struct NoPadding {
      uint64_t a; // 8 bytes
      uint32_t b; // 4 bytes
    }; // 12 bytes without padding

    REQUIRE(st::hasPadding<NoPadding>(&NoPadding::a, &NoPadding::b) == false);
    REQUIRE(st::hasPadding<NoPadding>(&NoPadding::b, &NoPadding::a) == false);
  } //  ....., No padding, case 1


  { // Padding, case 1, .....
    struct HasPadding {
      uint64_t a; // 8 bytes
      uint32_t b; // 4 bytes
      uint32_t c; // 4 bytes
    }; // 16 bytes with padding (4 bytes padding)
    REQUIRE(st::hasPadding<HasPadding>(&HasPadding::a, &HasPadding::b, &HasPadding::c) == true);
    REQUIRE(st::hasPadding<HasPadding>(&HasPadding::b, &HasPadding::c, &HasPadding::a) == true);
    REQUIRE(st::hasPadding<HasPadding>(&HasPadding::c, &HasPadding::a, &HasPadding::b) == true);
    REQUIRE(st::hasPadding<HasPadding>(&HasPadding::a, &HasPadding::c, &HasPadding::b) == true);
    REQUIRE(st::hasPadding<HasPadding>(&HasPadding::b, &HasPadding::a, &HasPadding::c) == true);
    REQUIRE(st::hasPadding<HasPadding>(&HasPadding::c, &HasPadding::b, &HasPadding::a) == true);
  } //  ....., Padding, case 1


  { // No padding, case 2, .....
    struct NoPadding2 {
      uint64_t a; // 8 bytes
      uint64_t b; // 8 bytes
      uint32_t c; // 4 bytes
      uint32_t d; // 4 bytes
    }; // 24 bytes without padding
    REQUIRE(st::hasPadding<NoPadding2>(&NoPadding2::a, &NoPadding2::b, &NoPadding2::c, &NoPadding2::d) == false);
    REQUIRE(st::hasPadding<NoPadding2>(&NoPadding2::b, &NoPadding2::a, &NoPadding2::d, &NoPadding2::c) == false);
  } //  ....., No padding, case 2
}

TEST_CASE("Validate Enum", "[unit]") 
{
  REQUIRE(static_cast<uint>(st::ios::in) == 0);
  REQUIRE(static_cast<uint>(st::ios::out) == 1);
  REQUIRE(static_cast<uint>(st::ios::app) == 2);
}