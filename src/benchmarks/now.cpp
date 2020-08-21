#include <benchmark/benchmark.h>
#include <dtz.hpp>

static void dtz_now(benchmark::State& state) {
  for (auto _ : state) {
    const auto str = dtz::now();
    benchmark::DoNotOptimize(str);
  }
}
BENCHMARK(dtz_now);
