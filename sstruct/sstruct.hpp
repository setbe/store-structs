#ifndef SSTRUCT_GUARD_HEADER
#define SSTRUCT_GUARD_HEADER

// std
#include <cstdint>
#include <type_traits>
#include <cstddef>
#include <fstream>
#include <typeinfo>
#include <iostream>

namespace sstruct {

/* Info About Sstruct ..... */
namespace detail {
  constexpr bool isDebugMode() {
    #if defined(CATCH_CONFIG_MAIN) || defined(SSTRUCT_DEBUG) || defined(DEBUG) || defined(_DEBUG)
      return true;
    #endif
    return false;
  }

  struct Version {
    uint major;
    uint minor;
    uint patch;
  }; // struct Version
  constexpr detail::Version version(1, 0, 0);
} // namespace detail
/* ..... Info About Sstruct */


/* Validate Struct Padding ..... */

  template <typename _Struct, typename... _Members_T>
  consteval size_t expectedSize(_Members_T _Struct::*... __members) {
    size_t offset = 0;
    size_t align = 1;

    ( (align = std::alignment_of_v<_Members_T>, 
       offset = (offset + align - 1) / align * align + sizeof(_Members_T)
      ),
    ...);

    // Alignment of the largest member
    align = std::max({std::alignment_of_v<_Members_T>...});
    return (offset + align - 1) / align * align;
  }

  template <typename _Struct, typename... _Members_T>
  inline bool hasPadding(_Members_T _Struct::*... __members) {
    constexpr size_t actual_size = sizeof(_Struct);
    constexpr size_t expected_size = expectedSize(__members...);
    
    if constexpr (detail::isDebugMode() && actual_size != expected_size) {
      std::cerr << "Error: Struct " << typeid(_Struct).name() << " has padding.\n";
      std::cerr << "Expected size: " << expected_size << " bytes, but got: " << actual_size << " bytes. "
      "(see https://en.wikipedia.org/wiki/Data_structure_alignment)\n";
      return true;
    }
    return false;
  }
/* ..... Validate Struct Padding */


enum class ios : uint {
  in,  // read - create
  out, // write - create, rewrite
  app  // append - create
};

} // namespace sstruct
#endif // SSTRUCT_GUARD_HEADER
