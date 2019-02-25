/* Provid an AngentInterface. */
#pragma once
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>

#include "../Testbed.h"

template <typename T> class Testbed;
template< typename T>
class AgentInterface{
    protected:
        // All agents should be test on testbed.
        Testbed<T> *testbed = nullptr;
        std::random_device rd;
        std::mt19937 gen;
    private:
        std::string agent_name;
        std::vector<double> history_rewards;
    public:
        AgentInterface( std::string &&name ):agent_name(name){
            gen = std::mt19937(rd());
        }
        /***
         * Operate testbed and select an arm to pull based on its strategy, 
         *
         * Return:
         *  The arm to pull.
         */
        virtual int PullArm() = 0;
        
        /***
         * Init state.  Assign a testbed.
         */
        virtual void Init(Testbed<T> *t){
            testbed = t;
            history_rewards.clear();
        }

        virtual std::string GetName(){ return agent_name; }

        /***
         * Log step-avg_reward data to file.
         * The log format contains n lines.  Each line contians a single double vlaue.
         *
         * Args:
         *  filename:  The file name, if not specified, it will use {agent_name} as default.
         */
        void LogDataToFile(std::string filename = "") {
            using namespace std::chrono;
            // Set log file to date if it is empty as default.
            if( filename.empty() ){
                std::time_t now = system_clock::to_time_t(system_clock::now());
                struct tm* time_info = localtime( &now );
                char buffer[80];
                strftime( buffer, 80, "%F_%H%M%S", time_info);
                filename = "./Logs/" + agent_name; // + "_" + std::string(buffer);
                size_t pos = 0;
                while( (pos = filename.find(" ", pos)) != std::string::npos ){
                    filename.replace( pos, 1, "_");
                    pos++;
                }
            }
            std::ofstream out(filename, std::ofstream::out );
            if( not history_rewards.empty() ){
                for( double reward : history_rewards ){
                    out<<reward<<std::endl;
                }
                out.close();
            }else{
            }
        }

    protected:
        inline virtual void LogReward( double reward ){
            history_rewards.push_back(reward);
        }

};
