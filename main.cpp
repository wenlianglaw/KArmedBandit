#include <iostream>
#include <random>
#include <string.h> // strcmp

#include "./Agents/Agents.h"
#include "./Machines/Machine.h"
#include "Testbed.h"

std::random_device rd;
std::mt19937 gen;

/***
 * Display help info.
 */
void Help() {
  std::cout << "--help to display help infomation." << std::endl;
  std::cout << "--plot to plot the statistic after running tests." << std::endl;
  std::cout << "--sigma X to set normal distribution's sigma.  This parameter "
               "only works when mahcine uses Normal distribution"
            << std::endl;
  std::cout << "--pulltimes X to set test pulling times." << std::endl;
  std::cout << "--tournament_times to set how many tournament will be runned."
            << std::endl;
  std::cout << "--k K K arms." << std::endl;
}

int main(int argc, char **argv) {
  using Uni __attribute__((unused)) = std::uniform_real_distribution<>;
  using Normal __attribute__((unused)) = std::normal_distribution<>;
  using Dis = Normal;

  Help();
  bool plot_afterwards = false;
  // The larger this number, the more difficult it is for an algorithm to
  // determine whether an arm is good or bad, which makes it a better test for
  // the algorithm. However, excessive randomness caused by a too large number
  // may backfire
  double sigma = 3.0f;
  int pull_times = 1000;
  int tournament_times = 100;
  // K armed machine
  int k = 15;

  gen = std::mt19937(rd());

  if (argc > 1) {
    int i = 0;
    while (++i < argc) {
      if (!strcmp(argv[i], "--plot"))
        plot_afterwards = true;
      else if (!strcmp(argv[i], "--sigma") && i + 1 < argc)
        sigma = std::atof(argv[++i]);
      else if (!strcmp(argv[i], "--pulltimes") && i + 1 < argc)
        pull_times = std::atoi(argv[++i]);
      else if (!strcmp(argv[i], "--help")) {
        Help();
        exit(0);
      } else if (!strcmp(argv[i], "--tournament_times") && i + 1 < argc)
        tournament_times = std::atoi(argv[++i]);
      else if (!strcmp(argv[i], "--k") && i + 1 < argc)
        k = std::atoi(argv[++i]);
      else {
        std::cout << "Incorrect Prarmeter: " << argv[i] << std::endl;
        exit(1);
      }
    }
  }

  std::cout << "sigma " << sigma << std::endl;

  // Init Machine
  std::function<Dis(void)> dist_init_func;
  if (std::is_same<Dis, Normal>())
    // The larger the difference in the inner number, the better it can define
    // whether an arm is good or bad.
    // If an arm is significantly worse than the others, most algorithms can
    // recognize it and avoid choosing the inferior arm.
    dist_init_func = [&]() { return Dis(Dis(0, 3)(gen), sigma); };
  else
    throw std::runtime_error("Unimplemented Distribution Init function");
  KArmMachine<Dis> machine(k, dist_init_func);

  // Testbed
  Testbed<Dis> testbed(&machine);

  // Agent1:  sample average agent
  AgentSampleAverage<Dis> sample_average_agent("WL's sample average agent");

  // Agent1.5: sample average with epslion
  AgentSampleAverage<Dis> sample_average_agent_with_epslion(
      "WL's sample average agent with epslion", 0.05f);

  // Agent2:  random agent
  RandomAgent<Dis> random_agent("WL's random agent");

  // Agent3: greedy agent.
  GreedyAgent<Dis> greedy_agent("WL's greedy agent");

  // Agent4: greedy with epslion agent.
  GreedyAgent<Dis> greedy_with_epslion_agent("WL's greedy agent with epslion",
                                             0.05f);

  // Agent5: sample average with customized step size agent
  AgentSampleAverage<Dis> sample_average_agent_with_step_size(
      "WL's sample average with step size", 0.00f, 0.8f);

  // Agent6: UCB
  UCBAgent<Dis> ucb_agent("My UCB agent", 1.4f /* c */);

  // Agent7: Gradient Bandit Agent
  GradientBanditAgent<Dis> gradient_bandit_agent("WL's Gradient Bandit Agent",
                                                 0.2f);

  // Register agents
  testbed.RegisterAgent(&gradient_bandit_agent);
  testbed.RegisterAgent(&ucb_agent);
  testbed.RegisterAgent(&sample_average_agent_with_step_size);
  // testbed.RegisterAgent( &greedy_with_epslion_agent);
  // testbed.RegisterAgent( &greedy_agent);
  // testbed.RegisterAgent( &random_agent);
  testbed.RegisterAgent(&sample_average_agent_with_epslion);
  testbed.RegisterAgent(&sample_average_agent);

  // Run a tournament
  if (tournament_times > 0) {
    testbed.RunTournment(tournament_times, pull_times);
    // Print each agent's score.
    testbed.SortAndPrintAgentRank();
  } else {
    // Test all agents, each of them pulls X times arms.
    testbed.RunAllAgents(pull_times);
    // Print each agent's score.
    testbed.SortAndPrintAgentRank();
  }

  // Log data to log files.
  testbed.LogAgentsData();

  // Plot
  if (plot_afterwards) {
    std::system("python3 ./plot_stats.py");
  }

  std::cout << "Thank you!" << std::endl;
  return 0;
}
