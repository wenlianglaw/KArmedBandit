/* Implements a random agent. */
#include <random>

#include "AgentInterface.h"

template<typename D>
class RandomAgent: public AgentInterface<D>{
    private:
        std::random_device rd;
        std::mt19937 gen;
    public:
        RandomAgent(MachineInterface *m): AgentInterface<D>(m){
            gen = std::mt19937(rd());
        }

        int PullArm() override {
            return gen() % (AgentInterface<D>::machine->GetArmCount());
        }

        void Init() override {};
};


