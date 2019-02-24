/* Implements a random agent. */
#include <random>
#include "AgentInterface.h"

template<typename T>
class RandomAgent: public AgentInterface<T>{
    private:
        std::random_device rd;
        std::mt19937 gen;
    public:
        RandomAgent(std::string &&name): AgentInterface<T>(std::forward<std::string&&>(name)) {
            gen = std::mt19937(rd());
        }

        int PullArm() override {
            // Do some logic and return selection.  Let's return a random selection.
            int selection = gen() % (AgentInterface<T>::testbed->GetArmsCount());

            // Operate testbed and pull arm.
            double reward = AgentInterface<T>::testbed->PullArm( this, selection );

            return selection;
        }
};
