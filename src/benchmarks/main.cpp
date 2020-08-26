#include <benchmark/benchmark.h>
#include <dtz/chrono.hpp>
#include <cstdlib>

int main(int argc, char** argv) {
  dtz::initialize();
  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return EXIT_FAILURE;
  }
  benchmark::RunSpecifiedBenchmarks();
  return EXIT_SUCCESS;
}
