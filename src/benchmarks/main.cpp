#include <benchmark/benchmark.h>
#include <dtz/chrono.hpp>
#include <cstdlib>

#include <fmt/format.h>

static void dtz_format_to_memory_buffer(benchmark::State& state) {
  int value = 33;
  fmt::basic_memory_buffer<char, 32> buffer;
  for (auto _ : state) {
    buffer.clear();
    fmt::format_to(buffer, "{}", value);
    benchmark::DoNotOptimize(value);
  }
}
BENCHMARK(dtz_format_to_memory_buffer);

static void dtz_format_to_back_insert_iterator(benchmark::State& state) {
  int value = 33;
  std::string buffer;
  buffer.reserve(32);
  for (auto _ : state) {
    buffer.clear();
    std::back_insert_iterator it{ buffer };
    fmt::format_to(it, "{}", value);
    benchmark::DoNotOptimize(value);
  }
}
BENCHMARK(dtz_format_to_back_insert_iterator);

int main(int argc, char** argv) {
  dtz::initialize();
  benchmark::Initialize(&argc, argv);
  if (benchmark::ReportUnrecognizedArguments(argc, argv)) {
    return EXIT_FAILURE;
  }
  benchmark::RunSpecifiedBenchmarks();
  return EXIT_SUCCESS;
}
