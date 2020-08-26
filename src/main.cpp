#include <dtz.hpp>

using namespace dtz::literals;

int main(int argc, char* argv[]) {
  fmt::print("[{}]\n", dtz::now() - dtz::years{ 2021 });
}
