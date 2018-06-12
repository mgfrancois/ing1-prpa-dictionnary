#include <functional>
#include "tools.hpp"
#include "naive_dictionary.hpp"
#include "naive_async_dictionary.hpp"

#include <benchmark/benchmark.h>

constexpr int NQUERIES = 10000;

class BMScenario : public ::benchmark::Fixture
{
public:
  void SetUp(benchmark::State&)
    {
      if (!m_scenario)
      {
        auto wl = load_word_list();
        m_scenario = std::make_unique<Scenario>(wl, NQUERIES);
      }
    }

protected:
  static std::unique_ptr<Scenario> m_scenario;
};

std::unique_ptr<Scenario> BMScenario::m_scenario;



BENCHMARK_DEFINE_F(BMScenario, Naive_NoAsync)(benchmark::State& st)
{
  naive_dictionary dic;
  m_scenario->prepare(dic);

  for (auto _ : st)
    m_scenario->execute(dic);

  st.SetItemsProcessed(st.iterations() * NQUERIES);
}

BENCHMARK_DEFINE_F(BMScenario, Naive_Async)(benchmark::State& st)
{
  naive_async_dictionary dic;
  m_scenario->prepare(dic);

  for (auto _ : st)
    m_scenario->execute(dic);

  st.SetItemsProcessed(st.iterations() * NQUERIES);
}

BENCHMARK_REGISTER_F(BMScenario, Naive_NoAsync)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(BMScenario, Naive_Async)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
