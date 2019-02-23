/* Provid an AngentInterface. */
#pragma once
#include "MachineInterface.h"

template< typename D>
class AgentInterface{
    public:
        MachineInterface<D> *machine;

    public:
        AgentInterface(MachineInterface<D> *m):machine(m){}
        // Pull kth arm.
        virtual double PullArm(int k) = 0;
        // Auto select an arm and pull it.
        virtual double PullArm() = 0;
        // Pull arm t times.
        virtual void RepeatPullArm(int t){ while(t--) PullArm(); }
        // Get historical average reward at step s. 
        virtual double GetAverageReward(int s) const  = 0;
        // Get total reward.
        virtual double GetTotalReward() const = 0;
        // Write step-avg_reward data to file.
        virtual void WriteData(std::string filename) = 0;
        // Init state.
        virtual void Init() = 0;
};
