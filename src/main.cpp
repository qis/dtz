#include <dtz.hpp>
#include <cstdio>

int main() {
  fmt::print("{}\n", dtz::now(dtz::current_zone()));
}
