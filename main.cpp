#include <iostream>
#include <random>
#include "Machine.h"
#include "AgentSampleAverage.h"

int main(){
    using Uni = std::uniform_real_distribution<>;
    using Normal = std::normal_distribution<>;
    using Dis = Normal;

    std::cout<<"hello"<<std::endl;

    // K armed machine
    int k = 5;
    KArmMachine<Dis>  machine(k);

    // Agent
    AgentSampleAverage<Dis> a(&machine);
    return 0;
}


