/* Test and measure different agent's performance. */

#pragma once
#include <functional>
#include <random>
#include <string>
#include <iostream>
#include <unordered_map>

#include "AgentInterface.h"

template <typename T = std::normal_distribution<>>
class Testbd {
    private:
        // User - User's Agent mapping
        std::unordered_map<std::string, AgentInterface<T>> user_agent;
        // User - User's average score mapping
        std::unordered_map<std::string, double> user_score;
        // Test pull times
        int pull_times;
        // Test machine, with probability
        MachineInterface *machine;
        // Test time out for each user, in seconds.
        int timeout;
    public:
        Testbd(MachineInterface *m): machine(m){
            Init();
        }

        // Initialize
        void Init(){
            timeout = 60;
        }

        // Provide your strategy function.
        void SetYourStrategy( AgentInterface<T> agent, std::string username ){
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
        }

        // After running tests, sort users by their performance and print to screen.
        void SortAndPrintUserRank(){
        }
};
