#include <iostream>
#include <random>
#include "Machine.h"
#include "AgentSampleAverage.h"
#include "RandomAgent.h"
#include "Testbed.h"


int main(){
    using Uni = std::uniform_real_distribution<>;
    using Normal = std::normal_distribution<>;
    using Dis = Normal;

    std::cout<<"hello"<<std::endl;

    // K armed machine
    int k = 5;
    KArmMachine<Dis>  machine(k);

    // Agent1:  sample average agent
    AgentSampleAverage<Dis> sample_average_agent( "WL's sample average agent");

    // Agent2:  random agent 
    RandomAgent<Dis> random_agent( "WL's random agent" );

    // Testbed
    Testbed<Dis> testbed(&machine);
    
    // Start testing Agents
    testbed.RegisterYourAgent( &random_agent);
    testbed.RegisterYourAgent( &sample_average_agent );

    // Test all agents
    testbed.RunAllAgents( 1000 );

    // Print each agent's score.
    testbed.SortAndPrintUserRank();

    std::cout<<"Thank you!"<<std::endl;
    return 0;
}


