/* Implements a random agent. */
#include "AgentInterface.h"
#include <random>

template <typename T> class RandomAgent : public AgentInterface<T> {
private:
public:
  RandomAgent(std::string &&name)
      : AgentInterface<T>(std::forward<std::string &&>(name)) {}

  int PullArm() override {
    // Do some logic and return selection.  Let's return a random selection.
    int selection = this->gen() % (AgentInterface<T>::testbed->GetArmsCount());

    // Operate testbed and pull arm.
    double reward __attribute__((unused)) =
        AgentInterface<T>::testbed->PullArm(this, selection);

    return selection;
  }
};
