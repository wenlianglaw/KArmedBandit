#include <iostream>
#include <random>
#include "Machine.h"
#include "AgentSampleAverage.h"
#include "RandomAgent.h"
#include "Testbed.h"
#include "GreedyAgent.h"

int main(){
    using Uni = std::uniform_real_distribution<>;
    using Normal = std::normal_distribution<>;
    using Dis = Normal;

    std::cout<<"hello"<<std::endl;

    // K armed machine
    int k = 7;
    KArmMachine<Dis>  machine(k);

    // Agent1:  sample average agent
    AgentSampleAverage<Dis> sample_average_agent( "WL's sample average agent");

    // Agent2:  random agent 
    RandomAgent<Dis> random_agent( "WL's random agent" );

    // Agent3: greedy agent.
    GreedyAgent<Dis> greedy_agent( "Wl's greedy agent" );

    // Testbed
    Testbed<Dis> testbed(&machine);
    
    // Start testing Agents
    testbed.RegisterYourAgent( &random_agent);
    testbed.RegisterYourAgent( &sample_average_agent );
    testbed.RegisterYourAgent( &greedy_agent);

    // Test all agents, each of them pulls X times arms.
    testbed.RunAllAgents( 2000 );

    // Print each agent's score.
    testbed.SortAndPrintUserRank();

    std::cout<<"Thank you!"<<std::endl;
    return 0;
}


