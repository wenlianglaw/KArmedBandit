/* Provid an AngentInterface. */
#pragma once
#include <fstream>
#include <string>

#include "Testbed.h"

template< typename T>
class AgentInterface{
    protected:
        // All agents should be test on testbed.
        Testbed<T> *testbed;
    private:
        std::string agent_name;
    public:
        AgentInterface( std::string &&name ):agent_name(name){}
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
        }

        /***
         * Write step-avg_reward data to file.
         */
        void WriteData(std::string filename) {
            std::ofstream out(filename, std::ofstream::out | std::ofstream::app);
            // TODO write data
            out.close();
        }
};
