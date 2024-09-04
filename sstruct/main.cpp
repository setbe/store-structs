#include "dstore.hpp"

#include <iostream>
#include <tuple>

template<typename T>
struct Reflect;

struct MyStruct {
  int x;
  double y;
};

template<>
struct Reflect<MyStruct> {
  using type = std::tuple<
    std::pair<const char*, size_t>,
    std::pair<const char*, size_t>
  >;

  static type getMetadata() {
    return type{
        {"int", sizeof(int)},
        {"double", sizeof(double)}
    };
  }
};

int main(int argc, char *argv[]) {
  auto meta = Reflect<MyStruct>::getMetadata();
  std::cout << "Metadata for MyStruct:\n";
  std::cout << "Field 1 type: " << std::get<0>(meta).first << ", size: " << std::get<0>(meta).second << " bytes\n";
  std::cout << "Field 2 type: " << std::get<1>(meta).first << ", size: " << std::get<1>(meta).second << " bytes\n";

  return 0;
}