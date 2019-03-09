#include <iostream>
#include <random>
#include <string.h> // strcmp

#include "./Machines/Machine.h"
#include "Testbed.h"
#include "./Agents/Agents.h"


/***
 * Display help info.
 */
void Help(){
    std::cout<<"--help to display help infomation."<<std::endl;
    std::cout<<"--plot to plot the statistic after running tests."<<std::endl;
    std::cout<<"--sigma X to set normal distribution's sigma.  This parameter only works when mahcine uses Normal distribution"<<std::endl;
    std::cout<<"--pulltimes X to set test pulling times."<<std::endl;
    std::cout<<"--tournament_times to set how many tournament will be runned."<<std::endl;
}

int main(int argc, char **argv){
    using Uni __attribute__((unused)) = std::uniform_real_distribution<>;
    using Normal __attribute__((unused)) = std::normal_distribution<>;
    using Dis = Normal;

    Help();
    bool plot_afterwards = false;
    double sigma = 1.0f;
    int pull_times = 1000;
    int tournament_times = 10;
    if( argc > 1 ){
        int i=0;
        while( ++i < argc ){
            if( !strcmp( argv[i], "--plot" ) ) plot_afterwards = true;
            else if( !strcmp (argv[i], "--sigma")  && i + 1 < argc) sigma = std::atof( argv[++i] );
            else if( !strcmp (argv[i], "--pulltimes") && i + 1 <argc) pull_times = std::atoi( argv[++i] );
            else if( !strcmp (argv[i], "--help") ) { Help(); exit(0); }
            else if( !strcmp (argv[i], "--tournament_times") && i + 1 <argc) tournament_times = std::atoi( argv[++i] );
            else { std::cout<<"Incorrect Prarmeter: "<<argv[i]<<std::endl; exit(1); }
        }
    }

    // K armed machine
    int k = 12;
    std::cout<<"sigma "<<sigma<<std::endl;
    KArmMachine<Dis>  machine(k, sigma );

    // Testbed
    Testbed<Dis> testbed(&machine);

    // Agent1:  sample average agent
    AgentSampleAverage<Dis> sample_average_agent( "WL's sample average agent");
    testbed.RegisterAgent( &sample_average_agent );

    // Agent1.5: sample average with epslion
    AgentSampleAverage<Dis> sample_average_agent_with_epslion( "WL's sample average agent with epslion", 0.05f);
    testbed.RegisterAgent( &sample_average_agent_with_epslion );

    // Agent2:  random agent 
    RandomAgent<Dis> random_agent( "WL's random agent" );
    testbed.RegisterAgent( &random_agent);

    // Agent3: greedy agent.
    GreedyAgent<Dis> greedy_agent( "WL's greedy agent" );
    testbed.RegisterAgent( &greedy_agent);

    // Agent4: greedy with epslion agent.
    GreedyAgent<Dis> greedy_with_epslion_agent( "WL's greedy agent with epslion" , 0.05f);
    testbed.RegisterAgent( &greedy_with_epslion_agent);

    // Agent5: sample average with customized step size agent
    AgentSampleAverage<Dis> sample_average_agent_with_step_size( "WL's sample average with step size", 0.00f, 0.8f);
    testbed.RegisterAgent( &sample_average_agent_with_step_size );

    // Agent6: UCB
    UCBAgent<Dis> ucb_agent("My UCB agent", .2f /* c */);
    testbed.RegisterAgent(&ucb_agent);
    
    try{
        testbed.RegisterAgent( &sample_average_agent );
    }catch(std::exception &ex){
        std::cout<<ex.what()<<std::endl;
    }
    // Test all agents, each of them pulls X times arms.
    testbed.RunAllAgents( pull_times );

    // Run a tournament
    testbed.RunTournment(tournament_times, pull_times);

    // Print each agent's score.
    //testbed.SortAndPrintAgentRank();

    // Log data to log files.
    testbed.LogAgentsData();

    // Plot
    if( plot_afterwards ){
        std::system("python ./plot_stats.py");
    }

    std::cout<<"Thank you!"<<std::endl;
    return 0;
}


