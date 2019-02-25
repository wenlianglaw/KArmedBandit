#include <iostream>
#include <random>

#include "./Machines/Machine.h"
#include "Testbed.h"
#include "./Agents/Agents.h"


/***
 * Display help info.
 */
void Help(){
    std::cout<<"--plot to plot the statistic after running tests."<<std::endl;
    std::cout<<"--sigma to set normal distribution's sigma.  This parameter only works when mahcine uses Normal distribution"<<std::endl;
}
int main(int argc, char **argv){
    using Uni = std::uniform_real_distribution<>;
    using Normal = std::normal_distribution<>;
    using Dis = Normal;

    Help();
    bool plot_afterwards = false;
    double sigma = 2.5f;

    if( argc > 1 ){
        int i=0;
        while( ++i < argc ){
            if( !strcmp( argv[i], "--plot" ) ) plot_afterwards = true;
            if( !strcmp (argv[i], "--sigma") ) sigma = std::atof( argv[++i] );
        }
    }
    
    std::cout<<"hello"<<std::endl;
    if( std::is_same<Uni, Dis>() )
        std::cout<<"Using uniform distribution"<<std::endl;
    else
        std::cout<<"Using normal distribution with sigma: "<<sigma<<std::endl;

    // K armed machine
    int k = 10;
    std::cout<<"sigma "<<sigma<<std::endl;
    KArmMachine<Dis>  machine(k, sigma );

    // Testbed
    Testbed<Dis> testbed(&machine);

    // Agent1:  sample average agent
    AgentSampleAverage<Dis> sample_average_agent( "WL's sample average agent");
    testbed.RegisterYourAgent( &sample_average_agent );

    // Agent2:  random agent 
    RandomAgent<Dis> random_agent( "WL's random agent" );
    testbed.RegisterYourAgent( &random_agent);

    // Agent3: greedy agent.
    GreedyAgent<Dis> greedy_agent( "WL's greedy agent" );
    testbed.RegisterYourAgent( &greedy_agent);

    // Agent4: greedy with epslion agent.
    GreedyWithEpslionAgent<Dis> greedy_with_epslion_agent( "WL's greedy agent with errors" , 0.05f);
    testbed.RegisterYourAgent( &greedy_with_epslion_agent);

    // Test all agents, each of them pulls X times arms.
    for(int i=0; i<5; i++){
        std::cout<<"Test: "<<i<<std::endl;
        testbed.RunAllAgents( 2000 );

        // Print each agent's score.
        testbed.SortAndPrintUserRank();
    }

    // Log data to log files.
    testbed.LogAgentsData();

    // Plot
    if( plot_afterwards ){
        std::system("python ./plot_stats.py");
    }

    std::cout<<"Thank you!"<<std::endl;
    return 0;
}


