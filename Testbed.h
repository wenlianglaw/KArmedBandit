/* Test and measure different agent's performance. */

#pragma once
#include <functional>
#include <random>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "MachineInterface.h"
#include "AgentInterface.h"

template <typename T> class AgentInterface;
template <typename T = std::normal_distribution<>>
class Testbed {
    private:
        // All agents
        std::unordered_set<AgentInterface<T>*> all_agents;
        // User - Total score Mapping
        std::unordered_map<AgentInterface<T>*, double> user_score;
        // User - Steps Mapping
        std::unordered_map<AgentInterface<T>*, int> user_steps;
        // Test machine, with probability
        MachineInterface *machine;
        // Test time out for each user, in seconds.
        int timeout;
    public:
        Testbed(MachineInterface *m): machine(m){
            Init();
        }

        /***
         * Initialize
         */
        void Init(){
            timeout = 60;
            machine->ResetArms();
        }

        /***
         * Initialize an agent.
         */
        void InitAgent(AgentInterface<T>* agent){
            agent->Init(this);
            user_score[agent] = user_steps[agent] = 0;
        }

        /***
         * Get arm count of the testing k-armed-machine
         */
        inline int GetArmsCount() const{
            return machine->GetArmsCount();
        }

        /***
         * Provide your agent.
         */
        void RegisterYourAgent( AgentInterface<T> *agent){
            if( all_agents.find( agent ) != all_agents.end() )
                throw("Agent with same name exists!");
            
            agent->Init(this);
            all_agents.insert(agent);
        }

        /***
         * Pull kth Arm and get a reward.
         *
         * Args:
         *  agent: From which agent.
         *  k: Pull kth arm.
         *
         * Return: kth arm's reward.
         */
        double PullArm( AgentInterface<T> *agent, int k ){
            double reward = machine->GetReward(k);
            user_steps[agent]++;
            user_score[agent] += reward;
            return reward;
        }

        /***
         * Get Users Stats
         *
         * Args:
         *  username: user name to query.
         * Return:
         *  pair<double, int> --- < Average Reward, total test steps >
         */
        std::pair<double, int> GetUserStats( std::string username ){
            return {1.0, 1};
        }

        /***
         * Run all agents, pulling arms for pull_times times.
         *
         * Args:
         *  pull_times: For each agent, pulling pull_times times arms.
         */
        void RunAllAgents( int pull_times ){
            for ( auto agent : all_agents){
                InitAgent( agent );
                for( int i=0; i<pull_times; i++){
                    agent->PullArm();
                }
            }
        }

        /***
         * After running tests, sort users by their performance and print to screen.
         *  ------------------------------------------------------
         * | Rank |  Agent Name  |  Total Score  |  Average Score |
         *  ------------------------------------------------------
         * |  1   |   ....       |    ......     |      ......    |
         *  ------------------------------------------------------
         */
        void SortAndPrintUserRank(){
            // Sort
            
            // Print
            using namespace std;
            for(auto agent : all_agents )
                cout<<"1"<<user_score[agent]<<" Steps :"<< user_steps[agent]<<"average score:"<< user_score[agent] / user_steps[agent]<<endl;

        }

    private:
        /***
         * Pretty print strings in column.
         */
        void PrettyPrint( ){}
};
