#include <iostream>
#include <random>
#include "Machine.h"
#include "AgentSampleAverage.h"
#include "RandomAgent.h"

int main(){
    using Uni = std::uniform_real_distribution<>;
    using Normal = std::normal_distribution<>;
    using Dis = Normal;

    std::cout<<"hello"<<std::endl;

    // K armed machine
    int k = 5;
    KArmMachine<Dis>  machine(k);

    // Agent1
    AgentSampleAverage<Dis> a(&machine);

    // Agent2
    RandomAgent<Dis> a2(&machine);

    for (int i=0;i<5;i++){
        std::cout<<"Random Agent chooses: "<< a2.PullArm() << std::endl;
    }
    return 0;
}


